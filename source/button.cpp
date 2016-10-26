#include "button.h"

Button::Button(const wxString& title, wxFrame* parent): wxButton(parent, wxID_EXIT, title,
  wxDefaultPosition,wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.15,20))
  {
    this->SetFocus();
    this->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
    this->SetForegroundColour(wxColour(wxT("WHITE")));
  };

void Button::OnClick(wxCommandEvent & WXUNUSED(event))
{
  Close(true);
};
