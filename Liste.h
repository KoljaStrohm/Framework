#ifndef Liste_H
#define Liste_H

#include "Zeichnung.h"
#include "Array.h"

namespace Framework
{
    class LRahmen; // Rahmen.h
    class AlphaFeld; // AlphaFeld.h
    class Bild; // Bild.h
    class Text; // Text.h
    class TextFeld; // TextFeld.h
    class VScrollBar; // Scroll.h
    struct TastaturEreignis; // TastaturEreignis.h
    struct MausEreignis; // MausEreignis.h
    class Schrift; // Schrift.h
    class AuswahlListe; // aus dieser datei

    // Eine Zeichnung des 2D GUI Frameworks, die eine Liste darstellt, aus der der Benutzer Elemente aus und abw�hlen kann
    class AuswahlListe : public ZeichnungHintergrund
    {
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 FeldRahmen = 0x0001000; // Legt fest, ob die Eintr�ge der Liste einen Rahmen haben
            const static __int64 FeldHintergrund = 0x0002000; // Legt fest, ob die Eintr�ge einen Hintergrund haben
            const static __int64 FeldHBild = 0x0004000; // Legt fest, ob die Eintr�ge ein Hintergrund Bild haben
            const static __int64 FeldHAlpha = 0x0008000; // Legt fest, ob beim zeichnen der Eintrag Hintergr�nde alpha blending verwendet werden soll
            const static __int64 FeldBuffer = 0x0010000; // Legt fest, ob die Eintr�ge einen Farb�bergang besitzen
            const static __int64 AuswahlHintergrund = 0x0020000; // Legt fest, ob die ausgew�hlten Eintr�ge einen Hintergrund haben
            const static __int64 AuswahlHBild = 0x0040000; // Legt fest, ob die ausgew�hlten eintr�ge ein Bild als Hintergrund haben
            const static __int64 AuswahlHAlpha = 0x0080000; // Legt fest, ob f�r das Zeichnen der Hintergr�nde der ausgew�hlten Eintr�ge alpha blending verwendet wird
            const static __int64 AuswahlBuffer = 0x0100000; // Legt fest, ob die ausgew�hlten Eintr�ge einen Farb�bergang besitzen
            const static __int64 AuswahlRahmen = 0x0200000; // Legt fest, ob die ausgew�hlten Eintr�ge einen Rahmen besitzen
            const static __int64 MultiStyled = 0x0400000; // Legt fest, ob jeder Eintrag seine eigenen Hintergrund, Farb�bergang und Rahmen hat, fals er ausgew�hlt ist
            const static __int64 MultiSelect = 0x0800000; // Legt fest, das mehrere Eintr�ge gleichzeitig ausgew�hlt sein k�nnen
            const static __int64 Ausgew�hlt = 0x1000000; // Legt fest, ob ein bestimmter Eintrag ausgew�hlt ist, falls MultiSelect gesetzt wurde.

