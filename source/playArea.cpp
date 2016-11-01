#include "playArea.h"
#include "button.h"
#include "imageInsert.h"

playArea::playArea(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
    wxBoxSizer *theMainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxFlexGridSizer *flexSizer = new wxFlexGridSizer(3,1,10,10);
    wxBoxSizer *playField = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *playArea = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *yourHand = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *playerOne = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *playerTwo = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *playerThree = new wxBoxSizer(wxVERTICAL);
    wxButton *Deck =  new wxButton(this, wxID_ANY,wxT("Deck"));
    wxButton *Discard = new wxButton(this, wxID_ANY, wxT("Discard"));

    for(int i= 0; i<8;i++){
      wxButton *card = new wxButton(this,wxID_ANY,wxT("Card"));
      yourHand->Add(card);
    }

    for(int i= 0; i<8;i++){
      wxButton *card = new wxButton(this,wxID_ANY,wxT("Card"));
      playerOne->Add(card);
    }

    for(int i= 0; i<8;i++){
      wxButton *card = new wxButton(this,wxID_ANY,wxT("Card"));
      playerTwo->Add(card);
    }

    for(int i= 0; i<8;i++){
      wxButton *card = new wxButton(this,wxID_ANY,wxT("Card"));
      playerThree->Add(card);
    }

    playArea->Add(playerOne);
    playArea->Add(Deck);
    playArea->Add(Discard);
    playArea->Add(playerThree);
    playField->Add(playArea);

    flexSizer->Add(playerTwo);
    flexSizer->Add(playField, wxCENTER,0);
    flexSizer->Add(yourHand);

    theMainSizer->Add(flexSizer);
    SetSizerAndFit(theMainSizer);
    Centre();
  }


playArea::~playArea(){

}
