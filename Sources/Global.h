// *****************************************************************************
// *                                                                           *
// *                           VARIABLES GLOBALES                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 11/08/2005                                                           *
// *   CopyRight (c)Neophile 2005                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/colourdata.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/version.h> 
#include <aw.h>

#define Base_Temps		100
#define PI				3.141592

// Ici décommentez la directive si vous souhaitez compiler une version
// non bridée à l'univers AW par défaut :

//#define AUTRE_UNIV

static const wxString CGVersion = _T("ChatGlobal V3.7.1 ");

#if AW_BUILD<77
static const wxString CGRevision = CGVersion + _(" For ") + _T("AW 3.6");
#else
	#if AW_BUILD<85
		static const wxString CGRevision = CGVersion + _(" For ") + _T("AW 4.1");
	#else
        #if AW_BUILD<93
            static const wxString CGRevision = CGVersion + _(" For ") + _T("AW 4.2");
        #else
			#if AW_BUILD<100
				static const wxString CGRevision = CGVersion + _(" For ") + _T("AW 5.1");
			#else
				static const wxString CGRevision = CGVersion + _(" For ") + _T("AW 6.0");
			#endif
        #endif
	#endif
#endif

static const wxString CGCopyright = _T("Neophile (c)2003-2020");

#ifdef SERVEUR
static const int NombreBot = 10;
#else
static const int NombreBot = 3;
#endif

static const long LongFileMax = 500000;

static const  int NbLigneMax = 150;

static const wxString CGLicence = CGRevision + _("\nby ") + CGCopyright + _("(All right reserved.)") + _("\nBuild with ") + wxVERSION_STRING +("\nAnd AW SDK Build ") + wxString::FromDouble(AW_BUILD);

static wxColourData BCouleur;

static wxString ConfPath;

#endif

