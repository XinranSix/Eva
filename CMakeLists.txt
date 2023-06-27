cmake_minimum_required(VERSION 3.10)

project(GameEngine)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./include)
link_directories(./lib)

add_subdirectory(./src)
#add_subdirectory(./test)
