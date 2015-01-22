// *****************************************************************************
// *                                                                           *
// *                   BOITE DE DIALOGUE COULEURS DU CIEL                      *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Neophile                                                      *
// *   Le 31/01/2007                                                           *
// *   CopyRight (c)Neophile 2007                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#ifndef CCOLBOX_H
#define CCOLBOX_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>

#include "Ciel.h"

enum
{
	CC_NA=wxID_HIGHEST,
	CC_NJ,CC_NC,CC_NN,
	CC_SA,CC_SJ,CC_SC,CC_SN,
	CC_EA,CC_EJ,CC_EC,CC_EN,
	CC_OA,CC_OJ,CC_OC,CC_ON,
	CC_ZA,CC_ZJ,CC_ZC,CC_ZN,
	CC_DA,CC_DJ,CC_DC,CC_DN,
	CC_LUMA,CC_LUMJ,CC_LUMC,CC_LUMN,
	CC_DIRA,CC_DIRJ,CC_DIRC,CC_DIRN
};

class CCColBox : public wxDialog
{
	public:
						CCColBox
						(
							wxWindow *parent,
							wxWindowID id,
							CCiel* PtCiel,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~CCColBox ();
virtual	bool			Validate();
	private:
		wxBoxSizer*		item0;
		wxBoxSizer*		item1;
		wxBoxSizer*		item2;
		wxStaticText*	item3;
		wxStaticText*	item4;
		wxStaticText*	item5;
		wxStaticText*	item6;
		wxStaticText*	item7;
		wxBoxSizer*		item8;
		wxStaticText*	item9;
		wxButton*		item10;
		wxButton*		item11;
		wxButton*		item12;
		wxButton*		item13;
		wxStaticText*	item15;
		wxBoxSizer*		item14;
		wxButton*		item16;
		wxButton*		item17;
		wxButton*		item18;
		wxButton*		item19;
		wxBoxSizer*		item20;
		wxStaticText*	item21;
		wxButton*		item22;
		wxButton*		item23;
		wxButton*		item24;
		wxButton*		item25;
		wxBoxSizer*		item26;
		wxStaticText*	item27;
		wxButton*		item28;
		wxButton*		item29;
		wxButton*		item30;
		wxButton*		item31;
		wxBoxSizer*		item32;
		wxStaticText*	item33;
		wxButton*		item34;
		wxButton*		item35;
		wxButton*		item36;
		wxButton*		item37;
		wxBoxSizer*		item38;
		wxStaticText*	item39;
		wxButton*		item40;
		wxButton*		item41;
		wxButton*		item42;
		wxButton*		item43;
		wxBoxSizer*		item44;
		wxStaticText*	item45;
		wxButton*		item46;
		wxButton*		item47;
		wxButton*		item48;
		wxButton*		item49;
		wxBoxSizer*		item50;
		wxStaticText*	item51;
		wxButton*		item52;
		wxButton*		item53;
		wxButton*		item54;
		wxButton*		item55;
		wxBoxSizer*		item56;
		wxButton*		item57;
		wxButton*		item58;

		void			OnOk	(wxCommandEvent & event);
		void			OnColClick (wxCommandEvent & event);
		CCiel*			Ciel;
		wxConfigBase*	pConfig;
		wxDECLARE_EVENT_TABLE();
};

#endif
