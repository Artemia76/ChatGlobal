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
// *                   DEFINITION DE LA CLASSE PRINCIPALE                      *
// *                                                                           *
// *****************************************************************************

#include "CXelagServer.h"

wxBEGIN_EVENT_TABLE(CXelag, wxEvtHandler)
	EVT_SOCKET (SOCKET_ID, CXelag::OnXelagEvent)
	EVT_TIMER  (XG_RECO,   CXelag::OnXgRecoEvent)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------

int CXelag::NbXelag = 0;

//------------------------------------------------------------------------------
// Constructeur

CXelag::CXelag (CBotCG* pBot)
{
	ID=NbXelag;
	NbXelag++;
	pConfig = wxConfigBase::Get();
	Bot=pBot;
// Configuration du Socket TCP
	SockXlg = new wxSocketClient ();
	SockXlg->SetEventHandler(*this, SOCKET_ID);
	SockXlg->SetNotify(
		wxSOCKET_CONNECTION_FLAG |
		wxSOCKET_INPUT_FLAG |
		wxSOCKET_LOST_FLAG
	);
	SockXlg->SetTimeout (5);
	SockXlg->Notify(true);
	XgRecoTimer = new wxTimer(this, XG_RECO);
	Logger = CCtrlLog::Create();
	PassPriv = CPassPriv::Create();

	On_Xelag=false;
	ConEC=false;
	DemCon=false;
	FirstCon=false;
	XgCompt=0;
	XgCGEna=false;
	XgRecoCnt=0;
	ModeReco=false;
	TamponTab.Empty();
}

//------------------------------------------------------------------------------
// Destructeur

CXelag::~CXelag ()
{

}

//------------------------------------------------------------------------------
// Charge les Paramètres du bot

void CXelag::Charge ()
{
	wxString s,S;

	S.Printf(_T("Bot%02d/"),ID);
	pConfig->Read( S + _T("/XgHost"), &XgHost, _T("localhost"));
	pConfig->Read( S + _T("/XgPassWord"), &s, _T(""));
	XgPassWord=PassPriv->Decode(s);
	pConfig->Read( S + _T("/XgPort") ,&XgPort, 5525);
	pConfig->Read( S + _T("/XgLogin") ,&XgLogin, _T("ChatGlobal"));
	pConfig->Read( S + _T("/XgAutoConnect") ,&XgConAuto, false);
	pConfig->Read( S + _T("/XgDelai"), &XgRecoDelay, 15);
	pConfig->Read( S + _T("/XgEssais"), &XgRecoRetry, 3);
	pConfig->Read( S + _T("/XgCGEna"), &XgCGEna, false);

	if (XgRecoRetry != 0) XgRecoEna=true;
	else XgRecoEna=false;
}

//------------------------------------------------------------------------------
// Sauvegarde les paramètres du bot

