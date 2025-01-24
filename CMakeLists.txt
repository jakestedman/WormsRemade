cmake_minimum_required (VERSION 3.27.4)

add_compile_definitions(LOG_ENABLED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(WormsRemade)

#add_subdirectory(lib)
add_subdirectory(src)

#target_link_libraries(${PROJECT_NAME} <ANOTHER LIB> <ANOTHER LIB>)

# To build from command line
# Navigate to build folder and run command
# cmake -S ../src/ -B .
# 
# Source dir    = -S
# Build dir     = -Bcd