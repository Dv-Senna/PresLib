workspace "NickelLib"
	configurations {"debug", "release"}



project "test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++20"
	targetdir "test/bin"
	objdir "test/obj"
	targetname "test"
	warnings "Extra"

	files {
		"test/**.cpp",
		"test/**.hpp",
		"test/**.inl"
	}

	includedirs {
		"lib/include",
		"vendors/SDL2/include",
		"vendors/SDL2/include/SDL2",
		"vendors/SDL2_ttf/include",
		"vendors/SDL2_image/include",
		"vendors/SDL2_latex/include",
		"vendors/glew/include",
	}

	libdirs {
		"lib/bin",
		"vendors/SDL2/lib",
		"vendors/SDL2_ttf/lib",
		"vendors/SDL2_image/lib",
		"vendors/SDL2_latex/lib",
		"vendors/glew/lib",
	}

	links {
		"preslib",
		"SDL2_ttf",
		"SDL2_latex",
		"SDL2_image",
		"SDL2",
		"SDL2main",
		"glew32",
		"opengl32",
	}


	filter {"system:Windows", "toolset:gcc"}
		links "mingw32"

	filter "configurations:debug"
		defines {"DEBUG", "PL_DEBUG"}
		symbols "On"

	filter "configurations:release"
		defines {"NDEBUG", "PL_NO_DEBUG", "PL_RELEASE"}
		optimize "On"

	filter "system:Windows"
		defines {"PL_PLATEFORM_WINDOWS"}

	filter "system:Unix"
		defines {"PL_PLATEFORM_UNIX"}

	filter "system:Mac"
		defines {"PL_PLATEFORM_MACOS"}

