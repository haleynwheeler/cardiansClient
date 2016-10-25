#include "button.h"

Button::Button(const wxString& title, wxFrame* parent): wxPanel(parent)
  {
    wxButton *button = new wxButton(parent, wxID_EXIT, title,
      wxDefaultPosition,wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.15,20));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
      wxCommandEventHandler(Button::OnClick));
    button->SetFocus();
    button->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
    button->SetForegroundColour(wxColour(wxT("WHITE")));
    Centre();
  };

void Button::OnClick(wxCommandEvent & WXUNUSED(event))
{
  Close(true);
};
