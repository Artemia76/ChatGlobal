// *****************************************************************************
// *                                                                           *
// *                          CONTROLEUR DE LOG                                *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 29/04/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "CtrlLog.h"

#include <wx/textfile.h>
#include <wx/file.h>
#include "Global.h"

//------------------------------------------------------------------------------
CCtrlLog* CCtrlLog::PtCtrlLog=0;
//------------------------------------------------------------------------------
CCtrlLog* CCtrlLog::Create (int Num)
{
	if (!PtCtrlLog) PtCtrlLog = new CCtrlLog(Num);
	return PtCtrlLog;
}
//------------------------------------------------------------------------------
void CCtrlLog::Kill()
{
	if (PtCtrlLog != 0) delete PtCtrlLog;
	CCtrlLog::PtCtrlLog=0;
}
//------------------------------------------------------------------------------
CCtrlLog::CCtrlLog(int Num)
{
	int i;
	NbPage=Num;
	wxString s;
	Init=false;
	LogFile = new bool [NbPage];
	FileName = new wxString [NbPage];
	LogPath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + _T("log") + wxFileName::GetPathSeparator();
	if (!wxDirExists(LogPath)) wxMkdir(LogPath);
	for (i=0 ; i<NbPage ; i++)
	{
		LogFile[i]=false;
		s.Printf(_T("LogBot%02d.log"), i);
		FileName [i] = LogPath + s;
	}
	wxDateTime::SetCountry (wxDateTime::Country(4));
}
//------------------------------------------------------------------------------
CCtrlLog::~CCtrlLog()
{
	for (wxVector<wxTextCtrl*>::iterator i = FenLog.begin(); i < FenLog.end(); i++)
	{
		delete (*i);
	}
	FenLog.clear();
	//delete [] LogFile;
	//delete [] FileName;
}
//------------------------------------------------------------------------------
void CCtrlLog::InitLog(wxWindow* Parent)
{
	int i;
	if (!Init)
	{
		for (i=0;i<NbPage;i++)
		{
			FenLog.push_back( new wxTextCtrl (Parent,
				-1,
				wxString(_T("")),
				wxDefaultPosition,
				wxDefaultSize,
				wxTE_MULTILINE |
				wxTE_READONLY |
				wxTE_RICH ));
			//if (i>0) FenLog[i].Show(false);
		}
		Init=true;
	}
}
//------------------------------------------------------------------------------
int CCtrlLog::Log
	(
		int NumPage,
		wxString Message,
		wxColour Coul,
		bool date,
		int Reason
	)
{
	if (NumPage<0) NumPage=0;
	else if (NumPage>=NbPage) NumPage=NbPage-1;
	wxString Texte=_T("");
	wxString Tampon,s;
	bool newfile=false;
	int lon;
	long Taille;
	char* Buff;
	Horloge = wxDateTime::Now();
	if (FenLog[NumPage]->GetNumberOfLines()> NbLigneMax )
	{
		lon=FenLog[NumPage]->GetLineLength(0);
		FenLog[NumPage]->Remove(0, lon+2);
	}
	FenLog[NumPage]->SetDefaultStyle(wxTextAttr(Coul));
	FenLog[NumPage]->SetInsertionPointEnd();
	if (date) Texte=Horloge.FormatDate()+_T(" ");
	Texte.Append(Horloge.FormatTime());
	Texte.Append(_T(" : "));
	Texte.Append(Message);
	Texte.Append(RC(Reason));
	FenLog[NumPage]->WriteText(Texte + _T("\n"));
	if (LogFile[NumPage])
	{
		wxFile* Test = new wxFile();
		if (Test->Exists(FileName[NumPage]))
		{
			Test->Open(FileName[NumPage],wxFile::read_write);
			Taille=Test->Length();
			if (Taille > LongFileMax)
			{
				Buff=new char [Taille];
				Test->Read(Buff, Taille);
				Test->Close();
				Test->Create(FileName[NumPage],true);
				s=LogPath;
				Tampon.Printf
				(
					_T("Bot%02d_%02d%02d%02d%02d%02d%04d.log"),
					NumPage,
					Horloge.GetHour(),
					Horloge.GetMinute(),
					Horloge.GetSecond(),
					Horloge.GetDay(),
					Horloge.GetMonth() + 1,
					Horloge.GetYear()
				);
				s.Append(Tampon);
				Test->Create(s,true,wxFile::read_write);
				Test->Write(Buff, Taille);
				newfile=true;
				delete Buff;
			}
		}
		delete Test;
		wxTextFile* File = new wxTextFile(FileName[NumPage]);
		if (!File->Exists()) File->Create();
		File->Open();
		if (File->IsOpened())
		{
			if (newfile)
				File->AddLine
				(
					Horloge.FormatDate()+
					_T(" ")+
					Horloge.FormatTime()+
					_(" : New Log File.")
				);
			File->AddLine(Texte);
		}
		else
		{
			Coul.Set(255, 0, 0);
			FenLog[NumPage]->SetDefaultStyle(wxTextAttr(Coul));
			FenLog[NumPage]->WriteText
			(
				Horloge.FormatTime()+
				_(" : Unable to open the log file.")
			);
			LogFile=false;
		}
		File->Write();
		File->Close();
		delete File;
	}
	return 0;
}

