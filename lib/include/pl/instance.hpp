#pragma once

#include <memory>
#include <string>

#include "internalApi.inl"
#include "math/vec2.hpp"


namespace pl
{
	struct InstanceCreateInfo
	{
		std::string presentationTitle {"PresLib"};
		pl::WindowApi windowApi {pl::WindowApi::SDL2};
		pl::GraphicsApi graphicsApi {pl::GraphicsApi::Software};
		pl::math::Vec2i viewportSize {1920, 1080};
	};


	struct InstanceImplementation
	{
		std::shared_ptr<void> internalState {nullptr};
		void (*setup) (pl::InstanceImplementation *impl, const pl::InstanceCreateInfo &createInfo) {nullptr};
		void (*cleanup) (pl::InstanceImplementation *impl) {nullptr};
		void (*run) (pl::InstanceImplementation *impl) {nullptr};
	};


	class Instance final
	{
		public:
			Instance(const pl::InstanceCreateInfo &createInfo);
			~Instance();

			void run();


		private:
			pl::InstanceImplementation m_impl;
	};

} // namespace pl
