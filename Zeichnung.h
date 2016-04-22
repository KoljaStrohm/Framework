#ifndef Zeichnung_H
#define Zeichnung_H

#include "Punkt.h"

namespace Framework
{
    struct VScrollData; // Scroll.h
    struct HScrollData; // Scroll.h
    struct MausEreignis; // MausEreignis.h
    struct TastaturEreignis; // TastaturEreignis.h
    class Bild; // Bild.h
    class Zeichnung; // Aus dieser Datei
    class ZeichnungArray; // Aus dieser Datei
    class ToolTip; // ToopTip.h
    class Bildschirm; // Bildschirm.h
    class LRahmen; // Rahmen.h
    class AlphaFeld; // AlphaFeld.h
    class VScrollBar; // Scroll.h
    class HScrollBar; // Scroll.h

    // Eine Zeichnung f�r das 2D GUI Framework
    class Zeichnung
    {
    public:
        class Style
        {
        public:
            const static __int64 Sichtbar = 0x00001; // Wenn dieser Style gesetzt ist, wird die Zeichnung beim Zeichnen angezeigt
            const static __int64 Erlaubt = 0x00002; // Wenn dieser Style gesetzt ist, kann der Benutzer mit der Zeichnung interagieren
            const static __int64 Fokus = 0x00004; // Wenn dieser Style gesetzt ist, werden die Tastatur Ereignisse von der Zeichnung verarbeitet
        };
    protected:
        Punkt pos;
        Punkt gr;
        void *makParam;
        void *takParam;
        bool( *Mak )( void *, void *, MausEreignis );
        bool( *Tak )( void *, void *, TastaturEreignis );
        void *nmakParam;
        void *ntakParam;
        bool( *nMak )( void *, void *, MausEreignis );
        bool( *nTak )( void *, void *, TastaturEreignis );
        bool mausIn;
        CRITICAL_SECTION cs;
        ToolTip *toolTip;
        __int64 style;
        bool rend;

