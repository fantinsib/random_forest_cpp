cmake_minimum_required(VERSION 3.16)

project(RandomForestCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RandomForestCPP
    src/main.cpp
    src/DecisionTree.cpp
    src/RandomForest.cpp
    src/node.cpp
    src/dataset.cpp

    include/myforest/decisiontree.h
    include/myforest/randomforest.h
    include/myforest/node.h
    include/myforest/dataset.h
)

target_include_directories(RandomForestCPP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
