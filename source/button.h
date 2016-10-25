#include <wx/wx.h>

class Button: public wxFrame{
public:
  //Passing in what's on the button
    Button(const wxString& title);
  //What to do when you click the button
  void OnClick(wxCommandEvent & event);
};
