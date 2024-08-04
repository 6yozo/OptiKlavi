# Release Process

This guide outlines the steps to prepare a distribution of the product.

## 1. Update Third-Party Libraries

- Review the third-party libraries listed in `native/CMakeLists.txt`.
- Check for updates or newer versions of these libraries.
- Update the library versions where applicable.
- Ensure compatibility with the current application code.
    - Review release notes for each library update to assess impact.
    - Apply necessary code changes to maintain compatibility.

## 2. Upgrade Nuget Packages

Upgrade Nuget packages

## 3. Test the Application

- After updating the libraries, run the full suite of tests.
    - Unit tests
    - Integration tests
    - Manual testing of critical features
- Verify that there are no regressions or issues introduced by the updates.

## 4. Compile the Application

- Compile the application in **Release** mode using the appropriate build commands:

```zsh
cmake --build ./cmake-build-debug --target clean -j 14
cmake --build ./cmake-build-debug --target all -j 14
```