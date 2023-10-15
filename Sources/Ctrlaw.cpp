// *****************************************************************************
// *                                                                           *
// *                         CONTROLEUR AW BODY                                *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 22/04/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "Ctrlaw.h"

#include <wx/datetime.h>
#include <wx/tokenzr.h>

#include <Aw.h>

#include "Global.h"

wxBEGIN_EVENT_TABLE(CCtrlAw, wxEvtHandler)
	EVT_TIMER (HEARTBEAT, CCtrlAw::On_HeartBeat)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// Pointeur Static

CCtrlAw* CCtrlAw::PtCCtrlAw = 0;

//------------------------------------------------------------------------------
// Createur
CCtrlAw* CCtrlAw::Create(int Nb,wxWindow* pParent)
{
	if (!PtCCtrlAw)
	{
		PtCCtrlAw = new CCtrlAw(Nb,pParent);
	}
	return PtCCtrlAw;
}

//------------------------------------------------------------------------------
// Tueur

void CCtrlAw::Kill()
{
	if (PtCCtrlAw != 0) delete PtCCtrlAw;
	PtCCtrlAw=0;
}

//------------------------------------------------------------------------------
// Constructeur Privé

CCtrlAw::CCtrlAw (int Nb,wxWindow* pParent)
{
	NbBot=Nb;
	Parent=pParent;
	Bot=0;
	AwInit=false;
	Logger=CCtrlLog::Create();
	pConfig=wxConfigBase::Get();
	AHeure=0;
	Heart = new wxTimer (this, HEARTBEAT);
	ShdEject=false;
}

//------------------------------------------------------------------------------
// Destructeur Privé

CCtrlAw::~CCtrlAw()
{
}

//------------------------------------------------------------------------------
// Initialisation SDK, Instance AW, Table des Events

int CCtrlAw::Init (bool flag)
{
	int rc;
	if ((flag) && (!AwInit))
	{
		if ((rc=aw_init (AW_BUILD)))
		{
			Logger->Log(-1,_("Unable to init the SDK, Reason :"),_T("RED"),false,rc);
			return rc;
		}
		// Installe les events AW
		aw_event_set (AW_EVENT_CHAT, CCtrlAw::On_Chat);
		aw_event_set (AW_EVENT_AVATAR_ADD, CCtrlAw::On_Avatar_Add);
		aw_event_set (AW_EVENT_AVATAR_CHANGE, CCtrlAw::On_Avatar_Change);
		aw_event_set (AW_EVENT_AVATAR_DELETE, CCtrlAw::On_Avatar_Delete);
		aw_event_set (AW_EVENT_WORLD_DISCONNECT, CCtrlAw::On_World_Disconnect);
		aw_event_set (AW_EVENT_UNIVERSE_DISCONNECT, CCtrlAw::On_Universe_Disconnect);
		aw_event_set (AW_EVENT_WORLD_ATTRIBUTES, CCtrlAw::On_World_Attributes);

		// Installe les callbacks AW
		aw_callback_set (AW_CALLBACK_LOGIN, CCtrlAw::On_Login);
		aw_callback_set (AW_CALLBACK_ENTER, CCtrlAw::On_Enter);
		aw_callback_set (AW_CALLBACK_ADDRESS, CCtrlAw::On_Address);
		aw_callback_set (AW_CALLBACK_CITIZEN_ATTRIBUTES, CCtrlAw::On_Citizen_Attributes);

		AwInit=true;
		for (size_t i=0 ; i<NbBot ; i++)
		{
			Bot.push_back(new CBotCG());
			Bot.back()->Charge();
			List.push_back (new CListUser(Parent,Bot.back()));
			Xelag.push_back(new CXelag(Bot.back()));
			Xelag.back()->Charge();
			if (Bot.back()->CGConAuto)
			{
				Bot.back()->Global=true;
				if (Bot.back()->CGRecoEna)
				{
					Bot.back()->CGRecoCnt=0;
					Bot.back()->CGRetente=Bot.back()->CGRecoDelay;
					Bot.back()->ModeReco=true;
				}
				Bot.back()->Connect();
			}
			if (Xelag.back()->XgConAuto)
			{
				if (Xelag.back()->XgRecoEna)
				{
					Xelag.back()->XgRecoCnt=0;
					Xelag.back()->XgRetente=Xelag.back()->XgRecoDelay;
					Xelag.back()->ModeReco=true;
				}
				Xelag.back()->Connect();
			}
		}
		Heart->Start(Base_Temps);
		return 0;
	}
	else if((!flag) && (AwInit))
	{
		Heart->Stop();
		for (wxVector<CXelag*>::iterator i = Xelag.begin() ; i < Xelag.end(); i++)
		{
			if ( (*i)->IsOnXelag())
			{
				(*i)->XgConnect(false);
			}
			delete (*i);
		}
		Xelag.clear();
		for (wxVector<CListUser*>::iterator i = List.begin(); i < List.end(); i++)
		{
			delete (*i);
		}
		List.clear();

		for (wxVector<CBotCG*>::iterator i = Bot.begin() ; i < Bot.end(); i++)
		{
			if ( (*i)->SetInstance())
			{
				(*i)->Connection(false);
			}
			delete (*i);
		}
		Bot.clear();
		aw_term();
		return 0;
	}
	return 1000;
}

