// *****************************************************************************
// *                                                                           *
// *                   ChatGlobal Fenetre Principale HEADER                    *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Neophile                                                      *
// *   Le 11/06/2005                                                           *
// *   Modifié Le 28/01/2007                                                   *
// *   CopyRight (c)Neophile 2005-2007                                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef MAINFRAME_H
#define MAINFRAME_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/wxprec.h>
#include <wx/splitter.h>
#include <wx/fileconf.h>
#include <wx/toolbar.h>

#include "CtrlLog.h"
#include "CBotCG.h"
#include "Ctrlaw.h"
#include "CTaskBar.h"
#include "CListUser.h"
#include "CXelagServer.h"
#include "COutils.h"
#include "CHorBox.h"
#include "CColBox.h"

enum MF_COMMANDS
{
	MF_MENU_EXIT = wxID_HIGHEST,
	MF_MENU_AWCONECT,
	MF_MENU_AWOPTION,
	MF_MENU_XGCONECT,
	MF_MENU_XGOPTION,
	MF_MENU_PERSO,
	MF_MENU_LOG,
	MF_MENU_CENA,
	MF_MENU_CHORO,
	MF_MENU_CCOLOR,
	MF_MENU_AIDE,
	MF_MENU_APROPOS,
	MF_MENU_FORUM,
	MF_MENU_BOT,
	MF_BTN_GAU,
	MF_BTN_DRO,
	MF_UPDATE
};


// Classe de notre fenêtre principale


class CMainFrame : public wxFrame, public COutils
{
	private:
		CCtrlAw*			CtrlAw;
		wxMenuBar*			MenuBar;
		wxMenu*				MenuBot;
		wxMenu*				MenuXg;
		wxMenu*				MenuAw;
		wxMenu*				MenuOptions;
		wxMenu*				MenuCiel;
		wxMenu*				MenuAide;

		wxToolBar*			Panel;
		CCtrlLog*			Logger;
		wxTextCtrl*			FenLog;
		wxBoxSizer* 		SizerPrin;
		CListUser*			Liste;
		wxConfigBase*		pConfig;
		wxTimer*			TUpdate;
		wxLocale&			m_locale;
		int					Bot_Sel;
		// Maintenance des icones
		int					ABot;
		bool				AConnect;
		bool				AXgConnect;

		CBotCG*				Bot;
		CXelag*				Xelag;
		CTaskBar*			TaskBar;

		void ChoixBot		(int NumBot);
	public:
							CMainFrame (wxLocale& locale);
	virtual					~CMainFrame ();
	protected:
		void				OnBot		(wxCommandEvent & event);
		void				OnConnectAw	(wxCommandEvent & event);
		void				OnConnectXg	(wxCommandEvent & event);
		void				OnExit		(wxCommandEvent & event);
		void				OnOptionsAw	(wxCommandEvent & event);
		void				OnOptionsXg	(wxCommandEvent & event);
		void				OnLog		(wxCommandEvent & event);
		void				OnPerso		(wxCommandEvent & event);
		void				OnCielEna	(wxCommandEvent & event);
		void				OnCielHoro	(wxCommandEvent & event);
		void				OnCielColo	(wxCommandEvent & event);
		void				OnAide		(wxCommandEvent & event);
		void				OnForum		(wxCommandEvent & event);
		void				OnAPropos	(wxCommandEvent & event);
		void				OnBotSup	(wxCommandEvent & event);
		void				OnBotInf	(wxCommandEvent & event);
		void				OnIconize	(wxIconizeEvent & event);
		void				OnTUpdate	(wxTimerEvent& event);
		void				OnCloseWindow (wxCloseEvent& event);
		wxDECLARE_EVENT_TABLE();
};

#endif
