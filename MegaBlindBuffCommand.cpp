#include "MegaBlindBuffCommand.h"

void MegaBlindBuffCommand::execute(GameSessionState& state) {
    state.setBlindScoreMultiplier(2.0f);
}
