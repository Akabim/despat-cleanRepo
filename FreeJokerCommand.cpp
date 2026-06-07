#include "FreeJokerCommand.h"

void FreeJokerCommand::execute(GameSessionState& state) {
    state.setIsNextJokerFree(true);
}
