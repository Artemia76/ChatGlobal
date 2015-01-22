// *****************************************************************************
// *                                                                           *
// *                       CLASSE DE GESTION DU CIEL	                       *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 27/01/2007                                                           *
// *   CopyRight (c)Neophile 2007                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CIEL_H
#define CIEL_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/fileconf.h>

#include "CtrlLog.h"

class CCiel
{
	private :
	wxFileConfig*	pConfig;
	CCtrlLog*		Logger;
	void			CalcCoul (wxColour& C1, wxColour& C2, wxColour& Re, int hd, int hf , int h);
	public :
					CCiel (int id);
					~CCiel ();
	int				Top;
	int				hdl,mdl;
	int				hfl,mfl;
	int				hdc,mdc;
	int				hfc,mfc;
	wxString		Soleil;
	wxString		MSoleil;
	int				TSoleil;
	wxString		Lune;
	wxString		MLune;
	int				TLune;
	wxColour		NN,NS,NO,NE,NZ,ND,NA,NL;
	wxColour		AN,AS,AO,AE,AZ,AD,AA,AL;
	wxColour		JN,JS,JO,JE,JZ,JD,JA,JL;
	wxColour		CN,CS,CO,CE,CZ,CD,CA,CL;
	bool			Enabled;
	void 			Sauve ();
	void 			MAJ();
};

#endif
