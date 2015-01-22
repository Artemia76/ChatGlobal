// *****************************************************************************
// *                                                                           *
// *                   Easy Mover Icone System Tray HEADER                     *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 08/01/2006                                                           *
// *   CopyRight (c)Neophile 2006                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                   DECLARATION DE LA CLASSE PRINCIPALE                     *
// *                                                                           *
// *****************************************************************************

#ifndef CTASKBAR_H
#define CTASKBAR_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/taskbar.h>

enum
{
	ST_EXIT = wxID_HIGHEST,
	ST_SHOW,
	ST_HIDE
};

class CTaskBar : public wxTaskBarIcon
{
	public:
							CTaskBar (wxWindow* pFenetre)
							{
								Fenetre=pFenetre;
							}

	private:
		virtual	wxMenu*		CreatePopupMenu ();
		wxWindow*			Fenetre;

	protected:
		void				OnClick (wxTaskBarIconEvent & event);
//		void				OnExit (wxCommandEvent & event);
		void				OnShow (wxCommandEvent & event);
		void				OnHide (wxCommandEvent & event);
	wxDECLARE_EVENT_TABLE();
};

#endif
