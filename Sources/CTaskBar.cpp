// *****************************************************************************
// *                                                                           *
// *                      EASY MOVER ICONE TRAY SYSTEM                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 08/01/2006                                                           *
// *   CopyRight (c)Neophile 2006                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                         DEFINITION DES MEMBRES                            *
// *                                                                           *
// *****************************************************************************

#include "CTaskBar.h"

//#include "Global.h"

//------------------------------------------------------------------------------
// Déclaration des Evenements

wxBEGIN_EVENT_TABLE (CTaskBar, wxTaskBarIcon)
	EVT_TASKBAR_LEFT_DOWN	( CTaskBar::OnClick)
//	EVT_MENU				( ST_EXIT	, CTaskBar::OnExit)
	EVT_MENU				( ST_SHOW	, CTaskBar::OnShow)
	EVT_MENU				( ST_HIDE	, CTaskBar::OnHide)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// Evenement Click Gauche de la souris

void CTaskBar::OnClick (wxTaskBarIconEvent& WXUNUSED(event))
{
	if (Fenetre->IsShown())
	{
		Fenetre->Show(false);
	}
	else
	{
		Fenetre->Show(true);
		Fenetre->Raise();
	}
}

//------------------------------------------------------------------------------
// MEnu System Tray

wxMenu*	CTaskBar::CreatePopupMenu()
{
	wxMenu* Menu = new wxMenu;
	//Menu->Append (ST_EXIT,_("Exit ChatGlobal"),_("Close this App"));
	Menu->Append (ST_SHOW,_("Show ChatGlobal"), _("Recall to ForeGround"));
	Menu->Append (ST_HIDE,_("Hide the ChatGlobal"),_("Hide this app"));
	return Menu;
}

//------------------------------------------------------------------------------
// Menu Exit

/*void	CTaskBar::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Fenetre->Close();
	Destroy();
}*/

//------------------------------------------------------------------------------
// Menu Show

void	CTaskBar::OnShow(wxCommandEvent& WXUNUSED(event))
{
	Fenetre->Show(true);
	//Fenetre->Raise();
}

//------------------------------------------------------------------------------
// Menu Hide

void	CTaskBar::OnHide(wxCommandEvent& WXUNUSED(event))
{
	Fenetre->Show(false);
}
