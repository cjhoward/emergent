cmake_minimum_required(VERSION 3.7)
project(emergent VERSION "0.0.0")

# Set compiler flags
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "/W3 /MP /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /Ox")
endif()

# Set linker flags
if(MSVC)
	#set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:MSVCRT")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
endif()

# Set emergent library options
set(EMERGENT_DEBUG_OPTIONS "")
set(EMERGENT_RELEASE_OPTIONS "")

# Find dependency packages
find_package(freetype REQUIRED CONFIG)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED COMPONENTS SDL2::SDL2-static SDL2::SDL2main CONFIG)

# Determine dependencies
set(EMERGENT_STATIC_LIBS
	freetype
	SDL2::SDL2-static
	SDL2::SDL2main)
set(EMERGENT_SHARED_LIBS
	${OPENGL_gl_LIBRARY})

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
configure_file(${PROJECT_SOURCE_DIR}/include/emergent/configuration.hpp.in ${EMERGENT_CONFIG_HEADER})

# Collect source files
file(GLOB_RECURSE EMERGENT_HEADER_FILES
	${PROJECT_SOURCE_DIR}/include/emergent/*.hpp
	${PROJECT_BINARY_DIR}/include/emergent/configuration.hpp)
file(GLOB_RECURSE EMERGENT_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/emergent/*.cpp
	${PROJECT_SOURCE_DIR}/src/gl3w/src/gl3w.c
	${PROJECT_SOURCE_DIR}/src/stb/stb_image.c)

# Add emergent library
if(BUILD_STATIC)
	add_library(emergent STATIC ${EMERGENT_SOURCE_FILES})
else()
	add_library(emergent SHARED ${EMERGENT_SOURCE_FILES})
endif(BUILD_STATIC)

# Set emergent library version
set_target_properties(emergent
	PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
		DEBUG_POSTFIX d)

# Set emergent library include directories
target_include_directories(emergent
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/glm>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/gl3w/include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/stb>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

# Set emergent library config options
target_compile_options(emergent PUBLIC "$<$<CONFIG:DEBUG>:${EMERGENT_DEBUG_OPTIONS}>")
target_compile_options(emergent PUBLIC "$<$<CONFIG:RELEASE>:${EMERGENT_RELEASE_OPTIONS}>")

# Link emergent library with shared libs
target_link_libraries(emergent
	PUBLIC ${EMERGENT_SHARED_LIBS}
	PRIVATE ${EMERGENT_STATIC_LIBS})

# Install emergent library
install(TARGETS emergent
	EXPORT emergent-targets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

# Install emergent headers
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/emergent
	DESTINATION include
	FILES_MATCHING PATTERN *.hpp)
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/src/glm/glm
	DESTINATION include)
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/src/gl3w/include/GL
	DESTINATION include)
install(
	FILES ${EMERGENT_CONFIG_HEADER}
	DESTINATION include/emergent)

# Install emergent CMake config file
install(EXPORT emergent-targets
	FILE emergent-targets.cmake
	DESTINATION lib/cmake/emergent)

# Build example programs
if(BUILD_EXAMPLES)

	# Set example executable name
	set(EXAMPLE_EXECUTABLE "hello-world-example")
	
	# Add example executable source files
	set(EXAMPLE_SOURCE_FILES
		${PROJECT_SOURCE_DIR}/src/examples/example-application.cpp
		${PROJECT_SOURCE_DIR}/src/examples/${EXAMPLE_EXECUTABLE}.cpp)
	
	# Make executable DPI-aware on Windows
	if(WIN32)
		set(EXAMPLE_SOURCE_FILES ${EXAMPLE_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/src/examples/dpi-aware.manifest)
	endif(WIN32)
	
	# Add executable
	add_executable(${EXAMPLE_EXECUTABLE} ${EXAMPLE_SOURCE_FILES})
	
	# Set link flags to show console window on debug builds and hide it on release builds
	if(MSVC)
		set_target_properties(${EXAMPLE_EXECUTABLE} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
		set_target_properties(${EXAMPLE_EXECUTABLE} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"")
	endif(MSVC)
	
	# Link executable
	target_link_libraries(${EXAMPLE_EXECUTABLE} emergent)

	# Install executable
	install(TARGETS ${EXAMPLE_EXECUTABLE} RUNTIME DESTINATION bin/emergent)
	
endif(BUILD_EXAMPLES)

# Generate documentation
if(BUILD_DOCS)
	# Configure Doxygen
	set(EMERGENT_DOXYFILE ${PROJECT_BINARY_DIR}/docs/Doxyfile)
	set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/include)
	set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)
	configure_file(${PROJECT_SOURCE_DIR}/docs/Doxyfile.in ${EMERGENT_DOXYFILE})

	# Build documentation
	add_custom_command(TARGET emergent
		POST_BUILD
		COMMAND ${DOXYGEN_BINARY}
		WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

	# Install documentation
	install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/api-reference
		DESTINATION docs/emergent)
endif(BUILD_DOCS)


include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/emergent-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/emergent-config.cmake
    INSTALL_DESTINATION lib/cmake/emergent
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/emergent-config.cmake
    DESTINATION lib/cmake/emergent
)
