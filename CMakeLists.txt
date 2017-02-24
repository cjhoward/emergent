cmake_minimum_required(VERSION 3.7)
project("Emergent"
	VERSION "0.0.0")

# Set output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -s -DNDEBUG")

# Set C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(Freetype REQUIRED)
message("${FREETYPE_INCLUDE_DIRS}")
message("${FREETYPE_LIBRARY}")
message("${FREETYPE_LIBRARIES}")

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

# Generate C++ configuration header
configure_file(${PROJECT_SOURCE_DIR}/include/emergent/configuration.hpp.in ${PROJECT_SOURCE_DIR}/include/emergent/configuration.hpp)

# Collect source files
set(emergent_SOURCES
	src/emergent/entity/component-manager.cpp
	src/emergent/entity/component-observer.cpp
	src/emergent/entity/entity-id-pool.cpp
	src/emergent/entity/entity-manager.cpp
	src/emergent/geometry/aabb.cpp
	src/emergent/geometry/convex-hull.cpp
	src/emergent/geometry/plane.cpp
	src/emergent/geometry/ray.cpp
	src/emergent/geometry/sphere.cpp
	src/emergent/geometry/view-frustum.cpp
	src/emergent/geometry/winged-edge.cpp
	src/emergent/graphics/ambient-light.cpp
	src/emergent/graphics/billboard.cpp
	src/emergent/graphics/bind-pose.cpp
	src/emergent/graphics/bone.cpp
	src/emergent/graphics/camera.cpp
	src/emergent/graphics/light.cpp
	src/emergent/graphics/material.cpp
	src/emergent/graphics/model.cpp
	src/emergent/graphics/pose.cpp
	src/emergent/graphics/renderer.cpp
	src/emergent/graphics/scene-layer.cpp
	src/emergent/graphics/scene-object.cpp
	src/emergent/graphics/scene.cpp
	src/emergent/graphics/shader.cpp
	src/emergent/graphics/shader-loader.cpp
	src/emergent/graphics/shader-parameter.cpp
	src/emergent/graphics/shader-parameter-set.cpp
	src/emergent/graphics/skeleton.cpp
	src/emergent/graphics/texture.cpp
	src/emergent/graphics/texture-loader.cpp
	src/emergent/math/math.cpp
	src/emergent/math/transform.cpp
	src/emergent/utility/timer.cpp
	src/emergent/font/font.cpp
	src/emergent/font/texture-atlas.cpp
	src/emergent/font/font-loader.cpp
	lib/gl3w/src/gl3w.c
	lib/stb/stb_image.c)

# Collect header files
set(emergent_HEADERS
	include/emergent/configuration.hpp
	include/emergent/behavior/action-node.hpp
	include/emergent/behavior/composite-node.hpp
	include/emergent/behavior/conditional-node.hpp
	include/emergent/behavior/counter-node.hpp
	include/emergent/behavior/decorator-node.hpp
	include/emergent/behavior/exit-status.hpp
	include/emergent/behavior/inverter-node.hpp
	include/emergent/behavior/loop-node.hpp
	include/emergent/behavior/node.hpp
	include/emergent/behavior/parallel-node.hpp
	include/emergent/behavior/selector-node.hpp
	include/emergent/behavior/sequence-node.hpp
	include/emergent/behavior/timer-node.hpp
	include/emergent/emergent.hpp
	include/emergent/entity/component-manager.hpp
	include/emergent/entity/component-observer.hpp
	include/emergent/entity/component.hpp
	include/emergent/entity/entity-context.hpp
	include/emergent/entity/entity-id-pool.hpp
	include/emergent/entity/entity-id.hpp
	include/emergent/entity/entity-manager.hpp
	include/emergent/geometry/aabb.hpp
	include/emergent/geometry/bounding-volume.hpp
	include/emergent/geometry/convex-hull.hpp
	include/emergent/geometry/plane.hpp
	include/emergent/geometry/ray.hpp
	include/emergent/geometry/rect.hpp
	include/emergent/geometry/sphere.hpp
	include/emergent/geometry/view-frustum.hpp
	include/emergent/geometry/winged-edge.hpp
	include/emergent/graphics/ambient-light.hpp
	include/emergent/graphics/billboard.hpp
	include/emergent/graphics/bind-pose.hpp
	include/emergent/graphics/bone.hpp
	include/emergent/graphics/camera.hpp
	include/emergent/graphics/gl3w.hpp
	include/emergent/graphics/light.hpp
	include/emergent/graphics/material.hpp
	include/emergent/graphics/model.hpp
	include/emergent/graphics/pose.hpp
	include/emergent/graphics/renderer.hpp
	include/emergent/graphics/scene-layer.hpp
	include/emergent/graphics/scene-object.hpp
	include/emergent/graphics/scene.hpp
	include/emergent/graphics/shader.hpp
	include/emergent/graphics/shader-loader.hpp
	include/emergent/graphics/shader-parameter.hpp
	include/emergent/graphics/shader-parameter-set.hpp
	include/emergent/graphics/skeleton.hpp
	include/emergent/graphics/stb-image.hpp
	include/emergent/graphics/texture.hpp
	include/emergent/graphics/texture-loader.hpp
	include/emergent/graphics/vertex-format.hpp
	include/emergent/math/glm.hpp
	include/emergent/math/hash.hpp
	include/emergent/math/math.hpp
	include/emergent/math/transform.hpp
	include/emergent/math/types.hpp
	include/emergent/utility/timer.hpp
	include/emergent/font/font.hpp
	include/emergent/font/font-loader.hpp
	include/emergent/font/font-metrics.hpp
	include/emergent/font/glyph.hpp
	include/emergent/font/glyph-metrics.hpp
	include/emergent/font/kerning-table.hpp
	include/emergent/font/texture-atlas.hpp)

# Set linked libraries
set(emergent_LIBRARIES
	m	
	#dl
	stdc++
	${FREETYPE_LIBRARIES}
)

# Build and install library
add_library(emergent ${emergent_SOURCES} ${emergent_HEADERS})

# Include directories
include_directories("${PROJECT_SOURCE_DIR}/include")
target_include_directories(emergent PUBLIC
	${PROJECT_SOURCE_DIR}/lib/gl3w/include
	${PROJECT_SOURCE_DIR}/lib/glm
	${PROJECT_SOURCE_DIR}/lib/stb
	${FREETYPE_INCLUDE_DIRS})
target_link_libraries(emergent ${emergent_LIBRARIES})
install(TARGETS emergent DESTINATION ${CMAKE_BINARY_DIR})

# Install public headers
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/emergent
	DESTINATION include
	FILES_MATCHING PATTERN *.hpp)

# Add Doxygen target_include_directories
add_custom_target(emergent-docs
	COMMAND doxygen
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs/api-reference
)