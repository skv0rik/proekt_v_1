cmake_minimum_required(VERSION 3.25.2)
project(proekt_)

set(CMAKE_CXX_STANDARD 23)

add_executable(proekt_ main.cpp Game.h Road.h Road.cpp Car.h Car.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(proekt_ sfml-system sfml-window sfml-graphics sfml-audio)
