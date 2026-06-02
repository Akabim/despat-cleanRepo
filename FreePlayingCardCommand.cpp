#include "FreePlayingCardCommand.h"
#include <iostream>

void FreePlayingCardCommand::execute(GameSessionState& session) {
    std::cout << "[Reward] Free Playing Card added to deck!" << std::endl;
    // Add a random card or a specific one
    session.addCardToDeck(Card(Card::ACE, Card::SPADES)); 
}
