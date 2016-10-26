#ifndef BUTTON_H
#define BUTTON_H

#include <wx/wx.h>

class Button: public wxButton{
public:
  //Passing in what's on the button
    Button(const wxString& title, wxFrame* parent);
  //What to do when you click the button
  void OnClick(wxCommandEvent & event);
};

#endif
