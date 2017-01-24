cmake_minimum_required(VERSION 3.5)
project(curve_fix)

set(CMAKE_CXX_STANDARD 11)

set ( PROJECT_LINK_LIBS quickfix )
link_directories( /usr/local/lib )

include_directories(include /usr/local/include/quickfix)

set(SOURCES src/main.cpp src/Application/Application.cpp)

add_executable(curve_fix ${SOURCES})

target_link_libraries(curve_fix ${PROJECT_LINK_LIBS} )