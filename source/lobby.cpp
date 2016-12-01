#include "lobby.h"

lobby::lobby(wxFrame *parent, wxString typeOfGame)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = new clientInfo();
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *centerSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
  // wxBoxSizer *ctrlSizer = new wxBoxSizer(wxHORIZONTAL);

  wxBitmapButton *theLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  theLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));
  theLogo->SetWindowStyle(wxBORDER_NONE);
  // imageInsert *theLogo = new imageInsert(this, wxT("../res/TextLogo.png"),
  //  wxBITMAP_TYPE_PNG, 100, 200);

  wxStaticText *gameType =
      new wxStaticText(this, wxID_ANY, typeOfGame, wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
  gameType->SetForegroundColour(wxColour(255, 255, 255));
  gameType->SetFont(
      wxFont(40, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  availableGames *currentGames = new availableGames(this, wxSize(150, 300));
  // wxListCtrl *listCtrl = new wxListCtrl(this, wxNewId(), wxDefaultPosition,
  //                                       wxDefaultSize, wxLC_REPORT);
  // listCtrl->InsertColumn(0, _("Games"));
  // listCtrl->InsertColumn(1, _("# of players"));
  //
  // long index = listCtrl->InsertItem(0, _("John Smith"));
  // listCtrl->SetItem(index, 1, _("3 of 4"));

  // wxPanel *listPanel =
  //     new wxPanel(this, wxID_ANY, wxDefaultPosition,
  //                 wxSize((screenInfo->getClientScreenSize().GetWidth() *
  //                 .35),
  //                        (screenInfo->getClientScreenSize().GetHeight() *
  //                        .35)),
  //                 wxTAB_TRAVERSAL, wxPanelNameStr);
  // listPanel->SetBackgroundColour(wxColour(200, 20, 20));

  wxButton *newGame = new wxButton(this, wxID_ANY, wxT("New Game"),
                                   wxDefaultPosition, screenInfo->lobbyButton(),
                                   0, wxDefaultValidator, wxButtonNameStr);
  newGame->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  newGame->SetForegroundColour(wxColour(wxT("WHITE")));

  wxButton *joinGame = new wxButton(
      this, wxID_ANY, wxT("Join Game"), wxDefaultPosition,
      screenInfo->lobbyButton(), 0, wxDefaultValidator, wxButtonNameStr);
  joinGame->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  joinGame->SetForegroundColour(wxColour(wxT("WHITE")));

  wxCollapsiblePane *sidePane =
      new wxCollapsiblePane(this, wxID_ANY, "Menu", wxDefaultPosition,
                            wxSize(800, 800), wxCP_NO_TLW_RESIZE);

  // COLLAPSIBLE PANE///////////////////////////////////////////////////
  wxWindow *win = sidePane->GetPane();
  wxSizer *paneSz = new wxBoxSizer(wxVERTICAL);

  wxButton *settingsBtn =
      new wxButton(win, wxID_ANY, wxT("Settings"), wxDefaultPosition,
                   wxSize(660, 100), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *heartsRulesBtn =
      new wxButton(win, wxID_ANY, wxT("Hearts Rules"), wxDefaultPosition,
                   wxSize(600, 100), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsRulesBtn =
      new wxButton(win, wxID_ANY, wxT("Crazy Eights Rules"), wxDefaultPosition,
                   wxSize(600, 100), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *statsBtn =
      new wxButton(win, wxID_ANY, wxT("Game Stats"), wxDefaultPosition,
                   wxSize(600, 100), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *logOutBtn =
      new wxButton(win, wxID_ANY, wxT("Log Out"), wxDefaultPosition,
                   wxSize(660, 100), 0, wxDefaultValidator, wxButtonNameStr);

  win->SetBackgroundColour(wxColour(0, 0, 0));
  sidePane->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));

  settingsBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  settingsBtn->SetForegroundColour(wxColour(255, 255, 255));

  heartsRulesBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  heartsRulesBtn->SetForegroundColour(wxColour(255, 255, 255));

  eightsRulesBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsRulesBtn->SetForegroundColour(wxColour(255, 255, 255));

  statsBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  statsBtn->SetForegroundColour(wxColour(255, 255, 255));

  logOutBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  logOutBtn->SetForegroundColour(wxColour(255, 255, 255));

  paneSz->Add(settingsBtn);
  paneSz->Add(heartsRulesBtn);
  paneSz->Add(eightsRulesBtn);
  paneSz->Add(statsBtn);
  paneSz->Add(logOutBtn);

  win->SetSizer(paneSz);
  paneSz->SetSizeHints(win);

  // END COLLAPSIBLE PANE/////////////////////////////////////////////////////

  leftSizer->Add(theLogo);
  leftSizer->AddSpacer(40);

  buttonSizer->Add(newGame);
  buttonSizer->AddSpacer(screenInfo->lobbyButtonSpacer());
  buttonSizer->Add(joinGame);

  centerSizer->Add(gameType, wxEXPAND | wxALIGN_RIGHT);
  centerSizer->AddSpacer(screenInfo->getClientScreenSize().GetHeight() * .10);
  centerSizer->Add(currentGames, 1, wxEXPAND, 0);
  // centerSizer->Add(listPanel);
  centerSizer->AddSpacer(screenInfo->getClientScreenSize().GetHeight() * .10);
  centerSizer->Add(buttonSizer, wxEXPAND | wxALIGN_CENTER);

  mainSizer->Add(leftSizer);
  mainSizer->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .15);
  mainSizer->Add(centerSizer);
  mainSizer->Add(sidePane);
  // mainSizer->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .35);
  SetSizerAndFit(mainSizer);
  Center();
}

lobby::~lobby() {}

BEGIN_EVENT_TABLE(lobby, wxPanel)
EVT_PAINT(lobby::OnPaint)
END_EVENT_TABLE()
