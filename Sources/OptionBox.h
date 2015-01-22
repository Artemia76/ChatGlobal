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
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#ifndef OPTDIAL_H
#define OPTDIAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>

#include "CBotCG.h"

enum
{
	ID_TEXT = wxID_HIGHEST,
	ID_CITOYEN,
	ID_MPASS,
	ID_UNIVERS,
	ID_PORT,
	ID_BOTNAME,
	ID_MONDE,
	ID_RECO,
	ID_TPSRECO,
	ID_NBESSAIS,
	ID_ENA_COL
};

class COptDial : public wxDialog
{
	public:
						COptDial
						(
							wxWindow *parent,
							wxWindowID id,
							CBotCG* Robot,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~COptDial ();
virtual	bool			Validate();
	private:
		void			OnOk(wxCommandEvent & event);
		void			OnPortChange(wxCommandEvent & event);
		bool			FirstPort;
		void			OnDelaiChange(wxCommandEvent & event);
		bool			FirstDelai;
		void			OnRetryChange(wxCommandEvent & event);
		bool			FirstRetry;
		CBotCG*			Bot;
		wxConfigBase*	pConfig;
		wxBoxSizer*		item0;
		wxBoxSizer*		item1;
		wxStaticText*	item2;
		wxTextCtrl*		item3;
		wxStaticText*	item4;
		wxTextCtrl*		item5;
		wxBoxSizer*		item6;
		wxStaticText*	item7;
		wxTextCtrl*		item8;
		wxStaticText*	item9;
		wxTextCtrl*		item10;
		wxBoxSizer*		item11;
		wxStaticText*	item12;
		wxTextCtrl*		item13;
		wxStaticText*	item14;
		wxTextCtrl*		item15;
		wxBoxSizer*		item16;
		wxButton*		item17;
		wxButton*		item18;
		wxCheckBox*		item19;
		wxBoxSizer*		item20;
		wxStaticText*	item21;
		wxTextCtrl*		item22;
		wxStaticText*	item23;
		wxTextCtrl*		item24;
		wxBoxSizer*		item25;
		wxCheckBox*		item26;
		DECLARE_EVENT_TABLE()
};

#endif
