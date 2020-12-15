// *****************************************************************************
// *                                                                           *
// *                      ChatGlobal FENETRE PRINCIPALE                        *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 22/04/2005                                                           *
// *   Modifié le 28/01/2007                                                   *
// *   CopyRight (c)Neophile 2005-2007                                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                         DEFINITION DES MEMBRES                            *
// *                                                                           *
// *****************************************************************************

#include <wx/numdlg.h>

#include "MainFrame.h"

#include "Global.h"

#include "OptionBox.h"
#include "AboutBox.h"
#include "XlgOptBox.h"
#include "PersoBox.h"

#include "chatglobal.xpm"
#include "connect.xpm"
#include "deco.xpm"
#include "droite.xpm"
#include "gauche.xpm"
#include "ndroite.xpm"
#include "ngauche.xpm"
#include "outils.xpm"
#include "perso.xpm"
#include "xelag_con.xpm"
#include "xelag_deco.xpm"

//------------------------------------------------------------------------------
// On Déclare les évenements à gêrer dans la fenêtre.

wxBEGIN_EVENT_TABLE (CMainFrame, wxFrame)
	EVT_MENU	(MF_MENU_BOT,		CMainFrame::OnBot)
	EVT_MENU	(MF_MENU_EXIT,		CMainFrame::OnExit)
	EVT_MENU	(MF_MENU_AWCONECT,	CMainFrame::OnConnectAw)
	EVT_MENU	(MF_MENU_AWOPTION,	CMainFrame::OnOptionsAw)
	EVT_MENU	(MF_MENU_XGCONECT,	CMainFrame::OnConnectXg)
	EVT_MENU	(MF_MENU_XGOPTION,	CMainFrame::OnOptionsXg)
	EVT_MENU	(MF_MENU_PERSO,		CMainFrame::OnPerso)
	EVT_MENU	(MF_MENU_LOG,		CMainFrame::OnLog)
	EVT_MENU	(MF_MENU_AIDE,		CMainFrame::OnAide)
	EVT_MENU	(MF_MENU_CENA,		CMainFrame::OnCielEna)
	EVT_MENU	(MF_MENU_CHORO,		CMainFrame::OnCielHoro)
	EVT_MENU	(MF_MENU_CCOLOR,	CMainFrame::OnCielColo)
	EVT_MENU	(MF_MENU_FORUM,		CMainFrame::OnForum)
	EVT_MENU	(MF_MENU_APROPOS,	CMainFrame::OnAPropos)
	EVT_MENU	(MF_BTN_GAU,		CMainFrame::OnBotInf)
	EVT_MENU	(MF_BTN_DRO,		CMainFrame::OnBotSup)
	EVT_TIMER	(MF_UPDATE,			CMainFrame::OnTUpdate)
	EVT_CLOSE	(					CMainFrame::OnCloseWindow)
	EVT_ICONIZE (CMainFrame::OnIconize)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// Constructeur

