#ifndef LOBBY_GAME
#define LOBBY_GAME

#include <memory>
#include <string>
#include <vector>

#include <boost/serialization/access.hpp>

//#include "source/PlayerAPI/Player.hpp"

enum GameType {
  HEARTGAME = 1,
  SPADEGAME = 2,
  EIGHTSGAME = 3,
  ALL = 4,     // used only in filtering when sending list to and from client
  UNKNOWN = 99 // used only in filtering when sending list to and from client
};

struct LobbyGame {
  std::string name;
  GameType type;
  std::vector<int> joinedPlayers;
  std::vector<std::string> playerNames;
  int numberJoined;

  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &name;
    ar &type;
    ar &numberJoined;
    /*auto tempCount = playerNames.size();
    ar & tempCount;
    for (size_t i = 0; i < tempCount; i++)
    {
      ar & playerNames[i];
    }*/
  }

  LobbyGame() {}

  LobbyGame(std::string name, GameType type)
      : name(name), type(type), numberJoined(0) {}
};

#endif // LOBBY_GAME
