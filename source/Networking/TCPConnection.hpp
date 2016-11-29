#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <exception>
#include <iostream>

/* KNOWN ISSUES

- when closing a connection the client side will fall through and cause infinite
read
operation if read was called during the loss of communication. This renders the
object
unuseable and will stall the using application.

- there is no error checking once read or write have been called and entered the
try block
this causes undesired effects, see above.

*/

/*
A wrapper for a basic TCP connection. Includes methods for connection and
reception
of connections.
*/
class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {
public:
  // Allows for ease of creation in other code.
  typedef boost::shared_ptr<TCPConnection> pointer;
  // Factory createor method.
  static pointer create(boost::asio::io_service &ioService, int port = 0);

  // Attempts to connect to the given host and port
  void connect(const char *host, const char *port);
  // Waits for a connection to be requested, fills that request and then returns
  void accept();
  // closes the exsisting connection
  void close();
  // Read from the connection until a '/n' is found
  std::string read();
  // Write to the connection. Automatically appends a '/n' to the end of the
  // message.
  void write(std::string msg);

  // performs an async read and calls the callback when the read succeds
  void aSyncRead(std::function<void(std::string)> callback);

  // returns the current active port
  const char *getPort();
  // returns the socket in use
  boost::asio::ip::tcp::socket &getSocket();
  // returns if the socket is connected
  bool isConnected();

private:
  void handleAsyncRead(const boost::system::error_code &e);

  // Constructor used by the create method
  TCPConnection(boost::asio::io_service &ioService, int port);
  // flag indicating if a conneciton is active
  bool connected;
  // flag indicating if the object is waiting for a connection request
  bool accepting;
  // the socket to perform communication on
  boost::asio::ip::tcp::socket socket;
  // The resolver to be used for attempting to connect
  boost::asio::ip::tcp::resolver resolver;
  // The acceptor to be used to wait for a connection
  boost::asio::ip::tcp::acceptor acceptor;
  std::function<void(std::string)> nextCallback;
  boost::asio::streambuf asycBuffer;
};

#endif // TCP_CONNECTION
