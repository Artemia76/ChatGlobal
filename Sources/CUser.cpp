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
// *                         DEFINITION DES MEMBRES                            *
// *                                                                           *
// *****************************************************************************

#include "CUser.h"

CUser::CUser
		(
			wxString Name,
			unsigned int Sess,
			unsigned int Cit,
			unsigned int Priv,
			wxString ip
		)
{
	Nom=Name;
	Session=Sess;
	Citizen=Cit;
	Privilege=Priv;
	IP=ip;
	Gras=false;
	Italique=false;
	Titre=false;
	Quali=false;
	Marked=false;
	Freq=0;
	Kling=0;
	Kloug=0;
	TexteTi=_T("");
	TexteQu=_T("");
	X=0;
	Y=0;
	Z=0;
	Mute=false;
}

