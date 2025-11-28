cmake_minimum_required(VERSION 3.14.0)
# Generator expression skips Debug/Release/... directories for MSVC
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
project(asset_convert)

# Adhere to GNU filesystem layout conventions
include(GNUInstallDirs)
include(../cmake/CPM.cmake)
set (CMAKE_CXX_STANDARD 20)

# MSVC needs a few defines to be GNU compatible
if(MSVC)
    add_compile_definitions(_USE_MATH_DEFINES=1 NOMINMAX=1)
endif()

CPMAddPackage("gh:fmtlib/fmt#10.0.0")
CPMAddPackage(
	NAME freetype
	VERSION 2.13.0
	GITHUB_REPOSITORY freetype/freetype
	GIT_TAG VER-2-13-0
	OPTIONS "FT_DISABLE_HARFBUZZ 1" "FT_DISABLE_BROTLI 1"
)
#TODO: lodepng

# Common
file(GLOB COMMON_src src/common/*.cpp src/common/*.c)
file(GLOB_RECURSE COMMON_hdr src/common/*.h src/common/*.hpp)
add_library(common STATIC ${COMMON_src} ${COMMON_hdr})
if(MINGW)
	message(STATUS "Building STATIC executables")
	target_link_libraries(common PUBLIC -static)
endif()
target_link_libraries(common PUBLIC freetype fmt::fmt)

# App-related
file(GLOB ASSET_CONVERT_src src/asset_convert.cpp)

add_executable(asset_convert ${ASSET_CONVERT_src})

target_link_libraries(asset_convert common)
