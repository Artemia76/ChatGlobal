// *****************************************************************************
// *                                                                           *
// *                       CLASSE DE GESTION DU CIEL	                       *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   Ecrit par Gianni Peschiutta {Neophile}                                  *
// *   Le 27/01/2007                                                           *
// *   CopyRight (c)Neophile 2007                                              *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *                         DEFINITION DE LA CLASSE                           *
// *                                                                           *
// *****************************************************************************

#include "Ciel.h"

#include <Aw.h>

#include <math.h>

#include "Global.h"

CCiel::CCiel (int id)
{
	wxString s,t;
	t.Printf(_T("Ciel%02d.ini"), id);
	wxFileName CielFileName = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator() + _T("Ciel") + wxFileName::GetPathSeparator() + t;
	if (!CielFileName.DirExists()) CielFileName.Mkdir(0777, wxPATH_MKDIR_FULL);
	pConfig = new wxFileConfig(_T("ChatGlobal"),wxEmptyString, CielFileName.GetLongPath (),wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
	pConfig->Read(_T("General/Enabled"), &Enabled, false);
	pConfig->Read(_T("Astres/Soleil"), &Soleil, _T(""));
	pConfig->Read(_T("Astres/MSoleil"), &MSoleil, _T(""));
	pConfig->Read(_T("Astres/TSoleil"), &TSoleil, 10);
	pConfig->Read(_T("Astres/Lune"), &Lune, _T(""));
	pConfig->Read(_T("Astres/MLune"), &MLune, _T(""));
	pConfig->Read(_T("Astres/TLune"), &TLune, 10);
	pConfig->Read(_T("Horaires/hdl"), &hdl, 8);
	pConfig->Read(_T("Horaires/mdl"), &mdl, 0);
	pConfig->Read(_T("Horaires/hfl"), &hfl, 9);
	pConfig->Read(_T("Horaires/mfl"), &mfl, 0);
	pConfig->Read(_T("Horaires/hdc"), &hdc, 17);
	pConfig->Read(_T("Horaires/mdc"), &mdc, 0);
	pConfig->Read(_T("Horaires/hfc"), &hfc, 18);
	pConfig->Read(_T("Horaires/mfc"), &mfc, 0);
	// Couleurs de la nuit
	pConfig->Read(_T("Couleurs/NN"), &s, _T("#000000"));
	NN=s;
	pConfig->Read(_T("Couleurs/NS"), &s, _T("#000000"));
	NS=s;
	pConfig->Read(_T("Couleurs/NE"), &s, _T("#000000"));
	NE=s;
	pConfig->Read(_T("Couleurs/NO"), &s, _T("#000000"));
	NO=s;
	pConfig->Read(_T("Couleurs/NZ"), &s, _T("#000000"));
	NZ=s;
	pConfig->Read(_T("Couleurs/ND"), &s, _T("#000000"));
	ND=s;
	pConfig->Read(_T("Couleurs/NA"), &s, _T("#B0B0B0"));
	NA=s;
	pConfig->Read(_T("Couleurs/NL"), &s, _T("#B0B0B0"));
	NL=s;
	// Couleurs de l'aube
	pConfig->Read(_T("Couleurs/AN"), &s, _T("#63BAFA"));
	AN=s;
	pConfig->Read(_T("Couleurs/AS"), &s, _T("#63BAFA"));
	AS=s;
	pConfig->Read(_T("Couleurs/AE"), &s, _T("#63BAFA"));
	AE=s;
	pConfig->Read(_T("Couleurs/AO"), &s, _T("#63BAFA"));
	AO=s;
	pConfig->Read(_T("Couleurs/AZ"), &s, _T("#63BAFA"));
	AZ=s;
	pConfig->Read(_T("Couleurs/AD"), &s, _T("#63BAFA"));
	AD=s;
	pConfig->Read(_T("Couleurs/AA"), &s, _T("#E0E0E0"));
	AA=s;
	pConfig->Read(_T("Couleurs/AL"), &s, _T("#E0E0E0"));
	AL=s;
	// Couleurs du jour
	pConfig->Read(_T("Couleurs/JN"), &s, _T("#63BAFA"));
	JN=s;
	pConfig->Read(_T("Couleurs/JS"), &s, _T("#63BAFA"));
	JS=s;
	pConfig->Read(_T("Couleurs/JE"), &s, _T("#63BAFA"));
	JE=s;
	pConfig->Read(_T("Couleurs/JO"), &s, _T("#63BAFA"));
	JO=s;
	pConfig->Read(_T("Couleurs/JZ"), &s, _T("#63BAFA"));
	JZ=s;
	pConfig->Read(_T("Couleurs/JD"), &s, _T("#63BAFA"));
	JD=s;
	pConfig->Read(_T("Couleurs/JA"), &s, _T("#FFFFFF"));
	JA=s;
	pConfig->Read(_T("Couleurs/JL"), &s, _T("#FFFFFF"));
	JL=s;
	// Couleurs du crépuscule
	pConfig->Read(_T("Couleurs/CN"), &s, _T("#63BAFA"));
	CN=s;
	pConfig->Read(_T("Couleurs/CS"), &s, _T("#63BAFA"));
	CS=s;
	pConfig->Read(_T("Couleurs/CE"), &s, _T("#63BAFA"));
	CE=s;
	pConfig->Read(_T("Couleurs/CO"), &s, _T("#63BAFA"));
	CO=s;
	pConfig->Read(_T("Couleurs/CZ"), &s, _T("#63BAFA"));
	CZ=s;
	pConfig->Read(_T("Couleurs/CD"), &s, _T("#000000"));
	CD=s;
	pConfig->Read(_T("Couleurs/CA"), &s, _T("#F08080"));
	CA=s;
	pConfig->Read(_T("Couleurs/CL"), &s, _T("#F08080"));
	CL=s;
	Sauve ();
	Logger = CCtrlLog::Create ();
}

CCiel::~CCiel ()
{
	Sauve ();
}

void CCiel::Sauve ()
{
	pConfig->Write(_T("General/Enabled"), Enabled);
	pConfig->Write(_T("Astres/Soleil"), Soleil);
	pConfig->Write(_T("Astres/MSoleil"), MSoleil);
	pConfig->Write(_T("Astres/TSoleil"), TSoleil);
	pConfig->Write(_T("Astres/Lune"), Lune);
	pConfig->Write(_T("Astres/MLune"), MLune);
	pConfig->Write(_T("Astres/TLune"), TLune);
	pConfig->Write(_T("Horaires/hdl"), hdl);
	pConfig->Write(_T("Horaires/mdl"), mdl);
	pConfig->Write(_T("Horaires/hfl"), hfl);
	pConfig->Write(_T("Horaires/mfl"), mfl);
	pConfig->Write(_T("Horaires/hdc"), hdc);
	pConfig->Write(_T("Horaires/mdc"), mdc);
	pConfig->Write(_T("Horaires/hfc"), hfc);
	pConfig->Write(_T("Horaires/mfc"), mfc);
	// Couleurs de la nuit
	pConfig->Write(_T("Couleurs/NN"), NN.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NS"), NS.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NE"), NE.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NO"), NO.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NZ"), NZ.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/ND"), ND.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NA"), NA.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/NL"), NL.GetAsString(wxC2S_HTML_SYNTAX));
	// Couleurs de l'aube
	pConfig->Write(_T("Couleurs/AN"), AN.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AS"), AS.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AE"), AE.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AO"), AO.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AZ"), AZ.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AD"), AD.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AA"), AA.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/AL"), AL.GetAsString(wxC2S_HTML_SYNTAX));
	// Couleurs du jour
	pConfig->Write(_T("Couleurs/JN"), JN.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JS"), JS.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JE"), JE.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JO"), JO.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JZ"), JZ.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JD"), JD.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JA"), JA.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/JL"), JL.GetAsString(wxC2S_HTML_SYNTAX));
	// Couleurs du crépuscule
	pConfig->Write(_T("Couleurs/CN"), CN.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CS"), CS.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CE"), CE.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CO"), CO.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CZ"), CZ.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CD"), CD.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CA"), CA.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Write(_T("Couleurs/CL"), CL.GetAsString(wxC2S_HTML_SYNTAX));
	pConfig->Flush();
}

