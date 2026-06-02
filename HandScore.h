#pragma once

struct HandScore {
    int chips;
    double mult;

    HandScore(int chips = 0, double mult = 1.0)
        : chips(chips), mult(mult) {
    }

    double getFinalScore() const {
        return chips * mult;
    }
};