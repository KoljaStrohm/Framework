#ifndef AuswahlBox_H
#define AuswahlBox_H

#include "Zeichnung.h"
#include "Array.h"

namespace Framework
{
	class TextFeld; // TextFeld.h
	class VScrollBar; // Scroll.h
	class LRahmen; // Rahmen.h
	class Knopf; // Knopf.h
	class AlphaFeld; // AlphaFeld.h
	class Text; // Tet.h
	class Schrift; // Schrift.h

    // Eine Zeichnung des 2D GUI Frameworks. Repr�sentiert eine Box, aus der der Nutzer durch ausklappen verschiedene Werte ausw�hlen kann
	class AuswahlBox : public ZeichnungHintergrund
	{
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 FeldRahmen = 0x000001000; // Wenn dieser Flag gesetzt ist, hat jeder Wert aus der Liste einen Rahmen
            const static __int64 FeldHintergrund = 0x000002000; // Wenn dieser Flag gesetzt ist, hat jeder Wert aus der Liste einen Hintergrund
            const static __int64 FeldHBild = 0x000004000; // Wenn dieser Flag gesetzt ist, hat jeder Wert aus der Liste ein Bild als Hintergrund
            const static __int64 FeldHAlpha = 0x000008000; // Wenn dieser Flag gesetzt ist, hat jeder Wert aus der Liste einen Transparenten Hintergrund
            const static __int64 FeldBuffer = 0x000010000; // Wenn dieser Flag gesetzt ist, hat jeder Wert aus der Liste einen Farb�bergang
            const static __int64 AuswahlHintergrund = 0x000020000; // Wenn dieser Flag gesetzt ist, bekommt der Wert, der gerade ausgew�hlt ist einen Hintergrund
            const static __int64 AuswahlHBild = 0x000040000; // Wenn dieser Flag gesetzt ist, bekommt der Wert, der gerade ausgew�hlt ist ein Hintergrundbild
            const static __int64 AuswahlHAlpha = 0x000080000; // Wenn dieser Flag gesetzt ist, bekommt der Wert, der gerade ausgew�hlt ist einen transparenten Hintergrund
            const static __int64 AuswahlBuffer = 0x000100000; // Wenn dieser Flag gesetzt ist, bekommt der Wert, der gerade ausgew�hlt ist einen Farb�bergang
            const static __int64 AuswahlRahmen = 0x000200000; // Wenn dieser Flag gesetzt ist, bekommt der Wert, der gerade ausgew�hlt ist einen Rahmen
            const static __int64 MultiStyled = 0x000400000; // Wenn dieser Flag gesetzt ist, hat jeder Wert seine eigenen Hintergr�nde unt Rahmen und nicht alle die selben
            const static __int64 MaxH�he = 0x004000000; // Legt eine maximale H�he der ausgeklappten Liste fest. Es erscheint automatisch eine Scrollbar wenn mehr Elemente da sind als sichtbar sein k�nnen
            const static __int64 MausHintergrund = 0x008000000; // Wenn dieser Flag gesetzt ist, hat ein Element, wo die Maus drau zeigt, einen Hintergrund
            const static __int64 MausHBild = 0x010000000; // Wenn dieser Flag gesetzt ist, hat ein Element, wo die Maus drauf zeigt, ein Hintergrundbild
            const static __int64 MausHAlpha = 0x020000000; // Wenn dieser Flag gesetzt ist, hat ein Element, wo die Maus drauf zeigt, einen transparenten Hintergrund
            const static __int64 MausBuffer = 0x040000000; // Wenn dieser Flag gesetzt ist, hat ein Element, wo die Maus drauf zeigt, einen Farb�bergang
            const static __int64 MausRahmen = 0x080000000; // Wenn dieser Flag gesetzt ist, hat ein Element, wo die Maus drauf zeigt, einen Rahmen
            //const int NachObenAusklappen	= 0x100000000;
            //const int AutoAusklappRichtung	= 0x200000000;

