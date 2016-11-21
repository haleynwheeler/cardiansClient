#include "Game.hpp"

Game::Game(wxFrame *mainFrame) {
  std::cout << "Creating Crazy Eights Game" << std::endl;
  // Construct a Player Named "You". This will be our Human Player.
  players.push_back(Player(0, "You"));

  // Construct the AI Players.
  for (auto i = 1; i < 4; i++) {
    players.push_back(Player(0, "AI"));
  }
  gui = new playArea(mainFrame);
  gui->setMadeMoveFunction([this](Card c) { humanMadeMove(c); });
  std::cout << "Created Play Area" << std::endl;
}

std::vector<Card> Game::initializeDeck() {
  std::vector<Card> deck;
  deck.reserve(52);
  std::vector<Suit> suits = {HEARTS, SPADES, CLUBS, DIAMONDS};
  for (auto &&suit : suits) {
    for (int i = 2; i < 15; i++) {
      deck.push_back(Card(suit, static_cast<Value>(i)));
    }
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(deck.begin(), deck.end(), generator);
  return deck;
}

void Game::showScores() {
  std::vector<int> allPlayersTotalScores;
  std::vector<int> allPlayersRoundScores;
  for (auto &&player : players) {
    allPlayersTotalScores.push_back(player.getTotalScore());
    allPlayersRoundScores.push_back(player.getRoundScore());
  }
  if (gui->endOfRoundDialog(allPlayersRoundScores, allPlayersTotalScores)) {
    startNewRound();
  }
}

void Game::showGame() { gui->Show(true); }

void Game::hideGame() { std::cout << "This is pointer" << gui << std::endl; }
