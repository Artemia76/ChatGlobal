// *****************************************************************************
// *                                                                           *
// *                   BOITE DE DIALOGUE HORAIRES DU CIEL                      *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Neophile                                                      *
// *   Le 28/01/2007                                                           *
// *   CopyRight (c)Neophile 2007                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#include "CHorBox.h"

wxBEGIN_EVENT_TABLE (CCHorBox, wxDialog)
	EVT_BUTTON		(wxID_OK, CCHorBox::OnOk)
wxEND_EVENT_TABLE()

CCHorBox::CCHorBox
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
	item2 = new wxStaticText( this, -1, _("Start of sun rising :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item3 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 23, 0 );
	item3->SetValue(Ciel->hdl);
	item4 = new wxStaticText( this, -1, _T("H"), wxDefaultPosition, wxDefaultSize, 0 );
	item5 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 59, 0);
	item5->SetValue(Ciel->mdl);
	item6 = new wxStaticText( this, -1, _T("Min"), wxDefaultPosition, wxDefaultSize, 0 );
	item7 = new wxBoxSizer( wxHORIZONTAL );
	item8 = new wxStaticText( this, -1, _("End of sun rising :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item9 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 23, 0);
	item9->SetValue(Ciel->hfl);
	item10 = new wxStaticText( this, -1,_T("H"), wxDefaultPosition, wxDefaultSize, 0 );
	item11 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 59, 0);
	item11->SetValue(Ciel->mfl);
	item12 = new wxStaticText( this, -1,_T("Min"), wxDefaultPosition, wxDefaultSize, 0 );
	item13 = new wxBoxSizer( wxHORIZONTAL );
	item14 = new wxStaticText( this, -1, _("Start of sun descent :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item15 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 23, 0);
	item15->SetValue(Ciel->hdc);
	item16 = new wxStaticText( this, -1, _T("H"), wxDefaultPosition, wxDefaultSize, 0 );
	item17 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 59, 0);
	item17->SetValue(Ciel->mdc);
	item18 = new wxStaticText( this, -1, _T("Min"), wxDefaultPosition, wxDefaultSize, 0 );
	item19 = new wxBoxSizer( wxHORIZONTAL );
	item20 = new wxStaticText( this, -1, _("End of sun descent :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item21 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 23, 0);
	item21->SetValue(Ciel->hfc);
	item22 = new wxStaticText( this, -1, _T("H"), wxDefaultPosition, wxDefaultSize, 0 );
	item23 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 59, 0);
	item23->SetValue(Ciel->mfc);
	item24 = new wxStaticText( this, -1,_T("Min"), wxDefaultPosition, wxDefaultSize, 0 );
	item34 = new wxStaticBox( this, -1, _("Sun" ));
	item35 = new wxStaticBoxSizer( item34, wxVERTICAL );
	item25 = new wxBoxSizer( wxHORIZONTAL );
	item26 = new wxStaticText( this, -1, _("Texture :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item27 = new wxTextCtrl( this, -1, Ciel->Soleil, wxDefaultPosition, wxSize(80,-1), 0 );
	item38 = new wxBoxSizer( wxHORIZONTAL );
	item39 = new wxStaticText( this, -1, _("Mask :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item40 = new wxTextCtrl( this, -1, Ciel->MSoleil, wxDefaultPosition, wxSize(80,-1), 0 );
	item41 = new wxBoxSizer( wxHORIZONTAL );
	item42 = new wxStaticText( this, -1, _("Size :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item43 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 100, 0);
	item43->SetValue(Ciel->TSoleil);
	item36 = new wxStaticBox( this, -1, _("Moon"));
	item37 = new wxStaticBoxSizer( item36, wxVERTICAL );
	item28 = new wxBoxSizer( wxHORIZONTAL );
	item29 = new wxStaticText( this, -1, _("Texture :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item30 = new wxTextCtrl( this, -1, Ciel->Lune, wxDefaultPosition, wxSize(80,-1), 0 );
	item44 = new wxBoxSizer( wxHORIZONTAL );
	item45 = new wxStaticText( this, -1, _("Mask :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item46 = new wxTextCtrl( this, -1, Ciel->MLune, wxDefaultPosition, wxSize(80,-1), 0 );
	item47 = new wxBoxSizer( wxHORIZONTAL );
	item48 = new wxStaticText( this, -1, _("Size :"), wxDefaultPosition, wxSize(100,-1), 0 );
	item49 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(45,-1), 0, 0, 100, 0);
	item49->SetValue(Ciel->TLune);

	item31 = new wxBoxSizer( wxHORIZONTAL );
	item32 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	item33 = new wxButton( this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0 );

	item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item1, 0, wxGROW|wxALL, 5 );
	item7->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );
	item7->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );
	item7->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item7->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );
	item7->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item7, 0, wxGROW|wxALL, 5 );
	item13->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );
	item13->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );
	item13->Add( item16, 0, wxALIGN_CENTER|wxALL, 5 );
	item13->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );
	item13->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item13, 0, wxGROW|wxALL, 5 );
	item19->Add( item20, 0, wxALIGN_CENTER|wxALL, 5 );
	item19->Add( item21, 0, wxALIGN_CENTER|wxALL, 5 );
	item19->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );
	item19->Add( item23, 0, wxALIGN_CENTER|wxALL, 5 );
	item19->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item19, 0, wxGROW|wxALL, 5 );
	item25->Add( item26, 0, wxALIGN_CENTER|wxALL, 5 );
	item25->Add( item27, 0, wxALIGN_CENTER|wxALL, 5 );
	item35->Add( item25, 0, wxGROW|wxALL, 0 );
	item38->Add( item39, 0, wxALIGN_CENTER|wxALL, 5 );
	item38->Add( item40, 0, wxALIGN_CENTER|wxALL, 5 );
	item35->Add( item38, 0, wxGROW|wxALL, 0 );
	item41->Add( item42, 0, wxALIGN_CENTER|wxALL, 5 );
	item41->Add( item43, 0, wxALIGN_CENTER|wxALL, 5 );
	item35->Add( item41, 0, wxGROW|wxALL, 0 );
	item0->Add( item35, 0, wxGROW|wxALL, 5 );
	item28->Add( item29, 0, wxALIGN_CENTER|wxALL, 5 );
	item28->Add( item30, 0, wxALIGN_CENTER|wxALL, 5 );
	item37->Add( item28, 0, wxGROW|wxALL, 0 );
	item44->Add( item45, 0, wxALIGN_CENTER|wxALL, 5 );
	item44->Add( item46, 0, wxALIGN_CENTER|wxALL, 5 );
	item37->Add( item44, 0, wxGROW|wxALL, 0 );
	item47->Add( item48, 0, wxALIGN_CENTER|wxALL, 5 );
	item47->Add( item49, 0, wxALIGN_CENTER|wxALL, 5 );
	item37->Add( item47, 0, wxGROW|wxALL, 0 );
	item0->Add( item37, 0, wxGROW|wxALL, 5 );
	item31->Add( item32, 0, wxALIGN_CENTER|wxALL, 5 );
	item31->Add( item33, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item31, 0, wxALIGN_RIGHT|wxALL, 5 );
	SetAutoLayout (true);
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x,y;
	pConfig->Read(_T("/Fenetre/HorCielx"),&x, 50),
	pConfig->Read(_T("/Fenetre/HorCiely"),&y, 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

CCHorBox::~CCHorBox ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/HorCielx"), x);
	pConfig->Write(_T("/Fenetre/HorCiely"), y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

bool CCHorBox::Validate()
{
	return true;
}

//------------------------------------------------------------------------------

void CCHorBox::OnOk(wxCommandEvent& WXUNUSED(event))
{
	int DL,FL,DC,FC;
	DL=(item3->GetValue() * 60) + item5->GetValue();
	FL=(item9->GetValue() * 60) + item11->GetValue();
	DC=(item15->GetValue() * 60) + item17->GetValue();
	FC=(item21->GetValue() * 60) + item23->GetValue();
	if (!((DL<FL) &&
		(FL<DC) &&
		(DC<FC)))
	{
		wxMessageBox (_("One of timing goes wrong, please check that time are following"),
						_("Error"), wxICON_EXCLAMATION | wxOK, this);
		return;
	}
	Ciel->hdl=item3->GetValue();
	Ciel->mdl=item5->GetValue();
	Ciel->hfl=item9->GetValue();
	Ciel->mfl=item11->GetValue();
	Ciel->hdc=item15->GetValue();
	Ciel->mdc=item17->GetValue();
	Ciel->hfc=item21->GetValue();
	Ciel->mfc=item23->GetValue();
	Ciel->Soleil=item27->GetValue();
	Ciel->MSoleil=item40->GetValue();
	Ciel->TSoleil=item43->GetValue();
	Ciel->Lune=item30->GetValue();
	Ciel->MLune=item46->GetValue();
	Ciel->TLune=item49->GetValue();
	Ciel->Sauve();
	Ciel->Top=-1;
	EndModal (true);
}

