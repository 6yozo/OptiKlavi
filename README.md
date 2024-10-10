# OptiKlavi

OptiKlavi is a cross-platform keyboard layout evaluator. The supported
platforms are: Linux / Windows / macOS.

OptiKlavi is a desktop application built using C#, Uno Platform and
C++ and aims to have a native look and feel on different operating
systems.

The combination of C#, Uno Platform, and C++ integrates robust
application logic, scalable UI development, and high-performance
computations.

## Install Development Environment

### Windows

'''
scoop install llvm
scoop install cmake
scoop install dotnet-sdk
scoop install ninja
'''

UNO Platform: Enter your VSCode license key
UNO Platform: Install the dotnet new templates

Create projects like:

'''
dotnet new unoapp -platforms desktop
'''

Create solutions and projects to it like:

'''
dotnet new sln -n OptiKlavi
dotnet sln OptiKlavi.sln add ./OptiKlavi.UI/OptiKlavi.UI/OptiKlavi.UI.csproj
'''

To set up environment see:

https://platform.uno/docs/articles/get-started-vscode.html?tabs=windows%2Cubuntu1804

uno-check --target skiawpf

# Technology Stack Rationale

## Cross-Platform Capability

Unlike other frameworks, such as WPF or Electron, Uno Platform provides
genuine cross-platform support without sacrificing the native user
experience on any platform.

## Performance

C++ excels in backend calculations and offers superior performance
where higher-level languages like Java or Python may not be as
efficient.

## Developer Productivity and Ecosystem

C# and Uno Platform integrates well with Visual Studio and other
.NET tools, providing a robust environment for debugging, testing, and
deploying applications.

## Native Look and Feel

The Uno Platform ensures that our application adheres to the design
principles and user interface guidelines of each platform, providing a
native look and feel. This is an improvement over frameworks like
Avalonia, which may require additional customization to achieve a
similar result.

## Future Maintenance and Scalability

Active communities and continuous updates back this tech stack,
ensuring long-term viability and support.
