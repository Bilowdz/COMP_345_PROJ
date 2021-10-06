cmake_minimum_required(VERSION 3.20)
project(COMP_345_PROJ)

set(CMAKE_CXX_STANDARD 14)

set(Headers Player.h Territory.h Order.h Hand.h OrderList.h)

add_executable(COMP_345_PROJ ${PROJECT_SOURCE_DIR}/ main.cpp Player.cpp Territory.cpp Order.cpp Hand.cpp OrderList.cpp)
