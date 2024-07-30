#include "pl/blocks/image.hpp"

#include "pl/instance.hpp"



namespace pl::blocks {
	Image::Image(const pl::blocks::Image::CreateInfos &createInfos) :
		m_instance {nullptr},
		m_vertexShader {nullptr},
		m_fragmentShader {nullptr},
		m_image {}
	{
		m_image = pl::ResourceManager::load<pl::Image> (createInfos.path);

		m_state.parent = nullptr;
		m_state.position = createInfos.position;
		m_state.rotation = 0.f;
		m_state.zoom = createInfos.scale;
		m_state.renderDescriptor.pipeline = nullptr;
		m_state.renderDescriptor.vertexLayout = nullptr;
	}


	Image::~Image() {
		if (m_instance == nullptr)
			return;

		if (m_state.renderDescriptor.vertexLayout != nullptr)
			m_instance->freeObject(m_state.renderDescriptor.vertexLayout);
		if (m_state.renderDescriptor.pipeline != nullptr)
			m_instance->freeObject(m_state.renderDescriptor.pipeline);
		if (m_fragmentShader != nullptr)
			m_instance->freeObject(m_fragmentShader);
		if (m_vertexShader != nullptr)
			m_instance->freeObject(m_vertexShader);
		if (m_image.isValid())
			pl::ResourceManager::unload(m_image);
	}


	void Image::compile(pl::Instance *instance) {
		m_instance = instance;

		m_image->compile(m_instance);

		pl::render::Shader::CreateInfos shaderCreateInfos {};
		shaderCreateInfos.entryPoint = "main";
		shaderCreateInfos.path = "texture.vert";
		shaderCreateInfos.stage = pl::render::ShaderStage::eVertex;
		m_vertexShader = m_instance->allocateObject<pl::render::Shader> (shaderCreateInfos);

		shaderCreateInfos.path = "texture.frag";
		shaderCreateInfos.stage = pl::render::ShaderStage::eFragment;
		m_fragmentShader = m_instance->allocateObject<pl::render::Shader> (shaderCreateInfos);

		pl::render::Pipeline::CreateInfos pipelineCreateInfos {};
		pipelineCreateInfos.state.blendMode = pl::render::BlendMode::eBlend;
		pipelineCreateInfos.state.faceCulling = false;
		pipelineCreateInfos.state.shaders = {m_vertexShader, m_fragmentShader};
		m_state.renderDescriptor.pipeline = m_instance->allocateObject<pl::render::Pipeline> (pipelineCreateInfos);

		pl::render::VertexLayout::CreateInfos vertexLayoutCreateInfos {};
		vertexLayoutCreateInfos.binding = 0;
		vertexLayoutCreateInfos.components = {
			{.location = 0, .dimension = 2, .type = pl::render::VertexComponentType::eFloat32, .isPosition = true},
			{.location = 1, .dimension = 2, .type = pl::render::VertexComponentType::eFloat32}
		};
		vertexLayoutCreateInfos.rate = pl::render::VertexRate::eVertex;
		m_state.renderDescriptor.vertexLayout = m_instance->allocateObject<pl::render::VertexLayout> (vertexLayoutCreateInfos);


		pl::Vec2f halfNormalizedSize {
			0.5f * m_image->getTexture().getSize().x,
			0.5f * m_image->getTexture().getSize().y
		};

		std::vector<pl::Float> vertices {
			-halfNormalizedSize.x, -halfNormalizedSize.y,    0.f, 0.f,
			halfNormalizedSize.x, -halfNormalizedSize.y,     1.f, 0.f,
			-halfNormalizedSize.x, halfNormalizedSize.y,     0.f, 1.f,

			halfNormalizedSize.x, halfNormalizedSize.y,      1.f, 1.f,
			-halfNormalizedSize.x, halfNormalizedSize.y,     0.f, 1.f,
			halfNormalizedSize.x, -halfNormalizedSize.y,     1.f, 0.f,
		};

		m_state.vertices.resize(sizeof(pl::Float) * vertices.size());
		memcpy(m_state.vertices.data(), vertices.data(), sizeof(pl::Float) * vertices.size());

		m_state.renderDescriptor.textures = {
			{0, &m_image->getTexture()}
		};

		m_state.renderDescriptor.uniforms = {
			{0, m_instance->getViewportUniform()}
		};

		m_state.rotation.x *= halfNormalizedSize.x;
		m_state.rotation.y *= halfNormalizedSize.y;
	}


} // namespace pl::blocks
