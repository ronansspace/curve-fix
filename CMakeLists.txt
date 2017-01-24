cmake_minimum_required(VERSION 3.5)
project(curve_fix)

set(CMAKE_CXX_STANDARD 11)

set ( PROJECT_LINK_LIBS quickfix )
link_directories( /usr/local/lib )

include_directories(/usr/local/include/quickfix)

set(SOURCE_FILES Application.cpp main.cpp)

add_executable(curve_fix ${SOURCE_FILES})

target_link_libraries(curve_fix ${PROJECT_LINK_LIBS} )