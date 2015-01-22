// *****************************************************************************
// *                                                                           *
// *                              CLASS DE BOT                                 *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 15/05/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CBOT_H
#define CBOT_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/vector.h>

#include "CtrlLog.h"
#include "Cpasspriv.h"
#include "CUser.h"

enum
{
	CG_RECO=wxID_HIGHEST
};

class CBot : public wxEvtHandler
{
	public:

	friend class CCtrlAw;
	friend class CListUser;

		bool			Global;			// Mode Global
		bool			CGConAuto;
		bool			CGRecoEna;
		bool			PerteUniv;
		bool			PerteMonde;
		bool			DemCon;
		bool			ConEC;
		bool			EntEC;
		bool			DemDeco;
		bool			ModeReco;
		wxString		PSList;
		wxString		ModoList;
		wxString		EminentList;
		wxString		OwnerList;

		int				CGRecoDelay;	// Temps de Reconnection sur AW
		int				CGRecoRetry;	// Nombres d'essais sur AW
		int				Citoyen;		// Numéro du citoyen
		int				Port;			// Port de l'univers
		int				CGRecoCnt;			// Compteur de tentative de reconnections AW
		int				CGRetente;

		wxString		Monde;			// Nom du Monde
		wxString		Nom;			// Nom du Bot
		wxString		PassWord;		// Mot de Passe Citoyen
		wxString		Univers;		// Adresse de l'univers

// Constructeur et Destructeur
						CBot ();
						~CBot();

// Entiers

		void			Connection	(bool);	// Connection/Deconnection de l'univers
		void			Enter		();	// Entrer/Sortir du monde
		void			Connect		();
		void			Deconnect	();
virtual	void			Update		();
		void			Login_CB	(int rc);
		void			Enter_CB	(int rc);
		void			Tentative	();

		bool			IsOnUniverse	();
		bool			IsOnWorld		();
		int				GetID			();
virtual	void			Sauve			();
virtual	void			Charge			();
		bool			SetInstance		();
		void*			GetInstance		();
		unsigned int	GetUserSession	(wxString&);
		int				GetUserX		(unsigned int);
		int				GetUserY		(unsigned int);
		int				GetUserZ		(unsigned int);
		wxArrayString	GetUserListe	();
		wxString		GetUserIP		(unsigned int);
		wxString		GetUserIP		(wxString&);
		wxString		GetUserName		(unsigned int);
		int				GetUserCitizen	(unsigned int);
		int				GetUserCitizen	(wxString&);
		int				GetUserPrivilege	(unsigned int);
		int				GetUserPrivilege	(wxString&);
	private:

		CPassPriv*			PassPriv;
		void*				Instance;

		bool				On_Universe;		// Etat de la connection univers
		bool				On_World;			// Etat de la connection au monde
		bool				Visible;			// Etat de la visibilité

static	int					NbBot;				// Index statique du nombre de bot


	protected:
		wxTimer*			CGRecoTimer;
		CCtrlLog*			Logger;		// Pointeur du Logger
		wxConfigBase*		pConfig;
		wxVector <CUser>	Users;
		int					ID;					// Identification du bot
		void				OnCGRecoEvent		(wxTimerEvent  & event);
		int					GetUserID			(unsigned int);
		int					GetUserID			(wxString&);
		int 				AddUser				(CUser&);
		int					DelUser				(unsigned int);
		int					DelUser				(wxString&);
		int					SetUserName			(unsigned int, wxString&);
		void				SetUserCoord		(unsigned int Sess,int X=0, int Y=0, int Z=0);
		int					SetUserIP			(unsigned int Sess=0,int IP=0);
		wxDECLARE_EVENT_TABLE();
};

#endif

