#include "pl/blocks/triangle.hpp"

#include "pl/instance.hpp"

#define UNPACK_VEC3(vec) vec.x, vec.y, vec.z


namespace pl::blocks {
	Triangle::Triangle(const pl::blocks::Triangle::CreateInfos &createInfos) :
		m_instance {nullptr}
	{
		m_state.parent = nullptr;
		m_state.position = createInfos.position;
		m_state.rotation = {};
		m_state.zoom = {1.f, 1.f, 1.f};
		m_state.renderDescriptor.pipeline = nullptr;
		m_state.renderDescriptor.vertexLayout = nullptr;

		std::vector<pl::Float> vertices {
			UNPACK_VEC3(createInfos.vertices[0]), UNPACK_VEC3(createInfos.color),
			UNPACK_VEC3(createInfos.vertices[1]), UNPACK_VEC3(createInfos.color),
			UNPACK_VEC3(createInfos.vertices[2]), UNPACK_VEC3(createInfos.color)
		};

		m_state.vertices.assign(vertices.data(), vertices.data() + vertices.size());
	}


	Triangle::~Triangle() {
		if (m_instance == nullptr)
			return;
	}


	void Triangle::compile(pl::Instance &instance) {
		m_instance = &instance;

		pl::render::Shader::CreateInfos shaderCreateInfos {};
		shaderCreateInfos.entryPoint = "main";
		shaderCreateInfos.path = "test.vert";
		shaderCreateInfos.stage = pl::render::ShaderStage::eVertex;
		m_vertexShader = m_instance->getObjectHeap().allocate<pl::render::Shader> (shaderCreateInfos);

		shaderCreateInfos.path = "test.frag";
		shaderCreateInfos.stage = pl::render::ShaderStage::eFragment;
		m_fragmentShader = m_instance->getObjectHeap().allocate<pl::render::Shader> (shaderCreateInfos);

		pl::render::Pipeline::CreateInfos pipelineCreateInfos {};
		pipelineCreateInfos.state.faceCulling = true;
		pipelineCreateInfos.state.shaders = {m_vertexShader, m_fragmentShader};
		m_state.renderDescriptor.pipeline = m_instance->getObjectHeap().allocate<pl::render::Pipeline> (pipelineCreateInfos);
	}


} // namespace pl::blocks
