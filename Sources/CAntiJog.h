// *****************************************************************************
// *                                                                           *
// *                           CLASS ANTI JOGGER                               *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 19/07/2006                                                           *
// *   CopyRight (c)Neophile 2006                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CANTIJOG_H
#define CANTIJOG_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/dynarray.h>
#include "CtrlLog.h"

class CJogger
{
	public:
		int				Session;
		long			Temps;
		int				Compteur;
		wxString		Nom;
};

WX_DECLARE_OBJARRAY(CJogger, AJogger);

class CAntiJog
{
	private:
		AJogger 		Joggers;
		CCtrlLog*		Logger;
		int				ID;
	public:
		wxConfigBase*	pConfig;
		int				NbEntreeMax;
		int				Delai;
		int				TpsEject;
		bool			EnaAntiJog;
		wxString		MessEject;
		wxColour		MessColour;
						CAntiJog (int id=0);
						~CAntiJog ();
		void			Charge ();
		void			Sauve ();
		void			Add (int Session=0, wxString Nom=_T(""));
		void			Update ();
};

#endif
