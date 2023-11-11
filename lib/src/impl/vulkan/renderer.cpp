#include <iostream>
#include <stdexcept>

#include <vulkan/vulkan.hpp>

#include "impl/vulkan/instance.hpp"
#include "impl/vulkan/renderer.hpp"



namespace pl::impl::vulkan
{
	struct InternalState
	{
		std::shared_ptr<pl::impl::vulkan::Instance> instance;


		bool isComplet()
		{
			return instance->isComplet();
		}

		~InternalState()
		{
			instance.reset();
		}
	};



	pl::impl::vulkan::InternalState *checkInternalStateValidity(std::shared_ptr<void> opaqueState, const std::string &function)
	{
		if (opaqueState == nullptr)
			throw std::runtime_error("PL : Vulkan has no internal state in function " + function);
		pl::impl::vulkan::InternalState *internalState {static_cast<pl::impl::vulkan::InternalState*> (opaqueState.get())};
		if (!internalState->isComplet())
			throw std::runtime_error("PL : Vulkan is not complete in function " + function);
		return internalState;
	}
	
	#define checkInternalStateValidity(opaqueState) checkInternalStateValidity(opaqueState, __func__)







	void Renderer::setup(pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &createInfo)
	{
		impl->internalState = std::make_shared<pl::impl::vulkan::InternalState> ();
		pl::impl::vulkan::InternalState *internalState {static_cast<pl::impl::vulkan::InternalState*> (impl->internalState.get())};

		internalState->instance = std::make_shared<pl::impl::vulkan::Instance> (createInfo);
	}



	void Renderer::cleanup(pl::Renderer::Implementation *impl)
	{
		impl->internalState.reset();
	}



	void Renderer::cleanViewport(pl::Renderer::Implementation */*impl*/, const pl::utils::Color &/*color*/, pl::graphics::CleanFlag /*flag*/)
	{

	}



	void Renderer::updateScreen(pl::Renderer::Implementation */*impl*/)
	{

	}



	pl::utils::Id Renderer::registerObject(
		pl::Renderer::Implementation */*impl*/,
		pl::utils::ObjectType /*type*/,
		const std::any &/*data*/
	)
	{
		return 1;
	}



	pl::utils::ObjectType Renderer::getObjectType(pl::Renderer::Implementation */*impl*/, pl::utils::Id /*objectID*/)
	{
		return pl::utils::ObjectType::framebuffer;
	}



	void Renderer::usePipeline(pl::Renderer::Implementation */*impl*/, pl::utils::Id /*pipeline*/)
	{

	}



	void Renderer::drawVertices(pl::Renderer::Implementation */*impl*/, pl::utils::Id /*vertices*/, bool /*forceNormalRenderMode*/)
	{

	}



	void Renderer::setUniformValues(
		pl::Renderer::Implementation */*impl*/,
		pl::utils::Id /*pipeline*/,
		const std::string &/*uboName*/,
		const std::vector<pl::graphics::UniformFieldValue> &/*values*/
	)
	{

	}


	
	void Renderer::bindTexture(
		pl::Renderer::Implementation */*impl*/,
		pl::utils::Id /*pipeline*/,
		pl::utils::Id /*texture*/,
		int /*bindingPoint*/
	)
	{

	}



	void Renderer::useFramebuffer(pl::Renderer::Implementation */*impl*/, pl::utils::Id /*framebuffer*/)
	{

	}



	pl::utils::Id Renderer::getFramebufferTexture(pl::Renderer::Implementation */*impl*/, pl::utils::Id /*framebuffer*/)
	{
		return 1;
	}



	void Renderer::setRenderMode(pl::Renderer::Implementation */*impl*/, pl::graphics::RenderMode /*renderMode*/)
	{

	}



} // namespace pl::impl::vulkan
