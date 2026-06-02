#include "BonusHandCommand.h"
#include <iostream>

void BonusHandCommand::execute(GameSessionState& session) {
    std::cout << "[Reward] Bonus Hand applied! +1 hand to session." << std::endl;
    session.addHandsRemaining(1);
}
