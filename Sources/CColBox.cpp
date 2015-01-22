// *****************************************************************************
// *                                                                           *
// *                   BOITE DE DIALOGUE COULEURS DU CIEL                      *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Neophile                                                      *
// *   Le 31/01/2007                                                           *
// *   CopyRight (c)Neophile 2007                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#include "CColBox.h"
#include <wx/colordlg.h>

#include "Global.h"

wxBEGIN_EVENT_TABLE (CCColBox, wxDialog)
	EVT_BUTTON		(CC_NA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_NJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_NC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_NN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_SA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_SJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_SC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_SN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_EA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_EJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_EC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_EN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_OA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_OJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_OC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_ON, CCColBox::OnColClick)
	EVT_BUTTON		(CC_ZA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_ZJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_ZC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_ZN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_LUMA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_LUMJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_LUMC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_LUMN, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DIRA, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DIRJ, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DIRC, CCColBox::OnColClick)
	EVT_BUTTON		(CC_DIRN, CCColBox::OnColClick)
	EVT_BUTTON		(wxID_OK, CCColBox::OnOk)
wxEND_EVENT_TABLE()

CCColBox::CCColBox
	(
		wxWindow* parent,
		wxWindowID id,
		CCiel* PtCiel,
		const wxString &title,
		const wxPoint &position,
		const wxSize &size,
		long style
	)	:
	wxDialog
	(
		parent,
		id,
		title,
		position,
		size,
		style
	)
{
	pConfig = wxConfigBase::Get();
	wxString s;
	Ciel=PtCiel;
	item0 = new wxBoxSizer( wxVERTICAL );
	item1 = new wxBoxSizer( wxHORIZONTAL );
	item2 = new wxBoxSizer( wxVERTICAL );
	item3 = new wxStaticText( this, -1, _T(""), wxDefaultPosition, wxSize(40,20), 0 );
    item4 = new wxStaticText( this, -1, _("Morning:"), wxDefaultPosition, wxSize(40,20), 0 );
	item5 = new wxStaticText( this, -1, _("Day:"), wxDefaultPosition, wxSize(40,20), 0 );
	item6 = new wxStaticText( this, -1, _("Evening:"), wxDefaultPosition, wxSize(40,20), 0 );
	item7 = new wxStaticText( this, -1, _("Night:"), wxDefaultPosition, wxSize(40,20), 0 );
	item8 = new wxBoxSizer( wxVERTICAL );
	item9 = new wxStaticText( this, -1, _("North"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item10 = new wxButton( this, CC_NA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item11 = new wxButton( this, CC_NJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item12 = new wxButton( this, CC_NC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item13 = new wxButton( this, CC_NN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item10->SetBackgroundColour(Ciel->AN);
	item11->SetBackgroundColour(Ciel->JN);
	item12->SetBackgroundColour(Ciel->CN);
	item13->SetBackgroundColour(Ciel->NN);
	item15 = new wxStaticText( this, -1, _("South"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item14 = new wxBoxSizer( wxVERTICAL );
	item16 = new wxButton( this, CC_SA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item17 = new wxButton( this, CC_SJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item18 = new wxButton( this, CC_SC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item19 = new wxButton( this, CC_SN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item16->SetBackgroundColour(Ciel->AS);
	item17->SetBackgroundColour(Ciel->JS);
	item18->SetBackgroundColour(Ciel->CS);
	item19->SetBackgroundColour(Ciel->NS);
	item20 = new wxBoxSizer( wxVERTICAL );
	item21 = new wxStaticText( this, -1, _("East"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item22 = new wxButton( this, CC_EA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item23 = new wxButton( this, CC_EJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item24 = new wxButton( this, CC_EC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item25 = new wxButton( this, CC_EN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item22->SetBackgroundColour(Ciel->AE);
	item23->SetBackgroundColour(Ciel->JE);
	item24->SetBackgroundColour(Ciel->CE);
	item25->SetBackgroundColour(Ciel->NE);
	item26 = new wxBoxSizer( wxVERTICAL );
	item27 = new wxStaticText( this, -1, _("West"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item28 = new wxButton( this, CC_OA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item29 = new wxButton( this, CC_OJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item30 = new wxButton( this, CC_OC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item31 = new wxButton( this, CC_ON, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item28->SetBackgroundColour(Ciel->AO);
	item29->SetBackgroundColour(Ciel->JO);
	item30->SetBackgroundColour(Ciel->CO);
	item31->SetBackgroundColour(Ciel->NO);
	item32 = new wxBoxSizer( wxVERTICAL );
	item33 = new wxStaticText( this, -1, _("Zenith"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item34 = new wxButton( this, CC_ZA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item35 = new wxButton( this, CC_ZJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item36 = new wxButton( this, CC_ZC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item37 = new wxButton( this, CC_ZN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item34->SetBackgroundColour(Ciel->AZ);
	item35->SetBackgroundColour(Ciel->JZ);
	item36->SetBackgroundColour(Ciel->CZ);
	item37->SetBackgroundColour(Ciel->NZ);
	item38 = new wxBoxSizer( wxVERTICAL );
	item39 = new wxStaticText( this, -1, _("Nadir"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item40 = new wxButton( this, CC_DA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item41 = new wxButton( this, CC_DJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item42 = new wxButton( this, CC_DC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item43 = new wxButton( this, CC_DN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item40->SetBackgroundColour(Ciel->AD);
	item41->SetBackgroundColour(Ciel->JD);
	item42->SetBackgroundColour(Ciel->CD);
	item43->SetBackgroundColour(Ciel->ND);
	item44 = new wxBoxSizer( wxVERTICAL );
	item45 = new wxStaticText( this, -1, _("Amb"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item46 = new wxButton( this, CC_LUMA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item47 = new wxButton( this, CC_LUMJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item48 = new wxButton( this, CC_LUMC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item49 = new wxButton( this, CC_LUMN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item46->SetBackgroundColour(Ciel->AA);
	item47->SetBackgroundColour(Ciel->JA);
	item48->SetBackgroundColour(Ciel->CA);
	item49->SetBackgroundColour(Ciel->NA);
	item50 = new wxBoxSizer( wxVERTICAL );
	item51 = new wxStaticText( this, -1, _("Direc"), wxDefaultPosition, wxSize(40,20), wxALIGN_CENTRE );
	item52 = new wxButton( this, CC_DIRA, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item53 = new wxButton( this, CC_DIRJ, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item54 = new wxButton( this, CC_DIRC, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item55 = new wxButton( this, CC_DIRN, _T(""), wxDefaultPosition, wxSize(20,20), 0 );
	item52->SetBackgroundColour(Ciel->AL);
	item53->SetBackgroundColour(Ciel->JL);
	item54->SetBackgroundColour(Ciel->CL);
	item55->SetBackgroundColour(Ciel->NL);
	item56 = new wxBoxSizer( wxHORIZONTAL );
	item57 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	item58 = new wxButton( this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0 );

	item2->Add( item3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item2->Add( item4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item2->Add( item5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item2->Add( item6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item2->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item1->Add( item2, 0, wxALIGN_CENTER, 0 );
	item8->Add( item9, 0, wxALIGN_CENTER, 0 );
	item8->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item8->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );
	item8->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item8->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item8, 0, wxALIGN_CENTER|wxALL, 0 );
	item14->Add( item15, 0, wxALIGN_CENTER|wxALL, 0 );
	item14->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );
	item14->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );
	item14->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item14->Add( item19, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item14, 0, wxALIGN_CENTER, 0 );
	item20->Add( item21, 0, wxALIGN_CENTER, 5 );
	item20->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item23, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item25, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item20, 0, wxALIGN_CENTER, 0 );
	item26->Add( item27, 0, wxALIGN_CENTER, 5 );
	item26->Add( item28, 0, wxALIGN_CENTER|wxALL, 5 );
	item26->Add( item29, 0, wxALIGN_CENTER|wxALL, 5 );
	item26->Add( item30, 0, wxALIGN_CENTER|wxALL, 5 );
	item26->Add( item31, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item26, 0, wxALIGN_CENTER, 0 );
	item32->Add( item33, 0, wxALIGN_CENTER, 5 );
	item32->Add( item34, 0, wxALIGN_CENTER|wxALL, 5 );
	item32->Add( item35, 0, wxALIGN_CENTER|wxALL, 5 );
	item32->Add( item36, 0, wxALIGN_CENTER|wxALL, 5 );
	item32->Add( item37, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item32, 0, wxALIGN_CENTER, 0 );
	item38->Add( item39, 0, wxALIGN_CENTER, 5 );
	item38->Add( item40, 0, wxALIGN_CENTER|wxALL, 5 );
	item38->Add( item41, 0, wxALIGN_CENTER|wxALL, 5 );
	item38->Add( item42, 0, wxALIGN_CENTER|wxALL, 5 );
	item38->Add( item43, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item38, 0, wxALIGN_CENTER, 0 );
	item44->Add( item45, 0, wxALIGN_CENTER, 5 );
	item44->Add( item46, 0, wxALIGN_CENTER|wxALL, 5 );
	item44->Add( item47, 0, wxALIGN_CENTER|wxALL, 5 );
	item44->Add( item48, 0, wxALIGN_CENTER|wxALL, 5 );
	item44->Add( item49, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item44, 0, wxALIGN_CENTER, 0 );
	item50->Add( item51, 0, wxALIGN_CENTER, 5 );
	item50->Add( item52, 0, wxALIGN_CENTER|wxALL, 5 );
	item50->Add( item53, 0, wxALIGN_CENTER|wxALL, 5 );
	item50->Add( item54, 0, wxALIGN_CENTER|wxALL, 5 );
	item50->Add( item55, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item50, 0, wxALIGN_CENTER, 0 );
	item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );
	item56->Add( item57, 0, wxALIGN_CENTER|wxALL, 5 );
	item56->Add( item58, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item56, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	SetAutoLayout (true);
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x = pConfig->Read(_T("/Fenetre/ColCielx"), 50),
		y = pConfig->Read(_T("/Fenetre/ColCiely"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

CCColBox::~CCColBox ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/ColCielx"), x);
	pConfig->Write(_T("/Fenetre/ColCiely"), y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

bool CCColBox::Validate()
{
	return true;
}

//------------------------------------------------------------------------------

void CCColBox::OnOk(wxCommandEvent& WXUNUSED(event))
{
	Ciel->AN=item10->GetBackgroundColour();
	Ciel->JN=item11->GetBackgroundColour();
	Ciel->CN=item12->GetBackgroundColour();
	Ciel->NN=item13->GetBackgroundColour();
	Ciel->AS=item16->GetBackgroundColour();
	Ciel->JS=item17->GetBackgroundColour();
	Ciel->CS=item18->GetBackgroundColour();
	Ciel->NS=item19->GetBackgroundColour();
	Ciel->AE=item22->GetBackgroundColour();
	Ciel->JE=item23->GetBackgroundColour();
	Ciel->CE=item24->GetBackgroundColour();
	Ciel->NE=item25->GetBackgroundColour();
	Ciel->AO=item28->GetBackgroundColour();
	Ciel->JO=item29->GetBackgroundColour();
	Ciel->CO=item30->GetBackgroundColour();
	Ciel->NO=item31->GetBackgroundColour();
	Ciel->AZ=item34->GetBackgroundColour();
	Ciel->JZ=item35->GetBackgroundColour();
	Ciel->CZ=item36->GetBackgroundColour();
	Ciel->NZ=item37->GetBackgroundColour();
	Ciel->AD=item40->GetBackgroundColour();
	Ciel->JD=item41->GetBackgroundColour();
	Ciel->CD=item42->GetBackgroundColour();
	Ciel->ND=item43->GetBackgroundColour();
	Ciel->AA=item46->GetBackgroundColour();
	Ciel->JA=item47->GetBackgroundColour();
	Ciel->CA=item48->GetBackgroundColour();
	Ciel->NA=item49->GetBackgroundColour();
	Ciel->AL=item52->GetBackgroundColour();
	Ciel->JL=item53->GetBackgroundColour();
	Ciel->CL=item54->GetBackgroundColour();
	Ciel->NL=item55->GetBackgroundColour();
	Ciel->Sauve ();
	Ciel->Top=-1;
	EndModal (true);
}

void CCColBox::OnColClick (wxCommandEvent & event)
{
	wxButton* Bouton = (wxButton*)event.GetEventObject ();
	BCouleur.SetColour(Bouton->GetBackgroundColour());
	wxColourDialog ColorDiag (this, &BCouleur);
	ColorDiag.ShowModal();
	BCouleur=ColorDiag.GetColourData();
	Bouton->SetBackgroundColour(BCouleur.GetColour());
}