CMainFrame::CMainFrame
	(
		wxLocale& locale
	) : wxFrame
	(
		(wxWindow*)NULL,
		wxID_ANY,
		_T("ChatGlobal"),
		wxDefaultPosition,
		wxDefaultSize,
		wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU |
		wxCAPTION | wxCLOSE_BOX
	),
	m_locale (locale)
{
	pConfig = wxConfigBase::Get();
	Bot_Sel=0;
	ABot=0;
	AConnect=true;
	AXgConnect=true;
	SetIcon (chatglobal_xpm);
	TaskBar = new CTaskBar (this);
	TaskBar->SetIcon(chatglobal_xpm);

	int	x,y,w,h;
	pConfig->Read(_T("/Fenetre/prinx"), &x, 50),
	pConfig->Read(_T("/Fenetre/priny"), &y, 50),
	pConfig->Read(_T("/Fenetre/prinw"), &w, 450),
	pConfig->Read(_T("/Fenetre/prinh"), &h, 200);

	if ((x<1) || (y<1))
    {
        x=50;
        y=50;
    }
	SetSize(wxSize(w,h));
	SetPosition(wxPoint(x,y));

	Logger = CCtrlLog::Create(NombreBot);
	Logger->InitLog(this);
	FenLog = Logger->GetPage(Bot_Sel);
	Logger->Log(-1,CGVersion + _(" running."),_T("ORANGE"), true);
	CtrlAw =CCtrlAw::Create(NombreBot,this);
	if (CtrlAw->Init(true)) return;
	Bot = CtrlAw->GetBot   (Bot_Sel);
	Xelag = CtrlAw->GetXelag (Bot_Sel);
	Liste=CtrlAw->GetList (Bot_Sel);
// Construction du Menu
	MenuBot = new wxMenu;
	MenuBot->Append(MF_MENU_BOT ,_("Bot..."), _("Select a bot"));
	MenuBot->AppendSeparator ();
	MenuBot->Append(MF_MENU_EXIT, _("E&xit"), _("Exiting the ChatGLobal"));
	MenuAw = new wxMenu;
	MenuAw->Append (MF_MENU_AWCONECT, _("Connect"), _("Connecting AW"));
	MenuAw->Append (MF_MENU_AWOPTION, _("Setup"), _("AW Setup"));
	MenuXg = new wxMenu;
	MenuXg->Append (MF_MENU_XGCONECT, _("Connect"), _("Xelag Server Connection"));
	MenuXg->Append (MF_MENU_XGOPTION, _("Setup"), _("Xelag Server Setup"));
	MenuOptions = new wxMenu;
	MenuOptions->Append (MF_MENU_PERSO,_("Customing"), _("Custom the ChatGlobal"));
	MenuOptions->AppendCheckItem (MF_MENU_LOG, _("Log Tchat"),_("Tchat recording"));
	MenuCiel = new wxMenu;
	MenuCiel->AppendCheckItem (MF_MENU_CENA, _("Enable"), _("Enable the auto sky engine"));
	MenuCiel->Append (MF_MENU_CHORO,_("Timing"), _("Sun setting"));
	MenuCiel->Append (MF_MENU_CCOLOR, _("Colours"), _("Sky colours setting"));
	MenuAide = new wxMenu;
	MenuAide->Append (MF_MENU_AIDE,_("Help"), _("ChatGLobal Help"));
	MenuAide->Append (MF_MENU_FORUM, _("Forum"), _("Abyssia Bots Support"));
	MenuAide->Append (MF_MENU_APROPOS, _("About..."), _("About the ChatGlobal"));
	MenuBar  = new wxMenuBar;
	MenuBar->Append(MenuBot, _("Bots"));
	MenuBar->Append(MenuAw, _("Aw"));
	MenuBar->Append(MenuXg, _("XelagServer"));
	MenuBar->Append(MenuOptions,_("Tools"));
	MenuBar->Append(MenuCiel, _("Sky"));
	MenuBar->Append(MenuAide, _("?"));
	SetMenuBar (MenuBar);

	SizerPrin = new wxBoxSizer(wxHORIZONTAL);
	SizerPrin->Add(Liste, 1, wxEXPAND);
	SizerPrin->Add(FenLog, 2, wxEXPAND);
	SetSizer(SizerPrin);

// Construction de la toolbar
	Panel = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL);
	Panel->SetToolBitmapSize (wxSize (48,48));
	Panel->AddTool (MF_MENU_AWCONECT, _T("deco"), wxBitmap(deco_xpm), _("Connection"));
	Panel->AddTool ( MF_MENU_XGCONECT, _T("Xelag"), wxBitmap(xelag_deco_xpm), _("Connection"));
	Panel->AddTool ( MF_BTN_GAU, _T("ngauche"), wxBitmap(ngauche_xpm), _("Next bot"));
	Panel->AddTool ( MF_BTN_DRO, _T("ndroite"), wxBitmap(droite_xpm), _("Previous bot"));
	Panel->AddTool (MF_MENU_AWOPTION, _T("Options"), wxBitmap(outils_xpm), _("Options"));
	Panel->AddTool ( MF_MENU_PERSO, _T("Perso"), wxBitmap(perso_xpm), _("Customization"));
	Panel->Realize();
	CreateStatusBar(3);

	for (size_t i=0; i < NombreBot; i++)
	{
		CtrlAw->GetList(i)->Refresh();
		Logger->GetPage(i)->Refresh();
	}

	TUpdate=new wxTimer (this, MF_UPDATE);
	TUpdate->Start (100, false);
	for (size_t i=0; i < NombreBot; i++)
	{
		ChoixBot (i);
	}
	ChoixBot (0);
}


