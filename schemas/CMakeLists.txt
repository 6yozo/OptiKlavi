cmake_minimum_required(VERSION 3.21)
project(OptiKlaviSchemas)

include(FetchContent)
FetchContent_Declare(
        flatbuffers
        GIT_REPOSITORY https://github.com/google/flatbuffers.git
        GIT_TAG v24.3.25  # Replace with the desired version
)
FetchContent_MakeAvailable(flatbuffers)

FetchContent_GetProperties(flatbuffers)
if(NOT flatbuffers_POPULATED)
    FetchContent_Populate(flatbuffers)
    add_subdirectory(${flatbuffers_SOURCE_DIR} ${flatbuffers_BINARY_DIR})
endif()

set(FLATC_EXECUTABLE "${flatbuffers_BINARY_DIR}/flatc")

if(NOT FLATC_EXECUTABLE)
    message(FATAL_ERROR "flatc (FlatBuffers compiler) not found. Install FlatBuffers or ensure flatc is in the PATH.")
endif()

# Directory where schemas are stored
set(SCHEMA_DIR "${CMAKE_SOURCE_DIR}/schemas")

# Output directories for generated code
set(FLATBUFFERS_CPP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/schemas/generated/cpp")
set(FLATBUFFERS_CSHARP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/schemas/generated/cs")

# Ensure the output directories exist
file(MAKE_DIRECTORY ${FLATBUFFERS_CPP_OUTPUT_DIR})
file(MAKE_DIRECTORY ${FLATBUFFERS_CSHARP_OUTPUT_DIR})

# Find all .fbs files in the schema directory
file(GLOB FLATBUFFER_SCHEMAS "${SCHEMA_DIR}/*.fbs")

# Generate C++ and C# code for each schema
foreach(SCHEMA_FILE ${FLATBUFFER_SCHEMAS})
    # Extract the schema filename without extension
    get_filename_component(SCHEMA_NAME ${SCHEMA_FILE} NAME_WE)

    # Define the exact C++ output file
    set(FLATBUFFER_CPP_OUTPUT_FILE "${FLATBUFFERS_CPP_OUTPUT_DIR}/${SCHEMA_NAME}_generated.h")

    # Generate C++ code
    add_custom_command(
            OUTPUT ${FLATBUFFER_CPP_OUTPUT_FILE}
            COMMAND ${FLATC_EXECUTABLE}
            ARGS --cpp -o ${FLATBUFFERS_CPP_OUTPUT_DIR} ${SCHEMA_FILE}
            DEPENDS ${SCHEMA_FILE} ${flatbuffers_BINARY_DIR}/flatc
            COMMENT "Generating C++ code from ${SCHEMA_FILE}"
            VERBATIM
    )

    # Define the exact C# output file
    set(FLATBUFFER_CSHARP_OUTPUT_FILE "${FLATBUFFERS_CSHARP_OUTPUT_DIR}/${SCHEMA_NAME}_generated.cs")

    # Generate C# code
    add_custom_command(
            OUTPUT ${FLATBUFFER_CSHARP_OUTPUT_FILE}
            COMMAND ${FLATC_EXECUTABLE}
            ARGS --csharp -o ${FLATBUFFERS_CSHARP_OUTPUT_DIR} ${SCHEMA_FILE}
            DEPENDS ${SCHEMA_FILE} ${flatbuffers_BINARY_DIR}/flatc
            COMMENT "Generating C# code from ${SCHEMA_FILE}"
            VERBATIM
    )

    # Add the generated files to a list for dependencies
    list(APPEND GENERATED_FILES ${FLATBUFFER_CPP_OUTPUT_FILE} ${FLATBUFFER_CSHARP_OUTPUT_FILE})

endforeach()

# Create a target to ensure code generation happens before the build
add_custom_target(GenerateFlatBuffers ALL DEPENDS ${GENERATED_FILES})