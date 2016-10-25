#include <wx/wx.h>
#include <wx/sizer.h>
#include "button.h"
#include "baseBackground.h"


class Simple : public wxFrame
{
public:
    Simple(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
      wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5,
      wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5))
	{
		Centre();
	}
};

class MyApp : public wxApp
{
public:
	bool OnInit()
	{
    wxInitAllImageHandlers();

    Simple *mainFrame;
    baseBackground *theBackgroundDrawable;

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    mainFrame = new Simple(wxT("Cardians of the Galaxy"));
    theBackgroundDrawable = new baseBackground(mainFrame, wxT("background.jpg"),
      wxBITMAP_TYPE_JPEG);
    sizer->Add(theBackgroundDrawable,1,wxEXPAND);

    mainFrame->SetSizer(sizer);
    mainFrame->Show();
      Button *logBut = new Button(wxT("Login"));
      Button *userBut = new Button(wxT("New User"));
      logBut->Show(true);
      userBut->Show(true);


    return true;
	}
};






wxIMPLEMENT_APP(MyApp);
