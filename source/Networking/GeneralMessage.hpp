#ifndef GENERAL_MESSAGE
#define GENERAL_MESSAGE

#include<string>
#include<sstream>

class GeneralMessage
{
public:
  GeneralMessage();
  ~GeneralMessage();

  std::string msg;

  virtual std::string encode();
  GeneralMessage decode(std::string msg);

private:

};

#endif // !GENERAL_MESSAGE
