#pragma once
#include "ScoreContext.h"
#include <string>

class IJoker {
public:
    virtual ~IJoker() = default;

    virtual std::string getName() const = 0;
    virtual bool canActivate(const ScoreContext& context) const = 0;
    virtual void apply(ScoreContext& context) = 0;
};