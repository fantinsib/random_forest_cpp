cmake_minimum_required(VERSION 3.16)
project(RandomForestCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PYBIND11_FINDPYTHON ON)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

add_library(myforest
  src/DecisionTree.cpp
  src/RandomForest.cpp
  src/node.cpp
  src/dataset.cpp
  src/helpers.cpp
)

target_include_directories(myforest PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pybind11_add_module(_treelib
  src/bindings.cpp
)
install(TARGETS _treelib LIBRARY DESTINATION treelib)
set_target_properties(_treelib PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/python/treelib"
)

target_link_libraries(_treelib PRIVATE
  myforest
  Python::Module
)

add_executable(RandomForestCPP
  src/main.cpp
)

target_link_libraries(RandomForestCPP PRIVATE myforest)