            const static __int64 Normal = Sichtbar | Erlaubt | Rahmen | FeldHAlpha | FeldHintergrund | FeldRahmen | AuswahlBuffer | AuswahlRahmen; // Vereint die Flags Sichtbar, Erlaubt, Rahmen, FeldHAlpha, FeldHintergrund, FeldRahmen, AuswahlBuffer, AuswahlRahmen
        };
    private:
        RCArray< TextFeld > *tfListe;
        int eintr�ge, auswahl;
        int ahFarbe;
        Bild *ahBild;
        AlphaFeld *aBuffer;
        LRahmen *aRahmen;
        Array< __int64 > *styles;
        Array< int > *ahFarbeListe;
        RCArray< Bild > *ahBildListe;
        RCArray< AlphaFeld > *aBufferListe;
        RCArray< LRahmen > *aRahmenListe;
        Schrift *schrift;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) AuswahlListe();
        // Destruktor 
        __declspec( dllexport ) ~AuswahlListe();
        // Aktualisiert die Styles, gr��e und Position der Eintr�ge
        __declspec( dllexport ) void update();
        // F�gt einen Eintrag hinzu
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) void addEintrag( Text *txt );
        // F�gt einen Eintrag hinzu
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) void addEintrag( const char *txt );
        // F�gt einen zeiger auf einen Eintrag hinzu
        //  tf: Das TextFeld, mit dem der Eintrag gezeichnet wird
        __declspec( dllexport ) void addEintragZ( TextFeld *tf );
        // F�gt einen Eintrag an einer bestimmten Position hinzu
        //  pos: Der Index des neuen Eintrags
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) void addEintrag( int pos, Text *txt );
        // F�gt einen Eintrag an einer bestimmten Position hinzu
        //  pos: Der Index des neuen Eintrags
        //  txt: Der Text des Eintrags
        __declspec( dllexport ) void addEintrag( int pos, const char *txt );
        // F�gt einen zeiger auf einen Eintrag an einer bestimmten Position hinzu
        //  pos: Der Index des neuen Eintrags
        //  tf: Das TextFeld, mit dem der Eintrag gezeichnet wird
        __declspec( dllexport ) void addEintragZ( int pos, TextFeld *tf );
        // �ndert einen Eintrag
        //  pos: Der Index des Eintrags
        //  txt: Der neue Text des Eintrags
        __declspec( dllexport ) void setEintrag( int pos, Text *txt );
        // �ndert einen Eintrag
        //  pos: Der Index des Eintrags
        //  txt: Der neue Text des Eintrags
        __declspec( dllexport ) void setEintrag( int pos, unsigned char *txt );
        // �ndert den Zeiger eines Eintrags
        //  pos: Der Index des Eintrags
        //  tf: Der neue Eintrag
        __declspec( dllexport ) void setEintragZ( int pos, TextFeld *tf );
        // Vertauscht die Positionen zweier Eintr�ge
        //  vpos: Der Index des ersten Eintrags
        //  npos: Der Index des zweiten Eintrags
        __declspec( dllexport ) void tauschEintragPos( int vpos, int npos );
        // L�scht einen Eintrag
        // pos: Der Index des Eintrags
        __declspec( dllexport ) void l�scheEintrag( int pos );
        // Setzt die verwendete Schrift
        //  schrift: Die Schrift
        __declspec( dllexport ) void setSchriftZ( Schrift *schrift );
        // Scrollt zu einem bestimmen Eintrag
        //  eintrag: Der Index des Eintrags
        __declspec( dllexport ) void setVScrollZuEintrag( int eintrag );
        // Aktualisiert die maximale Scroll H�he indem die H�he aller Eintr�ge addiert wird
        __declspec( dllexport ) void updateVScroll();
        // Setzt den Zeiger auf den Rahmen, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  rahmen: Der Rahmen
        __declspec( dllexport ) void setALRZ( LRahmen *rahmen );
        // Setzt die Breite des Rahmens, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setALRBreite( int br );
        // Setzt die Farbe des Rahmens, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setALRFarbe( int fc );
        // Setzt den Zeiger auf den Farb�bergnag, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  buffer: Der Farb�bergang
        __declspec( dllexport ) void setAAFZ( AlphaFeld *buffer );
        // Setzt die St�rke des Farb�bergnags, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  st: Die St�rke
        __declspec( dllexport ) void setAAFSt�rke( int st );
        // Setzt die Farbe des Farb�bergnags, der bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setAAFFarbe( int fc );
        // Setzt das Hintergrund Bild durch kopieren, das bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  bild: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setAHBild( Bild *bild );
        // Setzt einen Zeiger auf das Hintergrund Bild, das bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  bild: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setAHBildZ( Bild *bild );
        // Setzt die Hintergrund Farbe, die bei ausgew�hlten Eintr�gen verwendet wird, fals MulitStyled nicht gesetzt wurde
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setAHFarbe( int fc );
        // Setzt den Zeiger auf den Rahmen, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  rahmen: Der Rahmen
        __declspec( dllexport ) void setALRZ( int pos, LRahmen *rahmen );
        // Setzt die Breite des Rahmens, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setALRBreite( int pos, int br );
        // Setzt die Farbe des Rahmens, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setALRFarbe( int pos, int fc );
        // Setzt den Zeiger auf den Farb�bergnag, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  buffer: Der Farb�bergang
        __declspec( dllexport ) void setAAFZ( int pos, AlphaFeld *buffer );
        // Setzt die St�rke des Farb�bergnags, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  st: Die St�rke
        __declspec( dllexport ) void setAAFSt�rke( int pos, int st );
        // Setzt die Farbe des Farb�bergnags, der bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setAAFFarbe( int pos, int fc );
        // Setzt das Hintergrund Bild durch kopieren, das bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  bild: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setAHBild( int pos, Bild *bild );
        // Setzt einen Zeiger auf das Hintergrund Bild, das bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  bild: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setAHBildZ( int pos, Bild *bild );
        // Setzt die Hintergrund Farbe, die bei einem ausgew�hlten Eintrag verwendet wird, fals MulitStyled gesetzt wurde
        //  pos: Der Index des Eintrags
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setAHFarbe( int pos, int fc );
        // Setzt den Style eines Eintrags, falls MulitStyled gesetzt wurde und legt fest, ob ein Eintrag ausgew�hlt ist, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Der neue Style
        __declspec( dllexport ) void setMsStyle( int pos, __int64 style );
        // �ndert den Style eines Eintrags, falls MulitStyled gesetzt wurde und legt fest, ob ein Eintrag ausgew�hlt ist, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Der Style
        //  add_l�schen: 1, falls der Style hinzugef�gt werden soll. 0, falls der Style entfernt weden soll
        __declspec( dllexport ) void setMsStyle( int pos, __int64 style, bool add_l�schen );
        // F�gt Styles zu einem Eintrag hinzu, falls MulitStyled gesetzt wurde und legt fest, ob ein Eintrag ausgew�hlt ist, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Der Style, der hinzugef�gt werden soll
        __declspec( dllexport ) void addMsStyle( int pos, __int64 style );
        // Entfernt Styles von einem Eintrag, falls MulitStyled gesetzt wurde und legt fest, ob ein Eintrag ausgew�hlt ist, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Der Style, der entfernt werden soll
        __declspec( dllexport ) void l�scheMsStyle( int pos, __int64 style );
        // Verarbeitet Tastatur Nachrichten
        //  me: Das Ereignis, was durch die Tastatureingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Verarbeitet ein Tastatur Ereignis. Wird vom Framework automatisch aufgerufen
        //  te: Das Ereignis
        __declspec( dllexport ) void doTastaturEreignis( TastaturEreignis &te ) override;
        // Zeichnet das Objekt nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt den Index eines Eintrags zur�ck, auf den die Maus zeigt
        //  my: Die Position der Maus auf der Y Achse basierend auf dem oberend Rand der Liste
        __declspec( dllexport ) int getKlickEintrag( int my );
        // W�hlt einen Eintrag aus
        //  ausw: Der Index des Eintrags
        __declspec( dllexport ) void setAuswahl( int ausw );
        // W�hlt alle ausgew�hlten Eintr�ge ab
        __declspec( dllexport ) void deSelect();
        // Gibt die Anzahl an Eintr�gen zur�ck
        __declspec( dllexport ) int getEintragAnzahl() const;
        // Gibt den Index des ausgew�hlten Eintrags zur�ck, fals MultiSelect nicht gesetzt ist. Wenn MultiSelect gesetzt wurde, kann die Auswahl eines Eintrags mit hatMsStyle( Eintrag Index, AuswahlListe::Style::Ausgew�hlt ) gepr�ft werden
        __declspec( dllexport ) int getAuswahl() const;
        // Gibt den Index eines Eintrags zur�ck
        //  eintragText: Der Text des Eintrags
        __declspec( dllexport ) int getEintragPos( Text *eintragText );
        // Gibt einen Eintrag zur�ck
        //  pos: Der Index des Eintrags
        __declspec( dllexport ) TextFeld *getEintrag( int pos ) const;
        // Gibt einen Eintrag ohne erh�hten reference Counter zur�ck
        //  pos: Der Index des Eintrags
        __declspec( dllexport ) TextFeld *zEintrag( int pos ) const;
        // Gibt den Rahmen zur�ck, der f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) LRahmen *getARahmen() const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) LRahmen *zARahmen() const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) int getAHFarbe() const;
        // Gibt das Hintergrund Bild zur�ck, das f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) Bild *getAHBild() const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) Bild *zAHBild() const;
        // Gibt den Farbverlauf zur�ck, der f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) AlphaFeld *getABuffer() const;
        // Gibt den Farbverlauf ohne erh�hten Reference Counter zur�ck, der f�r ausgew�hlte Eintr�ge verwendet wird, falls MultiStyled nicht gesetzt wurde
        __declspec( dllexport ) AlphaFeld *zABuffer() const;
        // Gibt den Rahmen zur�ck, der f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) LRahmen *getARahmen( int pos ) const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck, der f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) LRahmen *zARahmen( int pos ) const;
        // Gibt die Hintegrrund Farbe im A8R8G8B8 Format zur�ck, die f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) int getAHFarbe( int pos ) const;
        // Gibt das Hintergrund Bild zur�ck, das f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) Bild *getAHBild( int pos ) const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) Bild *zAHBild( int pos ) const;
        // Gibt den Farb�bergang zur�ck, der f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) AlphaFeld *getABuffer( int pos ) const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der f�r einen ausgew�hlten Eintrag verwendet wird, falls MultiStyled gesetzt wurde
        __declspec( dllexport ) AlphaFeld *zABuffer( int pos ) const;
        // �berpr�ft, ob f�r einen Bestimmten Eintarg betimmte Styles gesetzt wurden, falls MultiStyled gesetzt wurde. �berpr�ft auch, ob ein Eintrag ausgew�hlt wurde, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Die zu pr�fenden Styles
        __declspec( dllexport ) inline bool hatMsStyle( int pos, __int64 style ) const;
        // �berpr�ft, ob f�r einen Bestimmten Eintarg betimmte Styles nicht gesetzt wurden, falls MultiStyled gesetzt wurde. �berpr�ft auch, ob ein Eintrag nicht ausgew�hlt wurde, falls MultiSelect gesetzt wurde
        //  pos: Der Index des Eintrags
        //  style: Die zu pr�fenden Styles
        __declspec( dllexport ) inline bool hatMsStyleNicht( int pos, __int64 style ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) AuswahlListe *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) AuswahlListe *release();
    };
}

#endif