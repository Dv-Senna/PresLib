#include "pl/blocks/triangle.hpp"

#include "pl/instance.hpp"

#define UNPACK_VEC2(vec) vec.x, vec.y
#define UNPACK_VEC3(vec) vec.x, vec.y, vec.z


namespace pl::blocks {
	Triangle::Triangle(const pl::blocks::Triangle::CreateInfos &createInfos) :
		m_instance {nullptr}
	{
		m_state.parent = nullptr;
		m_state.position = createInfos.position;
		m_state.rotation = 0.f;
		m_state.zoom = {1.f, 1.f};
		m_state.renderDescriptor.pipeline = nullptr;
		m_state.renderDescriptor.vertexLayout = nullptr;

		std::vector<pl::Float> vertices {
			UNPACK_VEC2(createInfos.vertices[0]), UNPACK_VEC3(createInfos.color),
			UNPACK_VEC2(createInfos.vertices[1]), UNPACK_VEC3(createInfos.color),
			UNPACK_VEC2(createInfos.vertices[2]), UNPACK_VEC3(createInfos.color)
		};

		m_state.vertices.resize(sizeof(pl::Float) * vertices.size());
		memcpy(m_state.vertices.data(), vertices.data(), sizeof(pl::Float) * vertices.size());
	}


	Triangle::~Triangle() {
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
	}


	void Triangle::compile(pl::Instance *instance) {
		m_instance = instance;

		pl::render::Shader::CreateInfos shaderCreateInfos {};
		shaderCreateInfos.entryPoint = "main";
		shaderCreateInfos.path = "test.vert";
		shaderCreateInfos.stage = pl::render::ShaderStage::eVertex;
		m_vertexShader = m_instance->allocateObject<pl::render::Shader> (shaderCreateInfos);

		shaderCreateInfos.path = "test.frag";
		shaderCreateInfos.stage = pl::render::ShaderStage::eFragment;
		m_fragmentShader = m_instance->allocateObject<pl::render::Shader> (shaderCreateInfos);

		pl::render::Pipeline::CreateInfos pipelineCreateInfos {};
		pipelineCreateInfos.state.faceCulling = false;
		pipelineCreateInfos.state.shaders = {m_vertexShader, m_fragmentShader};
		m_state.renderDescriptor.pipeline = m_instance->allocateObject<pl::render::Pipeline> (pipelineCreateInfos);

		pl::render::VertexLayout::CreateInfos vertexLayoutCreateInfos {};
		vertexLayoutCreateInfos.binding = 0;
		vertexLayoutCreateInfos.components = {
			{.location = 0, .dimension = 2, .type = pl::render::VertexComponentType::eFloat32, .isPosition = true},
			{.location = 1, .dimension = 3, .type = pl::render::VertexComponentType::eFloat32}
		};
		vertexLayoutCreateInfos.rate = pl::render::VertexRate::eVertex;
		m_state.renderDescriptor.vertexLayout = m_instance->allocateObject<pl::render::VertexLayout> (vertexLayoutCreateInfos);
	}


} // namespace pl::blocks
