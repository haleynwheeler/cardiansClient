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
    clientInfo *screenInfo;
    screenInfo = new clientInfo();
    Simple *mainFrame;
    mainFrame = new Simple(wxT("Cardians of the Galaxy"), screenInfo);
    mainFrame->SetBackgroundColour(wxColour(0, 0, 0));

    mainFrame->Show();

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
