// *****************************************************************************
// *                                                                           *
// *                               CLASS USER                                  *
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

#ifndef CUSER_H
#define CUSER_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/wxprec.h>

class CUser
{
	public:
						CUser
						(
							wxString Name=_T(""),
							unsigned int Sess=0,
							unsigned int Cit=0,
							unsigned int Priv=0,
							wxString ip=_T("0.0.0.0")
						);
		wxString 		Nom;
		unsigned int	Session;
		unsigned int	Citizen;
		unsigned int	Privilege;
		wxString		IP;
		bool			Gras;
		bool			Italique;
		bool			Titre;
		bool			Quali;
		bool			Marked;
		bool			Glob_Mode;
		bool			Reachable;
		int				Freq;
		int				Kling;
		int				Kloug;
		wxString		TexteTi;
		wxString		TexteQu;
		wxColour		Couleur;
		int				X;
		int				Y;
		int				Z;
		bool            Mute;
};

#endif
