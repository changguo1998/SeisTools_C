cmake_minimum_required(VERSION 3.0)

project(SeisToolS_C VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_PREFIX ./bin)
set(INC ./include)

file(GLOB_RECURSE INC_BASIC ${INC}/basic/*.c)
add_library(basic STATIC ${INC_BASIC})

file(GLOB_RECURSE INC_MATH ${INC}/math_adapter/*.c)
add_library(math STATIC ${INC_MATH})

file(GLOB_RECURSE INC_SEISMIC ${INC}/seismic/*.c)
add_library(seismic ${INC_SEISMIC})

add_executable(test_datetime.exe test/test_datetime.c)
target_link_libraries(test_datetime.exe basic)

add_executable(test_array.exe test/test_array.c)
target_link_libraries(test_array.exe basic math)
