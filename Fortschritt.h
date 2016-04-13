#ifndef Fortschritt_H
#define Fortschritt_H

#include "Zeichnung.h"

namespace Framework
{
	class LRahmen; // Rahmen.h
	class AlphaFeld; // AlphaFeld.h
	class Bild; // Bild.h
	class Schrift; // Schrift.h
	class FBalken; // aus dieser Datei

	class FBalken : public ZeichnungHintergrund
	{
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 Prozent = 0x001000;

            const static __int64 FRahmen = 0x002000;
            const static __int64 FFarbe = 0x004000;
            const static __int64 FBild = 0x008000;
            const static __int64 FAlpha = 0x10000;
            const static __int64 FBuffered = 0x20000;

            const static __int64 L_R = 0x0100000;
            const static __int64 R_L = 0x0200000;
            const static __int64 U_O = 0x0400000;
            const static __int64 O_U = 0x0800000;

            const static __int64 normal = Sichtbar | Rahmen | Hintergrund | HBild | FRahmen | FBild | L_R | Prozent;
        };
	private:
		__int64 maxAk;
		__int64 ak;
		LRahmen *fRahmen;
		AlphaFeld *fBuffer;
		int fBgF;
		Bild *fBgBild;
		Schrift *schrift;
		int schriftFarbe;
		unsigned char schriftGr��e;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) FBalken();
		// Destructor 
		__declspec( dllexport ) ~FBalken();
		// nicht constant 
		__declspec( dllexport ) void setAktionAnzahl( __int64 ak ); // setzt die anzahl der Aktionen
		__declspec( dllexport ) void aktionPlus(); // eine Aktion ist fertig
		__declspec( dllexport ) void aktionPlus( __int64 aktionen ); // mehrere Aktionen sind fertig
		__declspec( dllexport ) void reset(); // setzt die fertigen Aktionen zur�ck
		__declspec( dllexport ) void setFRahmenZ( LRahmen *ram ); // setzt einen Zeiger zum Fertig Rahmen
		__declspec( dllexport ) void setFRFarbe( int f ); // setzt die Fertig Rahmen Farbe
		__declspec( dllexport ) void setFRBreite( int br ); // setzt die Fertig Rahmen Breite
		__declspec( dllexport ) void setFAlphaFeldZ( AlphaFeld *af ); // setzt einen Zeiger zum Fertig Alpha Feld
		__declspec( dllexport ) void setFAFFarbe( int f ); // setzt die Fertig Alpha Feld Farbe
		__declspec( dllexport ) void setFAFSt�rke( int st ); // setzt die St�rke des Fertig Alpha Feldes
		__declspec( dllexport ) void setFBgFarbe( int f ); // setzt einen Zeiger zur Fertig Hintergrund Farbe
		__declspec( dllexport ) void setFBgBildZ( Bild *b ); // setzt das Fertig Hintergrund Bild
		__declspec( dllexport ) void setFBgBild( Bild *b ); // kopiert in das Fertig Hintergrund Bild
		__declspec( dllexport ) void setSchriftZ( Schrift *b ); // setzt die Schrift
		__declspec( dllexport ) void setSFarbe( int f ); // setzt die Schrift Farbe
		__declspec( dllexport ) void setSGr��e( unsigned char gr ); // setzt die Schrift gr��e
		__declspec( dllexport ) void render( Bild &zRObj ) override; // zeichnet nach zRObj
		// constant 
		__declspec( dllexport ) __int64 getAktionAnzahl() const; // gibt die Anzahl der Aktionen zur�ck
		__declspec( dllexport ) double getProzent() const; // gibt die momentane Prozentzahl zur�ck
		__declspec( dllexport ) __int64 getAktion() const; // gibt die fertigen Aktionen zur�ck
		__declspec( dllexport ) LRahmen *getFRahmen() const; // gibt den Fertig Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zFRahmen() const;
		__declspec( dllexport ) AlphaFeld *getFAlphaFeld() const; // gibt das Fertig Alpha Feld zur�ck
		__declspec( dllexport ) AlphaFeld *zFAlphaFeld() const;
		__declspec( dllexport ) int getFBgFarbe() const; // gibt die Fertig Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getFBgBild() const; // gibt das Fertig Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zFBgBild() const;
		__declspec( dllexport ) Schrift *getSchrift() const; // gibt die Schrift zur�ck
		__declspec( dllexport ) Schrift *zSchrift() const;
		__declspec( dllexport ) int getSFarbe() const; // gibt die Schrift Farbe zur�ck
		// Reference Counting 
		__declspec( dllexport ) FBalken *getThis();
		__declspec( dllexport ) FBalken *release();
	};
}

#endif