            const static __int64 Normal = Sichtbar | Erlaubt | Rahmen | FeldRahmen | AuswahlBuffer | AuswahlRahmen | MaxH�he | VScroll | MausRahmen | MausBuffer; // Normaler Style: Sichtbar, Erlaubt, Rahmen, FeldRahmen, AuswahlBuffer, AuswahlRahmen, MaxH�he, VScroll, MausRahmen, MausBuffer
        };
	private:
		Schrift *schrift;
		Array< __int64 > *msStyle;
		RCArray< TextFeld > *members;
		Knopf *ausfahren;
		LRahmen *auswRahmen;
		int auswBgF;
		Bild *auswBgB;
		AlphaFeld *auswAf;
		RCArray< LRahmen > *msAuswRahmen;
		Array< int > *msAuswBgF;
		RCArray< Bild > *msAuswBgB;
		RCArray< AlphaFeld > *msAuswAf;
		LRahmen *mausRahmen;
		int mausBgF;
		Bild *mausBgB;
		AlphaFeld *mausAf;
		RCArray< LRahmen > *msMausRahmen;
		Array< int > *msMausBgF;
		RCArray< Bild > *msMausBgB;
		RCArray< AlphaFeld > *msMausAf;
		int anzahl;
		int auswahl;
		bool ausgeklappt;
		int ausklappH�he;
		int ausklapMaxH�he;
		int eintragH�he;
		double tickval;
		int mausEintrag;
		bool scrollAnzeigen;
		void *eAkP;
		void( *eAk )( void *p, AuswahlBox *, int, int );
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) AuswahlBox();
		// Destruktor 
		__declspec( dllexport ) ~AuswahlBox();
		// Setzt den Parameter der R�ckruffunktion, die aufgerufen wird, wenn der Benutzer ein neues element ausw�hlt
        //  p: Der Parameter
		__declspec( dllexport ) void setEventParam( void *p );
        // Setzt die R�ckruffunktion, die Aufgerufen wird, wenn der Benutzer ein neues Element ausw�hlt
        //  eAk: Die R�ckruffunktion
        __declspec( dllexport ) void setEventAktion( void( *eAk )( void *p, AuswahlBox *, int, int ) );
        // Setzt die verwendete Schrift
        //  schrift: Die Schrift
		__declspec( dllexport ) void setSchriftZ( Schrift *schrift );
        // F�gt der Liste einen ausw�hlbaren Eintrag hinzu. Der erste Eintrag ist zu Beginn automatisch ausgew�hlt
        //  txt: Der Text des Eintrags
		__declspec( dllexport ) void addEintrag( const char *txt );
        // F�gt der Liste einen ausw�hlbaren Eintrag hinzu. Der erste Eintrag ist zu Beginn automatisch ausgew�hlt
        //  txt: Der Text des Eintrags
		__declspec( dllexport ) void addEintrag( Text *txt );
        // F�gt der Liste einen ausw�hlbaren Eintrag hinzu. Der erste Eintrag ist zu Beginn automatisch ausgew�hlt
        //  txt: Ein Zeiger auf den Eintrag
		__declspec( dllexport ) void addEintragZ( TextFeld *txt );
        // �ndert den Text eines Eintrags
        //  i: Der Index des Eintrags
        //  txt: Der neue Text
		__declspec( dllexport ) void setEintrag( int i, const char *txt );
        // �ndert den Text eines Eintrags
        //  i: Der Index des Eintrags
        //  txt: Der neue Text
		__declspec( dllexport ) void setEintrag( int i, Text *txt );
        // �ndert einen Eintrag
        //  i: Der Index des Eintrags
        //  txt: Ein Zeiger auf den neuen Eintrag
		__declspec( dllexport ) void setEintragZ( int i, TextFeld *txt );
        // L�scht einen Eintrag
        //  i: Der Index des Eintrags
		__declspec( dllexport ) void l�scheEintrag( int i );
        // Setzt einen Zeiger auf den Knopf, der zum aus und einklappen der Liste verwendet wird
        //  ausK: Der Knopf
		__declspec( dllexport ) void setAusklappKnopfZ( Knopf *ausK );
        // Setzt einen Zeiger auf einen Rahmen, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  rahmen: Der Rahemn
		__declspec( dllexport ) void setEintragRahmenZ( int i, LRahmen *rahmen );
        // Setzt die Farbe eines Rahmens, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  f: Die farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setEintragRahmenFarbe( int i, int f );
        // Setzt die Breite eines Rahmens, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  rbr: Die Breite des Rahmens in Pixeln
		__declspec( dllexport ) void setEintragRahmenBreite( int i, int rbr );
        // Setzt eine Hintergrund Farbe, die f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  f: Die farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setEintragHintergrundFarbe( int i, int f );
        // Setzt einen zeiger auf ein Hintergrund Bild, das f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  bgB: Das Hintergrund Bild
		__declspec( dllexport ) void setEintragHintergrundBildZ( int i, Bild *bgB );
        // Setzt ein Hintergrund Bild durch Kopieren, das f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  bgB: Das Hintergrund Bild
		__declspec( dllexport ) void setEintragHintergrundBild( int i, Bild *bgB );
        // Setzt einen zeiger auf einen Farb�bergangn, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  af: Der Farb�bergang
		__declspec( dllexport ) void setEintragAlphaFeldZ( int i, AlphaFeld *af );
        // Setzt dei Farbe eines Farb�bergangns, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  afF: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setEintragAlphaFeldFarbe( int i, int afF );
        // Setzt dei St�rke eines Farb�bergangns, der f�r einen bestimmten Eintrag benutzt wird
        //  i: Der Index des Eintrags
        //  afSt: Die St�rke
		__declspec( dllexport ) void setEintragAlphaFeldSt�rke( int i, int afSt );
        // Setzt eienen Zeiger auf einen Rahmen, der bei dem ausgew�hlten Eintrag verwendet wird
        //  rahmen: Der Rahmen
		__declspec( dllexport ) void setAuswRahmenZ( LRahmen *rahmen );
        // Setzt die Farbe eines Rahmens, der bei dem ausgew�hlten Eintrag verwendet wird
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAuswRahmenFarbe( int f );
        // Setzt die Breite eines Rahmens, der bei dem ausgew�hlten Eintrag verwendet wird
        //  rbr: Die Breite in Pixeln
		__declspec( dllexport ) void setAuswRahmenBreite( int rbr );
        // Setzt die Hintergrund Farbe, die bei dem ausgew�hlten Eintrag verwendet wird
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAuswHintergrundFarbe( int f );
        // Setzt den Zeiger auf ein Hintergrund Bild, das bei dem ausgew�hlten Eintrag verwendet wird
        //  bgB: Das Bild
		__declspec( dllexport ) void setAuswHintergrundBildZ( Bild *bgB );
        // Setzt ein Hintergrund Bild durch kopieren, das bei dem ausgew�hlten Eintrag verwendet wird
        //  bgB: Das Bild
		__declspec( dllexport ) void setAuswHintergrundBild( Bild *bgB );
        // Setzt den Zeiger auf einen Farb�bergang, der bei dem ausgew�hlten Eintrag verwendet wird
        //  af: Der Farb�bergang
		__declspec( dllexport ) void setAuswAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe eines Farb�bergangs, der bei dem ausgew�hlten Eintrag verwendet wird
        //  afF: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setAuswAlphaFeldFarbe( int afF );
        // Setzt die St�rke eines Farb�bergangs, der bei dem ausgew�hlten Eintrag verwendet wird
        //  afSt: Die St�rke
		__declspec( dllexport ) void setAuswAlphaFeldSt�rke( int afSt );
        // Setzt eienen Zeiger auf einen Rahmen, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  rahmen: Der Rahmen
		__declspec( dllexport ) void setMsAuswRahmenZ( int i, LRahmen *rahmen );
        // Setzt die Farbe einens Rahmens, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setMsAuswRahmenFarbe( int i, int f );
        // Setzt die Breite einens Rahmens, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  rbr: Die Breite in Pixeln
		__declspec( dllexport ) void setMsAuswRahmenBreite( int i, int rbr );
        // Setzt die Hintergrundfarbe, die bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  f: Die Farbe im A8R8G8B8 Format
		__declspec( dllexport ) void setMsAuswHintergrundFarbe( int i, int f );
        // Setzt eienen Zeiger auf eine Hintergrund Bild, das bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  bgB: Das Bild
		__declspec( dllexport ) void setMsAuswHintergrundBildZ( int i, Bild *bgB );
        // Setzt eien Hintergrund Bild durch kopieren, das bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  bgB: Das Bild
		__declspec( dllexport ) void setMsAuswHintergrundBild( int i, Bild *bgB );
        // Setzt eienen Zeiger auf einen Farbverlauf, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  af: Der Farbverlauf
		__declspec( dllexport ) void setMsAuswAlphaFeldZ( int i, AlphaFeld *af ); // Multistyle Auswahl AlphaFeld setzen
		__declspec( dllexport ) void setMsAuswAlphaFeldFarbe( int i, int afF ); // Multistyle Auswahl AlphaFeld Farbe setzen
		__declspec( dllexport ) void setMsAuswAlphaFeldSt�rke( int i, int afSt ); // Multistyle Auswahl AlphaFeld st�rke setzen
		__declspec( dllexport ) void setMausRahmenZ( LRahmen *rahmen ); // Maus Rahmen setzen
		__declspec( dllexport ) void setMausRahmenFarbe( int f ); // Maus Rahmen Farbe setzen
		__declspec( dllexport ) void setMausRahmenBreite( int rbr ); // Maus Rahmen breite setzen
		__declspec( dllexport ) void setMausHintergrundFarbe( int f ); // Maus Hintergrund Farbe setzen
		__declspec( dllexport ) void setMausHintergrundBildZ( Bild *bgB ); // Maus Hintergrund Bild setzen
		__declspec( dllexport ) void setMausHintergrundBild( Bild *bgB );
		__declspec( dllexport ) void setMausAlphaFeldZ( AlphaFeld *af ); // Maus AlphaFeld setzen
		__declspec( dllexport ) void setMausAlphaFeldFarbe( int afF ); // Maus AlphaFeld Farbe setzen
		__declspec( dllexport ) void setMausAlphaFeldSt�rke( int afSt ); // Maus AlphaFeld st�rke setzen
		__declspec( dllexport ) void setMsMausRahmenZ( int i, LRahmen *rahmen ); // Multistyle Maus Rahmen setzen
		__declspec( dllexport ) void setMsMausRahmenFarbe( int i, int f ); // Multistyle Maus Rahmen Farbe setzen
		__declspec( dllexport ) void setMsMausRahmenBreite( int i, int rbr ); // Multistyle Maus Rahmen breite setzen
		__declspec( dllexport ) void setMsMausHintergrundFarbe( int i, int f ); // Multistyle Maus Hintergrund Farbe setzen
		__declspec( dllexport ) void setMsMausHintergrundBildZ( int i, Bild *bgB ); // Multistyle Maus Hintergrund Bild setzen
		__declspec( dllexport ) void setMsMausHintergrundBild( int i, Bild *bgB );
		__declspec( dllexport ) void setMsMausAlphaFeldZ( int i, AlphaFeld *af ); // Multistyle Maus AlphaFeld setzen
		__declspec( dllexport ) void setMsMausAlphaFeldFarbe( int i, int afF ); // Multistyle Maus AlphaFeld Farbe setzen
		__declspec( dllexport ) void setMsMausAlphaFeldSt�rke( int i, int afSt ); // Multistyle Maus AlphaFeld st�rke setzen
		__declspec( dllexport ) void setAuswahl( int i ); // Eintrag ausw�hlen
		__declspec( dllexport ) void ausklappen(); // liste ausklappen
		__declspec( dllexport ) void einklappen(); // liste einklappen
		__declspec( dllexport ) void scrollZuEintrag( int i ); // liste scrollen
		__declspec( dllexport ) void setMaxAuskappH�he( int maxH�he ); // h�he der Liste beim ausklappen
		__declspec( dllexport ) void setEintragH�he( int h�he ); // setzt die H�he der Eintr�ge
		__declspec( dllexport ) void addMsStyle( int i, __int64 abStyle ); // Multistyle style hinzuf�gen
		__declspec( dllexport ) void setMsStyle( int i, __int64 abStyle, bool add ); // Multistyle style setzen
		__declspec( dllexport ) void setMsStyle( int i, __int64 abStyle );
		__declspec( dllexport ) void l�scheMsStyle( int i, __int64 abStyle ); // Multistyle style entfernen
		__declspec( dllexport ) bool tick( double tickVal ) override; // tick
		__declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override; // Maus
		__declspec( dllexport ) void doTastaturEreignis( TastaturEreignis &te ) override; // Tastatur
		__declspec( dllexport ) void render( Bild &zRObj ) override; // zeichnet nach zRObj
		// constant
		__declspec( dllexport ) int getEintragPos( const char *txt ) const; // gibt die Eintrag Position zur�ck
		__declspec( dllexport ) int getEintragPos( Text *txt ) const;
		__declspec( dllexport ) Text *getEintragText( int i ) const; // gibt den Eintrag Text zur�ck
		__declspec( dllexport ) Text *zEintragText( int i ) const;
		__declspec( dllexport ) TextFeld *getEintrag( int i ) const; // gibt den Eintrag zur�ck
		__declspec( dllexport ) TextFeld *zEintrag( int i ) const;
		__declspec( dllexport ) int getAuswahl() const; // gibt die Position des ausgew�hlten Eintrages zur�ck
		__declspec( dllexport ) int getEintragAnzahl() const; // gibt die Anzahl der Eintr�ge zur�ck
		__declspec( dllexport ) bool istAusgeklappt() const; // pr�ft, ob die Liste ausgeklappt ist
		__declspec( dllexport ) int getMaxH�he() const; // gibt die maximale H�he der Liste zur�ck
		__declspec( dllexport ) int getEintragH�he() const; // gibt die H�he der Eintr�ge zur�ck
		__declspec( dllexport ) Knopf *getAusklappKnopf() const; // gibt den aus-/einklapp Knopf zur�ck
		__declspec( dllexport ) Knopf *zAusklappKnopf() const;
		__declspec( dllexport ) LRahmen *getEintragRahmen( int i ) const; // gibt den Eintrag Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zEintragRahmen( int i ) const;
		__declspec( dllexport ) int getEintragRahmenFarbe( int i ) const; // gibt die Eintrag Rahmen Frabe zur�ck
		__declspec( dllexport ) int getEintragRahmenBreite( int i ) const; // gibt die Eintrag Rahmen Breite zur�ck
		__declspec( dllexport ) AlphaFeld *getEintragAlphaFeld( int i ) const; // gibt das Eintrag AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zEintragAlphaFeld( int i ) const;
		__declspec( dllexport ) int getEintragAlphaFeldFarbe( int i ) const; // gibt die Eintrag AlphaFeld Farbe zur�ck
		__declspec( dllexport ) int getEintragAlphaFeldSt�rke( int i ) const; // gibt die Eintrag AlphaFeld st�rke zur�ck
		__declspec( dllexport ) int getEintragHintergrundFarbe( int i ) const; // gibt die Eintrag Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getEintragHintergrundBild( int i ) const; // gibt das Eintrag Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zEintragHintergrundBild( int i ) const;
		__declspec( dllexport ) LRahmen *getAuswRahmen() const; // gibt den Auswahl Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zAuswRahmen() const;
		__declspec( dllexport ) int getAuswRahmenFarbe() const; // gibt die Auswahl Rahmen Frabe zur�ck
		__declspec( dllexport ) int getAuswRahmenBreite() const; // gibt die Auswahl Rahmen Breite zur�ck
		__declspec( dllexport ) AlphaFeld *getAuswAlphaFeld() const; // gibt das Auswahl AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zAuswAlphaFeld() const;
		__declspec( dllexport ) int getAuswAlphaFeldFarbe() const; // gibt die Auswahl AlphaFeld Farbe zur�ck
		__declspec( dllexport ) int getAuswAlphaFeldSt�rke() const; // gibt die Auswahl AlphaFeld st�rke zur�ck
		__declspec( dllexport ) int getAuswHintergrundFarbe() const; // gibt die Auswahl Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getAuswHintergrundBild() const; // gibt das Auswahl Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zAuswHintergrundBild() const;
		__declspec( dllexport ) LRahmen *getMsAuswRahmen( int i ) const; // gibt den Multistyle Auswahl Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zMsAuswRahmen( int i ) const;
		__declspec( dllexport ) int getMsAuswRahmenFarbe( int i ) const; // gibt die Multistyle Auswahl Rahmen Frabe zur�ck
		__declspec( dllexport ) int getMsAuswRahmenBreite( int i ) const; // gibt die Multistyle Auswahl Rahmen Breite zur�ck
		__declspec( dllexport ) AlphaFeld *getMsAuswAlphaFeld( int i ) const; // gibt das Multistyle Auswahl AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zMsAuswAlphaFeld( int i ) const;
		__declspec( dllexport ) int getMsAuswAlphaFeldFarbe( int i ) const; // gibt die Multistyle Auswahl AlphaFeld Farbe zur�ck
		__declspec( dllexport ) int getMsAuswAlphaFeldSt�rke( int i ) const; // gibt die Multistyle Auswahl AlphaFeld st�rke zur�ck
		__declspec( dllexport ) int getMsAuswHintergrundFarbe( int i ) const; // gibt die Multistyle Auswahl Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getMsAuswHintergrundBild( int i ) const; // gibt das Multistyle Auswahl Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zMsAuswHintergrundBild( int i ) const;
		__declspec( dllexport ) LRahmen *getMausRahmen() const; // gibt den Maus Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zMausRahmen() const;
		__declspec( dllexport ) int getMausRahmenFarbe() const; // gibt die Maus Rahmen Frabe zur�ck
		__declspec( dllexport ) int getMausRahmenBreite() const; // gibt die Maus Rahmen Breite zur�ck
		__declspec( dllexport ) AlphaFeld *getMausAlphaFeld() const; // gibt das Maus AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zMausAlphaFeld() const;
		__declspec( dllexport ) int getMausAlphaFeldFarbe() const; // gibt die Maus AlphaFeld Farbe zur�ck
		__declspec( dllexport ) int getMausAlphaFeldSt�rke() const; // gibt die Maus AlphaFeld st�rke zur�ck
		__declspec( dllexport ) int getMausHintergrundFarbe() const; // gibt die Maus Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getMausHintergrundBild() const; // gibt das Maus Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zMausHintergrundBild() const;
		__declspec( dllexport ) LRahmen *getMsMausRahmen( int i ) const; // gibt den Multistyle Maus Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zMsMausRahmen( int i ) const;
		__declspec( dllexport ) int getMsMausRahmenFarbe( int i ) const; // gibt die Multistyle Maus Rahmen Frabe zur�ck
		__declspec( dllexport ) int getMsMausRahmenBreite( int i ) const; // gibt die Multistyle Maus Rahmen Breite zur�ck
		__declspec( dllexport ) AlphaFeld *getMsMausAlphaFeld( int i ) const; // gibt das Multistyle Maus AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zMsMausAlphaFeld( int i ) const;
		__declspec( dllexport ) int getMsMausAlphaFeldFarbe( int i ) const; // gibt die Multistyle Maus AlphaFeld Farbe zur�ck
		__declspec( dllexport ) int getMsMausAlphaFeldSt�rke( int i ) const; // gibt die Multistyle Maus AlphaFeld st�rke zur�ck
		__declspec( dllexport ) int getMsMausHintergrundFarbe( int i ) const; // gibt die Multistyle Maus Hintergrund Farbe zur�ck
		__declspec( dllexport ) Bild *getMsMausHintergrundBild( int i ) const; // gibt das Multistyle Maus Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zMsMausHintergrundBild( int i ) const;
		__declspec( dllexport ) inline bool hatMsStyle( int i, __int64 abStyle ) const; // pr�ft ob Multistyle style vorhanden
		__declspec( dllexport ) inline bool hatMsStyleNicht( int i, __int64 abStyle ) const; // pr�ft ob Multistyle style nicht vorhanden
		__declspec( dllexport ) Zeichnung *dublizieren() const override; // Erzeugt eine Kopie des Zeichnungs
		// Reference Counting
		__declspec( dllexport ) AuswahlBox *getThis();
		__declspec( dllexport ) AuswahlBox *release();
	};
}

#endif