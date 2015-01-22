// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : CPasspriv.h                           *
// *                Password Encryption for storage in INI file                *
// *                                                                           *
// *****************************************************************************
// * This file is part of BackupAw.                                            *
// * BackupAw is free software; you can redistribute it and/or modify          *
// * it under the terms of the GNU General Public License as published by      *
// * the Free Software Foundation; either version 2 of the License, or         *
// * (at your option) any later version.                                       *
// *                                                                           *
// * BackupAw is distributed in the hope that it will be useful,               *
// * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
// * GNU General Public License for more details.                              *
// *                                                                           *
// * You should have received a copy of the GNU General Public License         *
// * along with BackupAw; if not, write to the Free Software                   *
// * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 22/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CPASSPRIV_H
#define CPASSPRIV_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

#include "COutils.h"

class CPassPriv : public COutils
{
	private:
					CPassPriv();
					~CPassPriv();
static	CPassPriv*	PtCPassPriv;
		unsigned int Serial;
		unsigned int Masque[4];
		int Decalage[4];
	public:
static	CPassPriv*		Create();
static	void			Kill();
		wxString		Code(wxString& MotDePasse);
		wxString		Decode(wxString& MotDePasse);;
};

#endif
