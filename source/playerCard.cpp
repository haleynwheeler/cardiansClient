#include "playerCard.h"
#include "baseBackground.h"


playerCard::playerCard(wxWindow *parent, Card *theCards, wxSize size) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, size,
      wxTAB_TRAVERSAL, wxPanelNameStr){
        wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
        if(size==wxSize(70,100)){
        wxBitmapButton *border = new wxBitmapButton(
          this, wxID_ANY, wxBitmap("../../res/fullBorder.png", wxBITMAP_TYPE_PNG),
          wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
          border->SetBackgroundColour(wxColour(90, 5, 18, 0));
        }
        else if(size==wxSize(80,120)){
          wxBitmapButton *border = new wxBitmapButton(
            this, wxID_ANY, wxBitmap("../../res/discard.png", wxBITMAP_TYPE_PNG),
            wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
            border->SetBackgroundColour(wxColour(90, 5, 18, 0));

        }
        else{
          wxBitmapButton *border = new wxBitmapButton(
            this, wxID_ANY, wxBitmap("../../res/leftBorder.png",  wxBITMAP_TYPE_PNG),
            wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
            border->SetBackgroundColour(wxColour(90, 5, 18, 0));
        }


      wxBoxSizer* panel =new wxBoxSizer(wxVERTICAL);
      wxPanel *tempPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1,50),
                wxTAB_TRAVERSAL, wxPanelNameStr);
    panel->Add(tempPanel);

    wxString suiter = wxString::Format(wxT("../../res/%i.png"),theCards->getSuit());
    wxBitmapButton *Suit = new wxBitmapButton(
      this, wxID_ANY, wxBitmap(suiter, wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
      Suit->SetBackgroundColour(wxColour(90, 5, 18, 0));
      Suit->CenterOnParent (wxBOTH);
    theCard = new Card(theCards->getSuit(),theCards->getValue());
    wxString textT = wxString::Format(wxT("%i"),theCards->getValue());
    wxString textU =  "\n" + textT;
    wxStaticText *text = new wxStaticText(this, wxID_ANY, textU,
    wxDefaultPosition,wxDefaultSize,wxALIGN_CENTRE);
    wxFont font = text->GetFont();
    text-> 	CenterOnParent(wxHORIZONTAL);
        font.SetPointSize(10);
  //      font.SetWeight(wxFONTWEIGHT_BOLD);
        text->SetFont(font);
     panel->Add(Suit);
     panel->Add(text);
       this->SetBackgroundColour(wxColour(255,255,255,0));
//    SetSizerAndFit(this);
}

// wxWindow *window, int proportion, int flag, int border, wxObjec
playerCard::~playerCard(){

}
