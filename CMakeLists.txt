cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Wall -g")

project(TravelMaker)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS  src/*.cpp)
add_executable(TravelMaker ${SRC_FILES})
target_include_directories(TravelMaker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


