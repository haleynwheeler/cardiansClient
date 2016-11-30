
xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(GameLogic
Card.hpp
Card.cpp
Player.hpp
Player.cpp
Game.hpp
Game.cpp
CrazyEightsGame.hpp
CrazyEightsGame.cpp
HeartsGame.hpp
HeartsGame.cpp
)
link_libraries(GameLogic ${externLibs})
