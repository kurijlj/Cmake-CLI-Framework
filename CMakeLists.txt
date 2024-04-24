# ============================================================================
# A CMake build script for the C++ CLI application using the clipp.h library.
# ============================================================================

# Define the minimum required version of CMake
cmake_minimum_required (VERSION 3.14...3.40)

# Define the project name and version
project (
    cli_framework
    VERSION 0.1
    DESCRIPTION "A simple C++ CLI application using the clipp.h library"
    HOMEPAGE_URL ""
    LANGUAGES C CXX
    )

# Set the C++ standard to C++17 and make it required
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set CMake module path
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Set to build with shared libraries by default
option (BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set to build with tests by default
option (BUILD_TESTS "Build with tests" ON)

# Determine whether the libraries are built as shared or static
if (BUILD_SHARED_LIBS)
    set (LIB_TYPE SHARED)
else ()
    set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the clipp.h library
add_library (clipp INTERFACE)
target_sources (clipp INTERFACE "${PROJECT_SOURCE_DIR}/extern/clipp/clipp.hpp")
target_include_directories (
    clipp
    INTERFACE
    "${PROJECT_SOURCE_DIR}/extern/clipp"
    )

# Add the sqlite3 library
add_library (sqlite3 STATIC)  # Use STATIC to avoid the need for the SQLITE_API
                              # macro in the sqlite3.h header
target_sources (
    sqlite3
    PRIVATE
    "${PROJECT_SOURCE_DIR}/extern/sqlite3/sqlite3.c"
    )
target_include_directories (
    sqlite3
    PUBLIC
    "${PROJECT_SOURCE_DIR}/extern/sqlite3"
    )

# Find the Libsodium library
if (MSVC)
    find_package (Libsodium 1.4.2 REQUIRED)
else ()
    find_package (Libsodium 1.0.19 REQUIRED)
endif ()

if (Libsodium_FOUND)
    message (STATUS "Libsodium found (version ${Libsodium_VERSION})")
    message (STATUS "Libsodium_INCLUDE_DIR: ${Libsodium_INCLUDE_DIR}")
    message (STATUS "Libsodium_LIBRARIES: ${Libsodium_LIBRARIES}")
    if (BUILD_SHARED_LIBS)
        message (STATUS "Libsodium link type: SHARED")
    else ()
        message (STATUS "Libsodium link type: STATIC")
        message (
            STATUS
            "I hope you included the '#define SODIUM_STATIC 1' in your code"
            )
    endif ()
else ()
    message (FATAL_ERROR "Libsodium not found")
endif ()

# Fetch GoogleTest framework
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif ()

# Add the source files directory
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

# Add the tests directory
if (BUILD_TESTS)
    add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")
endif ()