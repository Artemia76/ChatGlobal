// *****************************************************************************
// *                                                                           *
// *                  BOITE DE DIALOGUE DE PERSONNALISATION                    *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 14/05/2005                                                           *
// *   Modifié le 31/01/2007                                                   *
// *   CopyRight (c)Neophile 2005-2007                                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DECLARATION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#ifndef PERSODIAL_H
#define PERSODIAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/spinctrl.h>

#include "COutils.h"

#include "CBotCG.h"

enum
{
	PERSO_TEXT = wxID_HIGHEST,
	ID_ENAMESSAC,
	ID_TXTMESSAC,
	ID_CLRMESSAC,
	ID_ENAANNARR,
	ID_TXTANNARR,
	ID_CLRANNARR,
	ID_ENAANNDEP,
	ID_TXTANNDEP,
	ID_CLRANNDEP,
	ID_ENAANNKLI,
	ID_TXTANNKLI,
	ID_CLRANNKLI,
	ID_ENAANNKLO,
	ID_TXTANNKLO,
	ID_CLRANNKLO,
	ID_CLRANTIJOG
};

class CPersoDial : public wxDialog, public COutils
{
	public:
						CPersoDial
						(
							wxWindow *parent,
							wxWindowID id,
							CBotCG *Robot,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~CPersoDial ();
virtual	bool			Validate();
	private:
		CBotCG*			Bot;
		wxConfigBase*	pConfig;
		wxBoxSizer*		Boite;
		wxBoxSizer*		Ligne1;
		wxCheckBox*		Check1;
		wxTextCtrl*		Edit1;
		wxButton*		Couleur1;
		wxBoxSizer*		Ligne2;
		wxCheckBox*		Check2;
		wxTextCtrl*		Edit2;
		wxButton*		Couleur2;
		wxBoxSizer*		Ligne3;
		wxCheckBox*		Check3;
		wxTextCtrl*		Edit3;
		wxButton*		Couleur3;
		wxBoxSizer*		Ligne4;
		wxCheckBox*		Check4;
		wxTextCtrl*		Edit4;
		wxButton*		Couleur4;
		wxBoxSizer*		Ligne5;
		wxCheckBox*		Check5;
		wxTextCtrl*		Edit5;
		wxButton*		Couleur5;
		wxBoxSizer*		Bridage;
		wxCheckBox*		ChatBride;
		wxSpinCtrl*		ChatDistance;
		wxBoxSizer*		ExtBridage;
		wxCheckBox*		ExtBride;
		wxSpinCtrl*		ExtDistance;
		wxStaticText*	Text1;
		wxTextCtrl*		ExtCoord;
		wxBoxSizer*		AntiJog;
		wxCheckBox*		EnaAntiJogger;
		wxStaticText*	AntiJogTempsTxt;
		wxSpinCtrl*		AntiJogTemps;
		wxStaticText*	AntiJogNbTxt;
		wxSpinCtrl*		AntiJogNb;
		wxStaticText*	AntiJogEjecTxt;
		wxSpinCtrl*		AntiJogEjec;
		wxBoxSizer*		AntiJog2;
		wxStaticText*	AntiJogMessTxt;
		wxTextCtrl*		AntiJogMess;
		wxButton*		AntiJogBout;
		wxBoxSizer*		Boutons;
		wxButton*		Annuler;
		wxButton*		Ok;
protected:
		void			OnOk(wxCommandEvent & event);
		void			OnCouleur(wxCommandEvent & event);
		DECLARE_EVENT_TABLE()
};

#endif

