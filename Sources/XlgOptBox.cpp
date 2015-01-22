// *****************************************************************************
// *                                                                           *
// *               ITE DE DIALOGUE DES OPTIONS DU XELAG SERVER                 *
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

#include "XlgOptBox.h"

BEGIN_EVENT_TABLE (CXlgOpt, wxDialog)
	EVT_BUTTON ( wxID_OK, CXlgOpt::OnOk)
	EVT_TEXT ( ID_XGPORT, CXlgOpt::OnPortChange)
	EVT_TEXT ( ID_XGTPSRECO, CXlgOpt::OnDelaiChange)
	EVT_TEXT ( ID_XGNBESSAIS, CXlgOpt::OnRetryChange)
END_EVENT_TABLE()

CXlgOpt::CXlgOpt
	(
		wxWindow* parent,
		wxWindowID id,
		CXelag *Client,
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
	Xelag = Client;
	FirstPort=true;
	FirstDelai=true;
	FirstRetry=true;
// Création des Items
	item0 = new wxBoxSizer( wxVERTICAL );
	item1 = new wxBoxSizer( wxHORIZONTAL );
	item2 = new wxStaticText( this, ID_XGTEXT, _("Host :"), wxDefaultPosition, wxSize(50,-1), wxALIGN_RIGHT );
	item3 = new wxTextCtrl( this, ID_XGHOST, Xelag->XgHost , wxDefaultPosition, wxSize(120,-1), 0 );
	item4 = new wxStaticText( this, ID_XGTEXT, _("Port :"), wxDefaultPosition, wxSize(40,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Xelag->XgPort);
	item5 = new wxTextCtrl( this, ID_XGPORT, s, wxDefaultPosition, wxSize(40,-1), 0 );
	item6 = new wxBoxSizer( wxHORIZONTAL );
	item7 = new wxStaticText( this, ID_XGTEXT, _("Login :"), wxDefaultPosition, wxSize(50,-1), wxALIGN_RIGHT );
	item8 = new wxTextCtrl( this, ID_XGLOGIN, Xelag->XgLogin, wxDefaultPosition, wxSize(80,-1), 0 );
	item9 = new wxStaticText( this, ID_XGTEXT, _("PassWord :"), wxDefaultPosition, wxSize(80,-1), wxALIGN_RIGHT );
	item10 = new wxTextCtrl( this, ID_XGMPASS, Xelag->XgPassWord , wxDefaultPosition, wxSize(80,-1), wxTE_PASSWORD);
	item11 = new wxBoxSizer( wxHORIZONTAL );
	item12 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	item13 = new wxButton( this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	item14 = new wxCheckBox (this, ID_XGRECO, _("Auto connection on startup"),wxDefaultPosition, wxDefaultSize, 0 );
	item14->SetValue(Xelag->XgConAuto);
	item15 = new wxBoxSizer( wxHORIZONTAL );
	item16 = new wxStaticText( this, ID_XGTEXT, _("Reconnection Delay (sec) :"), wxDefaultPosition, wxSize(140,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Xelag->XgRecoDelay);
	item17 = new wxTextCtrl( this, ID_XGTPSRECO, s , wxDefaultPosition, wxSize(30,-1), 0 );
	item18 = new wxStaticText( this, ID_XGTEXT, _("Number of attempts :"), wxDefaultPosition, wxSize(130,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Xelag->XgRecoRetry);
	item19 = new wxTextCtrl( this, ID_XGNBESSAIS, s , wxDefaultPosition, wxSize(20,-1), 0 );

// Affectation des Items

	item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item1->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item15->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );
	item15->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );
	item15->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item15->Add( item19, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item15, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item11->Add( 30, 20, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item11->Add(item14, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( 30, 20, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x,y;
	pConfig->Read(_T("/Fenetre/xlgx"),&x, 50),
	pConfig->Read(_T("/Fenetre/xlgy"),&y, 50);
	Move(x, y);
}

CXlgOpt::~CXlgOpt ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/xlgx"), x);
	pConfig->Write(_T("/Fenetre/xlgy"), y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

void CXlgOpt::OnOk(wxCommandEvent& WXUNUSED(event))
{
	wxString s;
	long Valeur;
	Xelag->XgHost=item3->GetValue();
	s=item5->GetValue();
	s.ToLong(&Valeur);
	Xelag->XgPort=(int)Valeur;
	Xelag->XgLogin=item8->GetValue();
	Xelag->XgPassWord=item10->GetValue();
	Xelag->XgConAuto=item14->GetValue();
	s=item17->GetValue();
	s.ToLong(&Valeur);
	Xelag->XgRecoDelay=(int)Valeur;
	s=item19->GetValue();
	s.ToLong(&Valeur);
	Xelag->XgRecoRetry=(int)Valeur;
	if (Valeur != 0) Xelag->XgRecoEna=true;
	else Xelag->XgRecoEna=false;
	Xelag->Sauve();
	EndModal (1);
}

//-------------------------------_(-----------------------------------------------

bool CXlgOpt::Validate()
{
	return TRUE;
}

//------------------------------------------------------------------------------

void CXlgOpt::OnPortChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstPort )
	{
		FirstPort = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item5->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<0) || (valeur>65535))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 65535"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item5->Undo();
	}
}

//------------------------------------------------------------------------------

void CXlgOpt::OnDelaiChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstDelai )
	{
		FirstDelai = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item17->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<0) || (valeur>300))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 300 secondes"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item17->Undo();
	}
}

//------------------------------------------------------------------------------

void CXlgOpt::OnRetryChange(wxCommandEvent& WXUNUSED(event))
{
	if ( FirstRetry )
	{
		FirstRetry = FALSE;
		return;
	}
	wxString s;
	long valeur=0;
	s=item19->GetValue();
	s.ToLong(&valeur);
	if ((!s.IsNumber()) || (valeur<(-1)) || (valeur>10))
	{
		wxMessageBox (_("You have to set a number ranged between 0 and 10 attempts, for infinity set -1"),_("Help"), wxOK | wxICON_EXCLAMATION, this);
		item19->Undo();
	}
}
