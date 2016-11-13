/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../playArea.h"
#include "Card.hpp"
#include "Player.hpp"

#include <algorithm>
#include <random>

class Game {
protected:
  playArea *gui;
  std::vector<Player> players;
  int turn; // index in player vector
  std::vector<Card> initializeDeck();
  virtual void humanMadeMove(Card){};
  void displayEndOfRoundDialogBox();
  void showScores();
  virtual void startNewRound(){};

public:
  Game(wxFrame *);
  // void onButton(wxCommandEvent &event);
};

#endif
