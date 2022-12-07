cmake_minimum_required(VERSION 3.23)
project(json_prase)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./thirty_part/json)
add_subdirectory(./thirty_part/glog)

add_executable(json_prase main.cpp)
target_link_libraries(json_prase nlohmann_json glog::glog)
