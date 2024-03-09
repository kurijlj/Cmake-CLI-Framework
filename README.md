# Cmake-CLI-Framework

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

## Getting Started:

To start using the framework in this repository, follow these steps:

1. **Clone the Repository:** Clone this repository to your local machine using
the following command:
 ```
 git clone https://github.com/kurijlj/Cmake-CLI-Framework.git
 ```

2. **Navigate to a Project Tree:** Browse through the project tree and add
business logic and CMake build instructions required for your app.

3. **Compile the code:** Build as a regular CMake project:
   1. Create a build directory and `cd` into it.
   2. Create a directory structure and project makefiles using (optionally you
   can specify the generator by invoking with the -G switch):
   ```shell
   $ cmake -DBUILD_SHARED_LIBS:BOOL=[ON|OFF] -B . -S <project_source_tree>
   ```
   3. Build executable using:
   ```shell
   $ cmake --build . --config [Debug|RelWithDebInfo|Release|MinSizeRel]
   ```


## Third-party Library Integration:

- **clipp:** The framework assumes clipp as a header-only library. Steps on how
to link to the library are described in the top-level CMakeLists.txt file.
- **sqlite3:** The framework utilizes CMake's add_library function to integrate
sqlite3. Steps on how to link to the library are described in the top-level
CMakeLists.txt file.
- **libsodium:** The project leverages FindLibsodium.cmake to locate and
integrate libsodium. Steps on how to link to the library are described in the
top-level CMakeLists.txt file.

## License:

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.