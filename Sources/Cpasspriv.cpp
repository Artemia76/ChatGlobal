// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CPasspriv.cpp                          *
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

#include "Cpasspriv.h"
#include <math.h>


//------------------------------------------------------------------------------

CPassPriv* CPassPriv::PtCPassPriv = 0;

//------------------------------------------------------------------------------

CPassPriv* CPassPriv::Create()
{
	if (!PtCPassPriv) PtCPassPriv = new CPassPriv;
	return PtCPassPriv;
}

//------------------------------------------------------------------------------

void CPassPriv::Kill()
{
	if (PtCPassPriv)
	{
		delete PtCPassPriv;
		PtCPassPriv=0;
	}
}

//------------------------------------------------------------------------------

CPassPriv::CPassPriv()
{
	Serial=0x4BAF1FBA; //To Do : Find a better method to generate key like serial or MAC on each OS
	Masque[0]= 0x000000FF;
	Masque[1]= 0x0000FF00;
	Masque[2]= 0x00FF0000;
	Masque[3]= 0xFF000000;
	Decalage[0]= 0;
	Decalage[1]= 8;
	Decalage[2]= 16;
	Decalage[3]= 24;
}

//------------------------------------------------------------------------------

CPassPriv::~CPassPriv()
{
}

//------------------------------------------------------------------------------
// Crypt

wxString CPassPriv::Code(wxString& MotDePasse)
{
	char buff[3];
	size_t Long=MotDePasse.Len();
	wxString Resultat;
	int j=0;
	unsigned int temp;
	for (size_t i=0; i<Long; i++)
	{
		temp=MotDePasse[i];
		temp=temp^((Serial&Masque[j])>>Decalage[j]);
		sprintf(buff,"%02X",temp);
		Resultat << (wxChar) buff[0];
		Resultat << (wxChar) buff[1];
		j++;
		if (j>3) j=0;
	}
	return Resultat;
}

//------------------------------------------------------------------------------
// Uncrypt

wxString CPassPriv::Decode(wxString& MotDePasse)
{
	char buff[3];
	int j=0;
	unsigned int temp;
	wxString Resultat;
	size_t Long=MotDePasse.Len();
	for (size_t i=0; i<(Long/2); i++)
	{
		buff[0]=MotDePasse[i*2];
		buff[1]=MotDePasse[(i*2)+1];
		buff[2]='\0';
		temp=HexToDec(buff);
		Resultat << (wxChar)(temp^((Serial&Masque[j])>>Decalage[j]));
		j++;
		if (j>3) j=0;
	}
	return Resultat;
}


