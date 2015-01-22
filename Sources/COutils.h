// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : COutils.h                              *
// *                  Miscellanaleous Utils for BackupAw                       *
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
// *   CopyRight 2006 Neophile                                                 *
// *   Creation          : 30/06/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef COUTILS_H
#define COUTILS_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

class COutils
{
    public:
        wxString		CoordToAw	(int x=0, int z=0);
        void			AwToCoord	(int& x, int& y,wxString Coord=_T(""));
		void			AwToCoord	(double& x, double& y,double& a, wxString Coord=_T(""));
		wxString		BinToHex	(unsigned char* dat_ptr=0, size_t Longueur=0);
		size_t			HexToBin	(wxString& Data_Str, unsigned char* dat_ptr=0);
		unsigned short	HexToDec	(const char* Hexa);
};

#endif