//------------------------------------------------------------------------------
// Methode Statique Privées des evenements AW
// Mettez ici votre code à traiter


void CCtrlAw::On_Admin_Worlds_Delete(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Admin_Worlds_Info(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Add(void)
{
	wxString Name,Message;
	CBotCG* Robot;
	CXelag* Xlg;
	CUser User;
	void* Instance;
	User.Session=aw_int(AW_AVATAR_SESSION);
	User.Nom=
	#if AW_BUILD > 77
		aw_string(AW_AVATAR_NAME);
	#else
		wxString(aw_string(AW_AVATAR_NAME), wxConvISO8859_1);
	#endif
	User.Citizen=aw_int(AW_AVATAR_CITIZEN);
	User.Privilege=aw_int(AW_AVATAR_PRIVILEGE);
	User.X=aw_int(AW_AVATAR_X);
	User.Y=aw_int(AW_AVATAR_Y);
	User.Z=aw_int(AW_AVATAR_Z);
	Instance=aw_instance();
	Robot=PtCCtrlAw->GetBotInst(Instance);
	Robot->AddUser(User);
	PtCCtrlAw->List[Robot->GetID()]->Ajoute(User);
	PtCCtrlAw->List[Robot->GetID()]->MajIcones ();
	Xlg=PtCCtrlAw->GetXelag(Robot->GetID());
	Robot->Kling=true;
	Robot->NKling=User.Nom;
	int id;
	id=Robot->DBase->Identifie(User.Nom, User.Citizen);
	Robot->DBase->AddFreq(id);
	Robot->Mess_Bot(User.Nom, 1);
	Robot->Mess_Bot(User.Nom, 7,_T(""), User.Session);
	Message=User.Nom;
	Message.Append(_T(",MBot1"));
	Xlg->EnvoiMess (Message);
	aw_address (User.Session);
	Robot->AntiJog->Add(User.Session, User.Nom);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Change(void)
{
	CBotCG* Robot;
	CUser User;
	void* Instance;
	User.Session=aw_int(AW_AVATAR_SESSION);
	User.Nom=
	#if AW_BUILD > 77
		aw_string(AW_AVATAR_NAME);
	#else
		wxString(aw_string(AW_AVATAR_NAME), wxConvISO8859_1);
	#endif
	Instance=aw_instance();
	Robot=PtCCtrlAw->GetBotInst(Instance);
	if (Robot->GetUserName(User.Session)!=User.Nom)
	{
		Robot->SetUserName(User.Session,User.Nom);
	}
	Robot->SetUserCoord
					(
						User.Session,
						aw_int(AW_AVATAR_X),
						aw_int(AW_AVATAR_Y),
						aw_int(AW_AVATAR_Z)
					);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Delete(void)
{
	CBotCG* Robot;
	CXelag* Xlg;
	void* Instance;
	wxString Message;
	CUser User;
	User.Session=aw_int(AW_AVATAR_SESSION);
	User.Nom=
	#if AW_BUILD > 77
		aw_string(AW_AVATAR_NAME);
	#else
		wxString(aw_string(AW_AVATAR_NAME), wxConvISO8859_1);
	#endif
	Instance=aw_instance();
	Robot=PtCCtrlAw->GetBotInst(Instance);
	if (Robot->DelUser(User.Session)<0)
	{
		Message << _("Avatar_Delete_Error: Name=") << User.Nom << _(", Session=") << User.Session;
		Robot->Logger->Log(Robot->GetID(),Message, _T("RED"));
	}
	PtCCtrlAw->List[Robot->GetID()]->Supprime(User);
	PtCCtrlAw->List[Robot->GetID()]->MajIcones ();
	Xlg=PtCCtrlAw->GetXelag(Robot->GetID());
	Robot->Kloug=true;
	Robot->NKloug=User.Nom;
	Robot->Mess_Bot(User.Nom, 2);
	Message=User.Nom;
	Message.Append(_T(",MBot2"));
	Xlg->EnvoiMess (Message);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Click(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Cell_Begin(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Cell_End(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Cell_Object(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Chat(void)
{
	int Distance=0;
	int Session=aw_int(AW_CHAT_SESSION);
	wxString Message =
	#if AW_BUILD > 77
		aw_string(AW_CHAT_MESSAGE);
	#else
		wxString(aw_string(AW_CHAT_MESSAGE), wxConvISO8859_1);
	#endif
	int Type=aw_int(AW_CHAT_TYPE);
	void* Instance=aw_instance();
	CBotCG* Robot=PtCCtrlAw->GetBotInst(Instance);
	CXelag* Xlg=PtCCtrlAw->GetXelag(Robot->GetID());
	wxString Nom = Robot->GetUserName(Session);
	int Citoyen = Robot->GetUserCitizen(Session);
	int Privilege = Robot->GetUserPrivilege(Session);
	wxString Original=Robot->Analyse(Nom, Session, Citoyen, Message, Type, false, _T(""), Privilege);
	Message=Nom+ _T(",") + Original;
	if (Robot->ExtBride)
	{
		Distance=Robot->Distance(Session, 0, true);
		if (Distance < Robot->ExtDistance) Xlg->EnvoiMess (Message);
	}
	else Xlg->EnvoiMess (_T("PRIVMSG #lobby : From (DeltaWorld) ") + Message);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Console_Message(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Add(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Click(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Delete(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_select(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Teleport(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Universe_Attributes(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Url(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Attributes(void)
{
	CBotCG* Robot;
	Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->PSList=_T("");
	Robot->ModoList=_T("");
	Robot->EminentList=_T("");
	wxStringTokenizer Droits(
	#if AW_BUILD > 77
		aw_string(AW_WORLD_PUBLIC_SPEAKER_RIGHT)
	#else
		wxString(aw_string(AW_WORLD_PUBLIC_SPEAKER_RIGHT), wxConvISO8859_1)
	#endif
	,_T(", "));
	while ( Droits.HasMoreTokens() )
	{
		Robot->PSList << _T("[")
								<< Droits.GetNextToken()
								<< _T("]");
	}
	Droits.SetString (
	#if AW_BUILD > 77
		aw_string(AW_WORLD_EJECT_RIGHT)
	#else
		wxString(aw_string(AW_WORLD_EJECT_RIGHT), wxConvISO8859_1)
	#endif
	,_T(", "));
	while ( Droits.HasMoreTokens() )
	{
		Robot->ModoList << _T("[")
								<< Droits.GetNextToken()
								<< _T("]");
	}
	Droits.SetString (
	#if AW_BUILD > 77
		aw_string(AW_WORLD_EMINENT_DOMAIN_RIGHT)
	#else
		wxString(aw_string(AW_WORLD_EMINENT_DOMAIN_RIGHT), wxConvISO8859_1)
	#endif
	,_T(", "));
	while ( Droits.HasMoreTokens() )
	{
		Robot->EminentList << _T("[")
								<< Droits.GetNextToken()
								<< _T("]");
	}
	if ((!aw_bool(AW_WORLD_DISABLE_CHAT)) && (!Robot->BlockCG))
	{
		aw_bool_set(AW_WORLD_DISABLE_CHAT,true);
		aw_world_attributes_change ();
	}
	PtCCtrlAw->List[Robot->GetID()]->MajIcones();
}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Disconnect(void)
{
	CBotCG* Robot;
	Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->PerteMonde=true;
	Robot->Kling=false;
	Robot->Kloug=false;
	Robot->PSList=_T("");
	Robot->ModoList=_T("");
	Robot->EminentList=_T("");
}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Info(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_Begin(void)
{

}

void CCtrlAw::On_Terrain_Changed(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_Data(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_End(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Universe_Disconnect(void)
{
	CBotCG* Robot;
	Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->PerteUniv=true;
	Robot->Kling=false;
	Robot->Kloug=false;
}

//------------------------------------------------------------------------------
// Gestion des callbacks

void CCtrlAw::On_Login (int rc)
{
	CBotCG* Robot;
	Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->Login_CB(rc);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter (int rc)
{
	CBotCG* Robot;
	Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->Enter_CB(rc);
	if (!rc) 	Robot->OwnerList.Printf(_T("[%d]"),Robot->Citoyen);
}


//------------------------------------------------------------------------------

void CCtrlAw::On_Address (int rc)
{
	CBotCG* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	if (rc) Robot->Logger->Log (Robot->GetID(),_("Unable to resolve IP, Reason:"),_T("RED"),false,rc);
	else Robot->SetUserIP (aw_int(AW_AVATAR_SESSION) ,aw_int(AW_AVATAR_ADDRESS));
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Citizen_Attributes (int rc)
{
	CBotCG* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	wxString Resultat;
	Resultat	<< _("Result of Citizen Search:")
				<< _("\nNumber : ") << aw_int(AW_CITIZEN_NUMBER)
				<< _("\nName : ") << aw_string (AW_CITIZEN_NAME);
	Robot->ConMess (Robot->SessionReq, Resultat,45,145,244, true);
	Robot->SessionReq=0;
}

//------------------------------------------------------------------------------

CBotCG* CCtrlAw::GetBot (unsigned int num)
{
	if ( (num >= NbBot) || (!AwInit) ) return 0;
	return Bot[num];
}

//------------------------------------------------------------------------------

CListUser* CCtrlAw::GetList (unsigned int num)
{
	if ( (num >= NbBot) || (!AwInit) ) return 0;
	return List[num];
}

//------------------------------------------------------------------------------

CBotCG* CCtrlAw::GetBotInst(void* Instance)
{
	for (wxVector<CBotCG*>::iterator i = Bot.begin(); i< Bot.end(); i++)
	{
		if ((*i)->GetInstance()==Instance)
		{
			return (*i);
		}
	}
	return 0;
}

//------------------------------------------------------------------------------

CXelag* CCtrlAw::GetXelag (unsigned int num)
{
	if ( (num >= NbBot) || (!AwInit) ) return 0;
	return Xelag[num];
}

//------------------------------------------------------------------------------

void CCtrlAw::On_HeartBeat (wxTimerEvent& WXUNUSED(event))
{
	bool njour=false;
	Horloge = wxDateTime::Now();
	if ((AHeure != Horloge.GetHour()) && (AHeure==23)) njour=true;
	AHeure=Horloge.GetHour();
	aw_wait(0);
	for (wxVector<CBotCG*>::iterator i = Bot.begin(); i< Bot.end(); i++)
	{
		(*i)->SetInstance();
		(*i)->Update();
		if (ShdEject) (*i)->Eject ();
		if ((*i)->IsOnWorld()) (*i)->Ciel->MAJ ();
		Xelag[i- Bot.begin()]->Update ();
		(*i)->AntiJog->Update ();
		if (njour) Logger->Log(i- Bot.begin(),_("A new day happen"), _T("BLUE"), true);
	}
	if (ShdEject) ShdEject=false;
	if (CBotCG::Ejecte)
	{
		ShdEject=true;
		CBotCG::Ejecte=false;
	}
}
