// *****************************************************************************
// *                                                                           *
// *                           CHAT GLOBAL BODY                                *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 25/03/2006                                                           *
// *   CopyRight (c)Neophile 2006                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                         DEFINITION DES MEMBRES                            *
// *                                                                           *
// *****************************************************************************

#include "ChatGlobal.h"

#include "MainFrame.h"
#include "Global.h"

// On implemente la classe d'application principale (démarrage du prog)
wxIMPLEMENT_APP(CMainApp);

//------------------------------------------------------------------------------
// Méthode d'initialisation de l'application

bool CMainApp::OnInit()
{

	long lng=-1;
	ConfPath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator();
	wxFileName ConfFile = ConfPath + _T("chatglobal.ini");
	if (!ConfFile.DirExists()) ConfFile.Mkdir(0777, wxPATH_MKDIR_FULL);
	pConfig = new wxFileConfig
		(
			_T("ChatGlobal"),
			wxEmptyString,
			ConfFile.GetLongPath (),
			wxEmptyString,
			wxCONFIG_USE_LOCAL_FILE
		);
	wxConfigBase::Set(pConfig);
	pConfig->Read (_T("misc/language"),&lng,-1);
	if ((lng < 0) || (lng >= NB_MAX_LNG))
    {
        lng = wxGetSingleChoiceIndex
              (
                _T("Please choose language:"),
                _T("Language"),
                WXSIZEOF(langNames),
                langNames
              );
    }
	if (( lng >= 0 ) || (lng < NB_MAX_LNG))
    {
        // don't use wxLOCALE_LOAD_DEFAULT flag so that Init() doesn't return
        // false just because it failed to load wxstd catalog
        if ( !m_locale.Init(langIds[lng]) )
        {
            wxLogError(_T("This language is not supported by the system."));
            return false;
        }
        pConfig->Write (_T("misc/language"),lng);
        pConfig->Flush ();
    }
    else return false;

    // normally this wouldn't be necessary as the catalog files would be found
    // in the default locations, but when the program is not installed the
    // catalogs are in the build directory where we wouldn't find them by
    // default
    wxLocale::AddCatalogLookupPathPrefix(_T("./lng/"));

    // Initialize the catalogs we'll be using
    m_locale.AddCatalog(_T("chatglobal"));

    // this catalog is installed in standard location on Linux systems and
    // shows that you may make use of the standard message catalogs as well
    //
    // if it's not installed on your system, it is just silently ignored
#ifdef __LINUX__
    {
        wxLogNull noLog;
        m_locale.AddCatalog(_T("fileutils"));
    }
#endif
	CMainFrame* MainFrame = new CMainFrame (m_locale);
	MainFrame->Show(true);
	SetTopWindow(MainFrame);
	return true;
}

int CMainApp::OnExit()
{
	return 0;
}