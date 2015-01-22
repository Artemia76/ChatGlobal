#include "AboutBox.h"

#include "Global.h"

#include "buildwithwxwidgets.xpm"
#include "home.xpm"
#include "xelagot.xpm"
#include "chatglobal_big.xpm"

//------------------------------------------------------------------------------
// On déclare les évenements à gerer dans la boite de dialogue

wxBEGIN_EVENT_TABLE (AboutBox, wxDialog)
	EVT_BUTTON (ID_BTHOME, AboutBox::On_lien_abyssia)
	EVT_BUTTON (ID_SB_WXWINDOWS, AboutBox::On_lien_wxwidget)
	EVT_BUTTON (ID_XELAGOT, AboutBox::On_lien_xelagot)
wxEND_EVENT_TABLE()


//------------------------------------------------------------------------------
// Constructeur de la classe

AboutBox::AboutBox
	(
		wxWindow *parent,
		wxWindowID id,
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
	wxString text;
	text.append(CGVersion);
	text.append(_("\nBy "));
	text.append(CGCopyright);

	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer *item13= new wxBoxSizer( wxHORIZONTAL );
	wxStaticText *item3 = new wxStaticText
	(
		this,
		ID_TEXTS,
		CGVersion,
		wxDefaultPosition,
		wxDefaultSize,
		wxALIGN_CENTRE
	);
	item3->SetForegroundColour( *wxBLUE );
	item3->SetFont( wxFont( 19, wxROMAN, wxNORMAL, wxBOLD ) );
	item13->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer *item1 = new wxBoxSizer( wxHORIZONTAL );
	wxBitmap itemLogo(chatglobal_big_xpm);
	wxStaticBitmap *item2 = new wxStaticBitmap
	(
		this,
		ID_STATICBITMAP,
		itemLogo,
		wxDefaultPosition,
		wxDefaultSize
	);
	item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item1, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer *item4 = new wxBoxSizer( wxHORIZONTAL );
	wxTextCtrl *item5 = new wxTextCtrl
	(
		this,
		ID_TEXTECP,
		CGLicence,
		wxDefaultPosition,
		wxSize(300,100),
		wxTE_LEFT|wxTE_MULTILINE|wxTE_READONLY
	);
	item4->Add( item5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer *item6 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer *item14 = new wxBoxSizer( wxVERTICAL );
	wxStaticText *item15 = new wxStaticText( this, ID_TEXTECP, _("Uses xelagot server:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	wxBitmap itemXelag(xelagot_xpm);
	wxBitmapButton *item12 = new wxBitmapButton( this, ID_XELAGOT, itemXelag, wxDefaultPosition, wxDefaultSize );
	item14->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );
	item14->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );
	wxBitmap item9bitmap(home_xpm);
	wxBitmapButton *item7 = new wxBitmapButton( this, ID_BTHOME, item9bitmap, wxDefaultPosition, wxDefaultSize );
	item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
	wxBitmap item10Bitmap(builtwithwx_xpm);
	wxBitmapButton* item10 = new wxBitmapButton(this, ID_SB_WXWINDOWS, item10Bitmap, wxDefaultPosition, wxDefaultSize );
	item6->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer *item11 = new wxBoxSizer( wxHORIZONTAL );
	wxButton * item8 = new wxButton ( this, wxID_OK, _("OK"), wxPoint(60,130), wxDefaultSize);
	item11->Add(item8, 0, wxALIGN_CENTER|wxALL, 5);
	item0->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );
	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x = pConfig->Read(_T("/Fenetre/propx"), 50),
		y = pConfig->Read(_T("/Fenetre/propy"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------
// Destructeur de la Classe

AboutBox::~AboutBox ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/propx"), (long) x);
	pConfig->Write(_T("/Fenetre/propy"), (long) y);
}

//------------------------------------------------------------------------------
// Methode d'événement lorsqu'on clique sur l'icone home

void AboutBox::On_lien_abyssia (wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (_T("http://www.abyssia.fr/"));
}

//------------------------------------------------------------------------------
// Methode d'événement lorsqu'on clique sur l'icone des wxWidget

void AboutBox::On_lien_wxwidget (wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (_T("http://www.wxwindows.org/"));
}

//------------------------------------------------------------------------------
// Methode d'événement lorsqu'on clique sur l'icone de Xelagot

void AboutBox::On_lien_xelagot (wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (_T("http://www.imatowns.com/xelagot/"));
}
