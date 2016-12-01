#ifndef clientInfo_H
#define clientInfo_H

#include <wx/wx.h>

class clientInfo {
  // These are the actual deminsions of the images so we can keep the ratio
  wxSize backgroundImageSize;
  wxSize cardBackImageSize;
  wxSize cardBackHorImageSize;
  wxSize cardFrontSize;
  wxSize cardSliverSize;
  wxSize clientScreenSize;
  wxSize smallBackImageCardSize;
  wxSize smallBackHorImageCardSize;
  int cardBackType = 14;
  wxSize ratioHandlingDetermineWidth(wxSize imageRatioInfo, wxSize *wantedSize);
  wxSize ratioHandlingDetermineHeight(wxSize imageRatioInfo,
                                      wxSize *wantedSize);
  /*
    Breakdown of current ratio math
    Bottom Sizer Card math
    X = 2Borders + 12Smalls + largeCard
    B = 5/4largeCard
    S = 1/3Smalls
    X = 2*5/4lC 12*1/3LC + lc
  */

public:
  clientInfo();
  ~clientInfo();
  int c8middleVerSpace();
  int c8StrandardBorder();
  int c8MiddleHorSpace();
  int c8LogoDifference();

  int hStandardBorder();
  int hSpaceBetweenCardAndHand();
  int hSideFieldSpacer();
  int hSideVFieldSpacer();
  int hMiddleSpacer();

  wxSize getClientScreenSize();
  wxSize getLargeCardSize();
  wxSize getSmallCardSize();
  wxSize getLargeHorCardSize();
  wxSize getSmallHorCardSize();
  wxSize getCardFront();
  wxSize getSmallCardFront();
  wxSize sidePaneBtnSize();
  wxSize gamePlayBtnSize();
  wxSize sidePanelSize();
  wxSize loginBtnSize();
  wxSize loginTextSize();
  wxSize newUserBtnSize();
  wxSize newUserTextSize();

  int getcardBackType() { return cardBackType; };
};

#endif
