// #include<iostream>
// #include"ClientNetworkInterface.hpp"
//
//
// int main() {
//   io_service service;
//   ClientNetworkInterface NI(0, service, std::cout);
//   NI.connect("127.0.0.1", 12000); // the port wont change, but the IP will be
//   the Ip of
//                                   // the server.
//
//   if (NI.isConnected()) { // start the client in online mode
//     std::string msg = "";
//     while (msg != "EXIT") {
//       std::cout << "Enter message (EXIT to quit) :" << std::endl;
//       std::getline(std::cin, msg);
//       NI.send(msg);
//       std::cout << "Server says : " << NI.recieve() << std::endl;
//     }
//   }
//   else { // start in offline mode
//     std::cout << "Could not connect... press enter to quit";
//     std::cin.get();
//   }
//
// }
