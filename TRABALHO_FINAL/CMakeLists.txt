cmake_minimum_required(VERSION 3.31)
project(TRABALHO_FINAL)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ICU REQUIRED icu-uc icu-io)

include_directories(${ICU_INCLUDE_DIRS})
link_directories(${ICU_LIBRARY_DIRS})

add_executable(TRABALHO_FINAL main.cpp)

target_link_libraries(TRABALHO_FINAL ${ICU_LIBRARIES})
