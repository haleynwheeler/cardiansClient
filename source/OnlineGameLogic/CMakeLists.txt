
xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})

add_library(OnlineGameLogic
OnlineGame.hpp
OnlineGame.cpp
CrazyEightsOnline.cpp
CrazyEightsOnline.hpp
HeartsOnline.cpp
HeartsOnline.hpp
)

link_libraries(Networking ${externLibs})
