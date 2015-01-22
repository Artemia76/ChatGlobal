// *****************************************************************************
// *                                                                           *
// *                BOITE DE DIALOGUE DES OPTIONS XELAG SERVER                 *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 4/05/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#ifndef XLGDIAL_H
#define XLGDIAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>

#include "CXelagServer.h"

enum
{
	ID_XGTEXT = wxID_HIGHEST,
	ID_XGHOST,
	ID_XGPORT,
	ID_XGLOGIN,
	ID_XGMPASS,
	ID_XGRECO,
	ID_XGTPSRECO,
	ID_XGNBESSAIS
};

class CXlgOpt : public wxDialog
{
	public:
						CXlgOpt
						(
							wxWindow *parent,
							wxWindowID id,
							CXelag* Client,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~CXlgOpt ();
virtual	bool			Validate();
	private:
		void			OnOk(wxCommandEvent & event);
		void			OnPortChange(wxCommandEvent & event);
		bool			FirstPort;
		void			OnDelaiChange(wxCommandEvent & event);
		bool			FirstDelai;
		void			OnRetryChange(wxCommandEvent & event);
		bool			FirstRetry;
		CXelag*			Xelag;
		wxConfigBase*	pConfig;
		wxBoxSizer*		item0; //Sizer principal
		wxBoxSizer*		item1; //1ere Ligne
		wxStaticText*	item2;
		wxTextCtrl*		item3;
		wxStaticText*	item4;
		wxTextCtrl*		item5;
		wxBoxSizer*		item6; //2eme Ligne
		wxStaticText*	item7;
		wxTextCtrl*		item8;
		wxStaticText*	item9;
		wxTextCtrl*		item10;
		wxBoxSizer*		item11; //3eme Ligne
		wxButton*		item12;
		wxButton*		item13;
		wxCheckBox*		item14;
		wxBoxSizer*		item15;
		wxStaticText*	item16;
		wxTextCtrl*		item17;
		wxStaticText*	item18;
		wxTextCtrl*		item19;
		DECLARE_EVENT_TABLE()
};

#endif

