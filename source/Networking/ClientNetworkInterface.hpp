#ifndef CLIENT_NETWORK_INTERFACE
#define CLIENT_NETWORK_INTERFACE

#include "NetworkInterface.hpp"

using namespace boost::asio;

/* This is the NI that should be used by clients */
class ClientNetworkInterface : NetworkInterface {
public:
  // constructor
  ClientNetworkInterface(int port, io_service &service,
                         std::ostream &outStream);

  // method to attempt to connect to the given ip and port, check isConnected to
  // verify connection before proceding with send or recieve.
  void connect(std::string ip, int port);
  // method to sync recieve from the server
  std::string recieve();
  // method to sync send to the server
  void send(std::string msg);

  // returns if the underlying TCP connection is connected.
  bool isConnected();

private:
  // The TCP connection to be used by the NI for communication
  TCPConnection::pointer conn;
};

#endif // !CLIENT_NETWORK_INTERFACE
