#ifndef Rahmen_H
#define Rahmen_H

#include "Zeichnung.h"

namespace Framework
{
	class Bild; // aus Bild.h
	struct VScrollData; // Scroll.h
	struct HScrollData; // Scroll.h
	class LRahmen; // aus dieser Datei

	class LRahmen : public Zeichnung // Ramen aus Linien
	{
	private:
		int br;
		int farbe;
		bool alpha;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) LRahmen();
		// nicht constant 
		__declspec( dllexport ) void setRamenBreite( int br ); // setzt die Breite des Rahmens
		__declspec( dllexport ) void setAlpha( bool a ); // Legt fest, ob der Alphawert der Farbe ber�cksichtigt werden soll
		__declspec( dllexport ) void setFarbe( int f ); // Legt die Farbe des Rahmens fest
		__declspec( dllexport ) void render( Bild &zRObj ) override; // Zeichnet den Rahmen in das RenderZeichnung
		// constant 
		__declspec( dllexport ) int getRBreite() const; // Gibt die Breite des Rahmens zur�ck
		__declspec( dllexport ) int getFarbe() const; // Gibt die Farbe des Ramens zur�ck
		__declspec( dllexport ) bool hatAlpha() const; // Gibt zur�ck, ob der Alphawert der Farbe beachtet wird
		__declspec( dllexport ) Zeichnung *dublizieren() const override; // Kopiert das Zeichnung
		// Reference Counting 
		__declspec( dllexport ) LRahmen *getThis();
		__declspec( dllexport ) LRahmen *release();
	};
}

#endif