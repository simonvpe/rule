# To build with clang
# mkdir build && cd build && cmake .. -DCMAKE_CXX_COMPILER=clang++
cmake_minimum_required(VERSION 2.8.9)



set(PROJECT_NAME rule)
project(${PROJECT_NAME})

include_directories(include GSL)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CPP11_FLAG "-std=c++1z")

add_compile_options(-Wall -Wextra -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -pedantic ${CPP11_FLAG})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-Weverything -Wno-c++98-compat-pedantic -Wno-c++98-compat -Wno-documentation
    -Wno-switch-enum -Wno-weak-vtables -Wno-missing-prototypes -Wno-padded -Wno-missing-noreturn
    -Wno-exit-time-destructors -Wno-documentation-unknown-command)
else()
    add_definitions(-Wnoexcept)
endif()

# Cardgame example
file(GLOB CARDGAME_EXAMPLE_SOURCES examples/cardgame/*.cpp)
add_executable(cardgame_example ${CARDGAME_EXAMPLE_SOURCES})

# Run tests if test=ON
option(test "Build all tests." ON)
if(test)
  add_subdirectory(test)
endif()
