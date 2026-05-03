cmake_minimum_required(VERSION 3.10)
project(BalatroCOR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(balatro_checker
    main.cpp
    Card.cpp
    HandChecker.cpp
    RoyalFlushChecker.cpp
    FourOfAKindChecker.cpp
    FullHouseChecker.cpp
    FlushChecker.cpp
    StraightChecker.cpp
    ThreeOfAKindChecker.cpp
    TwoPairChecker.cpp
    PairChecker.cpp
    HighCardChecker.cpp
)

target_include_directories(balatro_checker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
