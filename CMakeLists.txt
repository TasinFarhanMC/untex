cmake_minimum_required(VERSION 3.11)
project(UNTEX CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/get_cpm.cmake)
cpmaddpackage("gh:g-truc/glm#1.0.1")
cpmaddpackage("gh:tasinfarhanmc/glext@3.3.3")
cpmaddpackage("gh:tasinfarhanmc/betr@0.2.5")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.c" "${SRC_DIR}/*.cpp")

add_library(untex STATIC "${SRC_FILES}")
target_include_directories(untex PUBLIC ${INCLUDE_DIRS})
target_link_libraries(
  untex
  PUBLIC glm
  PRIVATE glext betr)
set_property(TARGET untex PROPERTY CXX_SCAN_FOR_MODULES OFF)

if(UNTEX_TESTS)
  cpmaddpackage("gh:glfw/glfw#3.4")
  add_executable(true_color "${CMAKE_CURRENT_SOURCE_DIR}/test/true_color.cpp")
  target_link_libraries(true_color PRIVATE glfw untex glext betr)
endif()
