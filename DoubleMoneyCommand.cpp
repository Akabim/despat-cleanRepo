#include "DoubleMoneyCommand.h"

void DoubleMoneyCommand::execute(GameSessionState& state) {
    state.addMoney(state.getMoney()); // Doubles current money
}
