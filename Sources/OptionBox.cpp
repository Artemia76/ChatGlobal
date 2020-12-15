// *****************************************************************************
// *                                                                           *
// *                     BOITE DE DIALOGUE DES OPTIONS                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 22/04/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "OptionBox.h"

BEGIN_EVENT_TABLE (COptDial, wxDialog)
	EVT_BUTTON ( wxID_OK, COptDial::OnOk)
	EVT_TEXT ( ID_PORT, COptDial::OnPortChange)
	EVT_TEXT ( ID_PORT, COptDial::OnPortChange)
	EVT_TEXT ( ID_TPSRECO, COptDial::OnDelaiChange)
	EVT_TEXT ( ID_NBESSAIS, COptDial::OnRetryChange)
END_EVENT_TABLE()


COptDial::COptDial
	(
		wxWindow* parent,
		wxWindowID id,
		CBotCG* Robot,
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
	Bot=Robot;
	FirstPort=true;
	FirstDelai=true;
	FirstRetry=true;
// Création des Items
	item0 = new wxBoxSizer( wxVERTICAL );
	item1 = new wxBoxSizer( wxHORIZONTAL );
	s.Printf(_T("%d"),Bot->Citoyen);
	item2 = new wxStaticText( this, ID_TEXT, _("Citizen :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	item3 = new wxTextCtrl( this, ID_CITOYEN, s , wxDefaultPosition, wxSize(80,-1), 0 );
	item4 = new wxStaticText( this, ID_TEXT, _("PassWord :"), wxDefaultPosition, wxSize(80,-1), wxALIGN_RIGHT );
	item5 = new wxTextCtrl( this, ID_MPASS, Bot->PassWord, wxDefaultPosition, wxSize(80,-1), wxTE_PASSWORD );
	item6 = new wxBoxSizer( wxHORIZONTAL );
	item7 = new wxStaticText( this, ID_TEXT, _("Universe :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	item8 = new wxTextCtrl( this, ID_UNIVERS, Bot->Univers, wxDefaultPosition, wxSize(120,-1), 0 ); //wxTE_READONLY
	item9 = new wxStaticText( this, ID_TEXT, _("Port :"), wxDefaultPosition, wxSize(40,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->Port);
	item10 = new wxTextCtrl( this, ID_PORT, s , wxDefaultPosition, wxSize(40,-1), 0 ); //wxTE_READONLY
	item11 = new wxBoxSizer( wxHORIZONTAL );
	item12 = new wxStaticText( this, ID_TEXT, _("Bot Name :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	item13 = new wxTextCtrl( this, ID_BOTNAME, Bot->Nom, wxDefaultPosition, wxSize(80,-1), 0 );
	item14 = new wxStaticText( this, ID_TEXT, _("World :"), wxDefaultPosition, wxSize(80,-1), wxALIGN_RIGHT );
	item15 = new wxTextCtrl( this, ID_MONDE, Bot->Monde, wxDefaultPosition, wxSize(80,-1), 0 );
	item16 = new wxBoxSizer( wxHORIZONTAL );
	item17 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	item18 = new wxButton( this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	item19 = new wxCheckBox (this, ID_RECO, _("Auto connection on startup"),wxDefaultPosition, wxDefaultSize, 0 );
	item19->SetValue(Bot->CGConAuto);
	item20 = new wxBoxSizer( wxHORIZONTAL );
	item21 = new wxStaticText( this, ID_TEXT, _("Reconnection Delay (sec) :"), wxDefaultPosition, wxSize(140,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->CGRecoDelay);
	item22 = new wxTextCtrl( this, ID_TPSRECO, s , wxDefaultPosition, wxSize(30,-1), 0 );
	item23 = new wxStaticText( this, ID_TEXT, _("Number of attempts :"), wxDefaultPosition, wxSize(130,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->CGRecoRetry);
	item24 = new wxTextCtrl( this, ID_NBESSAIS, s , wxDefaultPosition, wxSize(20,-1), 0 );
	item25 = new wxBoxSizer( wxHORIZONTAL );
	item26 = new wxCheckBox (this, ID_ENA_COL, _("Allow the customized colors"),wxDefaultPosition, wxDefaultSize, 0 );
	item26->SetValue(Bot->EnaCoulPerso);

// Affectation des Items

	item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item3, 0, wxGROW|wxALL, 5 );
	item1->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item1, 0, wxGROW|wxALL, 5 );
	item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item6, 0, wxGROW|wxALL, 5 );
	item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item11, 0, wxGROW|wxALL, 5 );
	item20->Add( item21, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item23, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item20, 0, wxGROW||wxALL, 5 );
	item25->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	item25->Add( item26, 0, wxGROW|wxALL, 5 );
	item0->Add( item25, 0, wxGROW|wxALL, 5 );
	item16->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	item16->Add( item19, 0, wxGROW|wxALL, 5 );
	item16->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	item16->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );
	item16->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item16, 0, wxGROW|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x,y;
	pConfig->Read(_T("/Fenetre/optx"), &x, 50),
	pConfig->Read(_T("/Fenetre/opty"), &y, 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

COptDial::~COptDial ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/optx"), x);
	pConfig->Write(_T("/Fenetre/opty"), y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

void COptDial::OnOk(wxCommandEvent& WXUNUSED(event))
{
	wxString s;
	long Valeur;
	s=item3->GetValue();
	s.ToLong(&Valeur);
	Bot->Citoyen=(int)Valeur;
	Bot->Sauve();
	Bot->PassWord=item5->GetValue();
	Bot->Univers=item8->GetValue();
	s=item10->GetValue();
	s.ToLong(&Valeur);
	Bot->Port=(int)Valeur;
	Bot->Nom=item13->GetValue();
	Bot->Monde=item15->GetValue();
	Bot->CGConAuto=item19->GetValue();
	s=item22->GetValue();
	s.ToLong(&Valeur);
	Bot->CGRecoDelay=(int)Valeur;
	s=item24->GetValue();
	s.ToLong(&Valeur);
	Bot->CGRecoRetry=(int)Valeur;
	if (Valeur != 0) Bot->CGRecoEna=true;
	else Bot->CGRecoEna=false;
	Bot->EnaCoulPerso=item26->GetValue();
	Bot->Sauve();
	EndModal (1);
}

//------------------------------------------------------------------------------

bool COptDial::Validate()
{
	return TRUE;
}

//------------------------------------------------------------------------------

void COptDial::OnPortChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstPort )
	{
		FirstPort = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item10->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<0) || (valeur>65535))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 65535"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item10->Undo();
	}
}

//------------------------------------------------------------------------------

void COptDial::OnDelaiChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstDelai )
	{
		FirstDelai = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item22->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<0) || (valeur>300))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 300 secondes"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item22->Undo();
	}
}

//------------------------------------------------------------------------------

void COptDial::OnRetryChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstRetry )
	{
		FirstRetry = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item24->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<(-1)) || (valeur>10))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 10 attempts, for infinity set -1"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item24->Undo();
	}
}
