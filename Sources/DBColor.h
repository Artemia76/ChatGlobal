// *****************************************************************************
// *                                                                           *
// *                          BASE DE DONNEE COULEURS                          *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 27/11/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef DBCOLOR_H
#define DBCOLOR_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/fileconf.h>

#define NB_COLOR_MAX 100

enum {
	DBC_NOT_EXIST=-1,
	DBC_OK,
	DBC_LIST_FULL,
	DBC_ALREADY_EXIST
};

class CColor
{
	public:
		wxString	Nom;
		wxColour	Couleur;
};

class CDBColor
{
	private:
		int				nb_max;
		int				nb_colors;
		CColor			Colors[NB_COLOR_MAX];
		wxFileConfig*	pConfig;
		void			Sauve		(int id);
	public:
						CDBColor	(int id=0);
						~CDBColor 	();
		int				Identifie	(wxString& Nom);
		wxColour		GetColor	(int id);
		int				SetColor	(int id, wxColour& Color);
		wxString		GetName		(int id);
		int				Remove		(int id);
		int				Add			(wxString& Nom, wxColour& Color);
};

#endif
