// *****************************************************************************
// *                                                                           *
// *                            CLASS LIST USER                                *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 25/03/2006                                                           *
// *   CopyRight (c)Neophile 2005-2006                                         *
// *                                                                           *
// *   Modifié le 07/09/2006                                                   *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                         DEFINITION DES MEMBRES                            *
// *                                                                           *
// *****************************************************************************

#include "CListUser.h"

#include "ps_s.xpm"
#include "roi_s.xpm"
#include "ct_s.xpm"
#include "blanc_s.xpm"

wxBEGIN_EVENT_TABLE(CListUser, wxListCtrl)
	EVT_LIST_ITEM_RIGHT_CLICK	(LU_LISTCTRL, CListUser::On_Right_Click)
	EVT_MENU					(LU_MUTEUSER, CListUser::On_Mute)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------

CListUser::CListUser
		(
			wxWindow* parent,
			CBotCG*	pBot
		)
		: wxListCtrl
		(
			parent,
			LU_LISTCTRL,
			wxDefaultPosition,
			wxDefaultSize,
			wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_ALIGN_LEFT
		)
{
	Bot = pBot;
	Images = new wxImageList (16,16,true);
	Images->Add (wxIcon( blanc_s_xpm ));
	Images->Add (wxIcon( roi_s_xpm ));
	Images->Add (wxIcon( ct_s_xpm ));
	Images->Add (wxIcon( ps_s_xpm ));
	SetImageList(Images, wxIMAGE_LIST_SMALL);
	SetBackgroundColour(wxColour(254,235,200));
	wxListItem ItemCol;
	ItemCol.SetText(_("Users"));
	ItemCol.SetAlign(wxLIST_FORMAT_LEFT);
	InsertColumn(0, ItemCol);
	SetColumnWidth (0,80);
}

//------------------------------------------------------------------------------

CListUser::~CListUser ()
{
}

//------------------------------------------------------------------------------

int CListUser::Ajoute (CUser Utilisateur)
{
	if (Utilisateur.Nom==_T("")) return -1;
	InsertItem (GetItemCount(),Utilisateur.Nom);
	return 0;
}

//------------------------------------------------------------------------------

int CListUser::Supprime (CUser Utilisateur)
{
	long pos;
	pos=FindItem (-1,Utilisateur.Nom,false);
	if (pos<0) return -1;
	DeleteItem (pos);
	return 0;
}

//------------------------------------------------------------------------------

int CListUser::Change (CUser Utilisateur)
{
	long pos;
	if (Utilisateur.Nom==_T("")) return -1;
	pos=FindItem (-1,Utilisateur.Nom,false);
	if (pos<0) return -1;
	SetItemText (pos, Utilisateur.Nom);
	return 0;
}



//------------------------------------------------------------------------------

void CListUser::EffaceTout ()
{
	DeleteAllItems();
}

//------------------------------------------------------------------------------

void CListUser::MajIcones ()
{
	int ID=0;
	wxString Citizen,Privilege;
	for (CUser User : Bot->Users)
	{
		Citizen.Printf(_T("%d"), User.Citizen);
		Citizen=_T("[")+Citizen+_T("]");
		Privilege.Printf(_T("%d"), User.Privilege);
		Privilege=_T("[")+Privilege+_T("]");
		ID=FindItem (-1, User.Nom,false);
		if (Bot->OwnerList.Contains (Citizen))
		{
			SetItemTextColour (ID, wxColour (_T("BLUE")));
			SetItemImage (ID, 1);
		}
		else if (Bot->OwnerList.Contains (Privilege))
		{
			SetItemTextColour (ID, wxColour (_T("BLUE")));
			SetItemImage (ID, 2);
		}
		else if (Bot->PSList.Contains (Citizen))
		{
			SetItemTextColour (ID, wxColour (_T("RED")));
			SetItemImage (ID, 3);
		}
		else if (Citizen == _T("0"))
		{
			SetItemImage (ID, 0);
			SetItemTextColour (ID, wxColour (_T("GREY")));
		}
		else
		{
			SetItemTextColour (ID, wxColour (_T("BLACK")));
			SetItemImage (ID, 0);
		}
	}
}

void CListUser::On_Right_Click (wxListEvent& event)
{
	int i=event.GetIndex();
	wxPoint Position;
	wxRect Rectangle;
	wxString Label;
	GetItemPosition (i, Position);
	GetItemRect (i, Rectangle);

	int ID=Bot->GetUserID(GetItemText(i));
	if (ID > -1)
	{
		Menu = new wxMenu;
		Menu -> Append(LU_NOM ,Bot->Users[ID].Nom );
		Label.Printf (_("Citizen : %d"), Bot->Users[ID].Citizen);
		Menu -> Append(-1 , Label );
		Label.Printf (_("Privs : %d"), Bot->Users[ID].Privilege);
		Menu -> Append(-1 , Label );
		Menu -> Append(-1 , Bot->Users[ID].IP);
		Menu -> Append(-1 , CoordToAw (Bot->Users[ID].X, Bot->Users[ID].Z));
		Label.Printf (_("Altitude =%d m"), Bot->Users[ID].Y / 100);
		Menu -> Append(-1 , Label);
		Menu->AppendSeparator();
		Menu->AppendCheckItem (LU_MUTEUSER, _("Mute"));
		if (Bot->DBase->GetMuteMode(Bot->DBase->Search(Bot->Users[ID].Nom.Upper()))) Menu->Check (LU_MUTEUSER,true);
		else Menu->Check (LU_MUTEUSER,false);
		PopupMenu (Menu,Position.x + Rectangle.width, Position.y) ;
		delete Menu;
	}
}

//------------------------------------------------------------------------------

void CListUser::On_Mute (wxCommandEvent& WXUNUSED(event))
{
	if (Menu)
	{
		wxString Nom=Menu->GetLabel(LU_NOM);
		int i=Bot->DBase->Search(Nom.Upper());
		if (i>(-1))
		{
			if (Menu->IsChecked(LU_MUTEUSER)) Bot->DBase->SetMuteMode(i,false);
			else Bot->DBase->SetMuteMode(i,true);
		}
	}
}