//------------------------------------------------------------------------------
// Fermeture Application

CMainFrame::~CMainFrame ()
{

	delete TaskBar;
}

//------------------------------------------------------------------------------

void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void CMainFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
	TUpdate->Stop();
	int x, y, w, h;
	if (IsMaximized())
	{
		Maximize(false);
	}
	if (IsIconized())
	{
	    Iconize (false);
	}
	GetSize(&w, &h);
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/prinx"), x);
	pConfig->Write(_T("/Fenetre/priny"), y);
	pConfig->Write(_T("/Fenetre/prinw"), w);
	pConfig->Write(_T("/Fenetre/prinh"), h);
	pConfig->Flush();
	CtrlAw->Init(false);
	CCtrlAw::Kill();
	Logger->Log(-1,CGVersion + _(" Stopped."), _T("VIOLET RED"), true);
	CCtrlLog::Kill();
    Destroy();
}

//------------------------------------------------------------------------------

void CMainFrame::OnConnectAw (wxCommandEvent& WXUNUSED(event))
{
	if (Bot->ModeReco)
	{
		wxMessageDialog BoiteOuiNon
		(
			this,
			_("Are you sure want abording attempts of reconnection?"),
			_("Warning"),
			wxYES_NO|wxICON_EXCLAMATION
		);
		if (BoiteOuiNon.ShowModal()==wxID_YES)
		{
			Bot->ModeReco=false;
			Logger->Log(Bot->GetID(),_("Abording Attempts of reconnections"),_T("RED"));
		}
	}
	else if (!Bot->IsOnWorld())
	{
		Bot->Global=true;
		Bot->Connect();
	}
	else
	{
		Bot->Deconnect();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnConnectXg (wxCommandEvent& WXUNUSED(event))
{
	if (Xelag->ModeReco)
	{
		wxMessageDialog BoiteOuiNon
		(
			this,
			_("Are you sure want abording attempts of reconnection?"),
			_("Warning"),
			wxYES_NO|wxICON_EXCLAMATION
		);
		if (BoiteOuiNon.ShowModal()==wxID_YES)
		{
			Xelag->ModeReco=false;
			Logger->Log(Bot->GetID(),_("Abording Attempts of reconnections"),_T("RED"));
		}
	}
	else if (!Xelag->IsOnXelag())
	{
		Xelag->Connect ();
	}
	else Xelag->Deconnect();
}

//------------------------------------------------------------------------------

void CMainFrame::OnOptionsAw (wxCommandEvent& WXUNUSED(event))
{
	COptDial Option
	(
		this,
		-1,
		Bot,
		_("Active Worlds Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Option.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnOptionsXg (wxCommandEvent& WXUNUSED(event))
{
	CXlgOpt Option
	(
		this,
		-1,
		Xelag,
		_("Xelagot server setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Option.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnPerso(wxCommandEvent& WXUNUSED(event))
{
	CPersoDial Perso
	(
		this,
		-1,
		Bot,
		_("Customing"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Perso.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnLog (wxCommandEvent& WXUNUSED(event))
{
	if (Logger->GetLog(Bot_Sel)) Logger->SetLog(Bot_Sel,false);
	else Logger->SetLog(Bot_Sel,true);
	MenuOptions->Check (MF_MENU_LOG, Logger->GetLog(Bot_Sel));
	Bot->Sauve();
}

//------------------------------------------------------------------------------

void CMainFrame::OnCielEna (wxCommandEvent& WXUNUSED(event))
{
	if (Bot->Ciel->Enabled)
	{
		Bot->Ciel->Enabled=false;
		Logger->Log(Bot_Sel,_("Auto Sky Disabled"),_T("ORANGE"));
	}
	else
	{
		Bot->Ciel->Enabled=true;
		Logger->Log(Bot_Sel,_("Auto Sky Enabled"),_T("ORANGE"));
	}
	MenuCiel->Check (MF_MENU_CENA, Bot->Ciel->Enabled);
	Bot->Ciel->Sauve ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnCielHoro (wxCommandEvent& WXUNUSED(event))
{
	CCHorBox HorBox
	(
		this,
		-1,
		Bot->Ciel,
		_("Sun Time Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	HorBox.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnCielColo (wxCommandEvent& WXUNUSED(event))
{
	CCColBox ColBox
	(
		this,
		-1,
		Bot->Ciel,
		_("Sky Color Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	ColBox.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnAide (wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser (_("https://sourceforge.net/projects/chatglobal/"));

}

//------------------------------------------------------------------------------

void CMainFrame::OnForum (wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser (_("https://sourceforge.net/projects/chatglobal/"));
}

//------------------------------------------------------------------------------

void CMainFrame::OnAPropos (wxCommandEvent& WXUNUSED(event))
{
	AboutBox aboutDialog	(	this,
								-1,
								_("About..."),
								wxPoint(100,100),
								wxSize(300,300),
								wxDEFAULT_DIALOG_STYLE
							);
	aboutDialog.ShowModal();
}

//------------------------------------------------------------------------------
// Methode de choix de bot

void CMainFrame::OnBot (wxCommandEvent& WXUNUSED(event))
{
	long num;
	wxString S;
	S.Printf(_("Please Select a bot ( 1 -> %d):"), NombreBot );
	num = wxGetNumberFromUser ( _T(""), S, _("Bot Selection..."), (long)(Bot_Sel+1), 1l, (long)NombreBot);
	if (num!=(-1)) ChoixBot ((int)(num-1));
}

//------------------------------------------------------------------------------
// On Choisi le bot supérieur

void CMainFrame::OnBotSup (wxCommandEvent& WXUNUSED(event))
{
	if (Bot_Sel<(NombreBot-1))
	{
		ChoixBot (Bot_Sel+1);
	}
}

//------------------------------------------------------------------------------
// On Choisi le bot inférieur

void CMainFrame::OnBotInf (wxCommandEvent& WXUNUSED(event))
{
	if (Bot_Sel>0)
	{
		ChoixBot (Bot_Sel-1);
	}
}

//------------------------------------------------------------------------------
// Selection du bot

void CMainFrame::ChoixBot (int NumBot)
{
	wxWindow* OldFenLog=FenLog;
	wxWindow* OldListe=Liste;
	if (NumBot<0) NumBot =0;
	if (NumBot>=NombreBot) NumBot=NombreBot-1;
	Bot_Sel = NumBot;
	Bot=CtrlAw->GetBot(Bot_Sel);
	Xelag = CtrlAw->GetXelag (Bot_Sel);
	FenLog=Logger->GetPage(Bot_Sel);
	Liste=CtrlAw->GetList(Bot_Sel);
	OldFenLog->Show(false);
	OldListe->Show(false);
	SizerPrin->Replace(OldListe,Liste);
	SizerPrin->Replace(OldFenLog, FenLog);
	Layout();
	FenLog->Show(true);
	Liste->Show(true);
}

//------------------------------------------------------------------------------
// Mise a jour périodique des éléments dynamiques de la fenêtre principale

void CMainFrame::OnTUpdate (wxTimerEvent& WXUNUSED(event))
{
	wxString s,t;
	// Mise à jour du titre d'application
	t.Printf (_T("Bot %d"),Bot_Sel+1);
	s.Append(_T("Chat Global"));
	s.Append(_T(" : "));
	s.Append(t);
	s.Append(_T(" : "));
	s.Append(Bot->Nom);
	this->SetTitle(s);

	// Mise à jour des icones de connection
	if ((Bot->IsOnWorld())&&(!AConnect))
	{
		MenuBar->SetLabel (MF_MENU_AWCONECT, _("Disconnect"));
		MenuBar->SetHelpString (MF_MENU_AWCONECT, _("AW Disconnection"));
		s=_("Connected on world ");
		s.Append(Bot->Monde);
		SetStatusText (s , 1);
		Panel->DeleteTool (MF_MENU_AWCONECT);
		Panel->InsertTool ( 0, MF_MENU_AWCONECT,_T(""), wxBitmap(connect_xpm));
		AConnect=true;
		Panel->Realize();
	}
	else if ((!Bot->IsOnWorld())&&(AConnect))
	{
		MenuBar->SetLabel (MF_MENU_AWCONECT, _("Connect"));
		MenuBar->SetHelpString (MF_MENU_AWCONECT, _("Connecting AW"));
		s=_("Disconnected from AW");
		SetStatusText (s , 1);
		Panel->DeleteTool (MF_MENU_AWCONECT);
		Panel->InsertTool ( 0, MF_MENU_AWCONECT,_T(""), wxBitmap(deco_xpm));
		AConnect=false;
		Panel->Realize();
	}
	if ((Xelag->IsOnXelag())&&(!AXgConnect))
	{
		MenuBar->SetLabel (MF_MENU_XGCONECT, _("Disconnect"));
		MenuBar->SetHelpString (MF_MENU_XGCONECT,_("Xelag Server disconnection"));
		s=_("Connected on Xelag Server");
		SetStatusText (s , 2);
		Panel->DeleteTool (MF_MENU_XGCONECT);
		Panel->InsertTool ( 1, MF_MENU_XGCONECT,_T(""), wxBitmap(xelag_con_xpm));
		AXgConnect=true;
		Panel->Realize();
	}
	else if ((!Xelag->IsOnXelag())&&(AXgConnect))
	{
		MenuBar->SetLabel (MF_MENU_XGCONECT, _("Connect"));
		MenuBar->SetHelpString (MF_MENU_XGCONECT, _("Xelag Server Connection"));
		s=_("Disconnected from Xelag Server");
		SetStatusText (s , 2);
		Panel->DeleteTool (MF_MENU_XGCONECT);
		Panel->InsertTool ( 1, MF_MENU_XGCONECT,_T(""), wxBitmap(xelag_deco_xpm));
		AXgConnect=false;
		Panel->Realize();
	}
	// Mise à jour des icones de séléction de bot
	if (ABot != Bot_Sel)
	{
		Panel->DeleteTool (MF_BTN_GAU);

		if (Bot_Sel==0) Panel->InsertTool ( 2, MF_BTN_GAU,_T(""), wxBitmap(ngauche_xpm));
		else Panel->InsertTool ( 2, MF_BTN_GAU,_T(""), wxBitmap(gauche_xpm));
		Panel->Realize();

		Panel->DeleteTool (MF_BTN_DRO);

		if (Bot_Sel==(NombreBot-1)) Panel->InsertTool ( 3, MF_BTN_DRO,_T(""), wxBitmap(ndroite_xpm));
		else Panel->InsertTool ( 3, MF_BTN_DRO,_T(""), wxBitmap(droite_xpm));
		ABot=Bot_Sel;
		Panel->Realize();
	}

	// Mise à jour de l'état du menu de choix d'enregistrement de log
	if (Logger->GetLog(Bot_Sel)) MenuOptions->Check (MF_MENU_LOG, true);
	else MenuOptions->Check (MF_MENU_LOG, false);

	// Mise à jour de l'état du menu de choix d'activation du ciel
	if (Bot->Ciel->Enabled) MenuCiel->Check (MF_MENU_CENA, true);
	else MenuCiel->Check (MF_MENU_CENA, false);
}

//------------------------------------------------------------------------------
// On place la fenetre dans le system tray

void CMainFrame::OnIconize (wxIconizeEvent& WXUNUSED(event))
{
	Iconize (false);
	Show(false);
}