    public:
        // Konstruktor 
        __declspec( dllexport ) Zeichnung();
        // Destruktor 
        __declspec( dllexport ) ~Zeichnung();
        // Legt fest, ob sich die Zeichnung seit des letzten Bildes ver�ndert hat und neu gezeichnet werden muss
        __declspec( dllexport ) void setRender();
        // Setzt den Text, der erscheint, wenn der Benutzer f�r l�ngere Zeit mit der Maus in der Zeichnung verweilt
        //  txt: Der Text, der angezeigt werden soll
        //  zScreen: Ein Zeiger auf das Verwendete Bildschirm Objekt ohne erh�hten Reference Counter
        __declspec( dllexport ) void setToolTipText( const char *txt, Bildschirm *zScreen );
        // Dies ist notwendig, falls mehrere Threads gleichzeitig die Zeichnung benutzen.
        // Wenn lockZeichnung() von zwei threads aufgerufen wird, wartet der letzte so lange, bis der erste unlockZeichnung() aufgerufen hat.
        __declspec( dllexport ) void lockZeichnung();
        // Dies ist notwendig, falls mehrere Threads gleichzeitig die Zeichnung benutzen.
        // Wenn lockZeichnung() von zwei threads aufgerufen wird, wartet der letzte so lange, bis der erste unlockZeichnung() aufgerufen hat.
        __declspec( dllexport ) void unlockZeichnung();
        // setzt den Parameter, der bei einem Maus Ereignis an die R�ckruffunktion �bergeben wird
        //  p: Der Parameter
        __declspec( dllexport ) void setMausEreignisParameter( void *p );
        // Setzt den Parameter, der bei einem Tastatur Ereignis an die R�ckruffunktion �bergeben wird
        //  p: Der Parameter
        __declspec( dllexport ) void setTastaturEreignisParameter( void *p );
        // Setzt die R�ckruffunktion, die bei einem Maus Ereignis aufgerufen werden soll.
        // Wenn die R�ckruffunktion 0 zur�ckgiebt, oder nicht gesetzt wurde, wird ein Maus Ereignis von der Zeichnung nicht weiter beachtet
        // Es kann die Standartfunktion __ret1ME verwendet werden, die in MausEreignis.h definiert ist und immer 1 zur�ckgibt
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setMausEreignis( bool( *ak )( void *, void *, MausEreignis ) );
        // Setzt die R�ckruffunktion, die bei einem Tastatur Ereignis aufgerufen werdne soll.
        // Wenn die R�ckruffunktion 0 zur�ckgiebt, oder nicht gesetzt wurde, wird ein Tastatur Ereignis von der Zeichnung nicht weiter beachtet
        // Es kann die Standartfunktion __ret1TE verwendet werden, die in TastaturEreignis.h definiert ist und immer 1 zur�ckgibt
        // Weitere Standartfunktionen sind _nurNummernTE und _nurHexTE ebenfals aus TastaturEreignis.h
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setTastaturEreignis( bool( *ak )( void *, void *, TastaturEreignis ) );
        // setzt den Parameter, der bei einem Maus Ereignis an die R�ckruffunktion �bergeben wird, die aufgerufen wird, fals das Ereignis von der Zeichnung verarbeitet wurde
        //  p: Der Parameter
        __declspec( dllexport ) void setNMausEreignisParameter( void *p );
        // Setzt den Parameter, der bei einem Tastatur Ereignis an die R�ckruffunktion �bergeben wird, die aufgerufen wird, fals das Ereignis von der Zeichnung verarbeitet wurde
        //  p: Der Parameter
        __declspec( dllexport ) void setNTastaturEreignisParameter( void *p );
        // Setzt die R�ckruffunktion, die bei einem Maus Ereignis aufgerufen werden soll, nachdem das Ereignis bereits von der Zeichnung verarbeitet wurde
        // Wenn die R�ckruffunktion 1 zur�ckgiebt, oder nicht gesetzt wurde, wird das Maus Ereignis von keiner weiteren Zeichnung verarbeitet, die zum Beispiel hinter dieser Zeichnung liegen
        // Es kann die Standartfunktion __ret1ME verwendet werden, die in MausEreignis.h definiert ist und immer 1 zur�ckgibt
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setNMausEreignis( bool( *ak )( void *, void *, MausEreignis ) );
        // Setzt die R�ckruffunktion, die bei einem Tastatur Ereignis aufgerufen werdne soll, nachdem das Ereignis bereits von der Zeichnung verarbeitet wurde
        // Wenn die R�ckruffunktion 1 zur�ckgiebt, oder nicht gesetzt wurde, wird das Tastatur Ereignis von keiner weiteren Zeichnung verarbeitet
        // Es kann die Standartfunktion __ret1TE verwendet werden, die in TastaturEreignis.h definiert ist und immer 1 zur�ckgibt
        // Weitere Standartfunktionen sind _nurNummernTE und _nurHexTE ebenfals aus TastaturEreignis.h
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setNTastaturEreignis( bool( *ak )( void *, void *, TastaturEreignis ) );
        // Verarbeitet ein Maus Ereignis. Wird vom Framework automatisch aufgerufen.
        //  me: Das Ereignis
        __declspec( dllexport ) virtual void doMausEreignis( MausEreignis &me );
        // Verarbeitet ein Tastatur Ereignis. Wird vom Framework automatisch aufgerufen
        //  te: Das Ereignis
        __declspec( dllexport ) virtual void doTastaturEreignis( TastaturEreignis &te );
        // Verarbeitet die Zeit, die seit dem letzten aufruf dieser Funktion vergangen ist
        //  tickVal: Die vergangene Zeit in Sekunden
        __declspec( dllexport ) virtual bool tick( double tickval );
        // Setzt die Position der Zeichnung
        //  pos: Die Position in Pixeln
        __declspec( dllexport ) void setPosition( const Punkt &pos );
        // Setzt die X Position der Zeichnung
        //  xPos: Die Position in Pixeln
        __declspec( dllexport ) void setX( int xPos );
        // Setzt die Y Position der Zeichnung
        //  yPos: Die Position in Pixeln
        __declspec( dllexport ) void setY( int yPos );
        // Setzt die Gr��e der Zeichnung
        //  gr: Ein Punkt mit x als Breite und y als H�he in Pixeln
        __declspec( dllexport ) void setGr��e( const Punkt &gr );
        // Setzt die Position der Zeichnung
        //  x: Die X Position in Pixeln
        //  y: Die Y Position in Pixeln
        __declspec( dllexport ) void setPosition( int x, int y );
        // Setzt die Gr��e der Zeichnung
        //  br: Die Breite in Pixeln
        //  h�: Die H�he in Pixeln
        __declspec( dllexport ) void setGr��e( int br, int h� );
        // Setzt den Style der Zeichnung
        //  style: Der neue Style bestehend aus den Flags aus der zugeh�rigen Style Klasse
        __declspec( dllexport ) void setStyle( __int64 style );
        // Setzt den Style der Zeichnung
        //  style: Alle Style Flags, die ver�ndert werden sollen
        //  add_l�schen: 1, falls der Style hinzugef�gt werden soll. 0, falls der Style entfernt weden soll
        __declspec( dllexport ) void setStyle( __int64 style, bool add_l�schen );
        // F�gt Style Flags hinzu
        //  style: Der Style, der hinzugef�gt werden soll
        __declspec( dllexport ) void addStyle( __int64 style );
        // Entfernt Style Flags
        //  style: Der Style, der entfernt werden soll
        __declspec( dllexport ) void l�scheStyle( __int64 style );
        // Zeichnet die Zeihnung in ein bestimmtes Bild
        //  zRObj: Das Bild, in das gezeichnet werden soll
        __declspec( dllexport ) virtual void render( Bild &zRObj );
        // Gibt zur�ck, ob eine R�ckruffunktion f�r Maus Ereignisse gesetzt wurde
        __declspec( dllexport ) bool hatMausEreignis() const;
        // Gibt zur�ck, ob eine R�ckruffunktion f�r Tastatur Ereignisse gesetzt wurde
        __declspec( dllexport ) bool hatTastaturEreignis() const;
        // Gibt die Position der Zeichnung in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getPosition() const;
        // Gibt die Gr��e der Zeichnung in Pixeln zur�ck. x f�r Breite und y f�r H�he
        __declspec( dllexport ) const Punkt &getGr��e() const;
        // Gibt die Breite der Zeichnung in Pixeln zur�ck
        __declspec( dllexport ) int getBreite() const;
        // Gibt die H�he der Zeichnung in Pixeln zur�ck
        __declspec( dllexport ) int getH�he() const;
        // Gibt die X Position der Zeichnung in Pixeln zur�ck
        __declspec( dllexport ) int getX() const;
        // Gibt die Y Position der Zeichnung in Pixeln zur�ck
        __declspec( dllexport ) int getY() const;
        // Gibt einen Zeiger auf das Tooltip Objekt zur�ck, walls es verwendet wird
        __declspec( dllexport ) ToolTip *getToolTip() const;
        // Gibt einen Zeiger auf das Tooltip Objekt ohne erh�hten Reference Counter zur�ck, walls es verwendet wird
        __declspec( dllexport ) ToolTip *zToolTip() const;
        // Gibt zur�ck, ob bestimmte Styles gesetzt wurden
        //  style: Die Styles, die �berpr�ft werden sollen
        //  return: 1, falls alle Styles in style gesetzt wurden
        __declspec( dllexport ) inline bool hatStyle( __int64 style ) const;
        // Gibt zur�ck, ob bestimmte Styles nicht gesetzt wurden
        //  style: Die Styles, die gepr�ft werden sollen
        //  return: 1, falls alle Styles in style nicht gesetzt wurden
        __declspec( dllexport ) inline bool hatStyleNicht( __int64 style ) const;
        // Kopiert die Komplette Zeichnung, so dass sie ohne Effekt auf das Original ver�ndert werden kann
        __declspec( dllexport ) virtual Zeichnung *dublizieren() const;
    };

