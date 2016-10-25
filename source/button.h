#include <wx/wx.h>

class Button: public wxPanel{
public:
  //Passing in what's on the button
    Button(const wxString& title, wxFrame* parent);
  //What to do when you click the button
  void OnClick(wxCommandEvent & event);
};
