#include "playerCard.h"


playerCard::playerCard(wxFrame *parent, Card theCards) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
          wxTAB_TRAVERSAL, wxPanelNameStr){
            theCard = new Card(theCards.getSuit(),theCards.getValue());
            wxBoxSizer* panel = new wxBoxSizer(wxVERTICAL);
            wxString input = theCards.getSuit()+" ";
            panel->Add(new wxTextCtrl(this, wxID_ANY, input, wxDefaultPosition,
               wxDefaultSize, 0, wxDefaultValidator, wxTextCtrlNameStr));
            //SetSizerAndFit(this);
}

playerCard::~playerCard(){

}
