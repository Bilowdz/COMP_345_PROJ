cmake_minimum_required(VERSION 3.20)
project(COMP_345_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(COMP_345_PROJ main.cpp GameEngine.cpp GameEngine.h GameEngineDriver.cpp GameEngineDriver.h Map.cpp Map.h Player.cpp Player.h)
