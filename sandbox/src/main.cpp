#include <iostream>
#include <exception>

#include <pl/preslib.hpp>

#include <pl/memory/heapAllocator.hpp>
#include <pl/render/vertexLayout.hpp>



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


		instance.mainloop();
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
