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

#ifndef CHORBOX_H
#define CHORBOX_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/spinctrl.h>

#include "Ciel.h"

class CCHorBox : public wxDialog
{
	public:
						CCHorBox
						(
							wxWindow *parent,
							wxWindowID id,
							CCiel* PtCiel,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~CCHorBox ();
virtual	bool			Validate();
	private:
		CCiel*			Ciel;
		wxConfigBase*	pConfig;
		wxBoxSizer*			item0;
		wxBoxSizer*			item1;
		wxStaticText*		item2;
		wxSpinCtrl*			item3;
		wxStaticText*		item4;
		wxSpinCtrl*			item5;
		wxStaticText*		item6;
		wxBoxSizer*			item7;
		wxStaticText*		item8;
		wxSpinCtrl*			item9;
		wxStaticText*		item10;
		wxSpinCtrl*			item11;
		wxStaticText*		item12;
		wxBoxSizer*			item13;
		wxStaticText*		item14;
		wxSpinCtrl*			item15;
		wxStaticText*		item16;
		wxSpinCtrl*			item17;
		wxStaticText*		item18;
		wxBoxSizer*			item19;
		wxStaticText*		item20;
		wxSpinCtrl*			item21;
		wxStaticText*		item22;
		wxSpinCtrl*			item23;
		wxStaticText*		item24;
		wxBoxSizer*			item25;
		wxStaticText*		item26;
		wxTextCtrl*			item27;
		wxBoxSizer*			item28;
		wxStaticText*		item29;
		wxTextCtrl*			item30;
		wxBoxSizer*			item31;
		wxButton*			item32;
		wxButton*			item33;
		wxStaticBox*		item34;
		wxStaticBoxSizer*	item35;
		wxStaticBox*		item36;
		wxStaticBoxSizer*	item37;
		wxBoxSizer*			item38;
		wxStaticText*		item39;
		wxTextCtrl*			item40;
		wxBoxSizer*			item41;
		wxStaticText*		item42;
		wxSpinCtrl*			item43;
		wxBoxSizer*			item44;
		wxStaticText*		item45;
		wxTextCtrl*			item46;
		wxBoxSizer*			item47;
		wxStaticText*		item48;
		wxSpinCtrl*			item49;
	protected:
		void			OnOk	(wxCommandEvent & event);
		wxDECLARE_EVENT_TABLE();
};

#endif
