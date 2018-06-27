cmake_minimum_required(VERSION 3.7)
project(emergent-superbuild)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(SUBMODULE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/projects)
set(SUBMODULE_BUILD_DIR ${PROJECT_BINARY_DIR}/projects/build)
set(SUBMODULE_INSTALL_DIR ${PROJECT_BINARY_DIR}/projects/install)
set(SUBMODULE_CONFIG_DIR ${SUBMODULE_INSTALL_DIR}/lib/cmake)

# Build submodule SDL2
ExternalProject_Add(submodule-SDL2
	SOURCE_DIR ${SUBMODULE_SOURCE_DIR}/SDL2
	CMAKE_ARGS
	"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
	"-DCMAKE_INSTALL_PREFIX=${SUBMODULE_INSTALL_DIR}"
	"-DSDL_STATIC=true"
	"-DSDL_SHARED=false"
	BINARY_DIR ${SUBMODULE_BUILD_DIR}/SDL2
	INSTALL_DIR ${SUBMODULE_INSTALL_DIR})


# Build submodule freetype
ExternalProject_Add(submodule-freetype
	SOURCE_DIR ${SUBMODULE_SOURCE_DIR}/freetype
	CMAKE_ARGS
	"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
	"-DCMAKE_INSTALL_PREFIX=${SUBMODULE_INSTALL_DIR}"
	BINARY_DIR ${SUBMODULE_BUILD_DIR}/freetype
	INSTALL_DIR ${SUBMODULE_INSTALL_DIR})

# Build emergent
ExternalProject_Add(submodule-emergent
	DEPENDS submodule-freetype submodule-SDL2
	SOURCE_DIR ${SUBMODULE_SOURCE_DIR}/emergent
	CMAKE_ARGS
	"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
	"-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
	"-DEMERGENT_SOURCE_DIR=${CMAKE_SOURCE_DIR}"
	"-DSDL2_DIR=${SUBMODULE_CONFIG_DIR}/SDL2"
	"-Dfreetype_DIR=${SUBMODULE_CONFIG_DIR}/freetype"
	BINARY_DIR ${SUBMODULE_BUILD_DIR}/emergent
	INSTALL_DIR ${CMAKE_BINARY_DIR})

# Force rebuilds
ExternalProject_Add_Step(submodule-emergent forcebuild
	COMMAND ${CMAKE_COMMAND} -E echo_append ""
	DEPENDEES configure
	DEPENDERS build
	ALWAYS 1)

