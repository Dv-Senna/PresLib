set(CMAKE_PROJECT_MINIMUM_VERSION 3.20)
cmake_minimum_required(VERSION 3.20)

project(preslib
	VERSION 0.6.0
	LANGUAGES CXX
)

set(PROJECT_ACRONYM pl)
string(TOUPPER ${PROJECT_ACRONYM} PROJECT_ACRONYM_UPPERCASE)
set(PROJECT_CPP_DIALECT 23)



find_package(SDL2 CONFIG REQUIRED)
set(WSI_PROVIDER SDL2)
set(WSI_PROVIDER_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
set(WSI_PROVIDER_LIBRARIES ${SDL2_LIBRARIES})
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


if (NOT DEFINED PL_VENDORS_FOLDER)
	set(PL_VENDORS_FOLDER vendors)
endif()

add_subdirectory(${PL_VENDORS_FOLDER}/glad)
add_subdirectory(${PL_VENDORS_FOLDER}/freetype2)
#add_subdirectory(${PL_VENDORS_FOLDER}/utfcpp)
#add_subdirectory(${PL_VENDORS_FOLDER}/stb)


set(DEPS_INCLUDE_DIRS
	${SDL2_INCLUDE_DIRS}
	${PL_VENDORS_FOLDER}/glad/include
	${PL_VENDORS_FOLDER}/freetype2/include
	${PL_VENDORS_FOLDER}/utfcpp/source
	${PL_VENDORS_FOLDER}/stb
	${PL_VENDORS_FOLDER}/SteelEngine-Malge/se-malge/include
)

message("DEPS INCLUDE DIRS : ${DEPS_INCLUDE_DIRS}")

set(DEPS_LIBRARIES ${SDL2_LIBRARIES} glad freetype)


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