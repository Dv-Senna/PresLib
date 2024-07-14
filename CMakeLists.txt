cmake_minimum_required(VERSION 3.20)

project(PresLib
	VERSION 0.6.0
	LANGUAGES CXX C
)

set(PROJECT_ACRONYM pl)
string(TOUPPER ${PROJECT_ACRONYM} PROJECT_ACRONYM_UPPERCASE)
set(PROJECT_CPP_DIALECT 23)
set(PROJECT_C_DIALECT 23)

# external dependencies

find_package(SDL2 CONFIG REQUIRED)
set(WSI_PROVIDER SDL2)
if (WIN32)
	function(CLONE_SDL2_DLL target)
		add_custom_command(
			TARGET ${target} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:SDL2::SDL2>
			$<TARGET_FILE_DIR:${target}>
			VERBATIM)
	endfunction(CLONE_SDL2_DLL)
endif()

find_package(Vulkan REQUIRED)
message(${Vulkan_glslc_FOUND})
message(${Vulkan_GLSLC_EXECUTABLE})

add_subdirectory(vendors/freetype2)
add_subdirectory(vendors/glad)


set(DEPS_INCLUDE_DIRS
	${SDL2_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/vendors/freetype2/include
	${SE_GLAD_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/vendors/stb
	${CMAKE_SOURCE_DIR}/vendors/SteelEngine-Malge/se-malge/include
	${CMAKE_SOURCE_DIR}/vendors/utfcpp/source
)
set(DEPS_LIBRARIES ${SDL2_LIBRARIES} glad freetype)

message("Dependencies include path : " ${DEPS_INCLUDE_DIRS})
message("Dependencies libraries : " ${DEPS_LIBRARIES})


if (WIN32)
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_WINDOWS)
elseif (UNIX)
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_LINUX)
elseif (APPLE)
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_APPLE)
else()
	message(FATAL_ERROR "Platforms other than Windows, Linux and MacOS aren't supported for now")
endif()

add_subdirectory(lib)
add_subdirectory(sandbox)
add_subdirectory(shaders)