cmake_minimum_required(VERSION 3.21)
project(OptiKlaviCppComponent)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2
)
FetchContent_MakeAvailable(fmt)

# Add source files explicitly
set(SOURCES
        src/grams.cpp
)

# Define the executable to produce
add_library(OptiKlavi SHARED ${SOURCES})
add_dependencies(OptiKlavi GenerateFlatBuffers)
target_include_directories(OptiKlavi PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/schemas/generated/cpp
)
target_link_libraries(OptiKlavi fmt flatbuffers)

# Define OPTIKLAVI_EXPORT when building the library
target_compile_definitions(OptiKlavi PRIVATE OPTIKLAVI_EXPORT)
