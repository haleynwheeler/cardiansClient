
xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})

add_library(Networking
ClientNetworkInterface.cpp
ClientNetworkInterface.hpp
GeneralMessage.cpp
GeneralMessage.hpp
NetworkInterface.cpp
NetworkInterface.hpp
TCPConnection.cpp
TCPConnection.hpp
)

link_libraries(Networking ${externLibs})
