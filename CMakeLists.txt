cmake_minimum_required(VERSION 3.15)

project(SeisToolS_C VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_PREFIX bin)
list(APPEND INC ${PROJECT_SOURCE_DIR}/include "../c-basic-library/include")
list(APPEND LIB "../c-basic-library/build/")
message("INC: ${INC}")
include_directories(${INC})

file(GLOB headers include/*.h)
file(GLOB sources src/*.c)

message("headers: ${headers}")
message("sources: ${sources}")

add_library(SeisTools STATIC ${headers} ${sources})
target_include_directories(SeisTools PRIVATE ${INC})

add_executable(Geometry ${headers} ${sources} test/Geometry.c)
target_include_directories(Geometry PRIVATE ${INC})
target_link_directories(Geometry PRIVATE ${LIB})
target_link_libraries(Geometry libCBL.a)
