// *****************************************************************************
// *                                                                           *
// *                              CLASS DE BOT                                 *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 16/05/2005                                                           *
// *   CopyRight (c)Neophile 2005-2006                                         *
// *   Modifié le 11/11/2006                                                   *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                          DEFINITION DES MEMBRES                           *
// *                                                                           *
// *****************************************************************************

#include "CBot.h"

#include <aw.h>

// Event du Bot
wxBEGIN_EVENT_TABLE(CBot, wxEvtHandler)
	EVT_TIMER  (CG_RECO,   CBot::OnCGRecoEvent)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------

int CBot::NbBot = 0;

//------------------------------------------------------------------------------
// Contructeur

CBot::CBot ()
{
	pConfig = wxConfigBase::Get();
	ID=NbBot;
// Déclaration des instances
	CGRecoTimer = new wxTimer(this, CG_RECO);
	Logger = CCtrlLog::Create();
	PassPriv = CPassPriv::Create();

// Initialisation des variables internes

	NbBot++;
	Global=true;
	On_Universe=false;
	On_World=false;
	Visible=false;
	CGRecoCnt=0;
	PerteUniv=false;
	PerteMonde=false;
	Instance=0;
	DemCon=false;
	ConEC=false;
	EntEC=false;
	DemDeco=false;
	ModeReco=false;
	if (Logger->GetLog(ID)) Logger->Log(ID,_("Recording Started"),_T("ORANGE"), true);
}

//------------------------------------------------------------------------------
// Destructeur

CBot::~CBot ()
{
	if (On_World || On_Universe) Connection(false);
	if (Logger->GetLog(ID)) Logger->Log(ID,_("Recording Stopped"),_T("ORANGE"), true);
}

//------------------------------------------------------------------------------
// Methode de connection

void CBot::Connect()
{
	if ((!ConEC) && (!EntEC) && (!DemCon) && (!DemDeco) && (!On_Universe) && (!On_World)) DemCon=true;
}

//------------------------------------------------------------------------------
// Methode de Déconnection

void CBot::Deconnect()
{
	if ((!ConEC) && (!EntEC) && (!DemCon) && (!DemDeco) && ((On_Universe) || (On_World))) DemDeco=true;
}

//------------------------------------------------------------------------------
// Methode d'entrée/sortie d'univers

