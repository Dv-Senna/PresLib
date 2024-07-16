#include <iostream>
#include <exception>

#include <glad/gl.h>

#include <pl/preslib.hpp>
#include <pl/config.hpp>

#include <pl/memory/heapAllocator.hpp>
#include <pl/render/vertexLayout.hpp>
#include <pl/render/pipeline.hpp>



int main(int, char *[]) {
	try {
		pl::Instance::CreateInfos instanceCreateInfos {};
		instanceCreateInfos.presentationName = "Example";
		instanceCreateInfos.viewportSize = {16*70, 9*70};
		instanceCreateInfos.blockHeapSize = 1024*1024;
		pl::Instance instance {instanceCreateInfos};


		pl::Slide slide1 {};
		pl::Slide slide2 {};

		instance.registerSlide("slide2", &slide2);
		instance.registerSlide("slide1", &slide1);

		std::vector<pl::Float32> vertices {
			0.0f, 0.5f, 0.f,       1.f, 0.f, 0.f,
			0.5f, -0.5f, 0.f,      0.f, 1.f, 0.f,
			-0.5f, -0.5f, 0.f,     0.f, 0.f, 1.f,
		};

		pl::render::Buffer::CreateInfos bufferCreateInfos {};
		bufferCreateInfos.type = pl::render::BufferType::eVertex;
		bufferCreateInfos.usage = pl::render::BufferUsage::eStatic;
		bufferCreateInfos.size = sizeof(pl::Float32) * vertices.size();
		pl::render::Buffer verticesBuffer {bufferCreateInfos};
		verticesBuffer.write(0, vertices.size() * sizeof(pl::Float32), (const pl::Byte*)vertices.data());

		std::cout << "VERTEX LAYOUT" << std::endl;
		pl::render::VertexLayout::CreateInfos vertexLayoutCreateInfos {};
		vertexLayoutCreateInfos.binding = 0;
		vertexLayoutCreateInfos.components = {
			{0, 3, pl::render::VertexComponentType::eFloat32},
			{1, 3, pl::render::VertexComponentType::eFloat32}
		};
		vertexLayoutCreateInfos.rate = pl::render::VertexRate::eVertex;
		pl::render::VertexLayout vertexLayout {vertexLayoutCreateInfos};


		std::cout << "SHADER1" << std::endl;
		pl::render::Shader::CreateInfos shaderCreateInfos {};
		shaderCreateInfos.entryPoint = "main";
		shaderCreateInfos.stage = pl::render::ShaderStage::eVertex;
		shaderCreateInfos.path = "test.vert";
		pl::render::Shader vertexShader {shaderCreateInfos};

		std::cout << "SHADER2" << std::endl;
		shaderCreateInfos.stage = pl::render::ShaderStage::eFragment;
		shaderCreateInfos.path = "test.frag";
		pl::render::Shader fragmentShader {shaderCreateInfos};

		std::cout << "PIPELINE" << std::endl;
		pl::render::Pipeline::CreateInfos pipelineCreateInfos {};
		pipelineCreateInfos.state.faceCulling = false;
		pipelineCreateInfos.state.shaders = {&vertexShader, &fragmentShader};
		pl::render::Pipeline pipeline {pipelineCreateInfos};


		std::cout << "RENDER" << std::endl;
		pl::Config::setCustomRenderCallback([&] () {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		});

		glBindVertexArray(vertexLayout.getVAO());
		glUseProgram(pipeline.getProgram());
		glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer.getBuffer());
		instance.mainloop();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
		glBindVertexArray(0);
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
