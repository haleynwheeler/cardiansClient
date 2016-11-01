#include "button.h"

Button::Button(const wxString& title, wxFrame* parent, wxSize size):
    wxPanel(parent,wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
      wxPanelNameStr)
  {
    wxButton* theButton = new wxButton(this, wxID_ANY, title, wxDefaultPosition,
         size, 0, wxDefaultValidator, wxButtonNameStr);
    theButton->CentreOnParent();
    theButton->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
    theButton->SetForegroundColour(wxColour(wxT("WHITE")));
  };

void Button::OnClick(wxCommandEvent & event)
{
  std::cout<<"Pressed button"<<std::endl;
//  theButton.SetBackgroundColour(wxColour(0,0,0,wxALPHA_OPAQUE));
};

BEGIN_EVENT_TABLE ( Button, wxPanel)
    EVT_BUTTON(BUTTON_Hello, Button::OnClick)
END_EVENT_TABLE() // The button is pressed
