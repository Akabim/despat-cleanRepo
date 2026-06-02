cmake_minimum_required(VERSION 3.10)

project(balatro_checker)

set(CMAKE_CXX_STANDARD 14)
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
    FiveOfAKindChecker.cpp
    FlushFiveChecker.cpp
    FlushHouseChecker.cpp
    StraightFlushChecker.cpp

    HandGenerator.cpp

    HandScoreTable.cpp
    ScoreContext.cpp

    JokerManager.cpp
    BasicMultJoker.cpp
    PairMultJoker.cpp
    StraightXMultJoker.cpp

    BlindManager.cpp
    SmallBlindState.cpp
    BigBlindState.cpp
    BossBlindState.cpp
)