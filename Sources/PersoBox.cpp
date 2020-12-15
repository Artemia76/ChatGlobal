// *****************************************************************************
// *                                                                           *
// *                 BOITE DE DIALOGUE DES PERSONNALISATIONS                   *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 14/05/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "PersoBox.h"

#include <wx/colordlg.h>

#include "Global.h"

BEGIN_EVENT_TABLE (CPersoDial, wxDialog)
	EVT_BUTTON ( wxID_OK, CPersoDial::OnOk)
	EVT_BUTTON ( ID_CLRMESSAC, CPersoDial::OnCouleur)
	EVT_BUTTON ( ID_CLRANNARR, CPersoDial::OnCouleur)
	EVT_BUTTON ( ID_CLRANNDEP, CPersoDial::OnCouleur)
	EVT_BUTTON ( ID_CLRANNKLI, CPersoDial::OnCouleur)
	EVT_BUTTON ( ID_CLRANNKLO, CPersoDial::OnCouleur)
	EVT_BUTTON ( ID_CLRANTIJOG, CPersoDial::OnCouleur)
END_EVENT_TABLE()


CPersoDial::CPersoDial
	(
		wxWindow* parent,
		wxWindowID id,
		CBotCG *Robot,
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
// Création des Items
	Boite = new wxBoxSizer( wxVERTICAL );

	Ligne1   = new wxBoxSizer( wxHORIZONTAL );
	Check1   = new wxCheckBox (this, ID_ENAMESSAC, _("Welcome Message for guests :"),wxDefaultPosition, wxSize( 180, -1), 0);
	Check1->SetValue(Bot->EnaMessAc);
	Edit1    = new wxTextCtrl( this, ID_TXTMESSAC, Bot->TxtMessAc, wxDefaultPosition, wxSize(400,20), 0 );
	Couleur1 = new wxButton( this, ID_CLRMESSAC, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	Couleur1->SetBackgroundColour(Bot->ClrMessAc);

	Ligne2   = new wxBoxSizer( wxHORIZONTAL );
	Check2   = new wxCheckBox (this, ID_ENAANNARR,_("Incoming Public Message :"),wxDefaultPosition, wxSize( 180, -1), 0 );
	Check2->SetValue(Bot->EnaAnnArr);
	Edit2    = new wxTextCtrl( this, ID_TXTANNARR, Bot->TxtAnnArr, wxDefaultPosition, wxSize(400,20), 0 );
	Couleur2 = new wxButton( this, ID_CLRANNARR, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	Couleur2->SetBackgroundColour(Bot->ClrAnnArr);

	Ligne3   = new wxBoxSizer( wxHORIZONTAL );
	Check3   = new wxCheckBox (this, ID_ENAANNDEP, _("Outgoing Public Message :"),wxDefaultPosition, wxSize( 180, -1), 0 );
	Check3->SetValue(Bot->EnaAnnDep);
	Edit3    = new wxTextCtrl( this, ID_TXTANNDEP, Bot->TxtAnnDep, wxDefaultPosition, wxSize(400,20), 0 );
	Couleur3 = new wxButton( this, ID_CLRANNDEP, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	Couleur3->SetBackgroundColour(Bot->ClrAnnDep);

	Ligne4   = new wxBoxSizer( wxHORIZONTAL );
	Check4   = new wxCheckBox (this, ID_ENAANNKLI, _("Kling winner message :"),wxDefaultPosition, wxSize( 180, -1), 0 );
	Check4->SetValue(Bot->EnaAnnKli);
	Edit4    = new wxTextCtrl( this, ID_TXTANNKLI, Bot->TxtAnnKli, wxDefaultPosition, wxSize(400,20), 0 );
	Couleur4 = new wxButton( this, ID_CLRANNKLI, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	Couleur4->SetBackgroundColour(Bot->ClrAnnKli);

	Ligne5   = new wxBoxSizer( wxHORIZONTAL );
	Check5   = new wxCheckBox (this, ID_ENAANNKLO, _("Kloug winner message :"),wxDefaultPosition, wxSize( 180, -1), 0 );
	Check5->SetValue(Bot->EnaAnnKlo);
	Edit5    = new wxTextCtrl( this, ID_TXTANNKLO, Bot->TxtAnnKlo, wxDefaultPosition, wxSize(400,20), 0 );
	Couleur5 = new wxButton( this, ID_CLRANNKLO, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	Couleur5->SetBackgroundColour(Bot->ClrAnnKlo);

	Bridage = new wxBoxSizer( wxHORIZONTAL );
	ChatBride = new wxCheckBox (this, -1, _("Allow space limit hearing (in meters) :"),wxDefaultPosition, wxSize( 230, -1), 0 );
	ChatBride->SetValue(Bot->ChatBride);
	s.Printf(_T("%d"),Bot->ChatDistance);
	ChatDistance = new wxSpinCtrl( this, -1, s, wxDefaultPosition, wxSize (70,-1), wxSP_ARROW_KEYS, 0, 32000, Bot->ChatDistance);

	ExtBridage = new wxBoxSizer( wxHORIZONTAL );
	ExtBride = new wxCheckBox (this, -1, _("Allow area limit hearing Network (in meters) :"),wxDefaultPosition, wxSize( 230, -1), 0 );
	ExtBride->SetValue(Bot->ExtBride);
	s.Printf(_T("%d"),Bot->ExtDistance);
	ExtDistance = new wxSpinCtrl( this, -1, s, wxDefaultPosition, wxSize (70,-1), wxSP_ARROW_KEYS, 0, 32000, Bot->ChatDistance);
	Text1 = new wxStaticText( this, -1, _("Coord :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	ExtCoord= new wxTextCtrl( this, -1, CoordToAw (Bot->ExtCoordX,Bot->ExtCoordZ) , wxDefaultPosition, wxSize(70,-1), 0 );

	AntiJog = new wxBoxSizer( wxHORIZONTAL );
	EnaAntiJogger = new wxCheckBox (this, -1, _("Anti Jogger"),wxDefaultPosition, wxSize( 150, -1), 0 );
	EnaAntiJogger->SetValue(Bot->AntiJog->EnaAntiJog);
	AntiJogTempsTxt= new wxStaticText( this, -1, _("Time :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->AntiJog->Delai);
	AntiJogTemps = new wxSpinCtrl( this, -1, s, wxDefaultPosition, wxSize (70,-1), wxSP_ARROW_KEYS, 1, 600, Bot->ChatDistance);
	AntiJogNbTxt= new wxStaticText( this, -1, _("Attempt :"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->AntiJog->NbEntreeMax);
	AntiJogNb = new wxSpinCtrl( this, -1, s, wxDefaultPosition, wxSize (70,-1), wxSP_ARROW_KEYS, 2, 10, Bot->ChatDistance);
	AntiJogEjecTxt= new wxStaticText( this, -1, _("Ejection (Min):"), wxDefaultPosition, wxSize(70,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->AntiJog->TpsEject);
	AntiJogEjec = new wxSpinCtrl( this, -1, s, wxDefaultPosition, wxSize (70,-1), wxSP_ARROW_KEYS, 1, 60, Bot->ChatDistance);

	AntiJog2 = new wxBoxSizer( wxHORIZONTAL );
	AntiJogMessTxt= new wxStaticText( this, -1, _("Ejection message :"), wxDefaultPosition, wxSize(180,-1), wxALIGN_RIGHT );
	AntiJogMess = new wxTextCtrl( this, -1, Bot->AntiJog->MessEject, wxDefaultPosition, wxSize(400,20), 0 );
	AntiJogBout = new wxButton( this, ID_CLRANTIJOG, _T(""), wxDefaultPosition, wxSize(40, 20), 0 );
	AntiJogBout->SetBackgroundColour(Bot->AntiJog->MessColour);

	Boutons = new wxBoxSizer( wxHORIZONTAL );
	Annuler = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	Ok = new wxButton( this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, 0 );

// Affectation des Items

	Ligne1->Add( Check1, 0, wxALIGN_CENTER|wxALL, 5 );
	Ligne1->Add( Edit1, 0, wxGROW|wxALL, 5 );
	Ligne1->Add( Couleur1, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Ligne1, 0, wxGROW|wxALL, 5 );
	Ligne2->Add( Check2, 0, wxALIGN_CENTER|wxALL, 5 );
	Ligne2->Add( Edit2, 0, wxGROW|wxALL, 5 );
	Ligne2->Add( Couleur2, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Ligne2, 0, wxGROW|wxALL, 5 );
	Ligne3->Add( Check3, 0, wxALIGN_CENTER|wxALL, 5 );
	Ligne3->Add( Edit3, 0, wxGROW|wxALL, 5 );
	Ligne3->Add( Couleur3, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Ligne3, 0, wxGROW|wxALL, 5 );

	Ligne4->Add( Check4, 0, wxALIGN_CENTER|wxALL, 5 );
	Ligne4->Add( Edit4, 0, wxGROW|wxALL, 5 );
	Ligne4->Add( Couleur4, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Ligne4, 0, wxGROW|wxALL, 5 );

	Ligne5->Add( Check5, 0, wxALIGN_CENTER|wxALL, 5 );
	Ligne5->Add( Edit5, 0, wxGROW|wxALL, 5 );
	Ligne5->Add( Couleur5, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Ligne5, 0, wxGROW|wxALL, 5 );

	Bridage->Add( ChatBride, 0, wxALIGN_CENTER|wxALL, 5 );
	Bridage->Add( ChatDistance, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( Bridage, 0, wxGROW|wxALL, 5 );

	ExtBridage->Add( ExtBride, 0, wxALIGN_CENTER|wxALL, 5 );
	ExtBridage->Add( ExtDistance, 0, wxALIGN_CENTER|wxALL, 5 );
	ExtBridage->Add( Text1, 0, wxALIGN_CENTER|wxALL, 5 );
	ExtBridage->Add( ExtCoord, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add( ExtBridage, 0, wxGROW|wxALL, 5 );

	AntiJog->Add(EnaAntiJogger, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogTempsTxt, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogTemps, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogNbTxt, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogNb, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogEjecTxt, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog->Add(AntiJogEjec, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add(AntiJog, 0, wxGROW|wxALL, 5 );

	AntiJog2->Add(AntiJogMessTxt, 0, wxALIGN_CENTER|wxALL, 5 );
	AntiJog2->Add(AntiJogMess, 0, wxGROW|wxALL, 5 );
	AntiJog2->Add(AntiJogBout, 0, wxALIGN_CENTER|wxALL, 5 );
	Boite->Add(AntiJog2, 0, wxGROW|wxALL, 5 );

	Boutons->Add( 400, 20, 0, wxGROW|wxALL, 5 );
	Boutons->Add( Annuler, 0, wxGROW|wxALL, 5 );
	Boutons->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	Boutons->Add( Ok, 0, wxGROW|wxALL, 5 );
	Boite->Add( Boutons, 0, wxGROW|wxALL, 5 );

	SetAutoLayout (true);
	SetSizer( Boite );
	Boite->Fit(this);
	Boite->SetSizeHints(this);
	int	x = pConfig->Read(_T("/Fenetre/persox"), 50),
		y = pConfig->Read(_T("/Fenetre/persoy"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

CPersoDial::~CPersoDial ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/persox"), (long) x);
	pConfig->Write(_T("/Fenetre/persoy"), (long) y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

void CPersoDial::OnOk(wxCommandEvent& WXUNUSED(event))
{
	wxString Buff1, Buff2;
	int Pos1=0, Pos2=0;
	bool Flag;
	long num=0;
	Bot->EnaMessAc=Check1->GetValue();
	Bot->TxtMessAc=Edit1->GetValue();
	Bot->ClrMessAc=Couleur1->GetBackgroundColour();
	Bot->EnaAnnArr=Check2->GetValue();
	Bot->TxtAnnArr=Edit2->GetValue();
	Bot->ClrAnnArr=Couleur2->GetBackgroundColour();
	Bot->EnaAnnDep=Check3->GetValue();
	Bot->TxtAnnDep=Edit3->GetValue();
	Bot->ClrAnnDep=Couleur3->GetBackgroundColour();
	Bot->EnaAnnKli=Check4->GetValue();
	Bot->TxtAnnKli=Edit4->GetValue();
	Bot->ClrAnnKli=Couleur4->GetBackgroundColour();
	Bot->EnaAnnKlo=Check5->GetValue();
	Bot->TxtAnnKlo=Edit5->GetValue();
	Bot->ClrAnnKlo=Couleur5->GetBackgroundColour();
	Bot->ChatBride=ChatBride->GetValue();
	Bot->ChatDistance=ChatDistance->GetValue();
	Bot->ExtBride=ExtBride->GetValue();
	Bot->ExtDistance=ExtDistance->GetValue();
	Bot->AntiJog->EnaAntiJog=EnaAntiJogger->GetValue();
	Bot->AntiJog->Delai=AntiJogTemps->GetValue ();
	Bot->AntiJog->NbEntreeMax=AntiJogNb->GetValue ();
	Bot->AntiJog->TpsEject=AntiJogEjec->GetValue ();
	Bot->AntiJog->MessEject=AntiJogMess->GetValue();
	Bot->AntiJog->MessColour=AntiJogBout->GetBackgroundColour();
	Buff1=ExtCoord->GetValue();
	Buff1.UpperCase();
	Pos1=Buff1.Find(_T('N'),false);
	if (Pos1 == -1)
	{
		Pos1=Buff1.Find(_T('S'),false);
		if (Pos1 == -1) Pos1=0;
		Flag=false;
	}
	else
	{
		Flag=true;
	}
	Buff2=Buff1.Mid(0,Pos1);
	Buff2.ToLong (&num);
	if (Flag) Bot->ExtCoordZ=((int)num*1000)+500;
	else Bot->ExtCoordZ=((int)num*(-1000))+500;
	Pos2=Buff1.Find(_T('W'),false);
	if (Pos2 == -1)
	{
		Pos2=Buff1.Find(_T('E'),false);
		if (Pos2 == -1) Pos2=Pos1;
		Flag=false;
	}
	else
	{
		Flag=true;
	}
	Buff2=Buff1.Mid(Pos1+1,Pos2-(Pos1+1));
	Buff2.ToLong (&num);
	if (Flag) Bot->ExtCoordX=((int)num*1000)+500;
	else Bot->ExtCoordX=((int)num*(-1000))+500;
	Bot->Sauve();
	EndModal (1);
}

//------------------------------------------------------------------------------

bool CPersoDial::Validate()
{
	return true;
}

//------------------------------------------------------------------------------

void CPersoDial::OnCouleur(wxCommandEvent &event)
{
	wxButton* Bouton = (wxButton*)event.GetEventObject ();
	BCouleur.SetColour(Bouton->GetBackgroundColour());
	wxColourDialog ColorDiag (this, &BCouleur);
	ColorDiag.ShowModal();
	BCouleur=ColorDiag.GetColourData();
	Bouton->SetBackgroundColour(BCouleur.GetColour());
}