    // Ein Array von Zeichnungen, der von den Bildschirm Klassen verwendet wird, um die Objekte der GUI zu speichern
    class ZeichnungArray// Array von Zeichnungen
    {
    private:
        Zeichnung *This;
        ZeichnungArray *next;
        int index;

    public:
        // Konstruktor 
        __declspec( dllexport ) ZeichnungArray();
        // Destruktor 
        __declspec( dllexport ) ~ZeichnungArray();
        // F�gt dem Array eine Zeichnung hinzu. Es kann jede Zeichnung nur einmal hinzugef�gt werden
        //  obj: Die neue Zeichnung
        //  return: 1, falls die Zeichnung erfolgreich hinzugef�gt wurde.
        __declspec( dllexport ) bool addZeichnung( Zeichnung *obj );
        // Entfernt eine Zeichnung
        //  obj: Die Zeichnung, die entfernt werden soll
        //  return 1, falls die Zeichnung erfolgreich entfernt wurde
        __declspec( dllexport ) bool removeZeichnung( Zeichnung *obj );
        // Entfernt eine Zeichnung
        //  i: Der Index der Zeichnung, die entfernt werden soll
        //  return 1, falls die Zeichnung erfolgreich entfernt wurde
        __declspec( dllexport ) bool removeZeichnung( int i );
        // Setzt den Zeiger auf das N�chste Array Element auf 0
        __declspec( dllexport ) void setNext0();
        // Aktualisiert die Array indizes.
        //  i: Der Index des ersten Elements
        __declspec( dllexport ) void updateIndex( int i );
        // Gibt den Zeiger auf das nchste Array Element zur�ck
        __declspec( dllexport ) ZeichnungArray *getNext() const;
        // Gibt eine Zeichnung zur�ck
        //  i: Der Index der Zeichnung
        __declspec( dllexport ) Zeichnung *getZeichnung( int i ) const;
        // Gibt die Zeichnung dieses Array Elements zur�ck
        __declspec( dllexport ) Zeichnung *getZeichnung() const;
        // Gibt den Index dieses Array Elements zur�ck
        __declspec( dllexport ) int getIndex() const;
        // Sendet an alle Zeichnungen ein Maus Ereignis. Die zuletzt hinzugef�gte Zeichnung bekommt das Ereignis als Erste
        //  me: Das Ereignis
        __declspec( dllexport ) void sendMausAll( MausEreignis &me ) const;
        // Sendet an alle Zeichnungen ein Tastatur Ereignis. Die zuletzt hinzugef�gte Zeichnung bekommt das Ereignis als Erste
        //  te: Das Ereignis
        __declspec( dllexport ) void sendTastaturAll( TastaturEreignis &te ) const;
        // Zeichnet alle Zeichnungen. Die zuletzt hinzugef�gte Zeichnung ist oben
        //  zRObj: Das Bild, in das alle Zeichnungen gezeichnet werden sollen
        __declspec( dllexport ) void render( Bild &zRObj );
        // Verarbeitet bei allen Zeichnungen die Vergangene Zeit seit dem letzten Aufruf der Funktion
        //  tickVal: Die vergangene Zeit in Sekunden
        __declspec( dllexport ) bool tick( double tickval );
    };

