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
        __declspec( dllexport ) void setMsAuswAlphaFeldZ( int i, AlphaFeld *af );
        // Setzt die Farbe eines Farbverlaufs, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  afF: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMsAuswAlphaFeldFarbe( int i, int afF );
        // Setzt die St�rke eines Farbverlaufs, der bei dem Flag MultiStyled bei der Auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        //  afSt: Die St�rke
        __declspec( dllexport ) void setMsAuswAlphaFeldSt�rke( int i, int afSt );
        // Setzt einen Zeiger auf einen Rahmen, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  rahmen: Der Rahmen
        __declspec( dllexport ) void setMausRahmenZ( LRahmen *rahmen );
        // Setzt die Farbe eines Rahmens, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMausRahmenFarbe( int f );
        // Setzt die Breite eines Rahmens, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  rbr: Die Breite des Rahmens in Pixeln
        __declspec( dllexport ) void setMausRahmenBreite( int rbr );
        // Setzt die Hintergrund Farbe, die bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMausHintergrundFarbe( int f );
        // Setzt einen Zeiger auf ein Hintergrund Bild, das bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  bgB: Das Bild
        __declspec( dllexport ) void setMausHintergrundBildZ( Bild *bgB );
        // Setzt ein Hintergrund Bild durch kopieren, das bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  bgB: Das Bild
        __declspec( dllexport ) void setMausHintergrundBild( Bild *bgB );
        // Setzt einen Farbverlauf, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  af: Der Farbverlauf
        __declspec( dllexport ) void setMausAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe eines Farbverlaufs, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  afF: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMausAlphaFeldFarbe( int afF );
        // Setzt die St�rke eines Farbverlaufs, der bei dem Eintrag verwendet wird, auf den die Maus zeigt
        //  afSt: Die St�rke
        __declspec( dllexport ) void setMausAlphaFeldSt�rke( int afSt );
        // Setzt einen Zeiger auf einen Rahmen, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  rahmen: Der Rahmen
        __declspec( dllexport ) void setMsMausRahmenZ( int i, LRahmen *rahmen );
        // Setzt die Farbe eines Rahmes, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMsMausRahmenFarbe( int i, int f );
        // Setzt die Breite eines Rahmes, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  rbr: Die Breite in Pixeln
        __declspec( dllexport ) void setMsMausRahmenBreite( int i, int rbr );
        // Setzt die Hintergrund Farbe, die bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMsMausHintergrundFarbe( int i, int f );
        // Setzt einen Zeiger auf Hintergrund Bild, das bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  bgB: Das Bild
        __declspec( dllexport ) void setMsMausHintergrundBildZ( int i, Bild *bgB );
        // Setzt ein Hintergrund Bild durch kopieren, das bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  bgB: Das Bild
        __declspec( dllexport ) void setMsMausHintergrundBild( int i, Bild *bgB );
        // Setzt einen Zeiger auf einen Farb�bergang, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  af: Der Farbverlauf
        __declspec( dllexport ) void setMsMausAlphaFeldZ( int i, AlphaFeld *af );
        // Setzt die Farbe einens Farb�bergangs, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  afF: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setMsMausAlphaFeldFarbe( int i, int afF );
        // Setzt die St�rke einens Farb�bergangs, der bei dem Flag MultiStyled bei einem bestimmten Eintrag verwendet wird, auf den die Maus zeigt
        //  i: Der Index des Eintrags
        //  afSt: Die St�rke
        __declspec( dllexport ) void setMsMausAlphaFeldSt�rke( int i, int afSt );
        // W�hlt ein Element aus
        //  i: Der Index des Elements
        __declspec( dllexport ) void setAuswahl( int i );
        // Klappt die Liste zum Ausw�hlen aus
        __declspec( dllexport ) void ausklappen();
        // Klappt die Liste zum Ausw�hlen ein
        __declspec( dllexport ) void einklappen();
        // Scrollt in der Liste zu einem bestimmten Eintrag
        //  i: Der Index des Eintrags
        __declspec( dllexport ) void scrollZuEintrag( int i );
        // Setzt die maximale Ausklapp H�he der Liste
        //  maxH�he: Die maximale H�he in Pixeln
        __declspec( dllexport ) void setMaxAuskappH�he( int maxH�he );
        // Setzt die H�he der Eintr�ge
        //  h�he: Die H�he in Pixeln
        __declspec( dllexport ) void setEintragH�he( int h�he );
        // F�gt Styles zu einem bestimmten Eintrag hinzu, falls der Flag MultiStyled gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der Style, der hinzugef�gt werden soll
        __declspec( dllexport ) void addMsStyle( int i, __int64 abStyle );
        // Setzt Styles eines bestimmten Eintrags, falls der Flag MultiStyled gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der Style
        //  add: 1, falls die Styles hinzugef�gt werden sollen und 0, falls sie entfernt werden sollen
        __declspec( dllexport ) void setMsStyle( int i, __int64 abStyle, bool add );
        // Ersetzt die Styles eines bestimmten Eintrags, falls der Flag MultiStyled gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der neue Style
        __declspec( dllexport ) void setMsStyle( int i, __int64 abStyle );
        // Entfernt Styles von einem bestimmten Eintrag, falls der Flag MultiStyled gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der Style, der entfernt werden soll
        __declspec( dllexport ) void l�scheMsStyle( int i, __int64 abStyle );
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
        // Zeichnet das Objekt nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt den Index eines Eintrags zur�ck
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) int getEintragPos( const char *txt ) const;
        // Gibt den Index eines Eintrags zur�ck
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) int getEintragPos( Text *txt ) const;
        // Gibt den Text eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Text *getEintragText( int i ) const;
        // Gibt den Text eines Eintrags ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Text *zEintragText( int i ) const;
        // Gibt einen Eintrag zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) TextFeld *getEintrag( int i ) const;
        // Gibt einen Eintrag ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) TextFeld *zEintrag( int i ) const;
        // Gibt den Index des Ausgew�hlten Eintrags zur�ck
        __declspec( dllexport ) int getAuswahl() const;
        // Gibt die Anzahl der Eintr�ge zur�ck
        __declspec( dllexport ) int getEintragAnzahl() const;
        // Gibt zur�ck, ob die Liste gerade Ausgeklappt ist
        __declspec( dllexport ) bool istAusgeklappt() const;
        // Gibt die maximale H�he der ausgeklappten Liste zur�ck
        __declspec( dllexport ) int getMaxH�he() const;
        // Gibt die H�he eines Eintrags zur�ck
        __declspec( dllexport ) int getEintragH�he() const;
        // Gibt den Knopf zur�ck, der zum aus- und einklappen dr Liste verwendet wird
        __declspec( dllexport ) Knopf *getAusklappKnopf() const;
        // Gibt den Knopf ohne erh�hten Reference Counter zur�ck, der zum aus- und einklappen dr Liste verwendet wird
        __declspec( dllexport ) Knopf *zAusklappKnopf() const;
        // Gibt den Rahmen eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *getEintragRahmen( int i ) const;
        // Gibt den Rahmen eines Eintrags ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *zEintragRahmen( int i ) const;
        // Gibt die Farbe eines Rahmens eines Eintrags im A8R8G8B8 Format zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getEintragRahmenFarbe( int i ) const;
        // Gibt die Breite eines Rahmens eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getEintragRahmenBreite( int i ) const;
        // Gibt den Farb�bergang eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *getEintragAlphaFeld( int i ) const;
        // Gibt den Farb�bergang eines Eintrags ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *zEintragAlphaFeld( int i ) const;
        // Gibt die Farbe eines Farb�bergangs eines Eintrags im A8R8G8B8 Format zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getEintragAlphaFeldFarbe( int i ) const;
        // Gibt die St�rke eines Farb�bergangs eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getEintragAlphaFeldSt�rke( int i ) const;
        // Gibt die Hintergrund Farbe eines Eintrags im A8R8G8B8 Format zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getEintragHintergrundFarbe( int i ) const;
        // Gibt das Hintergrund Bild eines Eintrags zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *getEintragHintergrundBild( int i ) const;
        // Gibt das Hintergrund Bild eines Eintrags ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *zEintragHintergrundBild( int i ) const;
        // Gibt den Rahmen zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) LRahmen *getAuswRahmen() const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) LRahmen *zAuswRahmen() const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) int getAuswRahmenFarbe() const;
        // Gibt die Breite des Rahmens zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) int getAuswRahmenBreite() const;
        // Gibt den Farb�bergang zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) AlphaFeld *getAuswAlphaFeld() const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) AlphaFeld *zAuswAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) int getAuswAlphaFeldFarbe() const;
        // Gibt die St�rke des Farb�bergangs zur�ck, der bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) int getAuswAlphaFeldSt�rke() const;
        // Gibt die Hintergrundfarbe im A8R8G8B8 Format zur�ck, die bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) int getAuswHintergrundFarbe() const;
        // Gibt das Hintergrundbild zur�ck, das bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) Bild *getAuswHintergrundBild() const;
        // Gibt das Hintergrundbild ohne erh�hten Reference Counter zur�ck, das bei der Auswahl eines Eintrags verwendet wird
        __declspec( dllexport ) Bild *zAuswHintergrundBild() const;
        // Gibt den Rahmen zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *getMsAuswRahmen( int i ) const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *zMsAuswRahmen( int i ) const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsAuswRahmenFarbe( int i ) const;
        // Gibt die Breite des Rahmens zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsAuswRahmenBreite( int i ) const;
        // Gibt den Farb�bergang zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *getMsAuswAlphaFeld( int i ) const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *zMsAuswAlphaFeld( int i ) const;
        // Gibt die Farbe des Farb�bergangs im A8R8G8B8 Format zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsAuswAlphaFeldFarbe( int i ) const;
        // Gibt die St�rke des Farb�bergangs zur�ck, der bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsAuswAlphaFeldSt�rke( int i ) const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsAuswHintergrundFarbe( int i ) const;
        // Gibt das Hintergrund Bild zur�ck, das bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *getMsAuswHintergrundBild( int i ) const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das bei dem Flag MultiStyled bei der auswahl eines bestimmten Eintrags verwendet wird
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *zMsAuswHintergrundBild( int i ) const;
        // Gibt den Rahmen zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) LRahmen *getMausRahmen() const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) LRahmen *zMausRahmen() const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) int getMausRahmenFarbe() const;
        // Gibt die Breite des Rahmens zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) int getMausRahmenBreite() const;
        // Gibt den Farb�bergang zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) AlphaFeld *getMausAlphaFeld() const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) AlphaFeld *zMausAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs im A8R8G8B8 Format zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) int getMausAlphaFeldFarbe() const;
        // Gibt die Breite des Farb�bergangs zur�ck, der verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) int getMausAlphaFeldSt�rke() const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) int getMausHintergrundFarbe() const;
        // Gibt das Hintergrund Bild zur�ck, das verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) Bild *getMausHintergrundBild() const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das verwendet wird, wenn die Maus auf einen Eintrag zeigt
        __declspec( dllexport ) Bild *zMausHintergrundBild() const;
        // Gibt den Rahmen zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *getMsMausRahmen( int i ) const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) LRahmen *zMsMausRahmen( int i ) const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsMausRahmenFarbe( int i ) const;
        // Gibt die Breite des Rahmens zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsMausRahmenBreite( int i ) const;
        // Gibt den Farb�bergang zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *getMsMausAlphaFeld( int i ) const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) AlphaFeld *zMsMausAlphaFeld( int i ) const;
        // Gibt die Farbe des Farb�bergangs im A8R8G8B8 Format zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsMausAlphaFeldFarbe( int i ) const;
        // Gibt die St�rke des Farb�bergangs zur�ck, der bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsMausAlphaFeldSt�rke( int i ) const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) int getMsMausHintergrundFarbe( int i ) const;
        // Gibt das Hintergrund Bild zur�ck, das bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *getMsMausHintergrundBild( int i ) const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das bei dem Flag Multistyle verwendet wird, wenn die Maus auf einen bestimmten Eintrag zeigt
        //  i: Der Index des Eintrags
        __declspec( dllexport ) Bild *zMsMausHintergrundBild( int i ) const;
        // Pr�ft, ob bei dem Flag MultiStyled f�r einen Bestimmten Eintrag ein bestimmter Style gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der Style
        __declspec( dllexport ) inline bool hatMsStyle( int i, __int64 abStyle ) const;
        // Pr�ft, ob bei dem Flag MultiStyled f�r einen Bestimmten Eintrag ein bestimmter Style nicht gesetzt wurde
        //  i: Der Index des Eintrags
        //  abStyle: Der Style
        __declspec( dllexport ) inline bool hatMsStyleNicht( int i, __int64 abStyle ) const;
        __declspec( dllexport ) Zeichnung *dublizieren() const override; // Erzeugt eine Kopie des Zeichnungs
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) AuswahlBox *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) AuswahlBox *release();
    };
}

#endif