//#include "GameLogic/CrazyEightsGame.hpp"
#include "Simple.h"
#include "baseBackground.h"
#include "button.h"
#include "imageInsert.h"

//#include "playArea.h"

#include <wx/sizer.h>
#include <wx/wx.h>

class MyApp : public wxApp {
public:
  bool OnInit() {
    wxInitAllImageHandlers();

    Simple *mainFrame;

    mainFrame = new Simple(wxT("Cardians of the Galaxy"));

    mainFrame->Show();

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
