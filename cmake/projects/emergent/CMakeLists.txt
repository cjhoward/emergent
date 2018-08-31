cmake_minimum_required(VERSION 3.7)
project(emergent VERSION "0.0.0")

# Find dependency packages
find_package(freetype REQUIRED CONFIG)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED CONFIG)

# Set compiler options
set(EMERGENT_DEBUG_OPTIONS "")
set(EMERGENT_RELEASE_OPTIONS "")

# Determine dependencies
set(EMERGENT_STATIC_LIBS
	freetype
	${OPENGL_gl_LIBRARY}
	SDL2::SDL2-static
	SDL2::SDL2main
	freetype)
set(EMERGENT_SHARED_LIBS
	freetype
	${OPENGL_gl_LIBRARY}
	SDL2::SDL2
	SDL2::SDL2main)

# Setup configuration variables
set(EMERGENT_VERSION ${PROJECT_VERSION})
set(EMERGENT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(EMERGENT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(EMERGENT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(EMERGENT_DEBUG ON)
else()
	set(EMERGENT_DEBUG OFF)
endif()

# Generate configuration header
set(EMERGENT_CONFIG_HEADER ${PROJECT_BINARY_DIR}/include/emergent/configuration.hpp)
set(EMERGENT_SDL ON)
configure_file(${EMERGENT_SOURCE_DIR}/include/emergent/configuration.hpp.in ${EMERGENT_CONFIG_HEADER})

# Collect source files
file(GLOB_RECURSE EMERGENT_HEADER_FILES
	${EMERGENT_SOURCE_DIR}/include/emergent/*.hpp
	${PROJECT_BINARY_DIR}/include/emergent/configuration.hpp)
file(GLOB_RECURSE EMERGENT_SOURCE_FILES
	${EMERGENT_SOURCE_DIR}/src/emergent/*.cpp
	${EMERGENT_SOURCE_DIR}/src/gl3w/src/gl3w.c
	${EMERGENT_SOURCE_DIR}/src/stb/stb_image.c)

# Build emergent library
if(BUILD_STATIC)
	add_library(emergent STATIC ${EMERGENT_SOURCE_FILES})
	set(EMERGENT_EXTRA_LIBS ${EMERGENT_STATIC_LIBS})
else()
	add_library(emergent SHARED ${EMERGENT_SOURCE_FILES})
	set(EMERGENT_EXTRA_LIBS ${EMERGENT_SHARED_LIBS})
endif(BUILD_STATIC)
set_target_properties(emergent
	PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
		DEBUG_POSTFIX d)
target_include_directories(emergent
	PUBLIC
		$<BUILD_INTERFACE:${EMERGENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${EMERGENT_SOURCE_DIR}/src/glm>
		$<BUILD_INTERFACE:${EMERGENT_SOURCE_DIR}/src/gl3w/include>
		$<BUILD_INTERFACE:${EMERGENT_SOURCE_DIR}/src/stb>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		$<BUILD_INTERFACE:${EMERGENT_SOURCE_DIR}/src>)
target_compile_options(emergent PUBLIC "$<$<CONFIG:DEBUG>:${EMERGENT_DEBUG_OPTIONS}>")
target_compile_options(emergent PUBLIC "$<$<CONFIG:RELEASE>:${EMERGENT_RELEASE_OPTIONS}>")
target_link_libraries(emergent ${EMERGENT_EXTRA_LIBS})

# Install emergent library
install(TARGETS emergent
	EXPORT emergent-targets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

# Install emergent headers
install(
	DIRECTORY ${EMERGENT_SOURCE_DIR}/include/emergent
	DESTINATION include
	FILES_MATCHING PATTERN *.hpp)
install(
	FILES ${EMERGENT_CONFIG_HEADER}
	DESTINATION include/emergent)

# Install emergent CMake config file
install(EXPORT emergent-targets
	FILE emergent-config.cmake
	DESTINATION lib/cmake/emergent)

# Build example programs
if(BUILD_EXAMPLES)
	# Build examples
	add_executable(hello-world-example
		${EMERGENT_SOURCE_DIR}/src/examples/example-application.cpp
		${EMERGENT_SOURCE_DIR}/src/examples/hello-world-example.cpp)
	target_link_libraries(hello-world-example emergent)

	# Install examples
	install(TARGETS hello-world-example RUNTIME DESTINATION bin/emergent)
endif(BUILD_EXAMPLES)

# Generate documentation
if(BUILD_DOCS)
	# Configure Doxygen
	set(EMERGENT_DOXYFILE ${PROJECT_BINARY_DIR}/docs/Doxyfile)
	set(DOXYGEN_INPUT_DIR ${EMERGENT_SOURCE_DIR}/include)
	set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)
	configure_file(${EMERGENT_SOURCE_DIR}/docs/Doxyfile.in ${EMERGENT_DOXYFILE})

	# Build documentation
	add_custom_command(TARGET emergent
		POST_BUILD
		COMMAND ${DOXYGEN_BINARY}
		WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

	# Install documentation
	install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/api-reference
		DESTINATION docs/emergent)
endif(BUILD_DOCS)

