workspace "NickelLib"
	configurations {"debug", "release"}


project "lib"
	kind "StaticLib"
	language "C++"
	cppdialect "c++20"
	targetdir "lib/bin"
	objdir "lib/obj"
	targetname "preslib"
	warnings "Extra"

	defines {"PL_BUILD_LIB"}

	files {
		"lib/src/**.cpp",
		"lib/include/**.hpp",
		"lib/include/**.inl"
	}

	includedirs {
		"lib/include/pl",
		"vendors/SDL2/include",
		"vendors/SDL2_gfx/include",
		"vendors/SDL2/include/SDL2",
		"vendors/SDL2_ttf/include",
		"vendors/SDL2_image/include",
		"vendors/SDL2_latex/include",
		"vendors/SDL2_gpu/include",
	}

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


project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++20"
	targetdir "sandbox/bin"
	objdir "sandbox/obj"
	targetname "sandbox"
	warnings "Extra"

	files {
		"sandbox/src/**.cpp",
		"sandbox/include/**.hpp",
		"sandbox/include/**.inl"
	}

	includedirs {
		"sandbox/include",
		"lib/include",
		"vendors/SDL2/include",
		"vendors/SDL2_gfx/include",
		"vendors/SDL2/include/SDL2",
		"vendors/SDL2_ttf/include",
		"vendors/SDL2_image/include",
		"vendors/SDL2_latex/include",
		"vendors/SDL2_gpu/include",
	}

	libdirs {
		"lib/bin",
		"vendors/SDL2/lib",
		"vendors/SDL2_gfx/lib",
		"vendors/SDL2_ttf/lib",
		"vendors/SDL2_image/lib",
		"vendors/SDL2_latex/lib",
		"vendors/SDL2_gpu/lib",
	}

	links {
		"preslib",
		"SDL2_gfx",
		"SDL2_ttf",
		"SDL2_latex",
		"SDL2_image",
		"SDL2_gpu",
		"SDL2",
		"SDL2main",
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




