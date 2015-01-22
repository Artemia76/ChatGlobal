// *****************************************************************************
// *                                                                           *
// *                         BASE DE DONNEE COULEURS                           *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 27/11/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "DBColor.h"
#include "Global.h"

CDBColor::CDBColor(int id)
{
	int i,r,v,b;
	wxString s,t;
	t.Printf(_T("/Colors%02d.ini"), id);
	wxFileName DBCFileName = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + _T("DBase") + wxFileName::GetPathSeparator() + t;
	if (!DBCFileName.DirExists()) DBCFileName.Mkdir(0777, wxPATH_MKDIR_FULL);
	pConfig = new wxFileConfig(_T("ChatGlobal"),wxEmptyString, DBCFileName.GetLongPath (),wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
	nb_max=NB_COLOR_MAX;
	nb_colors=pConfig->Read(_T("/Colors/NbColors"), 0l);
	for (i=0 ; i<nb_colors ; i++)
	{
		s.Printf(_T("/Colors/Entree%d/"),i);
		pConfig->Read(_T("Nom"),&Colors[i].Nom, _T("Anonyme"));
		pConfig->Read(s+_T("R"), &r, 0);
		pConfig->Read(s+_T("V"), &v, 0);
		pConfig->Read(s+_T("B"), &b, 0);
		Colors[i].Couleur.Set(r,v,b);
	}
}

//------------------------------------------------------------------------------

CDBColor::~CDBColor()
{
	//delete pConfig;
}

//------------------------------------------------------------------------------

void CDBColor::Sauve (int id)
{
	pConfig->Write(_T("/Colors/NbColors"),(long)nb_colors);
	wxString s,t;
	s.Printf(_T("/Colors/Entree%d/"),id);
	pConfig->Write(s+_T("Nom"), Colors[id].Nom);
	pConfig->Write(s+_T("R"), (long)Colors[id].Couleur.Red());
	pConfig->Write(s+_T("V"), (long)Colors[id].Couleur.Green());
	pConfig->Write(s+_T("B"), (long)Colors[id].Couleur.Blue());
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

int CDBColor::Identifie (wxString& Nom)
{
	for (int i=0 ; i< nb_colors ; i++)
	{
		if (Colors[i].Nom==Nom)
		{
			return i;
		}
	}
	return DBC_NOT_EXIST;
}

//------------------------------------------------------------------------------

wxColour CDBColor::GetColor (int id)
{
	wxColour noir=_T("BLACK");
	if ((id<nb_colors) && (id>=0)) return Colors[id].Couleur;
	else
		return noir;
}

//------------------------------------------------------------------------------

int CDBColor::SetColor (int id, wxColour& Color)
{
	int rc=DBC_OK;
	if ((id<nb_colors) && (id>=0)) Colors[id].Couleur=Color;
	else rc=DBC_NOT_EXIST;
	Sauve(id);
	return rc;
}

//------------------------------------------------------------------------------

wxString CDBColor::GetName (int id)
{
	if ((id<nb_colors) && (id>=0)) return Colors[id].Nom;
	else
		return _T("");
}

//------------------------------------------------------------------------------

int CDBColor::Remove(int id)
{
	int i;
	if ((id>=nb_colors) && (id<0)) return DBC_NOT_EXIST;
	nb_colors--;
	if (id<(nb_colors))
	{
		for (i=id+1 ; i<=nb_colors; i++)
		{
			Colors[i-1].Nom=Colors[i].Nom;
			Colors[i-1].Couleur=Colors[i].Couleur;
			Sauve(i-1);
		}
	}
	return DBC_OK;
}

//------------------------------------------------------------------------------

int CDBColor::Add (wxString& Nom, wxColour& Color)
{
	if ((Identifie (Nom))!=DBC_NOT_EXIST) return DBC_ALREADY_EXIST;
	if (nb_colors==nb_max) return DBC_LIST_FULL;
	nb_colors++;
	Colors[nb_colors-1].Nom=Nom;
	Colors[nb_colors-1].Couleur=Color;
	Sauve(nb_colors-1);
	return DBC_OK;
}
