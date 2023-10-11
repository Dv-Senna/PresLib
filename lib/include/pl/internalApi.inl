#pragma once



namespace pl
{
	enum class GraphicsApi
	{
		Software,
		OpenGL,
		Vulkan,
		DirectX11,
		DirectX12
	};


	enum class WindowApi
	{
		SDL2,
		SDL3,
		glfw
	};


} // namespace pl
