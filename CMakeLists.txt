# Prevent in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds prohibited. Call cmake from the build directory.")
endif()

cmake_minimum_required(VERSION 3.7)

project(emergent-superbuild)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Setup configuration options
option(BUILD_DOCS "Build the API reference docs using Doxygen." OFF)
option(BUILD_EXAMPLES "Build the example programs." ON)
option(BUILD_STATIC "Build a static version of the library." ON)
set(DOXYGEN_BINARY "doxygen" CACHE PATH "Path to the Doxygen binary")
if(BUILD_STATIC)
	set(BUILD_SHARED FALSE)
else()
	set(BUILD_SHARED TRUE)
endif(BUILD_STATIC)

# Setup module directories
set(MODULE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/modules")
set(MODULE_BUILD_DIR "${PROJECT_BINARY_DIR}/modules/build")
set(MODULE_INSTALL_DIR "${CMAKE_BINARY_DIR}/modules/install")

# Build SDL2 module
ExternalProject_Add(module-SDL2
	SOURCE_DIR ${MODULE_SOURCE_DIR}/SDL2
	CMAKE_ARGS
	"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
	"-DCMAKE_INSTALL_PREFIX=${MODULE_INSTALL_DIR}"
	"-DSDL_ATOMIC=OFF"
	"-DSDL_AUDIO=OFF"
	"-DSDL_CPUINFO=ON"
	"-DSDL_DLOPEN=ON"
	"-DSDL_EVENTS=ON"
	"-DSDL_FILE=OFF"
	"-DSDL_FILESYSTEM=OFF"
	"-DSDL_HAPTIC=ON"
	"-DSDL_JOYSTICK=ON"
	"-DSDL_LOADSO=ON"
	"-DSDL_POWER=ON"
	"-DSDL_RENDER=OFF"
	"-DSDL_SHARED=OFF"
	"-DSDL_STATIC=ON"
	"-DSDL_STATIC_PIC=OFF"
	"-DSDL_TEST=OFF"
	"-DSDL_THREADS=OFF"
	"-DSDL_TIMERS=ON"
	"-DSDL_VIDEO=ON"
	"-DVIDEO_VULKAN=OFF"
	BINARY_DIR ${MODULE_BUILD_DIR}/SDL2
	INSTALL_DIR ${MODULE_INSTALL_DIR})

# Build freetype module
ExternalProject_Add(module-freetype
	SOURCE_DIR ${MODULE_SOURCE_DIR}/freetype
	CMAKE_ARGS
		"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
		"-DCMAKE_INSTALL_PREFIX=${MODULE_INSTALL_DIR}"
		"-DBUILD_SHARED_LIBS=OFF"
	BINARY_DIR ${MODULE_BUILD_DIR}/freetype
	INSTALL_DIR ${MODULE_INSTALL_DIR})

# Build emergent module
ExternalProject_Add(module-emergent
	DEPENDS module-freetype module-SDL2
	SOURCE_DIR ${MODULE_SOURCE_DIR}/emergent
	CMAKE_ARGS
	"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
	"-DCMAKE_INSTALL_PREFIX=${MODULE_INSTALL_DIR}"
	"-DCMAKE_PREFIX_PATH=${MODULE_INSTALL_DIR}"
	"-DBUILD_DOCS=${BUILD_DOCS}"
	"-DBUILD_EXAMPLES=${BUILD_EXAMPLES}"
	"-DBUILD_STATIC=${BUILD_STATIC}"
	"-DDOXYGEN_BINARY=${DOXYGEN_BINARY}"
	"-DEMERGENT_SDL=ON"
	BINARY_DIR ${MODULE_BUILD_DIR}/emergent
	BUILD_ALWAYS 1
	INSTALL_DIR ${MODULE_INSTALL_DIR})

# Install modules
file(MAKE_DIRECTORY ${MODULE_INSTALL_DIR}/bin)
file(MAKE_DIRECTORY ${MODULE_INSTALL_DIR}/cmake)
file(MAKE_DIRECTORY ${MODULE_INSTALL_DIR}/include)
file(MAKE_DIRECTORY ${MODULE_INSTALL_DIR}/lib)
file(MAKE_DIRECTORY ${MODULE_INSTALL_DIR}/share)
install(DIRECTORY "${MODULE_INSTALL_DIR}/bin" DESTINATION .)
install(DIRECTORY "${MODULE_INSTALL_DIR}/cmake" DESTINATION .)
install(DIRECTORY "${MODULE_INSTALL_DIR}/include" DESTINATION .)
install(DIRECTORY "${MODULE_INSTALL_DIR}/lib" DESTINATION .)
install(DIRECTORY "${MODULE_INSTALL_DIR}/share" DESTINATION .)

# Add clean target
add_custom_target(clean-build
	COMMAND git clean -fdX
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