    // Eine Zeichnung f�r das 2D GUI Framework mit Hintergrund, Rahmen und Scroll Balken
    class ZeichnungHintergrund : public Zeichnung
    {
    public:
        class Style : public Zeichnung::Style
        {
        public:
            const static __int64 Rahmen = 0x00010; // Wenn dieser Flag gesetzt wird, bekommt die Zeichnugn einen Rahmen
            const static __int64 Hintergrund = 0x00020; // Wenn dieser Flag gesetzt wird, bekommt die Zeichnung einen Hintergrund
            const static __int64 HAlpha = 0x00040; // Wenn dieser Flag gesetzt wird, wird der Hintergrund durchsichtig. Ben�tigt Flag Hintergrund
            const static __int64 HBild = 0x00080; // Wenn dieser Flag gesetzt wird, wird ein Bild als hintergrund verwendet. Ben�tigt Flag Hintergrund
            const static __int64 Buffered = 0x00100; // Wenn dieser Flag gesetzt wird, Erscheint ein Farb�bergang als Rahmen
            const static __int64 VScroll = 0x00200; // Wenn dieser Flag gesetzt wird, erscheint eine Scrollbar am rechten Rand
            const static __int64 HScroll = 0x00400; // Wenn dieser Flag gesetzt wird, erscheint eine Scrollbar am unteren Rand
        };

