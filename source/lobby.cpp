#include "lobby.h"
#include "Simple.h"

#include "Messages/LobbyGame.hpp"
#include <boost/archive/text_iarchive.hpp>

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

  currentGames = new availableGames(this, wxSize(150, 300));

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

void lobby::requestGames() {
  Simple *mainFrame = (Simple *)GetParent();

  std::string sendMsg = "GET GAMES";
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedGames(receivedMsg);
}

void lobby::receivedGames(std::string msg) {
  std::cout << msg << std::endl;
  currentGames->ClearAll();
  std::stringstream ss(msg);
  boost::archive::text_iarchive coded(ss);

  // std::vector<LobbyGame> decodedGames;
  // std::string game;
  //
  // while (!ss.eof()){
  //   std::string game;
  //   for (int i=0; i<3; i++){
  //     coded >> game;
  //   }
  //
  // }
  // while (!ss.eof()) {
  // LobbyGame tmp;
  // coded >> tmp;
  // decodedGames.push_back(tmp);
  // //}
  // // coded >> decodedGame;
  // for (auto &&game : decodedGames) {
  //   std::cout << game.name << std::endl;
  // }

  // while (!)
  // while (!ss.eof()) {
  //   ss >> game;
  //   std::cout << "!" << game << "!" << std::endl;
  // }
  // Need to check the format of ss but essentially we want to append game to
  // availableGames.
  // long index = this->InsertItem(0, _("GameName"));
  // this->SetItem(index, position in availableGames , _("3 of 4"));
}

// I didn't make some sort of dialog for this :(
void lobby::makeGame() {
  Simple *mainFrame = (Simple *)GetParent();
  std::string sendMsg = "MAKE HEARTS";
  auto receivedMsg = mainFrame->getResponse();
  if (receivedMsg == "FAILURE : UNKNOWN GAME TYPE") {
    std::cout << "Somethin done gone wrong" << std::endl;
  } else if (receivedMsg == "FAILURE : ALREADY EXSISTS") {
    std::cout << "This game name already exists" << std::endl;
  } else if (receivedMsg == "SUCCESS") {
    // somehow drop into game
  }
}

void lobby::joinGame() {
  Simple *mainFrame = (Simple *)GetParent();
  // Get game title it should be like selected item in wxListCtrl
  std::string desiredGame = "girls";
  std::string sendMsg = "JOIN " + desiredGame;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  // Do something???
}

lobby::~lobby() {}

BEGIN_EVENT_TABLE(lobby, wxPanel)
EVT_PAINT(lobby::OnPaint)
END_EVENT_TABLE()
