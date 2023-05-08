cmake_minimum_required(VERSION 3.25)
project(PingPongGameSFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(PingPongGameSFML main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(PingPongGameSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