void CBot::Connection(bool flag)
{
// Variables Internes
	wxString Message, s;
	int rc;
	if (flag)
	{
#if AW_BUILD>77
		if ((rc=aw_create(Univers, Port, &Instance))!=0)
#else
        if ((rc=aw_create(Univers.mb_str(), Port, &Instance))!=0)
#endif
		{
			Logger->Log(ID,_("Unable to create instance, Reason : "), _T("RED"), false, rc);
			DemCon=false;
			if (ModeReco) Tentative();
		}
		else
		{
			Logger->Log(ID,_("Instance Initialized."), _T("BLUE"));
			aw_int_set (AW_LOGIN_OWNER, Citoyen);
#if AW_BUILD>77
            aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord);
            aw_string_set (AW_LOGIN_APPLICATION, _T("Chat Global"));
            aw_string_set (AW_LOGIN_NAME,Nom);
#else
			aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord.To8BitData());
			aw_string_set (AW_LOGIN_APPLICATION, "Chat Global");
			aw_string_set (AW_LOGIN_NAME,Nom.To8BitData());
#endif
			aw_login();
			ConEC=true;
			CGRecoTimer->Start(15000,wxTIMER_ONE_SHOT);
		}
	}
	else
	{
		Users.clear();
	    aw_bool_set(AW_WORLD_DISABLE_CHAT,false);
	    aw_world_attributes_change ();
		aw_wait(0);
		aw_destroy();
		Instance=0;
		Logger->Log(ID,_("Disconnected from Universe "),_T("BLUE"));
		On_Universe=false;
		On_World=false;
		DemDeco=false;
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande de connection

void CBot::Login_CB(int rc)
{
	ConEC=false;
	if (CGRecoTimer->IsRunning()) CGRecoTimer->Stop();
	if (rc)
	{
		DemCon=false;
		Logger->Log(ID,_("Unable to join the universe, Reason :"), _T("RED"), false, rc);
		aw_destroy();
		if (ModeReco) Tentative();
	}
	else
	{
		Logger->Log(ID,_("Connected on Universe"), _T("BLUE"));
		On_Universe=true;
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande d'entrée sur un monde

void CBot::Enter_CB(int rc)
{
	wxString Message;
	EntEC=false;
	DemCon=false;
	if (rc)
	{
		DemCon=false;
		Message.Append (_("Unable to connect on world "));
		Message.Append (Monde);
		Message.Append (_(",Reason: "));
		Logger->Log(ID,Message, _T("RED"), false, rc);
		aw_destroy();
		On_Universe=false;
		On_World=false;
		if (ModeReco) Tentative();
	}
	else
	{
		Message.Append (_("Connected on world "));
		Message.Append (Monde);
		Logger->Log(ID,Message, _T("BLUE"));
		On_World=true;
		ModeReco=false;
		if (Visible)
		{
			aw_state_change();
		}
	}
}
//------------------------------------------------------------------------------
// Methode d'entrée ou de sortie d'un monde

void CBot::Enter()
{
	aw_bool_set (AW_ENTER_GLOBAL, Global);
	aw_enter(
	#if AW_BUILD > 77
		Monde);
	#else
		Monde.mb_str());
	#endif
	EntEC=true;
}

//------------------------------------------------------------------------------
// Charge les Paramètres du bot

void CBot::Charge ()
{
	wxString ParcPath = ::wxGetCwd();
	wxString s,S;
	bool Log;
	S.Printf(_T("Bot%02d/"),ID);
	pConfig->Read( S + _T("/Univers"), &Univers, _T("auth.activeworlds.com"));
	pConfig->Read( S + _T("/Monde"), &Monde, _T(""));
	pConfig->Read( S + _T("/Citoyen"), &Citoyen, 0);
	pConfig->Read( S + _T("/PassPriv"), &s, _T(""));
	PassWord=PassPriv->Decode(s);
	pConfig->Read( S + _T("/Nom"), &Nom, _T("Bot"));
	pConfig->Read( S + _T("/Port"), &Port, 6670);
	pConfig->Read( S + _T("/AutoConnect"), &CGConAuto, false);
	pConfig->Read( S + _T("/Delai"), &CGRecoDelay, 15);
	pConfig->Read( S + _T("/Essais"), &CGRecoRetry, 3);
	pConfig->Read( S + _T("/Log"), &Log, false);
	Logger->SetLog(ID , Log);
	if (CGRecoRetry != 0) CGRecoEna=true;
	else CGRecoEna=false;
}

//------------------------------------------------------------------------------
// Sauvegarde les paramètres du bot

void CBot::Sauve ()
{
	wxString S;
	S.Printf(_T("Bot%02d/"),ID);
	pConfig->Write( S + _T("/Univers") ,Univers);
	pConfig->Write( S + _T("/Monde") ,Monde);
	pConfig->Write( S + _T("/Citoyen") ,Citoyen);
	pConfig->Write( S + _T("/PassPriv") ,PassPriv->Code(PassWord));
	pConfig->Write( S + _T("/Nom") ,Nom);
	pConfig->Write( S + _T("/Port") ,Port);
	pConfig->Write( S + _T("/AutoConnect") , CGConAuto);
	pConfig->Write( S + _T("/Delai")  , CGRecoDelay);
	pConfig->Write( S + _T("/Essais") , CGRecoRetry);
	pConfig->Write( S + _T("/Log") , Logger->GetLog(ID));
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------
// Méthode de reconnection automatique du chat global

void CBot::OnCGRecoEvent (wxTimerEvent& WXUNUSED(event))
{
	if (ConEC)
	{
		Login_CB(1000);
	}
	else
	{
		Connect();
	}
}

//------------------------------------------------------------------------------
// Tentatives de nouvelle connection

void CBot::Tentative ()
{
	wxString Tampon;
	if ((CGRecoCnt<CGRecoRetry) || (CGRecoRetry < 0))
	{
		Tampon.Printf(_("A reconnection will be tryed in %d sec."),CGRetente);
		Logger->Log(ID,Tampon,_T("RED"));
		CGRecoTimer->Start(CGRetente * 1000,wxTIMER_ONE_SHOT);
		if (CGRecoRetry > (-1)) CGRecoCnt++;
		if (CGRetente < 900) CGRetente = CGRetente * 2;
	}
	else
	{
		Logger->Log(ID,_("End of attempts"),_T("RED"));
		ModeReco=false;
	}
}

//------------------------------------------------------------------------------
// Retourne l'état connection sur un monde

bool CBot::IsOnWorld()
{
	return On_World;
}

//------------------------------------------------------------------------------
// Retourne l'état connecté sur l'univers

bool CBot::IsOnUniverse()
{
	return On_Universe;
}

//------------------------------------------------------------------------------
// Mises à jours périodiques

void CBot::Update ()
{
	wxString Message;
	if (PerteUniv || PerteMonde)
	{
		if (PerteUniv) Message=_("Connection lost with universe ") + Univers + _T(".");
		else Message=_("Connection lost with the world ") + Monde + _T(".");
		Logger->Log(ID, Message, _T("RED") );
		PerteUniv=false;
		PerteMonde=false;
		On_Universe=false;
		On_World=false;
		Users.clear();
		aw_destroy();
		Instance=0;
		if (CGRecoEna)
		{
			CGRecoCnt=0;
			CGRetente=CGRecoDelay;
			Tentative();
			ModeReco=true;
		}
	}
	if (DemCon && (!On_Universe) && (!ConEC)) Connection(true);
	if (DemCon && On_Universe && (!On_World) && (!EntEC)) Enter();
	if (DemDeco) Connection(false);
	if (CGRecoTimer->IsRunning() && (!ConEC) && (!ModeReco)) CGRecoTimer->Stop();
}

//------------------------------------------------------------------------------
// Retourne l'ID

int CBot::GetID()
{
	return ID;
}

//------------------------------------------------------------------------------
// On Règle l'instance sur notre bot actuel

bool CBot::SetInstance ()
{
	if (!Instance) return false;
	aw_instance_set(Instance);
	return true;
}

//------------------------------------------------------------------------------
// On retourne l'instance du bot

void* CBot::GetInstance ()
{
	return Instance;
}

//------------------------------------------------------------------------------

int	CBot::GetUserX (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID > -1) return Users[ID].X;
	else return 0;
}

//------------------------------------------------------------------------------

int	CBot::GetUserY (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID > -1) return Users[ID].Y;
	else return 0;
}

//------------------------------------------------------------------------------

int	CBot::GetUserZ (unsigned int Sess)
{

	int ID=GetUserID(Sess);
	if (ID > -1) return Users[ID].Z;
	else return 0;
}

//------------------------------------------------------------------------------

int CBot::GetUserID(unsigned int Sess)
{
	for (wxVector<CUser>::iterator i= Users.begin(); i< Users.end(); i++)
	{
		if (i->Session==Sess) return i - Users.begin();
	}
	return -1;
}

//------------------------------------------------------------------------------

int CBot::GetUserID(wxString& Nom)
{
	Nom.MakeUpper();
	for (wxVector<CUser>::iterator i= Users.begin(); i< Users.end(); i++)
	{
		if (i->Nom.Upper()==Nom) return i - Users.begin();
	}
	return -1;
}

//------------------------------------------------------------------------------

wxArrayString CBot::GetUserListe ()
{
	wxArrayString Resultat;
	for (wxVector<CUser>::iterator i= Users.begin(); i< Users.end(); i++)
	{
		Resultat.Add
			(
				i->Nom +
				_T(" : ") +
				i->IP
			);
	}
	return Resultat;
}

//------------------------------------------------------------------------------

unsigned int CBot::GetUserSession (wxString& Nom)
{
	int ID=GetUserID(Nom);
	if (ID<0) return 0;
	return Users[ID].Session;
}

//------------------------------------------------------------------------------

wxString CBot::GetUserIP (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID<0) return _T("0.0.0.0");
	return Users[ID].IP;
}

