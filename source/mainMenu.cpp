#include "mainMenu.h"
#include "button.h"

#include "imageInsert.h"

// This panel is the main menu screen

mainMenu::mainMenu(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {

  wxBoxSizer *heartsContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *eightsContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *heartsLabelCont = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *eightsLabelCont = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *paneSizer = new wxBoxSizer(wxHORIZONTAL);

  SetFont(
      wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  // wxBoxSizer *wholeSizer = new wxBoxSizer(wxHORIZONTAL);

  imageInsert *theLogo =
      new imageInsert(this, wxT("../res/TextLogo.png"), wxBITMAP_TYPE_PNG,
                      screenInfo->getClientScreenSize().GetHeight() * .12,
                      screenInfo->getClientScreenSize().GetWidth() * .30);

  wxButton *heartsLocal = new wxButton(
      this, heartsLocalBtn, wxT("Hearts Local"), wxDefaultPosition,
      screenInfo->gamePlayBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *heartsOnline = new wxButton(
      this, heartsOnlineBtn, wxT("Hearts Online"), wxDefaultPosition,
      screenInfo->gamePlayBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsLocal = new wxButton(
      this, eightsLocalBtn, wxT("Eights Local"), wxDefaultPosition,
      screenInfo->gamePlayBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsOnline = new wxButton(
      this, eightsOnlineBtn, wxT("Eights Online"), wxDefaultPosition,
      screenInfo->gamePlayBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxCollapsiblePane *sidePane =
      new wxCollapsiblePane(this, wxID_ANY, "Menu", wxDefaultPosition,
                            screenInfo->sidePanelSize(), wxCP_NO_TLW_RESIZE);

  sidePane->SetFont(
      wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  heartsLabel = new wxStaticText(this, wxID_ANY, "HEARTS", wxDefaultPosition,
                                 wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
  eightsLabel =
      new wxStaticText(this, wxID_ANY, "CRAZY EIGHTS", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE | wxST_NO_AUTORESIZE);

  heartsLabel->SetForegroundColour(wxColour(255, 255, 255));
  eightsLabel->SetForegroundColour(wxColour(255, 255, 255));
  sidePane->SetForegroundColour(wxColour(255, 255, 255));

  heartsLabelCont->Add(heartsLabel, wxEXPAND);
  eightsLabelCont->Add(eightsLabel, wxEXPAND);
  heartsContainer->Add(heartsLocal, wxEXPAND);
  heartsContainer->Add(heartsOnline, wxEXPAND);
  eightsContainer->Add(eightsLocal, wxEXPAND);
  eightsContainer->Add(eightsOnline, wxEXPAND);

  // COLLAPSIBLE PANE///////////////////////////////////////////////////

  wxWindow *win = sidePane->GetPane();
  wxSizer *paneSz = new wxBoxSizer(wxVERTICAL);

  wxButton *settingsBtn = new wxButton(
      win, wxID_ANY, wxT("Settings"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *heartsRulesBtn = new wxButton(
      win, wxID_ANY, wxT("Hearts Rules"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsRulesBtn = new wxButton(
      win, wxID_ANY, wxT("Eights Rules"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *statsBtn = new wxButton(
      win, wxID_ANY, wxT("Game Stats"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *logOutBtn = new wxButton(
      win, wxID_ANY, wxT("Log Out"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

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

  heartsLocal->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  heartsLocal->SetForegroundColour(wxColour(wxT("WHITE")));

  heartsOnline->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  heartsOnline->SetForegroundColour(wxColour(wxT("WHITE")));

  eightsLocal->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsLocal->SetForegroundColour(wxColour(wxT("WHITE")));

  eightsOnline->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsOnline->SetForegroundColour(wxColour(wxT("WHITE")));

  theSizer->Add(theLogo);
  theSizer->AddSpacer(20);
  theSizer->Add(heartsLabelCont,
                wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
  theSizer->AddSpacer(20);
  theSizer->Add(heartsContainer);
  theSizer->AddSpacer(30);
  theSizer->Add(eightsLabelCont,
                wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
  theSizer->AddSpacer(20);
  theSizer->Add(eightsContainer);

  paneSizer->AddSpacer(50);
  paneSizer->Add(theSizer);
  paneSizer->AddSpacer(50);
  paneSizer->Add(sidePane);

  // paneSizer->Add(sidePane);

  // wholeSizer->Add(theSizer);
  // wholeSizer->Add(paneSizer);
  // wxButton *paneButton = new wxButton(this, testButton, wxT("TEST"),
  // wxDefaultPosition,
  //   wxSize(200,10), 0, wxDefaultValidator, wxButtonNameStr);
  //
  // wxWindow *win = sidePane->GetPane();
  // wxSizer *paneSz = new wxBoxSizer(wxVERTICAL);
  // paneSz->Add(paneButton);
  // win->SetSizer(paneSz);
  // paneSz->SetSizeHints(win);

  // paneSizer->Add(theSizer, wxALIGN_CENTER_HORIZONTAL);
  // paneSizer->Add(sidePane);

  SetSizerAndFit(paneSizer);
  // SetSizerAndFit(paneSizer);
  //  SetSizerAndFit(paneSizer);

  // SetSizerAndFit(eightsContainer);
  // Centre();
}

BEGIN_EVENT_TABLE(mainMenu, wxPanel)
// EVT_PAINT(mainMenu::paintingEvent)
EVT_PAINT(mainMenu::OnPaint)
END_EVENT_TABLE()