    protected:
        int hintergrundFarbe;
        LRahmen *rahmen;
        Bild *hintergrundBild;
        AlphaFeld *hintergrundFeld;
        VScrollBar *vertikalScrollBar;
        HScrollBar *horizontalScrollBar;
        Punkt innenPosition;
        Punkt innenGr��e;

    public:
        // Konstruktor 
        __declspec( dllexport ) ZeichnungHintergrund();
        // Destruktor 
        __declspec( dllexport ) ~ZeichnungHintergrund();
        // Setzt das Hintergrund Bild (ben�tigt Flag zum Zeichnen: Hintergrund, HBild)
        //  bild: Das Bild wird kopiert und als Hintergrundbild verwendet
        __declspec( dllexport ) void setHintergrundBild( Bild *bild );
        // Setzt einen Zeiger auf das Hintergrund Bild (ben�tigt Flag zum Zeichnen: Hintergrund)
        //  bild: Das Bild wid ohne es zu kopieren verwendet
        __declspec( dllexport ) void setHintergrundBildZ( Bild *bild );
        // Setzt die Hintergrund Farbe (ben�tigt Flag zum Zeichnen: Hintergrund)
        //  fc: Die Hintergrundfarbe im A8R8G8B8 Format
        __declspec( dllexport ) void setHintergrundFarbe( int fc );
        // Setzt einen Zeiger auf das AlphaFeld (ben�tigt Flag zum Zeichnen: Buffered)
        //  buff: Das AlphaFeld, das �ber den Hintergrund gezeichnet werden soll
        __declspec( dllexport ) void setAlphaFeldZ( AlphaFeld *buff );
        // Setzt die St�rke des AlphaFeldes (ben�tigt Flag zum Zeichnen: Buffered)
        //  st: Die St�rke des AlphaFeldes, welches �ber dem Hintergrund gezeichnet werden soll
        __declspec( dllexport ) void setAlphaFeldSt�rke( int st );
        // Setzt die Farbe des AlphaFeldes (ben�tigt Flag zum Zeichnen: Buffered)
        //  fc: Die Farbe des AlphaFeldes, welches �ber dem Hintergrund gezeichnet werden soll
        __declspec( dllexport ) void setAlphaFeldFarbe( int fc );
        // Setzt einen Zeiger zu dem Linien Rahmen, der um das TextFeld gezeichnet werden soll (ben�tigt Flag zum Zeichnen: Rahmen)
        //  ram: Der Rahmen
        __declspec( dllexport ) void setLinienRahmenZ( LRahmen *ram );
        // Setzt die Breite des Linien Rahmens (ben�tigt Flag zum Zeichnen: Rahmen)
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setLinienRahmenBreite( int br );
        // Setzt die Farbe des Linien Rahmens (ben�tigt Flag zum Zeichnen: Rahmen)
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setLinienRahmenFarbe( int fc );
        // Setzt die Scrollgeschwindigkeit der vertikalen ScrollBar (ben�tigt Flag zum Zeichnen: VScroll)
        //  ks: Die Scrollgeschwindigkeit in Pixeln f�r jeden Maus Klick
        __declspec( dllexport ) void setVertikalKlickScroll( int ks );
        // Scrollt an eine Bestimmte Stelle bei der vertikalen ScrollBar (ben�tigt Flag zum Zeichnen: VScroll)
        //  pos: Das Scroll Offset in Pixeln.
        __declspec( dllexport ) void setVertikalScrollPos( int pos );
        // Setzt die Farbe der vertikalen ScrollBar (ben�tigt Flag zum Zeichnen: VScroll)
        //  f: Die Fordergrundfarbe der ScrollBar im A8R8G8B8 Format
        //  bgF: Die Hintergrundfarbe der ScrollBar im A8R8G8B8 Format
        __declspec( dllexport ) void setVertikalScrollFarbe( int f, int bgF );
        // Setzt die Scrollgeschwindigkeit der horizontalen ScrollBar (ben�tigt Flag zum Zeichnen: HScroll)
        //  ks: Die Scrollgeschwindigkeit in Pixeln f�r jeden Maus Klick
        __declspec( dllexport ) void setHorizontalKlickScroll( int ks );
        // Scrollt an eine Bestimmte Stelle bei der horizontalen ScrollBar (ben�tigt Flag zum Zeichnen: HScroll)
        //  pos: Das Scroll Offset in Pixeln.
        __declspec( dllexport ) void setHorizontalScrollPos( int pos );
        // Setzt die Farbe der horizontalen ScrollBar (ben�tigt Flag zum Zeichnen: HScroll)
        //  f: Die Fordergrundfarbe der ScrollBar im A8R8G8B8 Format
        //  bgF: Die Hintergrundfarbe der ScrollBar im A8R8G8B8 Format
        __declspec( dllexport ) void setHorizontalScrollFarbe( int f, int bgF );
        // Updated den Zeichenhintergrund
        //  tickVal: Die vergangene Zeit in Sekunden, die seit dem Letzten Aufruf dieser Funktion verstrichen ist
        //  return: 1, wenn das Bild neu gezeichnet werden muss. 0 sonnst
        __declspec( dllexport ) bool tick( double tickVal ) override;
        // Zeichnet den Hintergrund eines Zeichnunges nach rObj
        __declspec( dllexport ) void render( Bild &rObj ) override;

