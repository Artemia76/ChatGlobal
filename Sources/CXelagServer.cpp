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
#include <wx/tokenzr.h>

wxBEGIN_EVENT_TABLE(CXelag, wxEvtHandler)
	EVT_SOCKET (SOCKET_ID, CXelag::OnXelagEvent)
	EVT_TIMER  (XG_RECO,   CXelag::OnXgRecoEvent)
	EVT_TIMER (XG_HB, CXelag::OnXgHeartBeat)
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
	XgHeartBeat = new wxTimer(this, XG_HB);
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
	wxStringTokenizer tokenizer;
	switch (event.GetSocketEvent())
	{
		case wxSOCKET_INPUT      :
			SockXlg->Read(buf1, sizeof(buf1));
			Message << wxString(buf1,wxConvISO8859_1);
			Message=Message.Truncate(SockXlg->LastCount());
			tokenizer.SetString(Message, "\n");
			while (tokenizer.HasMoreTokens())
			{
				TamponTab.Add(tokenizer.GetNextToken());
				// process token here
			}
			break;
		case wxSOCKET_OUTPUT :
			break;
		case wxSOCKET_CONNECTION :
			Logger->Log(ID,_("Connected on the remote host"),_T("BLUE"));
			On_Xelag = true;
			ConEC = false;
			FirstCon = false;
			ModeReco = false;
			XgCompt = 0;
			if (XgCGEna)
			{
				XgCGEna = false;
				CGON();
			}
			if (XgRecoTimer->IsRunning()) XgRecoTimer->Stop();
			XgHeartBeat->Start(5000, false);
			EnvoiMess(_T("HELLO"));
			EnvoiMess(_T("NICK ")+ XgLogin);
			EnvoiMess(_T("USER ") + XgLogin + _T(" 8 * :ChatGlobal IRC Client\n"));
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
			XgHeartBeat->Stop();
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
		XgHeartBeat->Stop();
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
// Méthode de reconnection automatique au serveur Xelagot

void CXelag::OnXgHeartBeat(wxTimerEvent& WXUNUSED(event))
{
	if (On_Xelag)
	{
		//EnvoiMess(_T("PING"));
	}
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
		Reponse = Message + _T("\n");
		Logger->Log(ID, _("Send : ") + Message, _T("BLUE"));
		SockXlg->Write(Reponse, Reponse.Len());
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
		Logger->Log(ID, _("Receive : ") + Message, _T("BLUE"));
		if (Message.StartsWith(_T("PING ")))
		{
			Message.StartsWith(_T("PING "), &Tampon);
			EnvoiMess(_T("PONG ") + Tampon);
		}
		if (Message.StartsWith(_T(":")+ XgLogin))
		{
			EnvoiMess(_T("JOIN #lobby"));
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
