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

  // wxBoxSizer *wholeSizer = new wxBoxSizer(wxHORIZONTAL);

  SetFont(
      wxFont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  imageInsert *theLogo =
      new imageInsert(this, wxT("textLogo.png"), wxBITMAP_TYPE_PNG, 100, 200);

  wxButton *heartsLocal =
      new wxButton(this, heartsLocalBtn, wxT("Hearts Local"), wxDefaultPosition,
                   wxSize(200, 200), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *heartsOnline = new wxButton(
      this, heartsOnlineBtn, wxT("Hearts Online"), wxDefaultPosition,
      wxSize(200, 200), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsLocal =
      new wxButton(this, eightsLocalBtn, wxT("Eights Local"), wxDefaultPosition,
                   wxSize(200, 200), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsOnline = new wxButton(
      this, eightsOnlineBtn, wxT("Eights Online"), wxDefaultPosition,
      wxSize(200, 200), 0, wxDefaultValidator, wxButtonNameStr);

  wxCollapsiblePane *sidePane = new wxCollapsiblePane(this, wxID_ANY, "Menu");

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

  heartsLocal->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  heartsLocal->SetForegroundColour(wxColour(wxT("WHITE")));

  heartsOnline->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  heartsOnline->SetForegroundColour(wxColour(wxT("WHITE")));

  eightsLocal->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsLocal->SetForegroundColour(wxColour(wxT("WHITE")));

  eightsOnline->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsOnline->SetForegroundColour(wxColour(wxT("WHITE")));

  theSizer->Add(theLogo);

  theSizer->Add(heartsLabelCont,
                wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
  theSizer->AddSpacer(20);
  theSizer->Add(heartsContainer);
  theSizer->AddSpacer(30);
  theSizer->Add(eightsLabelCont,
                wxSizerFlags(0).Align(wxALIGN_CENTER_HORIZONTAL));
  theSizer->AddSpacer(20);
  theSizer->Add(eightsContainer);

  paneSizer->Add(theSizer);
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
