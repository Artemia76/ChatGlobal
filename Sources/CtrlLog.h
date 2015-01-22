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
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLLOG_H
#define CTRLLOG_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/datetime.h>
#include <wx/splitter.h>
#include <wx/vector.h>

class CCtrlLog
{
	private:
        static CCtrlLog *PtCtrlLog;
        CCtrlLog (int Num);
        ~CCtrlLog ();
        wxFrame* Parent;
        bool Init;
        int NbPage;
        int ID;
        wxString LogPath;
        wxString *FileName;
        bool *LogFile;
        wxDateTime Horloge;

	public:
		static CCtrlLog* Create(int Num=1);
		static void Kill();
		wxVector<wxTextCtrl*>	FenLog;
        int			Log (int NumPage=0, wxString Message=_T(""),wxColour Coul=_T("BLACK"), bool date = false, int Reason=0);
		void		InitLog	(wxWindow*);
		void		SetLog	(int Num, bool Flag);
		bool		GetLog	(int Num);
		wxTextCtrl* GetPage	(int Num);
        wxString RC(int); // Traduction littérale du reason code
};

#endif

