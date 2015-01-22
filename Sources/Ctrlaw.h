// *****************************************************************************
// *                                                                           *
// *                         CONTROLEUR AW HEADER                              *
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

#ifndef CTRLAW_H
#define CTRLAW_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/wxprec.h>
#include <wx/vector.h>
#include <wx/config.h>

#include "CtrlLog.h"
#include "CBotCG.h"
#include "CXelagServer.h"
#include "CListUser.h"

enum
{
	HEARTBEAT=wxID_HIGHEST
};

class CCtrlAw : public wxEvtHandler
{
	public:

static		CCtrlAw*			Create (int Nb,wxWindow* pParent);
			CBotCG*				GetBot (unsigned int num);
			int					Init(bool); // On/off de la Dll
			CBotCG*				GetBotInst(void* Instance);
			CXelag*				GetXelag(unsigned int num);
			CListUser*			GetList(unsigned int num);
static		void				Kill();

	private:

static		CCtrlAw*			PtCCtrlAw;
			CCtrlLog*			Logger;
			wxVector<CBotCG*>	Bot;
			wxVector<CXelag*>	Xelag;
			wxVector<CListUser*> List;
			wxConfigBase*		pConfig;
			wxTimer*			Heart;
			wxWindow*			Parent;
			bool				AwInit;
			size_t				NbBot;
			wxDateTime			Horloge;
			int					AHeure;
			bool				ShdEject;

								CCtrlAw					(int Nb,wxWindow* pParent);
								~CCtrlAw				();

static		void				On_Admin_Worlds_Delete	();
static		void				On_Admin_Worlds_Info	();
static		void				On_Avatar_Add			();
static		void				On_Avatar_Change		();
static		void				On_Avatar_Delete		();
static		void				On_Avatar_Click			();
static		void				On_Cell_Begin			();
static		void				On_Cell_End				();
static		void				On_Cell_Object			();
static		void				On_Chat					();
static		void				On_Console_Message		();
static		void				On_Object_Add			();
static		void				On_Object_Click			();
static		void				On_Object_Delete		();
static		void				On_Object_select		();
static		void				On_Teleport				();
static		void				On_Universe_Attributes	();
static		void				On_Url					();
static		void				On_World_Attributes		();
static		void				On_World_Disconnect		();
static		void				On_World_Info			();
static		void				On_Terrain_Begin		();
static		void				On_Terrain_Changed		();
static		void				On_Terrain_Data			();
static		void				On_Terrain_End			();
static		void				On_Universe_Disconnect	();

// Callbacks AW

static		void				On_Login				(int rc);
static		void				On_Enter				(int rc);
static		void				On_ObjDelete			(int rc);
static		void				On_Address				(int rc);
static		void				On_Citizen_Attributes	(int rc);

// Battement de Coeur AW
			void				On_HeartBeat			(wxTimerEvent & event);
	protected:
			wxDECLARE_EVENT_TABLE();
};

#endif
