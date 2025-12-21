cmake_minimum_required(VERSION 3.16)
project(RandomForestCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Force pybind11 to use modern FindPython
set(PYBIND11_FINDPYTHON ON)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

# 2) Fetch pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# 3) C++ core library
add_library(myforest
  src/DecisionTree.cpp
  src/RandomForest.cpp
  src/node.cpp
  src/dataset.cpp
)

target_include_directories(myforest PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 4) Python extension module
pybind11_add_module(treelib
  src/bindings.cpp
)

target_link_libraries(treelib PRIVATE
  myforest
  Python::Module
)

#5) CLI executable
add_executable(RandomForestCPP
  src/main.cpp
)

target_link_libraries(RandomForestCPP PRIVATE myforest)

