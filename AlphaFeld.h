#ifndef AlphaFeld_H
#define AlphaFeld_H

#include "Zeichnung.h"

namespace Framework
{
	class Bild; // Bild.h
	class AlphaFeld; // Aus dieser Datei

    // Eine Zeichnung des 2D GUI Frameworks, die einen Farb�bergang zu einem Rechteck darstellt
	class AlphaFeld : public Zeichnung
	{
	private:
		int st�rke;
		int farbe;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) AlphaFeld();
		// Setzt die St�rke des �bergangs. Dies ist der Wert um den der Alpha Wert der Farbe f�r jeden Pixel nach innen abnimmt
        //  st: Die St�rke
		__declspec( dllexport ) void setSt�rke( int st );
        // Setzt die Farbe des Alpha Feldes
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setFarbe( int f );
        // Zeichnet die Zeihnung in ein bestimmtes Bild
        //  zRObj: Das Bild, in das gezeichnet werden soll
		__declspec( dllexport ) void render( Bild &zRObj ) override;
		// Gibt die St�rke des Alpha Feldes zur�ck
		__declspec( dllexport ) int getSt�rke() const;
        // gibt die Farbe des Alpha Feldes im A8R8G8B8 Format zur�ck
		__declspec( dllexport ) int getFarbe() const;
        // Kopiert das Alpha Feld, so dass es ohne auswirkungen auf das Original verwendet werden kann
		__declspec( dllexport ) Zeichnung *dublizieren() const override;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
		__declspec( dllexport ) AlphaFeld *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
		__declspec( dllexport ) AlphaFeld *release();
	};
}

#endif