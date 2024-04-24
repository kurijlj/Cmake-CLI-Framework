# Cmake-CLI-Framework

![GitHub License](https://img.shields.io/github/license/kurijlj/Cmake-CLI-Framework)
![GitHub Release](https://img.shields.io/github/v/release/kurilj/CMake-CLI-Framework?logo=github)
[![GitHub Super-Linter](https://github.com/kurijlj/Cmake-CLI-Framework/actions/workflows/code-syntax-style-check.yml/badge.svg)](https://github.com/marketplace/actions/super-linter)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/kurijlj/Cmake-CLI-Framework/cmake-multi-platform.yml?branch=main&event=push&style=flat&logo=cmake&label=CMake%20build&labelColor=%23064F8C)
![Static Badge](https://img.shields.io/badge/-v17-%23ffffff?style=flat&logo=cplusplus&labelColor=%2300599C)
![Static Badge](https://img.shields.io/badge/-3.14-%23ffffff?style=flat&logo=cmake&labelColor=%23064F8C)

The Cmake-CLI-Framework is a comprehensive CMake project template designed to
simplify the development process for C++ projects that utilize a command-line
interface (CLI) and integrate with third-party libraries. This framework offers
the following features:

- **Cross-Platform Support:** The framework is designed to work seamlessly
across various operating systems, including Windows and UNIX-like environments.
- **Multiple Generator and Compiler Compatibility:** The project aims to be
compatible with different CMake generators and compilers, allowing for
flexibility in your development environment.
- **Header-only and Precompiled Library Integration:** The framework supports
both header-only libraries, like clipp, and precompiled libraries with include
files, like sqlite3 and libsodium. This provides options for diverse library
dependencies.
- **Simplified CLI Integration:** The framework offers mechanisms to simplify
the integration of CLI functionalities into your C++ project.
- **Integrated GoogleTest Framework:** The project integrates GoogleTest for
unit testing, providing a robust testing framework out of the box.

This project aims to streamline the setup process for C++ projects by providing
a well-organized and extensible template that can be easily customized to suit
your needs. By leveraging CMake's flexibility and cross-platform support, this
framework offers a solid foundation for developing CLI applications with
third-party library integration.

## Table of Contents

1. [Getting Started](#getting-started)
2. [Third-party Library Integration](#third-party-library-integration)
3. [Project Structure](#project-structure)
4. [License](#license)

## Getting Started

To start using the framework in this repository, follow these steps:

1. **Clone the Repository:** Clone this repository to your local machine using
the following command:

    ``` shell
    git clone https://github.com/kurijlj/Cmake-CLI-Framework.git
    ```

2. **Navigate to a Project Tree:** Browse through the project tree and add
business logic and CMake build instructions required for your app.

3. **Compile the code:** Build as a regular CMake project:

   1. Create a build directory and `cd` into it.
   2. Create a directory structure and project makefiles using (optionally you
   can specify the generator by invoking with the -G switch):

       ``` shell
       cmake -DBUILD_SHARED_LIBS:BOOL=[ON|OFF] -B . -S <project_source_tree>
       ```

   3. Build executable using:

       ```shell
       cmake --build . --config [Debug|RelWithDebInfo|Release|MinSizeRel]
       ```

## Third-party Library Integration

- **clipp:** The framework assumes clipp as a header-only library. Steps on how
to link to the library are described in the top-level CMakeLists.txt file.
- **sqlite3:** The framework utilizes CMake's add_library function to integrate
sqlite3. Steps on how to link to the library are described in the top-level
CMakeLists.txt file.
- **libsodium:** The project leverages FindLibsodium.cmake to locate and
integrate libsodium. Steps on how to link to the library are described in the
top-level CMakeLists.txt file.
- **GoogleTest:** The project integrates GoogleTest using the FetchContent
module. The test target is added to the project in the CMakeLists.txt file.

## Project Structure

The project structure is organized as follows:

- **bin:** Contains the executable generated after building the project.
- **build:** Contains the makefiles and object files generated during the build
process.
- **extern:** Contains third-party libraries and dependencies.
- **include:** Contains the header files required for the project.
- **src:** Contains the source files for the project.
- **tests:** Contains the test files for the project.

## License

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.
