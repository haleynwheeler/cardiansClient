#include "clientInfo.h"

clientInfo::clientInfo() {
  backgroundImageSize = wxSize(1290, 800);
  cardBackImageSize = wxSize(576, 821);
  cardBackHorImageSize = wxSize(821, 576);
  cardFrontSize = wxSize(500, 726);
  cardSliverSize = wxSize(100, 725);
  smallBackImageCardSize = wxSize(165, 821);
  smallBackHorImageCardSize = wxSize(821, 165);

  wxSize *client =
      new wxSize((wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .7),
                 (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7));
  clientScreenSize = ratioHandlingDetermineWidth(backgroundImageSize, client);
  std::cout << "Screen Size" << client->GetWidth() << "." << client->GetHeight()
            << std::endl;
}

clientInfo::~clientInfo() {}

// Based off of the ratio of the base object it will correctly return an object
// that does not have a larger width thSan the imageRatioInfo and is the same
// ratio as the image provided
wxSize clientInfo::ratioHandlingDetermineWidth(wxSize imageRatioInfo,
                                               wxSize *wantedSize) {
  int desiredWidth =
      (double)(imageRatioInfo.GetWidth() * wantedSize->GetHeight()) /
      (double)imageRatioInfo.GetHeight();
  return wxSize(desiredWidth, (int)wantedSize->GetHeight());
}

wxSize clientInfo::ratioHandlingDetermineHeight(wxSize imageRatioInfo,
                                                wxSize *wantedSize) {
  int desiredHeight =
      (double)(imageRatioInfo.GetHeight() * wantedSize->GetWidth()) /
      (double)imageRatioInfo.GetWidth();
  return wxSize((int)wantedSize->GetWidth(), desiredHeight);
}

wxSize clientInfo::getClientScreenSize() {
  return wxSize(clientScreenSize.GetWidth(), clientScreenSize.GetHeight());
}

wxSize clientInfo::getLargeCardSize() {
  wxSize *wantedSize =
      new wxSize((clientScreenSize.GetWidth() * (1.0 / 15.0)), 1000);
  return ratioHandlingDetermineHeight(cardBackImageSize, wantedSize);
}

wxSize clientInfo::getSmallCardSize() {
  wxSize *wantedSize = new wxSize(
      (clientScreenSize.GetWidth() * (1.0 / 15.0)) * (165.0 / 576.0), 1000);
  return ratioHandlingDetermineHeight(smallBackImageCardSize, wantedSize);
}

wxSize clientInfo::getLargeHorCardSize() {
  wxSize *wantedSize =
      new wxSize(1000, (clientScreenSize.GetWidth() * (1.0 / 15.0)));
  return ratioHandlingDetermineWidth(cardBackHorImageSize, wantedSize);
}

wxSize clientInfo::getSmallHorCardSize() {
  wxSize *wantedSize = new wxSize(
      1000, (clientScreenSize.GetWidth() * (1.0 / 15.0)) * (165.0 / 576.0));
  return ratioHandlingDetermineWidth(smallBackHorImageCardSize, wantedSize);
}

wxSize clientInfo::getCardFront() {
  wxSize *wantedSize =
      new wxSize((clientScreenSize.GetWidth() * (1.0 / 13.5)), 1000);
  return ratioHandlingDetermineHeight(cardFrontSize, wantedSize);
}

wxSize clientInfo::getSmallCardFront() {
  wxSize *wantedSize = new wxSize(
      (clientScreenSize.GetWidth() * (1.0 / 13.5)) * (100.0 / 500.0), 1000);
  return ratioHandlingDetermineHeight(cardSliverSize, wantedSize);
}

int clientInfo::c8middleVerSpace() {
  return (clientScreenSize.GetHeight() * .2);
} // 180
int clientInfo::c8StrandardBorder() {
  return (clientScreenSize.GetHeight() * .02);
} // 20
int clientInfo::c8MiddleHorSpace() {
  return (clientScreenSize.GetWidth() * .3);
} // 270
int clientInfo::c8LogoDifference() {
  return (clientScreenSize.GetWidth() * .2);
} // 120

int clientInfo::hStandardBorder() {
  return (clientScreenSize.GetHeight() * .18);
}
int clientInfo::hSpaceBetweenCardAndHand() {
  return (clientScreenSize.GetHeight() * .02);
}
int clientInfo::hSideVFieldSpacer() {
  return (clientScreenSize.GetHeight() * .18);
}
int clientInfo::hSideFieldSpacer() {
  return (clientScreenSize.GetWidth() * .25);
}
int clientInfo::hMiddleSpacer() { return (clientScreenSize.GetHeight() * .18); }

wxSize clientInfo::sidePaneBtnSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.4),
                clientScreenSize.GetHeight() / 5.2);
}

wxSize clientInfo::gamePlayBtnSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.26),
                clientScreenSize.GetHeight() * .25);
}

wxSize clientInfo::sidePanelSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.40),
                clientScreenSize.GetHeight());
}

wxSize clientInfo::loginBtnSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.35),
                clientScreenSize.GetHeight() * .20);
}

wxSize clientInfo::loginTextSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.35),
                clientScreenSize.GetHeight() * .25);
}

wxSize clientInfo::newUserBtnSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.50),
                clientScreenSize.GetHeight() * .20);
}

wxSize clientInfo::newUserTextSize() {
  return wxSize((clientScreenSize.GetWidth() * 0.25),
                clientScreenSize.GetHeight() * .20);
}
