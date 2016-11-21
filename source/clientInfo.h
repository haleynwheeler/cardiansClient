#ifndef clientInfo_H
#define clientInfo_H

#include <wx/wx.h>

class clientInfo {
  int maxWidth = 1024;
  int maxHeight = 768;
  wxSize *clientScreenSize;
  wxSize *largeCardSize;
  wxSize *smallCardSize;
  double largeCardRatio;
  double smallCardRatio;
  double clientScreenRatio;
  int cardBackType = 12;

public:
  clientInfo();
  ~clientInfo();
  wxSize getClientScreenSize();
  wxSize getLargeCardSize();
  wxSize getSmallCardSize();
  int getcardBackType() { return cardBackType; };
};

#endif
