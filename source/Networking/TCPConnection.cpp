#include "TCPConnection.hpp"

TCPConnection::TCPConnection(boost::asio::io_service& ioService, int port) 
  : socket(ioService), resolver(ioService), 
  acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
  connected(false), accepting(false)
{

}

TCPConnection::pointer TCPConnection::create(boost::asio::io_service & io_service, int port)
{
  return pointer(new TCPConnection(io_service,port));
}

void TCPConnection::connect(const char * host, const char * port)
{
  boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
    boost::asio::ip::tcp::resolver::query(host, port));
  boost::asio::connect(socket, endpoint);
  connected = true;
}

void TCPConnection::accept()
{
  accepting = true;
  try {
    acceptor.accept(socket);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  accepting = false;
  connected = true;
}

void TCPConnection::close()
{
  socket.close();
}

std::string TCPConnection::read()
{
  boost::system::error_code error;
  boost::asio::streambuf buffer;
  try 
  {
    boost::asio::read_until(socket, buffer, "\n", error);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
    return std::string();
  }
  std::istream str(&buffer);
  std::string s;
  std::getline(str, s);
  return s;
}

void TCPConnection::aSyncRead(std::function<void(std::string)> callback)
{
  nextCallback = callback;
  boost::asio::async_read_until(socket, asycBuffer, "\n",
    boost::bind(&TCPConnection::handleAsyncRead,this,boost::asio::placeholders::error));
}

void TCPConnection::write(std::string msg)
{
  try
  {
    boost::asio::write(socket, boost::asio::buffer(msg + "\n"));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}


const char * TCPConnection::getPort()
{
  std::string port = std::to_string(socket.local_endpoint().port());
  return (port.c_str());
}

boost::asio::ip::tcp::socket& TCPConnection::getSocket()
{
  return socket;
}

bool TCPConnection::isConnected()
{
  return connected;
}

void TCPConnection::handleAsyncRead(const boost::system::error_code & e)
{
  if (!e) {
    std::istream is(&asycBuffer);
    std::string line;
    std::getline(is, line);
    nextCallback(line);
  }
  else {
    // something bad happened, no easy way to handle it... best way may be to 
    // send the error up to the callback, but not sure... This block means most
    // likely the client disconnected. Exception does not work since it will be 
    // delt with in the io_service internally and cause a crash.
    //throw new std::exception();
    connected = false;
  }
}

