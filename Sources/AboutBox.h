#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>

enum
{
	ID_TEXTS=wxID_HIGHEST,
	ID_SB_WXWINDOWS,
	ID_BTHOME,
	ID_TEXTECP,
	ID_STATICBITMAP,
	ID_XELAGOT
};


class AboutBox: public wxDialog
{
	public:
						AboutBox
						(
							wxWindow *parent,
							wxWindowID id,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~AboutBox ();
	private:
		wxConfigBase*	pConfig;
		wxStaticBitmap	*Logo;
		wxStaticText	*StaticText;
	protected:
		void			On_lien_abyssia (wxCommandEvent & event);
		void			On_lien_wxwidget (wxCommandEvent & event);
		void			On_lien_xelagot (wxCommandEvent & event);
		wxDECLARE_EVENT_TABLE();
};

#endif

