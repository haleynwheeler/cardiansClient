#include "GeneralMessage.hpp"

GeneralMessage::GeneralMessage() : msg("")
{
}

GeneralMessage::~GeneralMessage()
{
}

std::string GeneralMessage::encode()
{
  return msg;
}

GeneralMessage GeneralMessage::decode(std::string msg)
{
  /// do magic here, not sure how to parse yet.
  std::stringstream ss;
  return GeneralMessage();
}
