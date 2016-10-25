#include "button.h"

Button::Button(const wxString& title):
  wxFrame(NULL,wxID_ANY, title, wxDefaultPosition,wxSize(270,150))
  {
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxButton *button = new wxButton(panel, wxID_EXIT, title,
      wxPoint(100,20));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
      wxCommandEventHandler(Button::OnClick));
    button->SetFocus();
    panel->SetBackgroundColour(wxColour(243,8,92,wxALPHA_OPAQUE));
    Centre();
  };

void Button::OnClick(wxCommandEvent & WXUNUSED(event))
{
  Close(true);
};
