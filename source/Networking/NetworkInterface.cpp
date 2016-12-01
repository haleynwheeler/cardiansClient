#include "NetworkInterface.hpp"

NetworkInterface::NetworkInterface(int port, io_service &service,
                                   std::ostream &outStream)
    : activePort(port), ioService(service), out(outStream), active(true),
      ioThread(std::thread([&] { ioLoop(); })) {
  // io = std::thread([&] { ioLoop(); });
  out << "Network basic initialization complete..." << std::endl;
}

void NetworkInterface::ioLoop() {
  while (active) {
    ioService.run();
  }
}
