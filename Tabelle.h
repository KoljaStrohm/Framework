#ifndef Tabelle_H
#define Tabelle_H

#include "Zeichnung.h"
#include "Array.h"

namespace Framework
{
	class LRahmen; // Rahmen.h
	class AlphaFeld; // AlphaFeld.h
	class VScrollBar; // Scroll.h
	class HScrollBar; // Scroll.h
	class Text; // Text.h
	class ObjTabelle; // aus dieser Datei

    // Verwaltet eine Tabelle aus Zeichnungen
	class ObjTabelle : public ZeichnungHintergrund
	{
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 SpaltenBreite�nderbar = 0x00001000; // Wenn dieser Flag gesetzt wird, so kann der Benutzer die Spalten mit der Maus vergr��ern und verkleinern
            const static __int64 ZeilenH�he�nderbar = 0x00002000; // Wenn dieser Flag gesetzt wird, so kann der Benutzer die Spalten mit der Maus vergr��ern und verkleinern
            const static __int64 SpaltenBreiteMin = 0x00004000; // Wenn dieser Flag gesetzt wird, so kann der Nutzer trotz des Flags SpaltenBreite�nderbar die Spaltenbreite nicht kleiner machen als eine bestimmte Grenze
            const static __int64 SpaltenBreiteMax = 0x00008000; // Wenn dieser Flag gesetzt wird, so kann der Nutzer trotz des Flags SpaltenBreite�nderbar die Spaltenbreite nicht gr��er machen als eine bestimmte Grenze
            const static __int64 ZeilenH�heMin = 0x00010000; // Wenn dieser Flag gesetzt wird, so kann der Nutzer trotz des Flags ZeilenH�he�nderbar die Zeilenh�he nicht kleiner machen als eine bestimmte Grenze
            const static __int64 ZeilenH�heMax = 0x00020000; // Wenn dieser Flag gesetzt wird, so kann der Nutzer trotz des Flags ZeilenH�he�nderbar die Zeilenh�he nicht gr��er machen als eine bestimmte Grenze
            const static __int64 SpaltenBeweglich = 0x00040000; // Wenn dieser Flag gesetzt wird, so kann der Nutzer die Reihenfolge der Spalten bestimmen, in dem er sie per Drag and Drop verschiebt
            const static __int64 AuswahlRahmen = 0x0080000; // Wenn dieser Flag gesetzt ist, so bekommt das Feld, dass der Benutzer durch den Flag Erlaubt ausw�hlen kann einen anderen Rahmen
            const static __int64 AuswahlBuffer = 0x00100000; // Wenn dieser Flag gesetzt ist, so bekommt das Feld, dass der Benutzer durch den Flag Erlaubt ausw�hlen kann ein anderes AlphaFeld
            const static __int64 AuswahlMultistyled = 0x00200000; // Wenn dieser Flag gesetzt ist, so kann jedes Feld andere Rahmen und AlphaFelder beim Ausw�hlen haben.
            const static __int64 Raster = 0x00400000; // Wenn dieser Flag gesetzt ist, so werden zwischen den Feldern Linien gezeichnet