//------------------------------------------------------------------------------

wxTextCtrl* CCtrlLog::GetPage(int Num)
{
	if (Num>NbPage)
		return FenLog[0];
	else
		return FenLog[Num];
}

//------------------------------------------------------------------------------

bool CCtrlLog::GetLog(int Num)
{
	if (Num<0)
		return LogFile[0];
	else
		if (Num>=NbPage) return LogFile[NbPage-1];
		else return LogFile[Num];
}

//------------------------------------------------------------------------------

void CCtrlLog::SetLog(int Num, bool Flag)
{
	if (Num<0) Num=0;
	else if (Num>=NbPage) Num=NbPage-1;
	if (!Flag)
	{
		Log(Num,_("Tchat Recording stopped"),_T("ORANGE"),true);
		LogFile[Num]=Flag;
	}
	else
	{
		LogFile[Num]=Flag;
		Log(Num,_("TChat Recording Started"),_T("ORANGE"),true);
	}
}

//------------------------------------------------------------------------------
// Methode de Traduction du codes d'erreurs

wxString CCtrlLog::RC(int rc)
{
	wxString rcs;
	switch (rc)
	{
		case 0 :
			rcs=_T("");
			break;
		case 1 :
			rcs=_("Citizen Ship Expired");
			break;
		case 2 :
			rcs=_("Land Limit Exceeded");
			break;
		case 3 :
			rcs=_("No Such Citizen");
			break;
		case 4 :
			rcs=_("Message Length Bad");
			break;
		case 5 :
			rcs=_("License Password Contains Space");
			break;
		case 6 :
			rcs=_("License Password Too Long");
			break;
		case 7 :
    	    rcs=_("License Password Too Short");
    	    break;
		case 8 :
			rcs=_("License Range Too Large");
			break;
		case 9 :
			rcs=_("License Range Too Small");
			break;
		case 10 :
			rcs=_("License Users Too Large");
			break;
		case 11 :
			rcs=_("License Users Too Small");
			break;
		case 12 :
			rcs=_("License Contains Invalid Char");
			break;
		case 13 :
			rcs=_("Invalid Password");
			break;
		case 14 :
			rcs=_("Unable To Mail Back Number");
			break;
		case 15 :
			rcs=_("License World Too Short");
			break;
		case 16 :
			rcs=_("License World Too Long");
			break;
		case 17 :
			rcs=_("Server Out Of Memory");
			break;
		case 20 :
			rcs=_("Invalid World");
			break;
		case 21 :
			rcs=_("Server Outdated");
			break;
		case 22 :
			rcs=_("World Already Started");
			break;
		case 27 :
			rcs=_("No Such World");
			break;
		case 31 :
			rcs=_("Not Logged In");
			break;
		case 32 :
			rcs=_("Unauthorized");
			break;
		case 33 :
			rcs=_("World Already Exists");
			break;
		case 34 :
			rcs=_("No Such License");
			break;
		case 39 :
			rcs=_("Identity Already In Use");
			break;
		case 40 :
			rcs=_("Unable To Report Location");
			break;
		case 41 :
			rcs=_("Invalid Email");
			break;
		case 42 :
			rcs=_("No Such Acting Citizen");
			break;
		case 43 :
			rcs=_("Acting Password Invalid");
			break;
		case 45 :
			rcs=_("Universe Full");
			break;
		case 46 :
			rcs=_("Billing Timeout");
			break;
		case 47 :
			rcs=_("Billing Recv Failed");
			break;
		case 48 :
			rcs=_("Billing Response Invalid");
			break;
		case 55 :
			rcs=_("Billing Rejected");
			break;
		case 56 :
			rcs=_("Billing_Blocked");
			break;
		case 57 :
			rcs=_("Too Many Worlds");
			break;
		case 58 :
			rcs=_("Must Upgrade");
			break;
		case 59 :
			rcs=_("Bot Limit Exceeded");
			break;
		case 61 :
			rcs=_("World_Expired");
			break;
		case 62 :
			rcs=_("Citizen Does Not Expire");
			break;
		case 64 :
			rcs=_("License Sarts With Number");
			break;
		case 66 :
			rcs=_("No Such Ejection");
			break;
		case 67 :
			rcs=_("No Such Session");
			break;
		case 69 :
			rcs=_("Ejection Expired");
			break;
		case 70 :
			rcs=_("Acting Citizen Expired");
			break;
		case 71 :
			rcs=_("Already_Started");
			break;
		case 72 :
			rcs=_("World Running");
			break;
		case 73 :
			rcs=_("World Not Set");
			break;
		case 74 :
			rcs=_("No Such Cell");
			break;
		case 75 :
			rcs=_("No Registry");
			break;
		case 76 :
			rcs=_("Can't Open Registry");
			break;
		case 77 :
			rcs=_("Citizen_Disabled");
			break;
		case 78 :
			rcs=_("World Disabled");
			break;
		case 79 :
			rcs=_("Beta Required");
			break;
		case 80 :
			rcs=_("Acting Citizen Disabled");
			break;
		case 81 :
			rcs=_("Invalid Uuser Count");
			break;
		case 91 :
			rcs=_("Private World");
			break;
		case 92 :
			rcs=_("No Tourists");
			break;
		case 100 :
			rcs=_("EMail Contains Invalid Char");
			break;
		case 101 :
			rcs=_("EMail Ends With Blank");
			break;
		case 102 :
			rcs=_("EMail Missing Dot");
			break;
		case 103 :
			rcs=_("EMail Missing At");
			break;
		case 104 :
			rcs=_("EMail Starts With Blank");
			break;
		case 105 :
			rcs=_("EMail Too Long");
			break;
		case 106 :
			rcs=_("EMail Too Short");
			break;
		case 107 :
			rcs=_("Name Already Used");
			break;
		case 108 :
			rcs=_("Name Contains Nonalphanumeric Char");
			break;
		case 109 :
			rcs=_("Name Contains Invalid Blank");
			break;
		case 110 :
			rcs=_("Name Doesn't Exist");
			break;
		case 111 :
			rcs=_("Name Ends With Blank");
			break;
		case 112 :
			rcs=_("Name Too Long");
			break;
      	case 113 :
			rcs=_("Name Too Short");
			break;
		case 114 :
			rcs=_("Name Unused");
			break;
		case 115 :
			rcs=_("Password Too Long");
			break;
		case 116 :
			rcs=_("Password Too Short");
			break;
		case 117 :
			rcs=_("Password Wrong");
			break;
		case 119 :
			rcs=_("Unable To Delete Name");
			break;
		case 120 :
			rcs=_("Unable To Get Citizen");
			break;
		case 121 :
			rcs=_("Unable To Insert Citizen");
			break;
		case 122 :
			rcs=_("Unable To Insert Name");
			break;
		case 123 :
			rcs=_("Unable To Put Citizen Count");
			break;
		case 124 :
			rcs=_("Unable To Delete Citizen");
			break;
		case 126 :
			rcs=_("Number Already Used");
			break;
		case 127 :
			rcs=_("Number Out Of Range");
			break;
		case 128 :
			rcs=_("Privilege Password Is Too Short");
			break;
		case 129 :
			rcs=_("Privilege Password Is Too Long");
			break;
		case 203 :
			rcs=_("Not Change Owner");
			break;
		case 204 :
			rcs=_("Can't Find Old Element");
			break;
		case 210 :
			rcs=_("Unable To Change Attribute");
			break;
		case 211 :
			rcs=_("Can't Change Owner");
			break;
		case 212 :
			rcs=_("Imposter");
			break;
		case 213 :
			rcs=_("Invalid Request");
			break;
		case 216 :
			rcs=_("Can't Build Here");
			break;
		case 300 :
			rcs=_("Encroaches");
			break;
		case 301 :
			rcs=_("No Such Object");
			break;
		case 302 :
			rcs=_("Not Delete Owner");
			break;
		case 303 :
			rcs=_("Too Many Bytes");
			break;
		case 305 :
			rcs=_("Unable To Store");
			break;
		case 306 :
			rcs=_("Unregistered Object");
			break;
		case 308 :
			rcs=_("Element Already Exists");
			break;
		case 309 :
			rcs=_("Restricted Command");
			break;
		case 310 :
			rcs=_("No Build Rights");
			break;
		case 311 :
			rcs=_("Out Of Bounds");
			break;
		case 313 :
			rcs=_("Restricted Object");
			break;
		case 314 :
			rcs=_("Restricted Area");
			break;
		case 400 :
			rcs=_("Out Of Memory");
			break;
		case 401 :
			rcs=_("Not Yet");
			break;
		case 402 :
			rcs=_("Timeout");
			break;
		case 403 :
			rcs=_("Null Pointer");
			break;
		case 404 :
			rcs=_("Unable To Contact Universe");
			break;
		case 405 :
			rcs=_("Unable To Contact World");
			break;
		case 406 :
			rcs=_("Invalid World Name");
			break;
		case 415 :
			rcs=_("Send Failed");
			break;
		case 416 :
			rcs=_("Receive Failed");
			break;
		case 421 :
			rcs=_("Stream Empty");
			break;
		case 422 :
			rcs=_("Stream Message Too Long");
			break;
		case 423 :
			rcs=_("World Name Too Long");
			break;
		case 426 :
			rcs=_("Message Too Long");
			break;
		case 427 :
			rcs=_("Too Many Resets");
			break;
		case 428 :
			rcs=_("Unable To Create Socket");
			break;
		case 429 :
			rcs=_("Unable To Connect");
			break;
		case 430 :
			rcs=_("Unable To Set NonBlocking");
			break;
		case 434 :
			rcs=_("Can't Open Stream");
			break;
		case 435 :
			rcs=_("Can't Write Stream");
			break;
		case 436 :
			rcs=_("Can't Close Stream");
			break;
		case 439 :
			rcs=_("No Connection");
			break;
		case 442 :
			rcs=_("Unable To Initialize Network");
			break;
		case 443 :
			rcs=_("Incorrect Message Length");
			break;
		case 444 :
			rcs=_("Not Initialized");
			break;
		case 445 :
			rcs=_("No Instance");
			break;
		case 446 :
			rcs=_("Out Buffer Full");
			break;
		case 447 :
			rcs=_("Invalid Callback");
			break;
		case 448 :
			rcs=_("Invalid Attribute");
			break;
		case 449 :
			rcs=_("Type Mismatch");
			break;
		case 450 :
			rcs=_("String Too Long");
			break;
		case 451 :
			rcs=_("Read Only");
			break;
		case 452 :
			rcs=_("Unable To Register Resolve");
			break;
		case 453 :
			rcs=_("Invalid Instance");
			break;
		case 454 :
			rcs=_("Version Mismatch");
			break;
		case 461 :
			rcs=_("In Buffer Full");
			break;
		case 463 :
			rcs=_("Protocol Error");
			break;
		case 464 :
			rcs=_("Query In Progress");
			break;
		case 465 :
			rcs=_("World Full");
			break;
		case 466 :
			rcs=_("Ejected");
			break;
		case 467 :
			rcs=_("Not Welcome");
			break;
		case 468 :
			rcs=_("Unable To Bind");
			break;
		case 469 :
			rcs=_("Unable To Listen");
			break;
		case 470 :
			rcs=_("Unable To Accept");
			break;
		case 471 :
			rcs=_("Connection Lost");
			break;
		case 473 :
			rcs=_("No Stream");
			break;
		case 474 :
			rcs=_("Not Available");
			break;
		case 487 :
			rcs=_("Old Universe");
			break;
		case 488 :
			rcs=_("Old World");
			break;
		case 489 :
			rcs=_("World Not Running");
			break;
		case 505 :
			rcs=_("Invalid Argument");
			break;
		case 1000 :
			rcs=_("AwLogin CallBack TimeOut");
			break;
		default:
			rcs=_("Unknow Raison Code");
			break;
   }
   return rcs;
}
