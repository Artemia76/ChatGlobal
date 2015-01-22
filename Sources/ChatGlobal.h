// *****************************************************************************
// *                                                                           *
// *                            Easy Mover HEADER                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 11/06/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CHATGLOBAL_H
#define CHATGLOBAL_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/wxprec.h>

#include <wx/intl.h>
#include <wx/fileconf.h>

#define NB_MAX_LNG 3

// language data
static const wxLanguage langIds[] =
{
    wxLANGUAGE_ENGLISH,
    wxLANGUAGE_FRENCH,
    wxLANGUAGE_SPANISH
};

// note that it makes no sense to translate these strings, they are
// shown before we set the locale anyhow
const wxString langNames[] =
{
    _T("English"),
    _T("French"),
    _T("Spanish")
};

wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
                       LangArraysMismatch );



// Classe d'application générale

class CMainApp : public wxApp
{
	private:
		wxFileConfig*		pConfig;

	protected:
		virtual bool	OnInit ();
		virtual int 	OnExit ();
		wxLocale			m_locale;
};

#endif
