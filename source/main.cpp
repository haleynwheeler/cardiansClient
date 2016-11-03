#include "baseBackground.h"
#include "button.h"
#include "crazyEightsLogic/Game.hpp"
#include "imageInsert.h"
#include "login.h"
#include "playArea.h"
#include <wx/sizer.h>
#include <wx/wx.h>

class Simple : public wxFrame {
public:
  Simple(const wxString &title)
      : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
                wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
                       wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5)) {
    SetMaxSize(
        wxSize(wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
                      wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5)));
    SetMinSize(
        wxSize(wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
                      wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5)));
    Centre();
  }
};

class MyApp : public wxApp {
public:
  bool OnInit() {
    wxInitAllImageHandlers();

    Simple *mainFrame;
    baseBackground *theBackgroundDrawable;
    mainFrame = new Simple(wxT("Cardians of the Galaxy"));

    // Sets the background color
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    theBackgroundDrawable = new baseBackground(
        mainFrame, wxT("../../res/background.jpg"), wxBITMAP_TYPE_JPEG);
    sizer->Add(theBackgroundDrawable, 1, wxEXPAND);

    // login *loginPane;
    // loginPane = new login(mainFrame);

    //  playArea *theGame;
    //  theGame = new playArea(mainFrame);

    CrazyEightsGame *game = new CrazyEightsGame(mainFrame);

    mainFrame->SetSizer(sizer);
    mainFrame->Show();

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
