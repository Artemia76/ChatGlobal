// *****************************************************************************
// *                                                                           *
// *                         BASE DE DONNEE USER                               *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 22/04/2005                                                           *
// *   Modifié le 09/01/2007                                                   *
// *   CopyRight (c)Neophile 2005-2007                                         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                        DEFINITION DES MEMBRES                             *
// *                                                                           *
// *****************************************************************************

#include "DBase.h"
#include "Global.h"

CDBase::CDBase(int id)
{
	int r,v,b;
	wxString s,t;
	t.Printf(_T("User%02d.ini"), id);
	wxFileName DBFileName = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + _T("DBase") + wxFileName::GetPathSeparator() + t;
	if (!DBFileName.DirExists()) DBFileName.Mkdir(0777, wxPATH_MKDIR_FULL);
	pConfig = new wxFileConfig(_T("ChatGlobal"),wxEmptyString, DBFileName.GetLongPath (),wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
	nb_max=NB_USER_MAX;
	nb_user=pConfig->Read(_T("/Users/NbUser"), 0l);
	for (int i=0 ; i<nb_user ; i++)
	{
		s.Printf(_T("/Users/Entree%d/"),i);
		pConfig->Read(s+_T("Nom"), &Users[i].Nom, _T("Anonyme"));
		pConfig->Read(s+_T("Citoyen"), (int*)(&Users[i].Citizen), 0);
		pConfig->Read(s+_T("Couleur/R"), &r, 0);
		pConfig->Read(s+_T("Couleur/V"), &v, 0);
		pConfig->Read(s+_T("Couleur/B"), &b, 0);
		pConfig->Read(s+_T("Gras"), &Users[i].Gras, 0);
		pConfig->Read(s+_T("Italique"), &Users[i].Italique, 0);
		pConfig->Read(s+_T("Titre/Enabled"), &Users[i].Titre, 0);
		pConfig->Read(s+_T("Titre/Texte"), &Users[i].TexteTi, _T(""));
		pConfig->Read(s+_T("Qualite/Enabled"), &Users[i].Quali, 0);
		pConfig->Read(s+_T("Qualite/Texte"), &Users[i].TexteQu, _T(""));
		pConfig->Read(s+_T("Frequence"), &Users[i].Freq, 0);
		pConfig->Read(s+_T("Kling"), &Users[i].Kling, 0);
		pConfig->Read(s+_T("Kloug"), &Users[i].Kloug, 0);
		pConfig->Read(s+_T("Mute"),&Users[i].Mute,false);
		pConfig->Read(s+_T("GlobMode"),&Users[i].Glob_Mode,true);
		pConfig->Read(s+_T("Reachable"),&Users[i].Reachable,true);
		Users[i].Couleur.Set(r,v,b);
		Users[i].Marked=false;
	}
}

//------------------------------------------------------------------------------

CDBase::~CDBase()
{
}

//------------------------------------------------------------------------------

void CDBase::Sauve (int id)
{
	pConfig->Write(_T("/Users/NbUser"),(long)nb_user);
	wxString s;
	s.Printf(_T("/Users/Entree%d/"),id);
	pConfig->DeleteGroup (s);
	pConfig->Write(s+_T("Nom"), Users[id].Nom);
	pConfig->Write(s+_T("Citoyen"), (int)Users[id].Citizen);
	pConfig->Write(s+_T("Couleur/R"), Users[id].Couleur.Red());
	pConfig->Write(s+_T("Couleur/V"), Users[id].Couleur.Green());
	pConfig->Write(s+_T("Couleur/B"), Users[id].Couleur.Blue());
	pConfig->Write(s+_T("Gras"), Users[id].Gras);
	pConfig->Write(s+_T("Italique"), Users[id].Italique);
	pConfig->Write(s+_T("Titre/Enabled"), Users[id].Titre);
	pConfig->Write(s+_T("Titre/Texte"), Users[id].TexteTi);
	pConfig->Write(s+_T("Qualite/Enabled"), Users[id].Quali);
	pConfig->Write(s+_T("Qualite/Texte"), Users[id].TexteQu);
	pConfig->Write(s+_T("Frequence"), Users[id].Freq);
	pConfig->Write(s+_T("Kling"), Users[id].Kling);
	pConfig->Write(s+_T("Kloug"), Users[id].Kloug);
	pConfig->Write(s+_T("Mute"), Users[id].Mute);
	pConfig->Write(s+_T("GlobMode"), Users[id].Glob_Mode);
	pConfig->Write(s+_T("Reachable"), Users[id].Reachable);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------
// Routine d'identification d'un utilisateur AW ou d'ajout ou remplacement

int CDBase::Identifie (wxString& Nom, unsigned int Citoyen)
{
	int j=0,k=0;
	bool l=false;

	// On cherche si le citoyen existe, si il s'agit d'un touriste on saute

	if (Citoyen)
	{
		for (int i=0 ; i< nb_user ; i++)
		{
			if (Users[i].Citizen == Citoyen)
			{
				Users[i].Nom=Nom;
				Sauve (i);
				return i;
			}
		}
	}

	// Si la recherche citoyen n'a rien donnée ou qu'il s'agit d'un touriste
	// On cherche l'occurence par le nom

	for (int i=0 ; i< nb_user ; i++)
	{
		if (Users[i].Nom==Nom)
		{
			Users[i].Citizen=Citoyen;
			Sauve (i);
			return i;
		}
	}

	// si la précédente recherche n'a rien donnée, il s'agit d'un nouvel utilisateur
	// Si il rèste de la place dans la DB on inscrit le nouvel utilisateur

	if (nb_user < nb_max)
	{
		nb_user++;
		k=nb_user-1;
	}
	else
	{
	// Dernière solution, on cherche la plus petite fréqence pour remplacer un vieil
	// Utilisateur qui viens le moins souvent
	// On consèrve la priorité du citoyen par rapport au touriste
		k=-1;
		// La boucle while lance une première recherche
		// Dans cette 1ere recherche on disocie le touriste du citoyen
		// Si la 1ere recherche n'a rien donnée (que des citoyen dans la base)
		// On lance une seconde recherche sans discrimination qui sera déterministe elle
		while (k < 0)
		{
			j=9999;
			for (int i=0 ; i<nb_max ; i++)
			{
				if (Users[i].Freq<j)
				{
					if (l || ((!Citoyen) && (!Users[i].Citizen)))
					{
						j=Users[i].Freq;
						k=i;
					}
				}
			}
			if (l) break;
			l=true;
		}
	}
	// On inscrit le nouvel utilisateur

	Users[k].Nom=Nom;
	Users[k].Citizen=Citoyen;
	Users[k].Couleur.Set(0,0,0);
	Users[k].Gras=0;
	Users[k].Italique=0;
	Users[k].Titre=0;
	Users[k].Quali=0;
	Users[k].Freq=j;
	Users[k].Kling=0;
	Users[k].Kloug=0;
	Users[k].TexteTi=_T("");
	Users[k].TexteQu=_T("");
	Users[k].Mute=false;
	Users[k].Glob_Mode=true;
	Users[k].Reachable=true;
	Sauve (k);
	return k;
}

//------------------------------------------------------------------------------

wxColour CDBase::GetColor (int id)
{
	wxColour noir=_T("BLACK");
	if (id<nb_user) return Users[id].Couleur;
	else return noir;
}

//------------------------------------------------------------------------------

void CDBase::SetColor (int id, wxColour& Couleur)
{
	Users[id].Couleur=Couleur;
	Sauve(id);
}

//------------------------------------------------------------------------------

bool CDBase::GetGras (int id)
{
	if (id<nb_user) return Users[id].Gras;
	else
		return false;
}

//------------------------------------------------------------------------------

void CDBase::SetGras (int id, bool Gras)
{
	Users[id].Gras=Gras;
	Sauve(id);
}

//------------------------------------------------------------------------------

bool CDBase::GetItalique (int id)
{
	if (id<nb_user) return Users[id].Italique;
	else
		return false;
}

//------------------------------------------------------------------------------

void CDBase::SetItalique (int id, bool Ital)
{
	Users[id].Italique=Ital;
	Sauve(id);
}

//------------------------------------------------------------------------------

bool CDBase::GetTitre (int id)
{
	if (id<nb_user) return Users[id].Titre;
	else
		return false;
}

//------------------------------------------------------------------------------

bool CDBase::GetQuali (int id)
{
	if (id<nb_user) return Users[id].Quali;
	else
		return false;
}

//------------------------------------------------------------------------------

void CDBase::SetTitre (int id, bool Titre)
{
	Users[id].Titre=Titre;
	Sauve(id);
}

//------------------------------------------------------------------------------

void CDBase::SetQuali (int id, bool Quali)
{
	Users[id].Quali=Quali;
	Sauve(id);
}

//------------------------------------------------------------------------------

wxString CDBase::GetTxtTitre (int id)
{
	if (id<nb_user) return Users[id].TexteTi;
	else
		return _T("");
}

//------------------------------------------------------------------------------

wxString CDBase::GetTxtQuali (int id)
{
	if (id<nb_user) return Users[id].TexteQu;
	else
		return _T("");
}

//------------------------------------------------------------------------------

wxString CDBase::GetName (int id)
{
	if (id<nb_user) return Users[id].Nom;
	else
		return _T("");
}

//------------------------------------------------------------------------------

void CDBase::SetTxtTitre (int id, wxString& Titre)
{
	Users[id].TexteTi=Titre;
	Sauve(id);
}

//------------------------------------------------------------------------------$

void CDBase::SetTxtQuali (int id, wxString& Quali)
{
	Users[id].TexteQu=Quali;
	Sauve(id);
}

//------------------------------------------------------------------------------

int CDBase::GetNbKling (int id)
{
	if (id<nb_user) return Users[id].Kling;
	else
		return 0;
}

//------------------------------------------------------------------------------

int CDBase::GetNbKloug (int id)
{
	if (id<nb_user) return Users[id].Kloug;
	else
		return 0;
}

//------------------------------------------------------------------------------

int CDBase::GetRankKling (int rank)
{
	int i,j,ref,Score=9999,mem=0;
	for (j=0 ; j<nb_user ; j++) Users[j].Marked=false;
	for (i=0 ; i<rank ; i++)
	{
		ref=Score;
		Score=-1;
		mem=0;
		for (j=0 ; j<nb_user ; j++)
		{
			if (!Users[j].Marked)
			{
				if (Users[j].Kling == ref)
				{
					mem=j;
					Users[j].Marked=true;
					break;
				}
				if (Users[j].Kling > Score)
				{
					Score=Users[j].Kling;
					mem=j;
				}
			}
		}
		Users[mem].Marked=true;
	}
	return mem;
}

//------------------------------------------------------------------------------

int CDBase::GetRankKloug (int rank)
{
	int i,j,ref,Score=9999,mem=0;
	for (j=0 ; j<nb_user ; j++) Users[j].Marked=false;
	for (i=0 ; i<rank ; i++)
	{
		ref=Score;
		Score=-1;
		mem=0;
		for (j=0 ; j<nb_user ; j++)
		{
			if (!Users[j].Marked)
			{
				if (Users[j].Kloug == ref)
				{
					mem=j;
					Users[j].Marked=true;
					break;
				}
				if (Users[j].Kloug > Score)
				{
					Score=Users[j].Kloug;
					mem=j;
				}
			}
		}
		Users[mem].Marked=true;
	}
	return mem;
}

//------------------------------------------------------------------------------

void CDBase::AddFreq (int id)
{
	if (Users[id].Freq<9999) Users[id].Freq++;
	Sauve (id);
}

//------------------------------------------------------------------------------

void CDBase::AddKling (int id)
{
	if (Users[id].Kling<9999) Users[id].Kling++;
	Sauve (id);
}

//------------------------------------------------------------------------------

void CDBase::AddKloug (int id)
{
	if (Users[id].Kloug<9999) Users[id].Kloug++;
	Sauve (id);
}

//------------------------------------------------------------------------------

void CDBase::RstKlingKloug (void)
{
	int i;
	for (i=0 ; i<nb_user ; i++)
	{
		Users[i].Kling=0;
		Users[i].Kloug=0;
		Sauve (i);
	}
}

//------------------------------------------------------------------------------

void CDBase::SetMuteMode (int id, bool Mute)
{
	Users[id].Mute=Mute;
	Sauve(id);
}

//------------------------------------------------------------------------------

bool CDBase::GetMuteMode (int id)
{
	return Users[id].Mute;
}

//------------------------------------------------------------------------------

int CDBase::Search (wxString Nom)
{
	Nom.MakeUpper();
	for (int i=0; i < nb_user ; i++)
	{
		if (Users[i].Nom.Upper()==Nom) return i;
	}
	return -1;
}

//------------------------------------------------------------------------------

wxArrayString CDBase::GetMuteList ()
{
	wxArrayString Resultat;
	for (int i=0; i < nb_user ; i++)
	{
		if (Users[i].Mute) Resultat.Add(Users[i].Nom);
	}
	return Resultat;
}

//-------------------------------------------------------------------------------

SStats CDBase::Satistic ()
{
	SStats Result;
	int Cit=0,Tour=0,freq=0,kling=0,kloug=0;
	for (int i=0; i< nb_user; i++)
	{
		if (Users[i].Citizen) Cit++;
		else Tour++;
		freq+=Users[i].Freq;
		kling+=Users[i].Kling;
		kloug+=Users[i].Kloug;
	}
	Result.PCCitoyen= (int)((Cit*100)/nb_user);
	Result.PCTouriste= 100 - Result.PCCitoyen;
	Result.MFreq=freq/nb_user;
	Result.MKling=kling/nb_user;
	Result.MKloug=kloug/nb_user;
	Result.NbUtil=nb_user;
	return Result;
}

bool CDBase::GetGlobMode (int id)
{
	return Users[id].Glob_Mode;
}

void CDBase::SetGlobMode (int id, bool Glob)
{
	Users[id].Glob_Mode=Glob;
}

bool CDBase::GetReachable (int id)
{
	return Users[id].Reachable;
}

void CDBase::SetReachable	(int id, bool Reach)
{
	Users[id].Reachable=Reach;
}
