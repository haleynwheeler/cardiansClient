xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(Messages
LobbyGame.hpp
LobbyGame.cpp
GameMessage.hpp
)
target_link_libraries(Messages ${externLibs})
