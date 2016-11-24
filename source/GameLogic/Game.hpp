/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include "Player.hpp"

#include <algorithm>
#include <random>

class Game {
protected:
  std::vector<Player> players;
  int turn; // index in player vector
  std::vector<Card> initializeDeck();
  virtual void startNewRound(){};
  virtual void humanMadeMove(Card){};

public:
  Game();
};

#endif
