#ifndef NETWORK_INTERFACE
#define NETWORK_INTERFACE

#include "../GameLogic/Player.hpp"
#include "GeneralMessage.hpp"
#include "TCPConnection.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;
using ip::tcp;

/*
Core interface for creating a network connection. It encapsulates all the logic
needed to
send and recieve messages based on a single request-reply pattern.
*/
class NetworkInterface {
public:
protected:
  io_service &ioService;
  int activePort;
  bool active;
  std::ostream &out;
  std::thread ioThread;

  // default constructor
  NetworkInterface(int port, io_service &service, std::ostream &outStream);

  // deconstructor to clean up threads
  ~NetworkInterface() {
    active = false;
    if (ioThread.joinable()) {
      ioThread.join();
    }
  }
  // A loop called to continuously proccess the io service
  void ioLoop();
};
#endif // !NETWORK_INTERFACE
