cmake_minimum_required(VERSION 3.21)

# Include development-specific settings if available
# This file should set paths to compilers and other tools required for building
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CMakeDevSettings.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeDevSettings.cmake")
else()
    message(STATUS "CMakeDevSettings.cmake not found. Using default settings.")
endif()

project(OptiKlavi)

add_subdirectory(schemas)
add_subdirectory(native)

# Custom target for building the managed C# projects
add_custom_target(BuildDotNet ALL
    COMMAND "${DOTNET_CLI_EXECUTABLE}" build #"${CMAKE_SOURCE_DIR}/managed/OptiKlavi.sln"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/managed"
    DEPENDS GenerateFlatBuffers OptiKlavi
    COMMENT "Building .NET projects..."
)

# If you have tests, add another custom target for running them
add_custom_target(RunDotNetTests ALL
    COMMAND "${DOTNET_CLI_EXECUTABLE}" test #"${CMAKE_SOURCE_DIR}/managed/OptiKlavi.sln"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/managed"
    DEPENDS BuildDotNet
    COMMENT "Running .NET tests..."
)