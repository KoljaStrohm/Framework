#ifndef AlphaFeld_H
#define AlphaFeld_H

#include "Zeichnung.h"

namespace Framework
{
	class Bild; // Bild.h
	class AlphaFeld; // Aus dieser Datei

	class AlphaFeld : public Zeichnung
	{
	private:
		int st�rke;
		int farbe;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) AlphaFeld();
		// nicht constant 
		__declspec( dllexport ) void setSt�rke( int st ); // setzt die St�rke
		__declspec( dllexport ) void setFarbe( int f ); // setzt die Farbe
		__declspec( dllexport ) void render( Bild &zRObj ) override; // zeichnet nach zRObj
		// constant 
		__declspec( dllexport ) int getSt�rke() const; // gibt die St�rke zur�ck
		__declspec( dllexport ) int getFarbe() const; // gibt die Farbe zur�ck
		__declspec( dllexport ) Zeichnung *dublizieren() const override; // Kopiert das Zeichnung
		// Reference Counting 
		__declspec( dllexport ) AlphaFeld *getThis();
		__declspec( dllexport ) AlphaFeld *release();
	};
}

#endif