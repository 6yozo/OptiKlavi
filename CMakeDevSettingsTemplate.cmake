# Developer-specific CMake settings template
# Copy this file to 'CMakeDevSettings.cmake' and adjust the paths accordingly.
# 'CMakeDevSettings.cmake' is excluded from version control to allow
# user-specific customization.

# Set the path to the C++ compiler.
# Example: C:/Workspace/Programs/Scoop/apps/llvm/current/bin/clang++.exe
set(CMAKE_CXX_COMPILER "<path-to-clang++-exe>" CACHE PATH "C++ Compiler" FORCE)

# Set the path to the C compiler.
# Example: C:/Workspace/Programs/Scoop/apps/llvm/current/bin/clang.exe
set(CMAKE_C_COMPILER "<path-to-clang-exe>" CACHE PATH "C Compiler" FORCE)

# Set the path to the .NET CLI executable.
# Example: C:/Workspace/Programs/Scoop/apps/dotnet-sdk/current/dotnet.exe
set(DOTNET_CLI_EXECUTABLE "<path-to-dotnet-exe>" CACHE PATH "DotNet CLI" FORCE)