//------------------------------------------------------------------------------

wxString CBot::GetUserIP (wxString& Nom)
{
	int ID=GetUserID(Nom);
	if (ID<0) return _T("0.0.0.0");
	return Users[ID].IP;
}

//------------------------------------------------------------------------------

wxString CBot::GetUserName (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID<0) return _T("");
	return Users[ID].Nom;
}

//------------------------------------------------------------------------------

int CBot::GetUserCitizen (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID<0) return -1;
	return Users[ID].Citizen;
}

//------------------------------------------------------------------------------

int CBot::GetUserCitizen (wxString& Nom)
{
	int ID=GetUserID(Nom);
	if (ID<0) return -1;
	return Users[ID].Citizen;
}

//------------------------------------------------------------------------------

int CBot::AddUser (CUser& Utilisateur)
{
	if (Utilisateur.Nom==_T("")) return -1;
	Users.push_back (Utilisateur);
	return 0;
}

//------------------------------------------------------------------------------

int CBot::SetUserName (unsigned int Sess, wxString& Nom)
{
	int ID=GetUserID(Sess);
	if (ID<0) return -1;
	Users[ID].Nom=Nom;
	return 0;
}

//------------------------------------------------------------------------------

void CBot::SetUserCoord (unsigned int Sess,int X, int Y, int Z)
{
	int ID=GetUserID(Sess);
	if (ID > -1)
	{
		Users[ID].X=X;
		Users[ID].Y=Y;
		Users[ID].Z=Z;
	}
}

