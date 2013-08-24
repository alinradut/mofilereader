set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../lib)

add_executable(moReader ../../src/mo.cpp)

if ( NOT COMPILE_DLL )

add_definitions(-D_CONSOLE)
add_dependencies(moReader moFileReader.static)
target_link_libraries(moReader moFileReader.static)

else ( COMPILE_DLL )

add_definitions(-D_CONSOLE -DMOFILE_IMPORT)
add_dependencies(moReader moFileReader)
target_link_libraries(moReader moFileReader)

endif ()