            const static __int64 beweglich = SpaltenBreite�nderbar | ZeilenH�he�nderbar | SpaltenBeweglich; // Vereint die Flags: SpaltenBreite�nderbar, ZeilenH�he�nderbar, SpaltenBeweglich
            const static __int64 min_max = SpaltenBreiteMax | SpaltenBreiteMin | ZeilenH�heMax | ZeilenH�heMax; // Vereint die Flags: SpaltenBreiteMax, SpaltenBreiteMin, ZeilenH�heMax, ZeilenH�heMax
            const static __int64 scroll = VScroll | HScroll; // Vereint die Flags: VScroll, HScroll
            const static __int64 normal = Rahmen | Erlaubt | Sichtbar | AuswahlBuffer | AuswahlRahmen | Raster; // Vereint die Flags: Rahmen, Erlaubt, Sichtbar, SpaltenBeweglich, AuswahlBuffer, AuswahlRahmen, Raster
        };
	private:
		RCArray< Array< Zeichnung* > > *zZeichnungs;
		RCArray< Text > *spaltenNamen;
		RCArray< Text > *zeilenNamen;
		Array< int > *spaltenBreite;
		Array< int > *zeilenH�he;
		Array< int > *minSpaltenBreite;
		Array< int > *maxSpaltenBreite;
		Array< int > *minZeilenH�he;
		Array< int > *maxZeilenH�he;
		int spaltenAnzahl, zeilenAnzahl;
		int klickSpalte;
		double mSpalte, mZeile;
		int mx, my;
		Punkt selected;
		int rasterFarbe;
		int rasterBreite;
		LRahmen *aRam;
		AlphaFeld *aAf;
		RCArray< RCArray< LRahmen > > *msaRam;
		RCArray< RCArray< AlphaFeld > > *msaAf;
		RCArray< Array< __int64 > > *styles;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) ObjTabelle();
		// Destruktor 
		__declspec( dllexport ) ~ObjTabelle();
		// F�gt der Tabelle eine Spalte hinzu
        //  name: Der Name der Spalte
		__declspec( dllexport ) void addSpalte( const char *name );
        // F�gt der Tabelle eine Spalte hinzu
        //  name: Der Name der Spalte
		__declspec( dllexport ) void addSpalte( Text *name );
        // F�gt der Tabelle an einer bestimmten Position eine Spalte hinzu
        //  sNum: Der Index der neuen Spalte
        //  name: Der Name der neuen Spalte
		__declspec( dllexport ) void addSpalte( int sNum, const char *name );
        // F�gt der Tabelle an einer bestimmten Position eine Spalte hinzu
        //  sNum: Der Index der neuen Spalte
        //  name: Der Name der neuen Spalte
		__declspec( dllexport ) void addSpalte( int sNum, Text *name );
        // F�gt der Tabelle eine Zeile hinzu
        //  name: Der Name der Zeile
		__declspec( dllexport ) void addZeile( const char *name );
        // F�gt der Tabelle eine Zeile hinzu
        //  name: Der Name der Zeile
		__declspec( dllexport ) void addZeile( Text *name );
        // F�gt der Tabelle an einer bestimmten Position eine Zeile hinzu
        //  zNum: Der Index der neuen Zeile
        //  name: Der Name der neuen Zeile
		__declspec( dllexport ) void addZeile( int zNum, const char *name );
        // F�gt der Tabelle an einer bestimmten Position eine Zeile hinzu
        //  sNum: Der Index der neuen Zeile
        //  name: Der Name der neuen Zeile
		__declspec( dllexport ) void addZeile( int zNum, Text *name );
        // Entfernt eine Spalte
        //  sNum: Der Index der Spalte
		__declspec( dllexport ) void removeSpalte( int sNum );
        // Entfernt eine Spalte
        //  name: Der Name der Spalte
		__declspec( dllexport ) void removeSpalte( const char *name );
        // Entfernt eine Spalte
        //  name: Der Name der Spalte
		__declspec( dllexport ) void removeSpalte( Text *name );
        // Entfernt eine Zeile
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) void removeZeile( int zNum );
        // Entfernt eine Zeile
        //  name: Der Name der Zeile
		__declspec( dllexport ) void removeZeile( const char *name );
        // Entfernt eine Zeile
        //  name: Der Name der Zeile
		__declspec( dllexport ) void removeZeile( Text *name );
        // Setzt den Index einer Spalte
        //  name: Der Name der Spalte
        //  pos: Der neue Index der Spalte
		__declspec( dllexport ) void setSpaltePosition( const char *name, int pos );
        // Setzt den Index einer Spalte
        //  name: Der Name der Spalte
        //  pos: Der neue Index der Spalte
		__declspec( dllexport ) void setSpaltePosition( Text *name, int pos );
        // Setzt den Index einer Spalte
        //  sNum: Der alte Index der Spalte
        //  pos: Der neue Index der Spalte
		__declspec( dllexport ) void setSpaltePosition( int sNum, int pos );
        // Setzt den Index einer Zeile
        //  name: Der Name der Zeile
        //  pos: Der neue Index der Zeile
		__declspec( dllexport ) void setZeilePosition( const char *name, int pos );
        // Setzt den Index einer Zeile
        //  name: Der Name der Zeile
        //  pos: Der neue Index der Zeile
		__declspec( dllexport ) void setZeilePosition( Text *name, int pos );
        // Setzt den Index einer Zeile
        //  zNum: Der alte Index der Zeile
        //  pos: Der neue Index der Zeile
		__declspec( dllexport ) void setZeilePosition( int zNum, int pos );
        // Setzt ein Zeichnung, welches in einem Bestimmten Feld sein soll
        // Wenn bereits ein Zeichnung in dem Feld ist, wird es �berschrieben.
        //  sNum: Der Index der Spalte, in der das Zeichnung stehen soll
        //  zNum: Der Index der Zeile, in der das Zeichnung stehen soll
        //  zObj: Das Zeichnung welches in dem Feld sein soll
		__declspec( dllexport ) void setZeichnungZ( int sNum, int zNum, Zeichnung *zObj );
        // Setzt ein Zeichnung, welches in einem Bestimmten Feld sein soll
        // Wenn bereits ein Zeichnung in dem Feld ist, wird es �berschrieben.
        //  spaltenName: Der Name der Spalte, in der das Zeichnung stehen soll
        //  zeilenName: Der Name der Zeile, in der das Zeichnung stehen soll
        //  zZeichnung: Das Zeichnung welches in dem Feld sein soll
		__declspec( dllexport ) void setZeichnungZ( const char *spaltenName, const char *zeilenName, Zeichnung *zZeichnung );
        // Setzt ein Zeichnung, welches in einem Bestimmten Feld sein soll
        // Wenn bereits ein Zeichnung in dem Feld ist, wird es �berschrieben.
        //  spaltenName: Der Name der Spalte, in der das Zeichnung stehen soll
        //  zeilenName: Der Name der Zeile, in der das Zeichnung stehen soll
        //  zZeichnung: Das Zeichnung welches in dem Feld sein soll
		__declspec( dllexport ) void setZeichnungZ( Text *spaltenName, Text *zeilenName, Zeichnung *zZeichnung );
        // Setzt die Spalten Breite
        //  sNum: Der Index der Spalte
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setSpaltenBreite( int sNum, int br );
        // Setzt die Spalten Breite
        //  name: Der Name der Spalte
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setSpaltenBreite( const char *name, int br );
        // Setzt die Spalten Breite
        //  name: Der Name der Spalte
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setSpaltenBreite( Text *name, int br );
        // Setzt die Zeilen H�he
        //  zNum: Der Index der Zeile
        //  h�: Die H�he in Pixeln
		__declspec( dllexport ) void setZeilenH�he( int zNum, int h� );
        // Setzt die Zeilen H�he
        //  name: Der Index der Zeile
        //  h�: Die H�he in Pixeln
		__declspec( dllexport ) void setZeilenH�he( const char *name, int h� );
        // Setzt die Zeilen H�he
        //  name: Der Index der Zeile
        //  h�: Die H�he in Pixeln
		__declspec( dllexport ) void setZeilenH�he( Text *name, int h� );
        // Setzt die minimale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMin)
        //  sNum: Der Index der Spalte
        //  minBr: Die minimale Breite in Pixeln
		__declspec( dllexport ) void setMinSpaltenBreite( int sNum, int minBr );
        // Setzt die minimale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMin)
        //  name: Der Name der Spalte
        //  minBr: Die minimale Breite in Pixeln
		__declspec( dllexport ) void setMinSpaltenBreite( const char *name, int minBr );
        // Setzt die minimale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMin)
        //  name: Der Name der Spalte
        //  minBr: Die minimale Breite in Pixeln
		__declspec( dllexport ) void setMinSpaltenBreite( Text *name, int minBr );
        // Setzt die maximale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMax)
        //  sNum: Der Index der Spalte
        //  maxBr: Die maximale Breite in Pixeln
		__declspec( dllexport ) void setMaxSpaltenBreite( int sNum, int maxBr );
        // Setzt die maximale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMax)
        //  name: Der Name der Spalte
        //  maxBr: Die maximale Breite in Pixeln
		__declspec( dllexport ) void setMaxSpaltenBreite( const char *name, int maxBr );
        // Setzt die maximale Spalten Breite (ben�tigt Flag: SpaltenBreite�nderbar, SpaltenBreiteMax)
        //  name: Der Name der Spalte
        //  maxBr: Die maximale Breite in Pixeln
		__declspec( dllexport ) void setMaxSpaltenBreite( Text *name, int maxBr );
        // Setzt die minimale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMin)
        //  zNum: Der Index der Zeile
        //  minH�: Die minimale H�he in Pixeln
		__declspec( dllexport ) void setMinZeilenH�he( int zNum, int minH� );
        // Setzt die minimale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMin)
        //  name: Der Name der Zeile
        //  minH�: Die minimale H�he in Pixeln
		__declspec( dllexport ) void setMinZeilenH�he( const char *name, int minH� );
        // Setzt die minimale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMin)
        //  name: Der Name der Zeile
        //  minH�: Die minimale H�he in Pixeln
		__declspec( dllexport ) void setMinZeilenH�he( Text *name, int minH� );
        // Setzt die maximale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMax)
        //  zNum: Der Index der Zeile
        //  maxH�: Die maximale H�he in Pixeln
		__declspec( dllexport ) void setMaxZeilenH�he( int zNum, int maxH� );
        // Setzt die maximale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMax)
        //  name: Der Name der Zeile
        //  maxH�: Die maximale H�he in Pixeln
		__declspec( dllexport ) void setMaxZeilenH�he( const char *name, int maxH� );
        // Setzt die maximale Zeilen H�he (ben�tigt Flag: ZeilenH�he�nderbar, ZeienH�heMax)
        //  name: Der Name der Zeile
        //  maxH�: Die maximale H�he in Pixeln
		__declspec( dllexport ) void setMaxZeilenH�he( Text *name, int maxH� );
        // Legt fest, welches Feld ausgew�hlt ist (ben�tigt Flag: Erlaubt)
        //  sNum: Der Index der Spalte des Feldes
        //  zNum: Der Index der Zeile des Feldes
		__declspec( dllexport ) void setAuswahl( int sNum, int zNum );
        // Legt fest, welches Feld ausgew�hlt ist (ben�tigt Flag: Erlaubt)
        //  spaltenName: Der Name der Spalte des Feldes
        //  zeilenName: Der Name der Zeile des Feldes
		__declspec( dllexport ) void setAuswahl( const char *spaltenName, const char *zeilenName );
        // Legt fest, welches Feld ausgew�hlt ist (ben�tigt Flag: Erlaubt)
        //  spaltenName: Der Name der Spalte des Feldes
        //  zeilenName: Der Name der Zeile des Feldes
		__declspec( dllexport ) void setAuswahl( Text *spaltenName, Text *zeilenName );
        // Setzt dei Farbe des zwischen den K�stchen angezeigten Rasters
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setRasterFarbe( int f );
        // Setzt due Breite des zwischen den K�stchen angezeigten Raseter
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setRasterBreite( int br );
        // Setzte den Zeiger auf einen Rahmen, der um das ausgew�hlte K�stchen gezeichnet wird
        //  ram: Der Rahmen
		__declspec( dllexport ) void setARahmenZ( LRahmen *ram );
        // Setzt die farbe des Rahmens, der um das ausgew�hlte K�stchen gezeichnet wird
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setARFarbe( int f ); 
        // Setzt die Breite des Rahmens, der um das ausgew�hlte K�stchen gezeichnet wird
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setARBreite( int br );
        // Setzt einen Zeiger auf das AlphaFeld, das f�r das ausgew�hlte K�stchen verwendet wird
        //  af: Das AlphaFeld
		__declspec( dllexport ) void setAAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des AlphaFeldes, das f�r das ausgew�hlte K�stchen verwendet wird
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAAfFarbe( int f );
        // Setzt die St�rke des AlphaFeldes, das f�r das ausgew�hlte K�stchen verwendet wird
        //  st: Die St�rke
		__declspec( dllexport ) void setAAfSt�rke( int st );
        // Setzt einen Zeiger auf einen Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  ram: Der Rahmen
		__declspec( dllexport ) void setARahmenZ( int sNum, int zNum, LRahmen *ram );
        // Setzt einen Zeiger auf einen Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  ram: Der Rahmen
		__declspec( dllexport ) void setARahmenZ( const char *spaltenName, const char *zeilenName, LRahmen *ram );
        // Setzt einen Zeiger auf einen Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  ram: Der Rahmen
		__declspec( dllexport ) void setARahmenZ( Text *spaltenName, Text *zeilenName, LRahmen *ram );
        // Setzt die Farbe von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setARFarbe( int sNum, int zNum, int f );
        // Setzt die Farbe von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setARFarbe( const char *spaltenName, const char *zeilenName, int f );
        // Setzt die Farbe von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setARFarbe( Text *spaltenName, Text *zeilenName, int f );
        // Setzt die Breite von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setARBreite( int sNum, int zNum, int br );
        // Setzt die Breite von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setARBreite( const char *spaltenName, const char *zeilenName, int br );
        // Setzt die Breite von einem Rahmen, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  br: Die Breite in Pixeln
		__declspec( dllexport ) void setARBreite( Text *spaltenName, Text *zeilenName, int br );
        // Setzt den Farb�ergang, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  af: Der Farb�bergang
		__declspec( dllexport ) void setAAlphaFeldZ( int sNum, int zNum, AlphaFeld *af );
        // Setzt den Farb�ergang, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  af: Der Farb�bergang
		__declspec( dllexport ) void setAAlphaFeldZ( const char *spaltenName, const char *zeilenName, AlphaFeld *af );
        // Setzt den Farb�ergang, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  af: Der Farb�bergang
		__declspec( dllexport ) void setAAlphaFeldZ( Text *spaltenName, Text *zeilenName, AlphaFeld *af );
        // Setzt die Farbe des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAAfFarbe( int sNum, int zNum, int f );
        // Setzt die Farbe des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAAfFarbe( const char *spaltenName, const char *zeilenName, int f );
        // Setzt die Farbe des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAAfFarbe( Text *spaltenName, Text *zeilenName, int f );
        // Setzt die St�rke des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  st: Die St�rke
		__declspec( dllexport ) void setAAfSt�rke( int sNum, int zNum, int st );
        // Setzt die St�rke des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  st: Die St�rke
		__declspec( dllexport ) void setAAfSt�rke( const char *spaltenName, const char *zeilenName, int st );
        // Setzt die St�rke des Farb�ergangs, der bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte wird
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  st: Die St�rke
		__declspec( dllexport ) void setAAfSt�rke( Text *spaltenName, Text *zeilenName, int st );
        // F�gt Styles hinzu, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  style: der Style, der hinzugef�gt werden soll
		__declspec( dllexport ) void addMsStyle( int sNum, int zNum, __int64 style );
        // F�gt Styles hinzu, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der hinzugef�gt werden soll
		__declspec( dllexport ) void addMsStyle( const char *spaltenName, const char *zeilenName, __int64 style );
        // F�gt Styles hinzu, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der hinzugef�gt werden soll
		__declspec( dllexport ) void addMsStyle( Text *spaltenName, Text *zeilenName, __int64 style );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
		__declspec( dllexport ) void setMsStyle( int sNum, int zNum, __int64 style );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
		__declspec( dllexport ) void setMsStyle( const char *spaltenName, const char *zeilenName, __int64 style );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
		__declspec( dllexport ) void setMsStyle( Text *spaltenName, Text *zeilenName, __int64 style );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
        //  add_remove: 1, falls die �bergebenen Styles hinzugef�gt werden sollen. 0, fals sie entfernt werden sollen
		__declspec( dllexport ) void setMsStyle( int sNum, int zNum, __int64 style, bool add_remove );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
        //  add_remove: 1, falls die �bergebenen Styles hinzugef�gt werden sollen. 0, fals sie entfernt werden sollen
		__declspec( dllexport ) void setMsStyle( const char *spaltenName, const char *zeilenName, __int64 style, bool add_remove );
        // Setzt die Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der verwendet werden soll
        //  add_remove: 1, falls die �bergebenen Styles hinzugef�gt werden sollen. 0, fals sie entfernt werden sollen
		__declspec( dllexport ) void setMsStyle( Text *spaltenName, Text *zeilenName, __int64 style, bool add_remove );
        // Entfernt Styles von den Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  sNum: Der Index der Spalte des K�stchens
        //  zNum: Der Index der Zeile des K�stchens
        //  style: der Style, der entfernt werden soll
		__declspec( dllexport ) void l�scheMsStyle( int sNum, int zNum, __int64 style );
        // Entfernt Styles von den Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der entfernt werden soll
		__declspec( dllexport ) void l�scheMsStyle( const char *spaltenName, const char *zeilenName, __int64 style );
        // Entfernt Styles von den Styles, die bei dem Flag AuswahlMultistyled bei der Auswahl eines bestimmten K�stchens verwendte werden
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
        //  style: der Style, der entfernt werden soll
		__declspec( dllexport ) void l�scheMsStyle( Text *spaltenName, Text *zeilenName, __int64 style );
        // Aktualisiert das Objekt. Wird vom Framework aufgerufen
        //  tickVal: Die Zeit in sekunden, die seit dem lezten Aufruf dieser Funktion vergangen ist
        //  return: 1, wenn sich etwas ver�ndert hat und das Bild neu gezeichnet werden muss. 0 sonst
        __declspec( dllexport ) bool tick( double tickVal ) override;
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
		__declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Verarbeitet Tastatur Nachrichten
        //  me: Das Ereignis, was durch die Tastatureingabe ausgel��t wurde
		__declspec( dllexport ) void doTastaturEreignis( TastaturEreignis &te ) override;
        // Zeichnet das Objekt nach zRObj, falls er sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
		__declspec( dllexport ) void render( Bild &zRObj ) override;
		// Gibt die Anzahl der Spalten zur�ck
		__declspec( dllexport ) int getSpaltenAnzahl() const;
        // Gibt die Anzahl der Zeilen zur�ck
		__declspec( dllexport ) int getZeilenAnzahl() const;
        // Gibt den Index einer Spalte zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getSpaltenNummer( const char *name ) const;
        // Gibt den Index einer Spalte zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getSpaltenNummer( Text *name ) const;
        // Gibt den Namen einer Spalte zur�ck
        //  num: Der Index der Splate
		__declspec( dllexport ) Text *getSpaltenName( int num ) const;
        // Gibt den Namen einer Spalte ohne erh�hten reference Counter zur�ck
        //  num: Der Index der Splate
		__declspec( dllexport ) Text *zSpaltenName( int num ) const;
        // Gibt den Index einer Zeile zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getZeilenNummer( const char *name ) const;
        // Gibt den Index einer Zeile zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getZeilenNummer( Text *name ) const;
        // Gibt den Namen einer Zeile zur�ck
        //  num: Der Index der Zeile
		__declspec( dllexport ) Text *getZeilenName( int num ) const;
        // Gibt den Namen einer Zeile ohne erh�hten Reference Counter zur�ck
        //  num: Der Index der Zeile
		__declspec( dllexport ) Text *zZeilenName( int num ) const;
        // Sucht eine Zeichnung in der Tabelle und gibt den Index der Spalte als x und den der Zeile als y zur�ck. (-1, -1) falls das Objekt nicht gefunden wurde
        //  zObj: Die Zeichnung
		__declspec( dllexport ) Punkt getZeichnungPosition( Zeichnung *zObj ) const;
        // Gibt die Zeichnung zur�ck, die in einem bestimmten K�stchen der Tabelle ist
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) Zeichnung *zZeichnung( int sNum, int zNum ) const;
        // Gibt die Zeichnung zur�ck, die in einem bestimmten K�stchen der Tabelle ist
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
		__declspec( dllexport ) Zeichnung *zZeichnung( const char *spaltenName, const char *zeilenName ) const;
        // Gibt die Zeichnung zur�ck, die in einem bestimmten K�stchen der Tabelle ist
        //  spaltenName: Der Name der Spalte des K�stchens
        //  zeilenName: Der Name der Zeile des K�stchens
		__declspec( dllexport ) Zeichnung *zZeichnung( Text *spaltenName, Text *zeilenName ) const;
        // Gibt die Breite einer Spalte in Pixeln zur�ck
        //  num: Der Index der Spalte
		__declspec( dllexport ) int getSpaltenBreite( int num ) const;
        // Gibt die Breite einer Spalte in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getSpaltenBreite( const char *name ) const;
        // Gibt die Breite einer Spalte in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getSpaltenBreite( Text *name ) const;
        // Gibt die H�he einer Zeile in Pixeln zur�ck
        //  num: Der Index der Zeile
		__declspec( dllexport ) int getZeilenH�he( int num ) const;
        // Gibt die H�he einer Zeile in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getZeilenH�he( const char *name ) const;
        // Gibt die H�he einer Zeile in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getZeilenH�he( Text *name ) const;
        // Gibt die minimale Spalten breite in Pixeln zur�ck
        //  num: Der Index der Spalte
		__declspec( dllexport ) int getMinSpaltenBreite( int num ) const;
        // Gibt die minimale Spalten breite in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getMinSpaltenBreite( const char *name ) const;
        // Gibt die minimale Spalten breite in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getMinSpaltenBreite( Text *name ) const;
        // Gibt die maximale Spalten breite in Pixeln zur�ck
        //  num: Der Index der Spalte
		__declspec( dllexport ) int getMaxSpaltenBreite( int num ) const;
        // Gibt die maximale Spalten breite in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getMaxSpaltenBreite( const char *name ) const;
        // Gibt die maximale Spalten breite in Pixeln zur�ck
        //  name: Der Name der Spalte
		__declspec( dllexport ) int getMaxSpaltenBreite( Text *name ) const;
        // Gibt die minimale Zeilen H�he in Pixeln zur�ck
        //  num: Der Index der Zeile
		__declspec( dllexport ) int getMinZeilenH�he( int num ) const;
        // Gibt die minimale Zeilen H�he in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getMinZeilenH�he( const char *name ) const;
        // Gibt die minimale Zeilen H�he in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getMinZeilenH�he( Text *name ) const;
        // Gibt die maximale Zeilen H�he in Pixeln zur�ck
        //  num: Der Index der Zeile
		__declspec( dllexport ) int getMaxZeilenH�he( int num ) const;
        // Gibt die maximale Zeilen H�he in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getMaxZeilenH�he( const char *name ) const;
        // Gibt die maximale Zeilen H�he in Pixeln zur�ck
        //  name: Der Name der Zeile
		__declspec( dllexport ) int getMaxZeilenH�he( Text *name ) const;
        // Gibt den index der Splate zur�ck, auf die die Maus zeigt
        //  mx: Die x Koordinate der Mausposition basierend zum linken Rand der Tabelle in Pixeln
		__declspec( dllexport ) double getMausSpalte( int mx ) const;
        // Gibt den Namen der Splate zur�ck, auf die die Maus zeigt
        //  mx: Die x Koordinate der Mausposition basierend zum linken Rand der Tabelle in Pixeln
		__declspec( dllexport ) Text *getMausSpaltenName( int mx ) const;
        // Gibt den Namen der Splate ohne erh�hten Reference Counter zur�ck, auf die die Maus zeigt
        //  mx: Die x Koordinate der Mausposition basierend zum linken Rand der Tabelle in Pixeln
		__declspec( dllexport ) Text *zMausSpaltenName( int mx ) const;
        // Gibt den index der Zeile zur�ck, auf die die Maus zeigt
        //  my: Die Y Koordinate der Mausposition basierend zum oberen Rand der Tabelle in Pixeln
		__declspec( dllexport ) double getMausZeile( int my ) const;
        // Gibt den Namen der Zeile zur�ck, auf die die Maus zeigt
        //  my: Die Y Koordinate der Mausposition basierend zum oberen Rand der Tabelle in Pixeln
		__declspec( dllexport ) Text *getMausZeilenName( int my ) const;
        // Gibt den Namen der Zeile ohne erh�hten Reference Counter zur�ck, auf die die Maus zeigt
        //  my: Die Y Koordinate der Mausposition basierend zum oberen Rand der Tabelle in Pixeln
		__declspec( dllexport ) Text *zMausZeilenName( int my ) const;
        // Gibt den Index der Spalte als x und den der Zeile als y des ausgew�hlten Feldes zur�ck
		__declspec( dllexport ) const Punkt &getAuswahlPosition() const;
        // Gibt die Farbe des Rasters im A8R8G8B8 Format zur�ck
		__declspec( dllexport ) int getRasterFarbe() const;
        // Gibt die Breite des Rasters in Pixeln zur�ck
		__declspec( dllexport ) int getRasterBreite() const;
        // Gibt einen Zeiger auf den Rahmen zur�ck, der bei dem ausgew�hlten Feld verwendet wird
        __declspec( dllexport ) LRahmen *getARahmen() const;
        // Gibt einen Zeiger auf den Rahmen ohne erh�hten Reference Counter zur�ck, der bei dem ausgew�hlten Feld verwendet wird
		__declspec( dllexport ) LRahmen *zARahmen() const;
        // Gibt einen Zeiger auf den Farb�bergang zur�ck, der bei dem ausgew�hlten Feld verwendet wird
		__declspec( dllexport ) AlphaFeld *getAAlphaFeld() const;
        // Gibt einen Zeiger auf den Farb�bergang ohne erh�hten Reference Counter zur�ck, der bei dem ausgew�hlten Feld verwendet wird
		__declspec( dllexport ) AlphaFeld *zAAlphaFeld() const;
        // Gibt einen Zeiger auf den Rahmen zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) LRahmen *getARahmen( int sNum, int zNum ) const;
        // Gibt einen Zeiger auf den Rahmen ohne erh�hten Reference Couner zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) LRahmen *zARahmen( int sNum, int zNum ) const;
        // Gibt einen Zeiger auf den Farb�bergang zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) AlphaFeld *getAAlphaFeld( int sNum, int zNum ) const;
        // Gibt einen Zeiger auf den Farb�bergang ohne erh�hten Reference Couner zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
		__declspec( dllexport ) AlphaFeld *zAAlphaFeld( int sNum, int zNum ) const;
        // Gibt einen Zeiger auf den Rahmen zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) LRahmen *getARahmen( const char *spaltenName, const char *zeilenName ) const;
        // Gibt einen Zeiger auf den Rahmen ohne erh�hten Reference Coune zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) LRahmen *zARahmen( const char *spaltenName, const char *zeilenName ) const;
        // Gibt einen Zeiger auf den Farb�bergang zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) AlphaFeld *getAAlphaFeld( const char *spaltenName, const char *zeilenName ) const;
        // Gibt einen Zeiger auf den Farb�bergang ohne erh�hten Reference Coune zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) AlphaFeld *zAAlphaFeld( const char *spaltenName, const char *zeilenName ) const;
        // Gibt einen Zeiger auf den Rahmen zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) LRahmen *getARahmen( Text *spaltenName, Text *zeilenName ) const;
        // Gibt einen Zeiger auf den Rahmen ohne erh�hten Reference Coune zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) LRahmen *zARahmen( Text *spaltenName, Text *zeilenName ) const;
        // Gibt einen Zeiger auf den Farb�bergang zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) AlphaFeld *getAAlphaFeld( Text *spaltenName, Text *zeilenName ) const;
        // Gibt einen Zeiger auf den Farb�bergang ohne erh�hten Reference Coune zur�ck, der bei dem Flag AuswahlMultistyled bei der auswahl eines bestimmten K�stchens verwendet wird
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
		__declspec( dllexport ) AlphaFeld *zAAlphaFeld( Text *spaltenName, Text *zeilenName ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style gesetzt ist
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyle( int sNum, int zNum, __int64 style ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style nicht gesetzt ist
        //  sNum: Der Index der Spalte
        //  zNum: Der Index der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyleNicht( int sNum, int zNum, __int64 style ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style gesetzt ist
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyle( const char *spaltenName, const char *zeilenName, __int64 style ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style nicht gesetzt ist
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyleNicht( const char *spaltenName, const char *zeilenName, __int64 style ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style gesetzt ist
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyle( Text *spaltenName, Text *zeilenName, __int64 style ) const;
        // Pr�ft ob bei dem Flag AuswahlMultistyled f�r ein bestimmtes K�stchen ein bestimmter Style nicht gesetzt ist
        //  spaltenName: Der Name der Spalte
        //  zeilenName: Der Name der Zeile
        //  style: Der Style, der gepf�ft werden soll
		__declspec( dllexport ) inline bool hatMsStyleNicht( Text *spaltenName, Text *zeilenName, __int64 style ) const;
        // Erzeugt eine Kopie der Tabelle, die ohne auswirkungen auf das Original ver�ndert werden kann
		__declspec( dllexport ) Zeichnung *dublizieren() const override;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
		__declspec( dllexport ) ObjTabelle *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
		__declspec( dllexport ) ObjTabelle *release();
	};
}
#endif