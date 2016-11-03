#ifndef BUTTON_H
#define BUTTON_H

#include <wx/wx.h>

class Button: public wxButton{
//  wxButton theButton;
public:
  //Passing in what's on the button
    Button(const wxString& title, wxFrame* parent, wxSize size);
  //What to do when you click the button
  void OnClick(wxCommandEvent & event);


  enum
      {
        BUTTON_Hello = wxID_HIGHEST + 1 // declares an id which will be used to call our button
      };
 wxDECLARE_EVENT_TABLE();
};



#endif
