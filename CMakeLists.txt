cmake_minimum_required(VERSION 3.10)
project(Villainous)
include(FetchContent)
FetchContent_Declare(yaml-cpp GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git)
FetchContent_Declare(enet GIT_REPOSITORY https://github.com/lsalzman/enet.git)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(yaml-cpp enet SFML)

file(GLOB_RECURSE SRCS src/*.cxx)
add_executable(villainous ${SRCS})
set_property(TARGET villainous PROPERTY CXX_STANDARD 17)
target_include_directories(villainous PUBLIC include)
file(COPY extensions DESTINATION .)

install(TARGETS villainous DESTINATION villainous/bin)
install(DIRECTORY extensions DESTINATION villainous/bin)

# 3rd party
target_link_libraries(villainous PRIVATE yaml-cpp::yaml-cpp)
target_include_directories(villainous PRIVATE ${yaml-cpp_SOURCE_DIR}/include/yaml-cpp)

target_link_libraries(villainous PRIVATE enet)
target_include_directories(villainous PRIVATE ${enet_SOURCE_DIR}/include)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
target_link_libraries(villainous PRIVATE sfml-graphics)