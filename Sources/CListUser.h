// *****************************************************************************
// *                                                                           *
// *                            CLASS LIST USER                                *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 25/03/2006                                                           *
// *   CopyRight (c)Neophile 2005-2006                                         *
// *                                                                           *
// *   Modifié le 07/09/2006                                                   *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CLISTUSER_H
#define CLISTUSER_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/wxprec.h>

#include <wx/listctrl.h>
#include "COutils.h"
#include "CBotCG.h"

enum
{
	LU_LISTCTRL = 20600,
	LU_MUTEUSER,
	LU_NOM
};

class CListUser : public wxListCtrl, public COutils
{
	public:
						CListUser		( wxWindow* parent, CBotCG* pBot);
						~CListUser		();
		wxImageList*	Images;
		int				Ajoute			(CUser Utilisateur);
		int				Change			(CUser Utilisateur);
		int				Supprime		(CUser Utilisateur);
		void			EffaceTout		();
		void			MajIcones		();
	private:
		wxMenu*			Menu;
		CBotCG*			Bot;
	protected:
		void			On_Right_Click	(wxListEvent& event);
		void			On_Mute			(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
};


#endif