void CCiel::MAJ()
{
	wxDateTime now = wxDateTime::Now();
	int Heure=now.GetHour ();
	int Minute=now.GetMinute ();
	Minute+=(Heure*60);
	if ((Minute==Top)||(!Enabled))  return;
	Top=Minute;
	// Définition des variables de calcul
	wxColour CielN;
	wxColour CielS;
	wxColour CielE;
	wxColour CielO;
	wxColour CielZ;
	wxColour CielD;
	wxColour LumA;
	wxColour LumL;
	float LumX,LumY,LumZ;
	double TopR,Delta;
	wxString Astre;
	wxString MAstre;
	int TAstre;
	int DAube = (hdl*60) + mdl;
	int FAube = (hfl*60) + mfl;
	int MAube = (DAube+FAube)/2;
	int DCouche = (hdc*60) + mdc;
	int FCouche = (hfc*60) + mfc;
	int MCouche = (DCouche + FCouche)/2;
	// Avant l'aube
	if ((Top < DAube) || (Top >=FCouche))
	{
		CielN=NN;
		CielS=NS;
		CielO=NO;
		CielE=NE;
		CielZ=NZ;
		CielD=ND;
		LumA=NA;
		LumL=NL;
	}
	// Transition de l'aube
	else if ((Top >= DAube) && (Top <FAube))
	{
		if (Top < MAube)
		{
			CalcCoul(NN,AN,CielN,DAube,MAube,Top);
			CalcCoul(NS,AS,CielS,DAube,MAube,Top);
			CalcCoul(NO,AO,CielO,DAube,MAube,Top);
			CalcCoul(NE,AE,CielE,DAube,MAube,Top);
			CalcCoul(NZ,AZ,CielZ,DAube,MAube,Top);
			CalcCoul(ND,AD,CielD,DAube,MAube,Top);
			CalcCoul(NA,AA,LumA,DAube,MAube,Top);
			CalcCoul(NL,AL,LumL,DAube,MAube,Top);
		}
		else
		{
			CalcCoul(AN,JN,CielN,MAube,FAube,Top);
			CalcCoul(AS,JS,CielS,MAube,FAube,Top);
			CalcCoul(AO,JO,CielO,MAube,FAube,Top);
			CalcCoul(AE,JE,CielE,MAube,FAube,Top);
			CalcCoul(AZ,JZ,CielZ,MAube,FAube,Top);
			CalcCoul(AD,JD,CielD,MAube,FAube,Top);
			CalcCoul(AA,JA,LumA,MAube,FAube,Top);
			CalcCoul(AL,JL,LumL,MAube,FAube,Top);
		}
	}
	else if ((Top >= FAube) && (Top < DCouche))
	{
		CielN=JN;
		CielS=JS;
		CielO=JO;
		CielE=JE;
		CielZ=JZ;
		CielD=JD;
		LumA=JA;
		LumL=JL;
	}
	//Transission du Crépuscule
	else if ((Top >= DCouche) && (Top < FCouche))
	{
		if (Top < MCouche)
		{
			CalcCoul(JN,CN,CielN,DCouche,MCouche,Top);
			CalcCoul(JS,CS,CielS,DCouche,MCouche,Top);
			CalcCoul(JO,CO,CielO,DCouche,MCouche,Top);
			CalcCoul(JE,CE,CielE,DCouche,MCouche,Top);
			CalcCoul(JZ,CZ,CielZ,DCouche,MCouche,Top);
			CalcCoul(JD,CD,CielD,DCouche,MCouche,Top);
			CalcCoul(JA,CA,LumA,DCouche,MCouche,Top);
			CalcCoul(JL,CL,LumL,DCouche,MCouche,Top);
		}
		else
		{
			CalcCoul(CN,NN,CielN,MCouche,FCouche,Top);
			CalcCoul(CS,NS,CielS,MCouche,FCouche,Top);
			CalcCoul(CO,NO,CielO,MCouche,FCouche,Top);
			CalcCoul(CE,NE,CielE,MCouche,FCouche,Top);
			CalcCoul(CZ,NZ,CielZ,MCouche,FCouche,Top);
			CalcCoul(CD,ND,CielD,MCouche,FCouche,Top);
			CalcCoul(CA,NA,LumA,MCouche,FCouche,Top);
			CalcCoul(CL,NL,LumL,MCouche,FCouche,Top);
		}
	}
	// Calcul de la position du soleil ou de la lune
	LumZ=0; // On ne gère pas encore l'inclinaison
	if ((Top < DAube) || (Top >= FCouche))
	{
		Astre=Lune;
		MAstre=MLune;
		TAstre=TLune;
		Delta = (1440-FCouche)+DAube;
		if (Top>FCouche) TopR=Top-FCouche;
		else TopR=(1440-FCouche)+Top;
	}
	else
	{
		if ((Top >= MAube) && (Top < MCouche))
		{
			Astre=Soleil;
			MAstre=MSoleil;
			TAstre=TSoleil;
		}
		else
		{
			Astre=_T("");
			MAstre=_T("");
			TAstre=0;
		}
		Delta = MCouche-MAube;
		TopR= (Top - MAube);
	}
	LumY=(-1* sin (PI *(TopR/Delta)));
	LumX= cos (PI *(TopR/Delta));

	// Chargement dans les propriété du monde
	aw_int_set(AW_WORLD_SKY_NORTH_RED,CielN.Red());
	aw_int_set(AW_WORLD_SKY_NORTH_GREEN,CielN.Green());
	aw_int_set(AW_WORLD_SKY_NORTH_BLUE,CielN.Blue());
	aw_int_set(AW_WORLD_SKY_SOUTH_RED,CielS.Red());
	aw_int_set(AW_WORLD_SKY_SOUTH_GREEN,CielS.Green());
	aw_int_set(AW_WORLD_SKY_SOUTH_BLUE,CielS.Blue());
	aw_int_set(AW_WORLD_SKY_WEST_RED,CielO.Red());
	aw_int_set(AW_WORLD_SKY_WEST_GREEN,CielO.Green());
	aw_int_set(AW_WORLD_SKY_WEST_BLUE,CielO.Blue());
	aw_int_set(AW_WORLD_SKY_EAST_RED,CielE.Red());
	aw_int_set(AW_WORLD_SKY_EAST_GREEN,CielE.Green());
	aw_int_set(AW_WORLD_SKY_EAST_BLUE,CielE.Blue());
	aw_int_set(AW_WORLD_SKY_TOP_RED,CielZ.Red());
	aw_int_set(AW_WORLD_SKY_TOP_GREEN,CielZ.Green());
	aw_int_set(AW_WORLD_SKY_TOP_BLUE,CielZ.Blue());
	aw_int_set(AW_WORLD_SKY_BOTTOM_RED,CielD.Red());
	aw_int_set(AW_WORLD_SKY_BOTTOM_GREEN,CielD.Green());
	aw_int_set(AW_WORLD_SKY_BOTTOM_BLUE,CielD.Blue());
	aw_int_set(AW_WORLD_AMBIENT_LIGHT_RED,LumA.Red());
	aw_int_set(AW_WORLD_AMBIENT_LIGHT_GREEN,LumA.Green());
	aw_int_set(AW_WORLD_AMBIENT_LIGHT_BLUE,LumA.Blue());
	aw_int_set(AW_WORLD_LIGHT_RED,LumL.Red());
	aw_int_set(AW_WORLD_LIGHT_GREEN,LumL.Green());
	aw_int_set(AW_WORLD_LIGHT_BLUE,LumL.Blue());
	aw_string_set(AW_WORLD_LIGHT_TEXTURE,
	#if AW_BUILD > 77
		Astre);
	#else
		Astre.mb_str());
	#endif
	aw_string_set(AW_WORLD_LIGHT_MASK,
	#if AW_BUILD > 77
		MAstre);
	#else
		MAstre.mb_str());
	#endif
	aw_int_set(AW_WORLD_LIGHT_DRAW_SIZE,TAstre);
	aw_float_set(AW_WORLD_LIGHT_X,LumX);
	aw_float_set(AW_WORLD_LIGHT_Y,LumY);
	aw_float_set(AW_WORLD_LIGHT_Z,LumZ);
	aw_world_attributes_change ();
}

void CCiel::CalcCoul (wxColour& C1, wxColour& C2, wxColour& Re, int hd, int hf , int h)
{
	int DTon, ADTon,R,V,B;
	double Coef = (double)(h-hd)/(double)(hf - hd);
	DTon = C2.Red() - C1.Red();
	ADTon = abs (DTon);
	if (DTon > 0) R=(int)((double)C1.Red() + ((double)ADTon * Coef));
	else if (DTon < 0) R=(int)((double)C1.Red() - ((double)ADTon * Coef));
	else R=C2.Red();

	DTon = C2.Green() - C1.Green();
	ADTon = abs (DTon);

	if (DTon > 0) V=(int)((double)C1.Green() + ((double)ADTon * Coef));
	else if (DTon < 0) V=(int)((double)C1.Green() - ((double)ADTon * Coef));
	else V=C2.Green();

	DTon = C2.Blue() - C1.Blue();
	ADTon = abs (DTon);
	if (DTon > 0) B=(int)((double)C1.Blue() + ((double)ADTon * Coef));
	else if (DTon < 0) B=(int)((double)C1.Blue() - ((double)ADTon * Coef));
	else B=C2.Blue();

	Re.Set (R,V,B);
}

