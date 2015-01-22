// *****************************************************************************
// *                                                                           *
// *                          BASE DE DONNEE USER                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 22/04/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef DBASE_H
#define DBASE_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

#include <wx/fileconf.h>

#include "CUser.h"

#define NB_USER_MAX 200

struct SStats
{
	int PCCitoyen;
	int PCTouriste;
	int MFreq;
	int MKling;
	int MKloug;
	int NbUtil;
};

class CDBase
{
	private:
		int				nb_max;
		int				nb_user;
		wxFileConfig*	pConfig;
		CUser			Users[NB_USER_MAX];
		void			Sauve		(int id);
	public:
						CDBase			(int id=0);
						~CDBase 		();
		void			AddFreq			(int id);
		void			AddKling		(int id);
		void			AddKloug		(int id);
		int				Identifie		(wxString& Nom, unsigned int Citoyen=0);
		wxColour		GetColor		(int id);
		bool			GetGras			(int id);
		bool			GetItalique		(int id);
		wxString		GetName			(int id);
		int				GetNbKling		(int id);
		int				GetNbKloug		(int id);
		bool			GetQuali		(int id);
		int				GetRankKling	(int rank);
		int				GetRankKloug	(int rank);
		bool			GetTitre		(int id);
		wxString		GetTxtQuali		(int id);
		wxString		GetTxtTitre		(int id);
		void			SetColor		(int id, wxColour& Couleur);
		void			SetGras			(int id, bool Gras);
		void			SetItalique		(int id, bool Ital);
		void			SetQuali		(int id, bool Quali);
		void			SetTitre		(int id, bool Titre);
		void			SetTxtQuali		(int id, wxString& Quali);
		void			SetTxtTitre		(int id, wxString& Titre);
		void			RstKlingKloug	(void);
		void            SetMuteMode     (int id, bool Mute);
		bool			GetMuteMode		(int id);
		bool			GetGlobMode		(int id);
		void			SetGlobMode		(int id, bool Glob);
		bool			GetReachable	(int id);
		void			SetReachable	(int id, bool Reach);
		int				Search			(wxString Nom);
		SStats			Satistic		();
		wxArrayString	GetMuteList		();
};

#endif