        // Gibt das Hintergrundbild zur�ck.
        //  return: 0, falls kein Hintergrundbild verwendet wird
        __declspec( dllexport ) Bild *getHintergrundBild() const;
        // Gibt das Hintergrundbild ohne erh�hten reference Counter zur�ck.
        //  return: 0, falls kein Hintergrundbild verwendet wird
        __declspec( dllexport ) Bild *zHintergrundBild() const;
        // Gibt die Hintergrundfarbe im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getHintergrundFarbe() const;
        // Gibt das AlphaFeld zur�ck, das �ber den Hintergrund gezeichnet wird.
        //  return: 0, falls das AlphaFeld nicht definiert wurde
        __declspec( dllexport ) AlphaFeld *getAlphaFeld() const;
        // Gibt das AlphaFeld ohne erh�hten Reference Counter zur�ck, das �ber den Hintergrund gezeichnet wird.
        //  return: 0, falls das AlphaFeld nicht definiert wurde
        __declspec( dllexport ) AlphaFeld *zAlphaFeld() const;
        // Git die St�rke des Alphafeldes zur�ck
        __declspec( dllexport ) int getAlphaFeldSt�rke() const;
        // Gibt die Farbe des Alphafedes im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getAlphaFeldFarbe() const;
        // Gibt den Rahmen zur�ck
        //  return: 0, falls kein Rahmen definiert wurde
        __declspec( dllexport ) LRahmen *getLinienRahmen() const;
        // Gibt den Rahmen ohne erh�hten Reference Counter zur�ck
        //  return: 0, falls kein Rahmen definiert wurde
        __declspec( dllexport ) LRahmen *zLinienRahmen() const;
        // Gibt die Breite des Rahmens in Pixeln zur�ck
        __declspec( dllexport ) int getLinienRahmenBreite() const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getLinienRahmenFarbe() const;
        // Gibt die Scroll geschwindigkeit der vertikalen Scroll Bar zur�ck
        __declspec( dllexport ) int getVertikalKlickScroll() const;
        // Gibt die Scroll Position der vertikalen Scroll Bar zur�ck
        __declspec( dllexport ) int getVertikalScrollPos() const;
        // Gibt die Farbe der vertikalen Scroll Bar im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getVertikalScrollFarbe() const;
        // Gibt die Hintergrundfarbe der vertikalen Scroll Bar im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getVertikalScrollHintergrund() const;
        // Gibt die Scroll geschwindigkeit der horizontalen Scroll Bar zur�ck
        __declspec( dllexport ) int getHorizontalKlickScroll() const;
        // Gibt die Scroll Position der horizontalen Scroll Bar zur�ck
        __declspec( dllexport ) int getHorizontalScrollPos() const;
        // Gibt die Farbe der horizontalen Scroll Bar im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getHorizontalScrollFarbe() const;
        // Gibt die Hintergrundfarbe der horizontalen Scroll Bar im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getHorizontalScrollHintergrund() const;
        // Erzeugt eine Kopie der Zeichnung, die ohne Auswirkungen auf das Original ver�ndert werden kann
        __declspec( dllexport ) virtual Zeichnung *dublizieren() const;
    };
}

#endif