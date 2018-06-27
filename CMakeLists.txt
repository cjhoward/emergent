# Prevent in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds prohibited. Call cmake from another directory.")
endif()

cmake_minimum_required(VERSION 3.7)
add_subdirectory(${PROJECT_SOURCE_DIR}/cmake)

