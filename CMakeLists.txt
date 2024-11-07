cmake_minimum_required(VERSION 3.26)
project(playground-cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)

set(PROJECT_SOURCES w32_test.cpp)

#add_executable(playground-cpp WIN32 ${PROJECT_SOURCES})
#add_executable(playground-cpp ${PROJECT_SOURCES})
add_executable(playground-cpp tsf_test.cpp)

target_link_libraries(playground-cpp)

#target_link_libraries(Toolbox
#        Qt::Core
#        Qt::Gui
#        Qt::Widgets
#)
