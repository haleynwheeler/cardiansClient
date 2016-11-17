#include "clientInfo.h"

clientInfo::clientInfo() {
  int width = wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5;
  int height = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  double X_Ratio = (double)maxWidth / (double)width;
  double Y_Ratio = (double)maxHeight / (double)height;
  clientScreenRatio = X_Ratio < Y_Ratio ? X_Ratio : Y_Ratio;
  clientScreenSize = new wxSize((int)(clientScreenRatio * width),
                                (int)(clientScreenRatio * height));
}

clientInfo::~clientInfo() {}

wxSize clientInfo::getClientScreenSize() {
  return wxSize(clientScreenSize->GetWidth(), clientScreenSize->GetHeight());
}

wxSize clientInfo::getLargeCardSize() {
  return wxSize((clientScreenSize->GetWidth() / 6), 100);
}

wxSize clientInfo::getSmallCardSize() { return wxSize(100, 20); }
