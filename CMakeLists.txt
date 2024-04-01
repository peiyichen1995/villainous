cmake_minimum_required(VERSION 3.10)
project(Villainous)

file(GLOB_RECURSE SRCS src/*.cxx)
add_executable(villainous ${SRCS})
set_property(TARGET villainous PROPERTY CXX_STANDARD 17)
target_include_directories(villainous PUBLIC include)