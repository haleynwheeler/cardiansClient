#include "playerCard.h"


playerCard::playerCard(wxFrame *parent, Card *theCards, wxSize size) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, size,
      wxTAB_TRAVERSAL, wxPanelNameStr){

    theCard = new Card(theCards->getSuit(),theCards->getValue());
    wxString textS = wxString::Format(wxT("%i"),theCards->getSuit());
    wxString textT = wxString::Format(wxT("%i"),theCards->getValue());
    wxString textU = textS + "\n" + textT;
    wxStaticText *text = new wxStaticText(this, wxID_ANY, textU,
    wxDefaultPosition,wxDefaultSize,wxALIGN_CENTRE);

    // panel->Add(text);
       this->SetBackgroundColour(wxColour(255,255,255,wxALPHA_OPAQUE));
//    SetSizerAndFit(this);""
}

// wxWindow *window, int proportion, int flag, int border, wxObjec
playerCard::~playerCard(){

}
