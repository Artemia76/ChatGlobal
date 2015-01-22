// *****************************************************************************
// *                                                                           *
// *                           CLASS ANTI JOGGER                               *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 19/07/2006                                                           *
// *   CopyRight (c)Neophile 2006                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DEFINITION DE LA CLASSE PRINCIPALE                      *
// *                                                                           *
// *****************************************************************************

#include "CAntiJog.h"

#include <Aw.h>

#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(AJogger);

//------------------------------------------------------------------------------
// Constructeur

CAntiJog::CAntiJog (int id)
{
	ID=id;
	Logger = CCtrlLog::Create();
	pConfig=wxConfigBase::Get ();
}

//------------------------------------------------------------------------------
// Destructeur

CAntiJog::~CAntiJog ()
{

}

//------------------------------------------------------------------------------
// Charge la configuration

void CAntiJog::Charge()
{
	wxString S;
	int R=0,V=0,B=0;
	S.Printf(_T("Bot%02d/AntiPurge/"),ID);
	pConfig->Read( S + _T("/NbEntreeMax") ,&NbEntreeMax, 3);
	pConfig->Read( S + _T("/Delai") ,&Delai, 10);
	pConfig->Read( S + _T("/TpsEject") ,&TpsEject, 5);
	pConfig->Read(S + _T("/EnaAntiJog"), &EnaAntiJog, false);
	pConfig->Read(S + _T("/MessEject"), &MessEject, _("The Jogger %n has been ejected."));
	pConfig->Read(S + _T("/ClrEjectJog/R"),&R,255);
	pConfig->Read(S + _T("/ClrEjectJog/V"),&V,100);
	pConfig->Read(S + _T("/ClrEjectJog/B"),&B,100);
	MessColour.Set (R,V,B);
}

//------------------------------------------------------------------------------
// Sauve la configuration

void CAntiJog::Sauve()
{
	wxString S;
	S.Printf(_T("Bot%02d/AntiPurge/"),ID);
	pConfig->Write(	S + _T("/NbEntreeMax"), NbEntreeMax);
	pConfig->Write(	S + _T("/Delai"), Delai);
	pConfig->Write(	S + _T("/TpsEject"), TpsEject);
	pConfig->Write( S + _T("/EnaAntiJog"), EnaAntiJog);
	pConfig->Write(S + _T("/MessEject"), MessEject);
	pConfig->Write(S + _T("/ClrEjectJog/R"),MessColour.Red());
	pConfig->Write(S + _T("/ClrEjectJog/V"),MessColour.Green());
	pConfig->Write(S + _T("/ClrEjectJog/B"),MessColour.Blue());
	pConfig->Flush();
}

//------------------------------------------------------------------------------
// Ajoute ou incrémente un jogger potentiel

void CAntiJog::Add (int Session, wxString Nom)
{
	CJogger Jog;
	int id=-1;
	wxString Message;
	if (EnaAntiJog)
	{
		for (unsigned int i=0; i < Joggers.GetCount(); i++)
		{
			if (Joggers[i].Session==Session)
			{
				id=i;
				break;
			}
		}
		if (id >= 0)
		{
			Joggers[id].Compteur++;
			if (Joggers[id].Compteur >= NbEntreeMax)
			{
				aw_int_set(AW_EJECT_SESSION, Joggers[id].Session);
				aw_int_set(AW_EJECT_DURATION, TpsEject * 60);
				aw_world_eject ();
				Message = MessEject;
				Message.Replace(_T("%n"),Joggers[id].Nom, true);
				Logger->Log(ID, Message,_T("ORANGE"));
				aw_string_set(AW_CONSOLE_MESSAGE,
				#if AW_BUILD > 77
					Message);
				#else
					Message.mb_str());
				#endif
				aw_int_set(AW_CONSOLE_RED, MessColour.Red());
				aw_int_set(AW_CONSOLE_GREEN, MessColour.Green());
				aw_int_set(AW_CONSOLE_BLUE, MessColour.Blue());
				aw_bool_set(AW_CONSOLE_BOLD, true);
				aw_bool_set(AW_CONSOLE_ITALICS, false);
				aw_console_message (0);
				Joggers.RemoveAt(id);
			}
		}
		else
		{
			Jog.Session = Session;
			Jog.Compteur = 1;
			Jog.Temps = wxGetLocalTime();
			Jog.Nom=Nom;
			Joggers.Add (Jog);
		}
	}
}

//------------------------------------------------------------------------------
// Met à jour la liste des Joggers potentiel

void CAntiJog::Update()
{
	if (EnaAntiJog)
	{
		for (unsigned int i=0; i < Joggers.GetCount(); i++)
		{
			if ((wxGetLocalTime() - Joggers[i].Temps)>=Delai)
			{
				Joggers.RemoveAt (i);
				i--;
			}
		}
	}
}
