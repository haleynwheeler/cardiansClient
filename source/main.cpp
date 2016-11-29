//#include "GameLogic/CrazyEightsGame.hpp"
#include "Simple.h"
#include "baseBackground.h"
#include "button.h"
#include "clientInfo.h"
#include "imageInsert.h"

//#include "playArea.h"

#include <wx/sizer.h>
#include <wx/wx.h>

class MyApp : public wxApp {
public:
  bool OnInit() {
    wxInitAllImageHandlers();
    clientInfo *theClient = new clientInfo();
    wxBoxSizer *backgroundSizer = new wxBoxSizer(wxHORIZONTAL);
    Simple *mainFrame;
    mainFrame = new Simple(wxT("Cardians of the Galaxy"), theClient);
    // baseBackground *theBackground = new baseBackground(
    // mainFrame, wxT("../res/background.jpg"), wxBITMAP_TYPE_JPEG);
    // backgroundSizer->Add(theBackground);
    mainFrame->Show();

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
