#include <wx/wx.h>
#include <wx/sizer.h>
#include "button.h"
#include "baseBackground.h"
#include "login.h"

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
    mainFrame = new Simple(wxT("Cardians of the Galaxy"));

    //Sets the background color
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    theBackgroundDrawable = new baseBackground(mainFrame, wxT("background.jpg"),
      wxBITMAP_TYPE_JPEG);
    sizer->Add(theBackgroundDrawable,1,wxEXPAND);
/*
    Button *logBut = new Button(wxT("Login"),mainFrame);
    Button *userBut = new Button(wxT("New User"),mainFrame);
*/
    login *loginPane;
    loginPane = new login(mainFrame);

    mainFrame->SetSizer(sizer);
    mainFrame->Show();
  //  logBut->Show(true);
  //  userBut->Show(true);


    return true;
	}
};






wxIMPLEMENT_APP(MyApp);
