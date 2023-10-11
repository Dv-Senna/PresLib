#pragma once

#include <memory>
#include <string>

#include "internalApi.inl"
#include "math/vec2.hpp"


namespace pl
{
	class Instance final
	{
		public:
			struct CreateInfo
			{
				std::string presentationTitle {"PresLib"};
				pl::WindowApi windowApi {pl::WindowApi::SDL2};
				pl::GraphicsApi graphicsApi {pl::GraphicsApi::Software};
				pl::math::Vec2i viewportSize {1920, 1080};
			};

			struct Implementation
			{
				std::shared_ptr<void> internalState {nullptr};
				void (*setup) (pl::Instance::Implementation *impl, const pl::Instance::CreateInfo &createInfo) {nullptr};
				void (*cleanup) (pl::Instance::Implementation *impl) {nullptr};
				void (*run) (pl::Instance::Implementation *impl) {nullptr};
			};

			Instance(const pl::Instance::CreateInfo &createInfo);
			~Instance();

			void run();


		private:
			pl::Instance::Implementation m_impl;
	};

} // namespace pl