void CXelag::Sauve ()
{
	wxString S;
	S.Printf(_T("Bot%02d/"),ID);
	pConfig->Write( S + _T("/XgHost") , XgHost);
	pConfig->Write( S + _T("/XgPassWord") , PassPriv->Code(XgPassWord));
	pConfig->Write( S + _T("/XgPort") , XgPort);
	pConfig->Write( S + _T("/XgLogin") , XgLogin);
	pConfig->Write( S + _T("/XgAutoConnect") , XgConAuto);
	pConfig->Write( S + _T("/XgDelai") , XgRecoDelay);
	pConfig->Write( S + _T("/XgEssais") , XgRecoRetry);
	pConfig->Write( S + _T("/XgCGEna") , XgCGEna);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------
// Le socket client reçois un evenement

void CXelag::OnXelagEvent (wxSocketEvent& event)
{
	char buf1[1000];
	wxString Message=_T("");
	wxString Tampon,Name,Client,Reponse;
	switch (event.GetSocketEvent())
	{
		case wxSOCKET_INPUT      :
			SockXlg->Read(buf1, sizeof(buf1));
			Message << wxString(buf1,wxConvISO8859_1);
			Message=Message.Truncate(SockXlg->LastCount());
			TamponTab.Add (Message);
			break;
		case wxSOCKET_OUTPUT :
			break;
		case wxSOCKET_CONNECTION :
			Logger->Log(ID,_("Connected on the remote host"),_T("BLUE"));
			break;
		case wxSOCKET_LOST :
			Message=_("Xelag Server Connection lost.Reason : ");
			switch (SockXlg->LastError())
			{
				case wxSOCKET_NOERROR :
					Message.Append (_("No Error."));
					break;
				case wxSOCKET_INVOP :
					Message.Append (_("Invalid operation."));
					break;
				case wxSOCKET_IOERR :
					Message.Append (_("Input/Output error."));
					break;
				case wxSOCKET_INVADDR :
					Message.Append (_("Invalid address."));
					break;
				case wxSOCKET_INVSOCK :
					Message.Append (_("Invalid socket."));
					break;
				case wxSOCKET_NOHOST :
					Message.Append (_("No corresponding host."));
					break;
				case wxSOCKET_INVPORT :
					Message.Append (_("Invalid port."));
					break;
				case wxSOCKET_WOULDBLOCK :
					Message.Append (_("Timeout."));
					break;
				case wxSOCKET_TIMEDOUT :
					Message.Append (_("TimeOut Expired."));
					break;
				case wxSOCKET_MEMERR :
					Message.Append (_("Memory exhausted."));
					break;
				default :
					Message.Append (_("Unknown."));
			}
			Logger->Log(ID,Message,_T("RED"));
			On_Xelag=false;
			ConEC=false;
			FirstCon=false;
			TamponTab.Empty();
			SockXlg->Close();
			if (!FirstCon)
			{
				if (XgRecoEna)
				{
					if (!ModeReco)
					{
						if (Bot->IsOnWorld()) Bot->Mess_Bot (XgLogin, 4, _T(""), 0);
						XgRecoCnt=0;
						XgRetente=XgRecoDelay;
						ModeReco=true;
					}
					Tentative();
				}
			}
			break;
		default :
			break;
	}
}

//------------------------------------------------------------------------------

bool CXelag::IsOnXelag ()
{
	return On_Xelag;
}

//------------------------------------------------------------------------------
// Methode de connection

void CXelag::Connect()
{
	if ((!ConEC) && (!DemCon) && (!On_Xelag))
	{
		DemCon=true;
		FirstCon=true;
	}
}

//------------------------------------------------------------------------------
// Methode de Déconnection

void CXelag::Deconnect()
{
	if ((!ConEC) && (!DemCon) && On_Xelag) XgConnect(false);
}

//------------------------------------------------------------------------------
// Connection du socket client

void CXelag::XgConnect (bool choix)
{
	wxIPV4address addr;
	if (choix && (!On_Xelag) && (!ConEC))
	{
		ConEC=true;
		DemCon=false;
		addr.Hostname(XgHost);
		addr.Service(XgPort);
		SockXlg->Connect(addr, false);
		Logger->Log(ID,_("Host Connection..."), _T("BLUE"));
	}
	else
	{
		if (On_Xelag)
		{
			Logger->Log(ID,_("Disconnected from Xelag server"), _T("BLUE"));
			if (Bot->IsOnWorld()) Bot->Mess_Bot (XgLogin, 4, _T(""), 0);
			On_Xelag=false;
		}
		ConEC=false;
		FirstCon=false;
		TamponTab.Empty();
		SockXlg->Close();
	}
}

//------------------------------------------------------------------------------
// Méthode de reconnection automatique au serveur Xelagot

void CXelag::OnXgRecoEvent (wxTimerEvent& WXUNUSED(event))
{
	XgConnect (true);
}

//------------------------------------------------------------------------------
// Tentatives de nouvelle connection

void CXelag::Tentative ()
{
	wxString Tampon;
	if ((XgRecoCnt<XgRecoRetry) || (XgRecoRetry < 0))
	{
		Tampon.Printf(_("A reconnection will be tryed in %d s."), XgRetente);
		Logger->Log(ID, Tampon, _T("RED"));
		XgRecoTimer->Start(XgRetente * 1000,wxTIMER_ONE_SHOT);
		if (XgRecoRetry > (-1)) XgRecoCnt++;
		if (XgRetente < 900) XgRetente = XgRetente * 2;
	}
	else
	{
		Logger->Log(ID,_("End of attempts"), _T("RED"));
		ModeReco=false;
	}
}

//------------------------------------------------------------------------------
// Envoie de Messages sur le reseau Xelagot

void CXelag::EnvoiMess(wxString Message, int Type, wxString Name)
{
	wxString Reponse;
	if (On_Xelag)
	{
		while(1)
		{
			if (Type==1) Reponse=_T("BCR_") + Name + _T(":");
			else if ((!Type)&&XgCGEna) Reponse=_T("BCM_:");
				else break;
			Reponse.Append(Message);
			SockXlg->Write(Reponse, Reponse.Len());
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Conection du TChat sur le flux de texte intermonde

wxString CXelag::CGON ()
{
	wxString Reponse;
	if (!XgCGEna)
	{
		XgCGEna=true;
		Sauve();
		Reponse=_("The Chat network mode is alive.\n");
		EnvoiMess(XgLogin + _T(",MBot3"));
		if (Bot->IsOnWorld()) Bot->Mess_Bot (XgLogin, 3, _T(""), 0);
	}
	else
	{
		Reponse=_("The Chat network mode is already alive.\n");
	}
	return Reponse;
}

//------------------------------------------------------------------------------
// Déconnection du TChat du flux de texte

wxString CXelag::CGOFF ()
{
	wxString Reponse;
	if (XgCGEna)
	{
		Reponse=_("The Chat network mode is stopped.\n");
		EnvoiMess(XgLogin + _T(",MBot4"));
		if (Bot->IsOnWorld()) Bot->Mess_Bot (XgLogin, 4, _T(""), 0);
		XgCGEna=false;
		Sauve();
	}
	else
	{
		Reponse=_("The Chat network mode is already stopped.\n");
	}
	return Reponse;
}

//------------------------------------------------------------------------------
// Traitement de la file d'attente

void CXelag::Update()
{
	int len;
	long num;
	wxString Message=_T("");
	wxString Tampon,Name,Client,Reponse;
	while (!TamponTab.IsEmpty())
	{
		Message =TamponTab[0];
		TamponTab.RemoveAt (0);
		while (1)
		{
			if (!On_Xelag)
			{
				if (Message.StartsWith(_T("send login:")))
				{
					if (XgCompt>0)
					{
						XgCompt=0;
						Logger->Log(ID,_("Bad Login : Check the conection setting for the Xelag server"),_T("RED"));
						XgConnect (false);
						break;
					}
					Logger->Log(ID,_("Send login to Xelag Server..."),_T("BLUE"));
					SockXlg->Write(XgLogin, XgLogin.Len());
					XgCompt++;
				}
				if (Message.StartsWith(_T("send password:")))
				{
					if (XgCompt>1)
					{
						XgCompt=0;
						Logger->Log(ID,_("Bad PassWord : Check the conection setting for the Xelag server"),_T("RED"));
						XgConnect (false);
						break;
					}
					Logger->Log(ID,_("Send the password to Xelag Server..."),_T("BLUE"));
					SockXlg->Write(XgPassWord, XgPassWord.Len());
					XgCompt++;
				}
				if (Message.StartsWith(_T("already logged in... :(")))
				{
					Logger->Log(ID,_("Unable to connect on Xelag Server : Someone is already connected with this login"),_T("RED"));
					XgConnect (false);
				}
				if (Message.Contains(_T(":)")))
				{
					Logger->Log(ID,_("Connected on xelag server"),_T("BLUE"));
					On_Xelag=true;
					ConEC=false;
					FirstCon=false;
					ModeReco=false;
					XgCompt=0;
					if (XgCGEna)
					{
						XgCGEna=false;
						CGON();
					}
					if (XgRecoTimer->IsRunning()) XgRecoTimer->Stop();
				}
			}
			if (Bot->IsOnWorld()&&XgCGEna)
			{
				if (Message.StartsWith(_T("XSA_"),&Tampon))
				{
				}
				if (Message.StartsWith(_T("XSD_"),&Tampon))
				{
					Message=Tampon;
					len=Message.First(_T(':'));
					Client=Message.Left (len);
					Bot->Mess_Bot (Client, 4, _T(""), 0);
				}
				if ((Message.StartsWith(_T("BCM_"),&Tampon))&&(Bot->IsOnWorld())&&XgCGEna)
				{
					Message=Tampon;
					len=Message.First(':');
					Client=Message.Left (len);
					Tampon=Message.Remove(0,len+1);
					Message=Tampon;
					len=Message.First(',');
					Name=Message.Left (len);
					Tampon=Message.Remove(0,len+1);
					Message=Tampon.Left(Tampon.Len()-1);
					if (Message.StartsWith(_T("MBot")))
					{
						if(Message.Contains(_T("MBot1")))
						{
							Bot->Mess_Bot(Name, 5, Client, 0 );
							Bot->Kling=true;
							Bot->NKling=Name;
						}
						if(Message.Contains(_T("MBot2")))
						{
							Bot->Mess_Bot(Name, 6, Client, 0 );
							Bot->Kloug=true;
							Bot->NKloug=Name;
						}
						if(Message.Contains(_T("MBot3")))
						{
							Bot->Mess_Bot(Name, 3, Client, 0 );
						}
						if(Message.Contains(_T("MBot4")))
						{
							Bot->Mess_Bot(Name, 4, Client, 0 );
						}
					}
					else Bot->Analyse (Name, 0, 0, Message, 0, true, Client);
					}
				}
			if (Message.StartsWith(_T("BCW_"),&Tampon))
			{
				Message=Tampon;
				len=Message.First(':');
				Name=Message.Left (len);
				Tampon=Message.Remove(0,len+1);
				Message=Tampon;
				len=Message.First(',');
				Tampon=Message.Remove(0,len+1);
				Message=Tampon.Left(Tampon.Len()-1);
				if (Message==XgLogin)
				{
					Reponse=_("Hello ") + Name;
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message==_T("connect"))
				{
					if(Bot->IsOnWorld())
					{
						Reponse= _("Already connected on ") + Bot->Monde + _T(".");
						EnvoiMess( Reponse, 1, Name);
					}
					else
					{
						Reponse=_("Connecting on world ") + Bot->Monde + _T("...");
						EnvoiMess( Reponse, 1, Name);
						Bot->Global=true;
						Bot->Connect();
					}
					break;
				}
				if (Message==_T("disconnect"))
				{
					if (!Bot->IsOnUniverse())
					{
						Reponse=_("Already Disconnected.");
						EnvoiMess( Reponse, 1, Name);
					}
					else
					{
						Bot->Deconnect();
						Reponse=_("Disconnecting.");
						EnvoiMess( Reponse, 1, Name);
					}
					break;
				}
				if (Message.StartsWith(_T("acctext "),&Tampon))
				{
					Bot->TxtMessAc=Tampon;
					Bot->Sauve();
					Reponse=_("Welcome Message changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("acccol "),&Tampon))
				{
					Bot->ClrMessAc=Bot->ExtColor(Tampon);
					Bot->Sauve();
					Reponse=_("The color of welcome message has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("entertext "),&Tampon))
				{
					Bot->TxtAnnArr=Tampon;
					Bot->Sauve();
					Reponse=_("Incoming Message changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("entercol "),&Tampon))
				{
					Bot->ClrAnnArr=Bot->ExtColor(Tampon);
					Bot->Sauve();
					Reponse=_("The Incoming message color has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("exittext "),&Tampon))
				{
					Bot->TxtAnnDep=Tampon;
					Bot->Sauve();
					Reponse=_("Outgoing message changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("exitcol "),&Tampon))
				{
					Bot->ClrAnnDep=Bot->ExtColor(Tampon);
					Bot->Sauve();
					Reponse=_("The Outgoing message color has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("klingtext "),&Tampon))
				{
					Bot->TxtAnnKli=Tampon;
					Bot->Sauve();
					Reponse=_("Kling winner message changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("klingcol "),&Tampon))
				{
					Bot->ClrAnnKli=Bot->ExtColor(Tampon);
					Bot->Sauve();
					Reponse=_("The kling winner message color has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("klougtext "),&Tampon))
				{
					Bot->TxtAnnKlo=Tampon;
					Bot->Sauve();
					Reponse=_("Kloug winner message changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("klougcol "),&Tampon))
				{
					Bot->ClrAnnKlo=Bot->ExtColor(Tampon);
					Bot->Sauve();
					Reponse=_("The Kloug winner message color has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("citoyen "),&Tampon))
				{
					Tampon.ToLong(&num);
					Bot->Citoyen=num;
					Bot->Sauve();
					Reponse=_("Citizen account has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("password "),&Tampon))
				{
					Bot->PassWord=Tampon;
					Bot->Sauve();
					Reponse=_("Privilege Password has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("monde "),&Tampon))
				{
					Bot->Monde=Tampon;
					Bot->Sauve();
					Reponse=_("The world has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message==_T("cgon"))
				{
					Reponse=CGON ();
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message==_T("cgoff"))
				{
					Reponse=CGOFF ();
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				if (Message.StartsWith(_T("nom "),&Tampon))
				{
					Bot->Nom=Tampon;
					Bot->Sauve();
					Reponse=_("The bot name has been changed.");
					EnvoiMess( Reponse, 1, Name);
					break;
				}
				break;
			}
			break;
		}
	}
	if (Bot->DemCGON)
	{
		Bot->DemCGON=false;
		CGON();
	}
	if (Bot->DemCGOFF)
	{
		Bot->DemCGOFF=false;
		CGOFF();
	}
	if (DemCon && (!On_Xelag) && (!ConEC)) XgConnect(true);
	if (XgRecoTimer->IsRunning() && (!ModeReco)) XgRecoTimer->Stop();
}
