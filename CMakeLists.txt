cmake_minimum_required(VERSION 3.20)
project(COMP_345_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(COMP_345_PROJ main.cpp GameEngine.cpp GameEngine.h Map.cpp Map.h Player.cpp Player.h Orders.cpp Orders.h Card.cpp Card.h LoggingObserver.h LoggingObserver.cpp CommandProcessing.cpp CommandProcessing.h State.h PlayerStrategy.cpp PlayerStrategy.h HumanPlayerStrategy.cpp HumanPlayerStrategy.h AggressivePlayerStrategy.cpp AggressivePlayerStrategy.h BenevolentPlayerStrategy.cpp BenevolentPlayerStrategy.h NeutralPlayerStrategy.cpp NeutralPlayerStrategy.h CheaterPlayerStrategy.cpp CheaterPlayerStrategy.h)
