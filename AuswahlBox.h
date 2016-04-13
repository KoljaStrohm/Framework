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

	class AuswahlBox : public ZeichnungHintergrund
	{
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 FeldRahmen = 0x000001000;
            const static __int64 FeldHintergrund = 0x000002000;
            const static __int64 FeldHBild = 0x000004000;
            const static __int64 FeldHAlpha = 0x000008000;
            const static __int64 FeldBuffer = 0x000010000;
            const static __int64 AuswahlHintergrund = 0x000020000;
            const static __int64 AuswahlHBild = 0x000040000;
            const static __int64 AuswahlHAlpha = 0x000080000;
            const static __int64 AuswahlBuffer = 0x000100000;
            const static __int64 AuswahlRahmen = 0x000200000;
            const static __int64 MultiStyled = 0x000400000;
            const static __int64 MaxH�he = 0x004000000;
            const static __int64 MausHintergrund = 0x008000000;
            const static __int64 MausHBild = 0x010000000;
            const static __int64 MausHAlpha = 0x020000000;
            const static __int64 MausBuffer = 0x040000000;
            const static __int64 MausRahmen = 0x080000000;
            //const int NachObenAusklappen	= 0x100000000;
            //const int AutoAusklappRichtung	= 0x200000000;

            const static __int64 Normal = Sichtbar | Erlaubt | Rahmen | FeldRahmen | AuswahlBuffer | AuswahlRahmen | MaxH�he | VScroll | MausRahmen | MausBuffer;
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
		// nicht constant
		__declspec( dllexport ) void setEventParam( void *p ); // setzt den Event Parameter
		__declspec( dllexport ) void setEventAktion( void( *eAk )( void *p, AuswahlBox *, int, int ) ); // setzt die Event Funktion
		__declspec( dllexport ) void setSchriftZ( Schrift *schrift ); // setzt die schrift
		__declspec( dllexport ) void addEintrag( const char *txt ); // Eintrag hinzuf�gen
		__declspec( dllexport ) void addEintrag( Text *txt );
		__declspec( dllexport ) void addEintragZ( TextFeld *txt );
		__declspec( dllexport ) void setEintrag( int i, const char *txt ); // Eintrag setzen
		__declspec( dllexport ) void setEintrag( int i, Text *txt );
		__declspec( dllexport ) void setEintragZ( int i, TextFeld *txt );
		__declspec( dllexport ) void l�scheEintrag( int i ); // Eintrag entfernen
		__declspec( dllexport ) void setAusklappKnopfZ( Knopf *ausK ); // Ausklapp Knopf setzen
		__declspec( dllexport ) void setEintragRahmenZ( int i, LRahmen *rahmen ); // Eintrag Rahmen setzen
		__declspec( dllexport ) void setEintragRahmenFarbe( int i, int f ); // Eintrag Rahmen Farbe setzen
		__declspec( dllexport ) void setEintragRahmenBreite( int i, int rbr ); // Eintrag Rahmen Breite setzen
		__declspec( dllexport ) void setEintragHintergrundFarbe( int i, int f ); // Eintrag Hintergrund farbe setzen
		__declspec( dllexport ) void setEintragHintergrundBildZ( int i, Bild *bgB ); // Eintrag Hintergrund Bild setzen
		__declspec( dllexport ) void setEintragHintergrundBild( int i, Bild *bgB );
		__declspec( dllexport ) void setEintragAlphaFeldZ( int i, AlphaFeld *af ); // Eintrag AlphaFeld setzen
		__declspec( dllexport ) void setEintragAlphaFeldFarbe( int i, int afF ); // Eintrag AlphaFeld Farbe setzen
		__declspec( dllexport ) void setEintragAlphaFeldSt�rke( int i, int afSt ); // Eintrag AlphaFeld St�rke setzen
		__declspec( dllexport ) void setAuswRahmenZ( LRahmen *rahmen ); // Auswahl Rahmen setzen
		__declspec( dllexport ) void setAuswRahmenFarbe( int f ); // Auswahl Rahmen Farbe setzen
		__declspec( dllexport ) void setAuswRahmenBreite( int rbr ); // Auswahl Rahmen Breite setzen
		__declspec( dllexport ) void setAuswHintergrundFarbe( int f ); // Auswahl Hintergrund Farbe setzen
		__declspec( dllexport ) void setAuswHintergrundBildZ( Bild *bgB ); // Auswahl Hintergrund Bild setzen
		__declspec( dllexport ) void setAuswHintergrundBild( Bild *bgB );
		__declspec( dllexport ) void setAuswAlphaFeldZ( AlphaFeld *af ); // Auswahl AlphaFeld setzen
		__declspec( dllexport ) void setAuswAlphaFeldFarbe( int afF ); // Auswahl AlphaFeld Farbe setzen
		__declspec( dllexport ) void setAuswAlphaFeldSt�rke( int afSt ); // Auswahl Alpha Feld st�rke setzen
		__declspec( dllexport ) void setMsAuswRahmenZ( int i, LRahmen *rahmen ); // Multistyle Auswahl Rahmen setzen
		__declspec( dllexport ) void setMsAuswRahmenFarbe( int i, int f ); // Multistyle Auswahl Rahmen Farbe setzen
		__declspec( dllexport ) void setMsAuswRahmenBreite( int i, int rbr ); // Multistyle Auswahl Breite setzen
		__declspec( dllexport ) void setMsAuswHintergrundFarbe( int i, int f ); // Multistyle Auswahl Hintergrund Farbe setzen
		__declspec( dllexport ) void setMsAuswHintergrundBildZ( int i, Bild *bgB ); // Multistyle Auswahl Hintergrund Bild setzen
		__declspec( dllexport ) void setMsAuswHintergrundBild( int i, Bild *bgB );
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