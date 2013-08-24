#-------------------------------------------------------
# moFileReader Main Build Script
#
# Defined Variables:
#   - COMPILE_DLL 
#     - ON  : Compiles the code as a shared Library
#     - OFF : Compiles the code as a static Library
#   - BUILD_DEBUG
#     - ON  : Compiles Debug-Information into the output
#     - OFF : Optimizes the compilation with O2.
#
# Run cmake with -DVARNAME=ON/OFF to benefit from those
# possible settings.
#-------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
project(moFileReader)

# Set Output Directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)


# The main include directory
include_directories(BEFORE ../include)

# executable build directory
add_subdirectory(bin)

# Let the user choose between static lib and dll
# To use it, call cmake -DCOMPILE_DLL=ON
option(COMPILE_DLL "Set this to ON if you want to compile the library as an DLL. When this is OFF, a static library is created (default)." OFF)

# Dependency
link_directories(../lib)

if ( NOT COMPILE_DLL )

    # Static build
    add_library(moFileReader.static STATIC ../src/moFileReader.cpp ../src/mo.cpp)

else ( COMPILE_DLL )

    # DLL
    add_definitions(-D_USRDLL -DMOFILE_EXPORTS)
    add_library(moFileReader SHARED ../src/moFileReader.cpp ../src/mo.cpp)

endif ()






