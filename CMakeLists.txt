cmake_minimum_required(VERSION 3.10)
project(Villainous)

file(GLOB_RECURSE SRCS src/*.cxx)
add_executable(villainous ${SRCS})
set_property(TARGET villainous PROPERTY CXX_STANDARD 17)
target_include_directories(villainous PUBLIC include)
file(COPY extensions DESTINATION .)

install(TARGETS villainous DESTINATION villainous/bin)
install(DIRECTORY extensions DESTINATION villainous/bin)

include(FetchContent)

FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_GetProperties(yaml-cpp)
FetchContent_Populate(yaml-cpp)
add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
target_link_libraries(villainous PUBLIC yaml-cpp::yaml-cpp)
target_include_directories(villainous PUBLIC ${yaml-cpp_SOURCE_DIR}/include/yaml-cpp)