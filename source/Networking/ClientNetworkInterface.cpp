#include "ClientNetworkInterface.hpp"

ClientNetworkInterface::ClientNetworkInterface(int port, io_service &service,
                                               std::ostream &outStream)
    : NetworkInterface(port, service, outStream),
      conn(TCPConnection::create(service)) {
  out << "Client network interface initialized..." << std::endl;
}

void ClientNetworkInterface::connect(std::string ip, int port) {
  out << "Attempting to connect to " << ip << ":" << port << "..." << std::endl;

  try {
    conn->connect(ip.data(), std::to_string(port).data());
    out << "Connected..." << std::endl;
  } catch (boost::system::system_error e) {
    out << "Failed to connect to " << ip << ":" << port << "..." << std::endl;
    out << "Error code = " << e.code() << " : " << e.code().message()
        << std::endl;
  }
}

std::string ClientNetworkInterface::recieve() { return conn->read(); }
//
// std::string ClientNetworkInterface::tryRecieve()
//{
//  return std::string();
//}
//
void ClientNetworkInterface::send(std::string msg) { conn->write(msg); }

bool ClientNetworkInterface::isConnected() { return conn->isConnected(); }
