// *****************************************************************************
// *                                                                           *
// *                        CLASS CLIENT XELAGSERVER                           *
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

#ifndef CXELAGSERV_H
#define CXELAGSERV_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/socket.h>
#include <wx/config.h>

#include "CtrlLog.h"
#include "Cpasspriv.h"
#include "CBotCG.h"

enum
{
	SOCKET_ID=wxID_HIGHEST,
	XG_RECO,
	XG_HB
};

class CXelag : public wxEvtHandler
{
	public:
		friend class CCtrlAw;
	private:
		wxSocketClient*	SockXlg;
		wxTimer*		XgRecoTimer;
		wxTimer*		XgHeartBeat;
		CCtrlLog*		Logger;
		CPassPriv*		PassPriv;

		bool			ConEC;
		bool			DemCon;
		bool			On_Xelag;
		bool			FirstCon;

		int				ID;
static	int				NbXelag;

		void			Tentative		();
		wxArrayString	TamponTab;

	public:

		wxConfigBase	*pConfig;
		CBotCG			*Bot;

		bool			XgConAuto;
		bool			XgRecoEna;
		bool			XgCGEna;
		bool			ModeReco;
		wxString		CGON ();
		wxString		CGOFF ();

		int				XgCompt;
		int				XgPort;				// Port du serveur Xelag
		int				XgRecoDelay;
		int				XgRecoRetry;
		int				XgRecoCnt;
		int				XgRetente;

		wxString		XgHost;				// Adresse du serveur Xelag
		wxString		XgLogin;			// Login du compte xelag
		wxString		XgPassWord;			// Mdp du compte Xelag

						CXelag			(CBotCG*);
						~CXelag			();

		void			Connect		();
		void			Deconnect	();
		bool			IsOnXelag	();
		void			Charge			();
		void			Sauve			();
		void			EnvoiMess
						(
							wxString Message,
							int Type=0,
							wxString Name=_T("")
						);
		void			Update			();

	protected:
		void			XgConnect		(bool);// Connection/Deconnection au serveur Xelag
		void			OnXgRecoEvent	(wxTimerEvent  & event);
		void			OnXgHeartBeat   (wxTimerEvent& event);
		void			OnXelagEvent	(wxSocketEvent & event);
		wxDECLARE_EVENT_TABLE();
};

#endif
