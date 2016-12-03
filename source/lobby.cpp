#include "lobby.h"
#include "Simple.h"

#include "Messages/LobbyGame.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <wx/textdlg.h>

lobby::lobby(wxFrame *parent, wxString type)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = new clientInfo();
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *centerSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

  typeOfGame = type;
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

  newGameBut = new wxButton(this, newGameButton, wxT("New Game"),
                            wxDefaultPosition, screenInfo->lobbyButton(), 0,
                            wxDefaultValidator, wxButtonNameStr);
  newGameBut->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  newGameBut->SetForegroundColour(wxColour(wxT("WHITE")));

  joinGameBut = new wxButton(this, joinGameButton, wxT("Join Game"),
                             wxDefaultPosition, screenInfo->lobbyButton(), 0,
                             wxDefaultValidator, wxButtonNameStr);
  joinGameBut->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  joinGameBut->SetForegroundColour(wxColour(wxT("WHITE")));

  wxCollapsiblePane *sidePane =
      new wxCollapsiblePane(this, wxID_ANY, "Menu", wxDefaultPosition,
                            wxSize(800, 800), wxCP_NO_TLW_RESIZE);

  startGameBut = new wxButton(this, startGameButton, wxT("Start Game"),
                              wxDefaultPosition, screenInfo->lobbyButton(), 0,
                              wxDefaultValidator, wxButtonNameStr);
  startGameBut->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  startGameBut->SetForegroundColour(wxColour(wxT("WHITE")));
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

  buttonSizer->Add(newGameBut);
  buttonSizer->AddSpacer(screenInfo->lobbyButtonSpacer());
  buttonSizer->Add(joinGameBut);
  buttonSizer->Add(startGameBut);

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
  std::string sendMsg = "GET GAMES " + typeOfGame.ToStdString();
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedGames(receivedMsg);
}

void lobby::receivedGames(std::string msg) {
  std::cout << msg << std::endl;
  currentGames->ClearAll();
  std::stringstream ss(msg);
  boost::archive::text_iarchive coded(ss);
  std::vector<LobbyGame> decodedGames;
  coded &decodedGames;
  for (auto &&game : decodedGames) {
    std::cout << game.name << std::endl;
  }
}

void lobby::makeGame(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  wxTextEntryDialog dialog(
      NULL, "Please enter the name of the game you would like to create.",
      "Create a Game");
  dialog.ShowModal();
  auto response = dialog.GetValue();
  std::cout << response << std::endl;
  std::string sendMsg =
      "MAKE " + typeOfGame.ToStdString() + " " + response.ToStdString();
  std::cout << sendMsg << std::endl;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedMakeGameResponse(receivedMsg);
}

void lobby::receivedMakeGameResponse(std::string receivedMsg) {
  showGeneralDialogBox(receivedMsg);
  if (receivedMsg == "FAILURE : UNKNOWN GAME TYPE") {
    std::cout << "Somethin done gone wrong" << std::endl;
  } else if (receivedMsg == "FAILURE : ALREADY EXSISTS") {
    std::cout << "This game name already exists" << std::endl;
  } else if (receivedMsg == "SUCCESS") {
    std::cout << "Game created successfully" << std::endl;
    requestGames();
  }
}

void lobby::joinGame(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  wxTextEntryDialog dialog(
      NULL, "Please enter the name of the game you would like to join.",
      "Join a Game");
  dialog.ShowModal();
  auto response = dialog.GetValue();
  std::cout << response << std::endl;
  std::string sendMsg = "JOIN " + response.ToStdString();
  std::cout << sendMsg << std::endl;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedJoinGameResponse(receivedMsg);
}

void lobby::startGame(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  wxTextEntryDialog dialog(
      NULL, "Please enter the name of the game you would like to join.",
      "Join a Game");
  dialog.ShowModal();
  auto response = dialog.GetValue();
  std::cout << response << std::endl;
  std::string sendMsg = "START " + response.ToStdString();
  std::cout << sendMsg << std::endl;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedJoinGameResponse(receivedMsg);
}

void lobby::receivedJoinGameResponse(std::string receivedMsg) {
  showGeneralDialogBox(receivedMsg);
  if (receivedMsg == "FAILURE : GAME NOT FOUND") {
    std::cout << "Game could not be found" << std::endl;
  } else if (receivedMsg == "FAILURE : GAME FULL") {
    std::cout << "This game is full" << std::endl;
  } else if (receivedMsg == "SUCCESS") {
    std::cout << "Game joined successfully" << std::endl;
    requestGames();
  }
}

void lobby::receivedStartGameResponse(std::string receivedMsg) {
  showGeneralDialogBox(receivedMsg);
  if (receivedMsg == "FAILURE : GAME NOT FOUND") {
    std::cout << "Game could not be found";
  } else if (receivedMsg == "SUCCESS") {
    std::cout << "Game joined successfully" << std::endl;
    // TODO: link to appropriate in game screen.
  }
}

void lobby::showGeneralDialogBox(std::string msg) {
  wxMessageDialog dialog(NULL, msg);
  dialog.ShowModal();
}

lobby::~lobby() {}

wxBEGIN_EVENT_TABLE(lobby, wxPanel) EVT_PAINT(lobby::OnPaint)
    EVT_BUTTON(newGameButton, lobby::makeGame)
        EVT_BUTTON(joinGameButton, lobby::joinGame)
            EVT_BUTTON(startGameButton, lobby::startGame) END_EVENT_TABLE()
