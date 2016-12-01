#include "CrazyEightsOnline.hpp"

CrazyEightsOnline::CrazyEightsOnline(TCPConnection::pointer connect,
                                     wxFrame *mainFrame)
    : OnlineGame(connect) {
  gui = new playArea(mainFrame);
}

void CrazyEightsOnline::receivedServerRequest(std::string msg) {}

void CrazyEightsOnline::sendServerResponse(std::string msg) {}
