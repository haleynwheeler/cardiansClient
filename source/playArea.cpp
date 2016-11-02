#include "playArea.h"
#include "button.h"
#include "imageInsert.h"

playArea::playArea(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.7), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
    int cardWidth = 20;
    int cardHeight = 100;

    int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.7;
    heightLeft -= 850;

    wxBoxSizer *theMainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *upperPortion = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *middlePortion = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lowerPortion = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *fieldArea = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *verticalfieldArea =new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *yourHand = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *playerOne = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *playerTwo = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *playerThree = new wxBoxSizer(wxVERTICAL);
    wxBitmapButton *Deck = new wxBitmapButton(this, wxID_ANY, wxBitmap("upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxBitmapButton *Discard = new wxBitmapButton(this, wxID_ANY, wxBitmap("white.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

      wxBitmapButton *card1 = new wxBitmapButton(this, wxID_ANY, wxBitmap("upFull.jpg",
        wxBITMAP_TYPE_JPEG), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
      yourHand->Add(card1);
    for(int i= 0; i<8;i++){
      wxBitmapButton *card = new wxBitmapButton(this, wxID_ANY, wxBitmap("up.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
      yourHand->Add(card);
    }

    wxBitmapButton *card2 = new wxBitmapButton(this, wxID_ANY, wxBitmap("leftFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    playerOne->Add(card2);
    for(int i= 0; i<8;i++){
      wxBitmapButton *card = new wxBitmapButton(this, wxID_ANY, wxBitmap("left.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
      playerOne->Add(card);
    }

    wxBitmapButton *card3 = new wxBitmapButton(this, wxID_ANY, wxBitmap("downFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    playerTwo->Add(card3);
    for(int i= 0; i<8;i++){
      wxBitmapButton *card = new wxBitmapButton(this, wxID_ANY, wxBitmap("down.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
      playerTwo->Add(card);
    }

    wxBitmapButton *card4 = new wxBitmapButton(this, wxID_ANY, wxBitmap("rightFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    playerThree->Add(card4);
    for(int i= 0; i<8;i++){
      wxBitmapButton *card = new wxBitmapButton(this, wxID_ANY, wxBitmap("right.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
      playerThree->Add(card);
    }

    fieldArea->Add(Deck);
    fieldArea->Add(Discard);

    verticalfieldArea->AddSpacer(100);
    verticalfieldArea->Add(fieldArea);

    upperPortion->AddSpacer(270);
    upperPortion->Add(playerTwo);

    middlePortion->AddSpacer(20);
    middlePortion->Add(playerOne);
    middlePortion->AddSpacer(270);
    middlePortion->Add(verticalfieldArea);
    middlePortion->AddSpacer(270);
    middlePortion->Add(playerThree);

    lowerPortion->AddSpacer(270);
    lowerPortion->Add(yourHand);

    theMainSizer->AddSpacer(45);
    theMainSizer->Add(upperPortion);
    theMainSizer->AddSpacer(20);
    theMainSizer->Add(middlePortion);
    theMainSizer->AddSpacer(20);
    theMainSizer->Add(lowerPortion,wxCENTER);
    SetSizerAndFit(theMainSizer);
  }


playArea::~playArea(){

}