//------------------------------------------------------------------------------

int	CBot::SetUserIP (unsigned int Sess,int IP)
{
	int ID=GetUserID(Sess);
	wxString Tampon=_T(""),Temp=_T("");
	if (ID<0) return ID;
	Tampon.Printf (_T("%d."), (IP & 0x000000FF));
	Temp.Append(Tampon);
	Tampon.Printf (_T("%d."), ((IP & 0x0000FF00)>>8));
	Temp.Append(Tampon);
	Tampon.Printf (_T("%d."), ((IP & 0x00FF0000)>>16));
	Temp.Append(Tampon);
	Tampon.Printf (_T("%d"), ((IP & 0xFF000000)>>24));
	Temp.Append(Tampon);
	Users[ID].IP=Temp;
	return 0;
}

//------------------------------------------------------------------------------

int CBot::DelUser (unsigned int Sess)
{
	for (wxVector<CUser>::iterator i= Users.begin(); i< Users.end(); i++)
	{
		if (i->Session == Sess)
		{
			Users.erase (i);
			return 0;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------

int CBot::DelUser (wxString& Nom)
{
	for (wxVector<CUser>::iterator i= Users.begin(); i< Users.end(); i++)
	{
		if (i->Nom == Nom)
		{
			Users.erase (i);
			return 0;
		}
	}
	return -1;
}


//------------------------------------------------------------------------------

int CBot::GetUserPrivilege (unsigned int Sess)
{
	int ID=GetUserID(Sess);
	if (ID<0) return -1;
	return Users[ID].Privilege;
}

//------------------------------------------------------------------------------

int CBot::GetUserPrivilege (wxString& Nom)
{
	int ID=GetUserID(Nom);
	if (ID<0) return -1;
	return Users[ID].Privilege;
}
