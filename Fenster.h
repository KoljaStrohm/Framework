#ifndef Fenster_H
#define Fenster_H

#include "Zeichnung.h"

namespace Framework
{
    class VScrollBar; // Scroll.h
    class HScrollBar; // Scroll.h
    class TextFeld; // TextFeld.h
    class LRahmen; // Rahmen.h
    class Bildschirm; // Bildschirm.h
    class AlphaFeld; // AlphaFeld.h
    class Schrift; // Schrift.h
    class Text; // Text.h
    class Bild; // Bild.h
    class WFenster; // aus dieser Datei
    class WFensterArray; // aus dieser Datei
    class Fenster; // aus dieser Datei
#ifdef WIN32
    // Erzeugt eine normale Fensterklasse der Windows API
    //  hInst: Die HINSTANCE des Programms (Wird vom Framework an die Start funktion in der Startparam Struktur �bergeben)
    __declspec( dllexport ) WNDCLASS F_Normal( HINSTANCE hInst );
    // Erzeugt eine normale Fensterklasse der Windows API
    //  hInst: Die HINSTANCE des Programms (Wird vom Framework an die Start funktion in der Startparam Struktur �bergeben)
    __declspec( dllexport ) WNDCLASSEX F_NormalEx( HINSTANCE hInst );
    // Funktion des Frameworks, die alle Nachichten von Windows oder anderen Prozessen verarbeitet
    __declspec( dllexport ) LRESULT CALLBACK WindowProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
    // Startet eine Schleife, die die Benutzereingaben verarbeitet. Die Schleife l�uft, bis irgendwo im Programm StopNachrichtenSchleife aufgerufen wird
    __declspec( dllexport ) void StartNachrichtenSchleife();
    // Stoppt die Ausf�hrung der Nachrichten Schleife des Frameworks.
    //  hwnd: Ein Handle auf ein beliebiges Fenster des Frameworks, das Nachrichten empfangen kann. Wird ben�tigt, um eine Nachricht zu senden, damit die funktion StartNachrichtenSchleife nicht mehr wartet und sofort beendet wird
    __declspec( dllexport ) void StopNachrichtenSchleife( HWND hwnd );
    // �bersetzt einen Keycode, der von Windows gesendet wurde in den Buchstaben der gedr�ckten Taste
    __declspec( dllexport ) unsigned char VirtualZuChar( int Virtual );

    // Klasse f�r ein Fenster der Windows API
    class WFenster
    {
    private:
        HWND hWnd; // Handel zum Fenster
        int style;
        void *makParam;
        void *sakParam;
        void *takParam;
        bool( *MausAktion )( void *, void *, MausEreignis );
        void( *VSchlie�Aktion )( void *, void * );
        void( *NSchlie�Aktion )( void *, void * );
        bool( *TastaturAktion )( void *, void *, TastaturEreignis );
        Bildschirm *screen;
        int mx, my;
        bool verschiebbar;
        int ref;
        HWND rahmen;
        HBITMAP bitmap;
        HDC hdc;

    public:
        //--Konstruktor--
        __declspec( dllexport ) WFenster();
        //--Konstruktor--
        //  hwnd: Ein Handle zum Fenster, das von dieser Klasse verwaltet werden soll
        __declspec( dllexport ) WFenster( HWND hWnd );
        //--Destruktor--
        __declspec( dllexport ) ~WFenster();
        // erstellt das Fenster
        //  style: Der Style des Fensters. Beispiel: WS_OVERLAPPEDWINDOW (F�r ein normales Fenster wie man es kennt)
        //  wc: Die Fensterklasse der Windows API, von der ein Fenster erstellt werden soll. Kann mit der Funktion F_Normal erstellt werden. Es muss lpszClassName gesetzt worden sein.
        __declspec( dllexport ) void erstellen( int style, WNDCLASS wc );
        // erstellt das Fenster
        //  exStyle: Der EX Style des Fensters. Beispiel: WS_EX_OVERLAPPEDWINDOW (F�r ein normales Fenster wie man es kennt)
        //  style: Der Style des Fensters. Beispiel: WS_OVERLAPPEDWINDOW (F�r ein normales Fenster wie man es kennt)
        //  wc: Die Fensterklasse der Windows API, von der ein Fenster erstellt werden soll. Kann mit der Funktion F_Normal erstellt werden. Es muss lpszClassName gesetzt worden sein.
        __declspec( dllexport ) void erstellenEx( int exStyle, int style, WNDCLASSEX wc );
        // Setzt den Anzeigemodus des Fensters
        //  mod: Der Modus. Beispiel: SW_SHOWNORMAL, um das Fenster anzuzeigen und SW_HIDE um es einzuklappen
        __declspec( dllexport ) void setAnzeigeModus( int mod );
        // Setzt den Fokus auf das Fenster, so dass Tastatureingaben empfangen werden
        __declspec( dllexport ) bool setFokus();
        // Setzt die Position des fensters auf dem Bildschirm
        //  pos: Die Position in Pixeln
        __declspec( dllexport ) void setPosition( Punkt &pos );
        // Setzt die Gr��e des Fensters auf dem Bildschirm
        //  gr��e: Die Gr��e in Pixeln
        __declspec( dllexport ) void setSize( Punkt &gr��e );
        // Setzt die Gr��e des Fensters auf dem Bildschirm
        //  breite: Die Breite in Pixeln
        //  h�he: Die H�he in Pixeln
        __declspec( dllexport ) void setSize( int breite, int h�he );
        // Setzt die Position und die Gr��e des Fensters
        //  pos: Die Position in Pixeln
        //  gr��e: Die Gr��e in Pixeln
        __declspec( dllexport ) void setBounds( Punkt &pos, Punkt &gr��e );
        // Setzt das Verwendete Bildschirm Objekt, um Tastatur und Maus Eingaben an die Objekte des Frameworks weiterzugeben. Muss vor dem Zerst�ren des Fensters mit 0 aufgerufen werden.
        //  screen: Das Bildschirm Objekt
        __declspec( dllexport ) void setBildschirm( Bildschirm *screen );
        // Zerst�rt das Fenster
        __declspec( dllexport ) void zerst�ren();
        // Verarbeitet Maus Nachrichten. Ruft MausAktion auf und gibt die Ereignisse an den Bildschirm mit den Objekten weiter, wenn MausAktion 1 zur�ckgibt
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausAktion( MausEreignis &me );
        // Ruft die VSchlie�Aktion R�ckruffunktion auf
        __declspec( dllexport ) void doVSchlie�Aktion();
        // Ruft die NSchlie�Aktion R�ckruffunktion auf
        __declspec( dllexport ) void doNSchlie�Aktion();
        // Verarbeitet Tastatur Nachrichten. Ruft TastaturAktion auf und gibt die Ereignisse an den Bildschirm mit den Objekten weiter, wenn TastaturAktion 1 zur�ckgibt
        //  me: Das Ereignis, was durch die Tastatureingabe ausgel��t wurde
        __declspec( dllexport ) void doTastaturAktion( TastaturEreignis &et );
        // Macht den Rahmen des Fensters sichtbar, fals ladeRahmenFenster aufgerufen wurde
        __declspec( dllexport ) void doRestoreMessage();
        // setzt den Parameter, der bei einem Maus Ereignis an die R�ckruffunktion �bergeben wird
        //  p: Der Parameter
        __declspec( dllexport ) void setMausEreignisParameter( void *p );
        // setzt den Parameter, der beim Schlie�en an die R�ckruffunktion �bergeben wird
        //  p: Der Parameter
        __declspec( dllexport ) void setSchlie�EreignisParameter( void *p );
        // Setzt den Parameter, der bei einem Tastatur Ereignis an die R�ckruffunktion �bergeben wird
        //  p: Der Parameter
        __declspec( dllexport ) void setTastaturEreignisParameter( void *p );
        // Setzt die R�ckruffunktion, die bei einem Maus Ereignis aufgerufen werden soll.
        // Wenn die R�ckruffunktion 0 zur�ckgiebt, oder nicht gesetzt wurde, wird ein Maus Ereignis von dem Fenster nicht weiter beachtet
        // Es kann die Standartfunktion __ret1ME verwendet werden, die in MausEreignis.h definiert ist und immer 1 zur�ckgibt
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setMausAktion( bool( *MausAk )( void *, void *, MausEreignis ) );
        // Setzt die R�ckruffunktion, die bei vor dem Schlie�en aufgerufen werden soll.
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setVSchlie�Aktion( void( *vSchlie�Ak )( void *, void * ) );
        // Setzt die R�ckruffunktion, die bei nach dem Schlie�en aufgerufen werden soll.
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setNSchlie�Aktion( void( *nSchlie�Ak )( void *, void * ) );
        // Setzt die R�ckruffunktion, die bei einem Tastatur Ereignis aufgerufen werdne soll.
        // Wenn die R�ckruffunktion 0 zur�ckgiebt, oder nicht gesetzt wurde, wird ein Tastatur Ereignis von der Zeichnung nicht weiter beachtet
        // Es kann die Standartfunktion __ret1TE verwendet werden, die in TastaturEreignis.h definiert ist und immer 1 zur�ckgibt
        // Weitere Standartfunktionen sind _nurNummernTE und _nurHexTE ebenfals aus TastaturEreignis.h
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setTastaturAktion( bool( *TastaturAk )( void *, void *, TastaturEreignis ) );
        //  Setzt das Handle zum Fenster, das von dieser Klasse verwaltet werden soll
        //  hwnd: Das Handle
        __declspec( dllexport ) void setFensterHandle( HWND hWnd );
        // legt fest, ob das Fenster durch ziehen mit Maus verschoben werden kann
        //  verschiebbar: 1, wenn das Fenster verschoben werden darf
        __declspec( dllexport ) void setVerschiebbar( bool verschiebbar );
        // Setzt einen Transparenten Rahmen um das Fenster
        //  zBild: Ein Bild, was den Rahmen enth�lt
        //  hins: Die HINSTANCE des Programms (Wird vom Framework an die Start funktion in der Startparam Struktur �bergeben)
        __declspec( dllexport ) void ladeRahmenFenster( Bild *zBild, HINSTANCE hinst ); // setzt einen Transpatenten Rahmen um das Fenster
        // Gibt das Handle des verwalteten Fensters zur�ck
        __declspec( dllexport ) HWND getFensterHandle() const;
        // Gibt die Position des Fensters in Pixeln zur�ck
        __declspec( dllexport ) Punkt getPosition() const;
        // Gibt die Gr��e des Fensters in Pixeln zur�ck
        __declspec( dllexport ) Punkt getGr��e() const;
        // Gibt die Gr��e des Fensterk�rpers in Pixeln zur�ck
        __declspec( dllexport ) Punkt getK�rperGr��e() const;
        // Gibt die Breite des Fensterk�rpers in Pixeln zur�ck
        __declspec( dllexport ) int getK�rperBreite() const;
        // Gibt die H�he des Fensterk�rpers in Pixeln zur�ck
        __declspec( dllexport ) int getK�rperH�he() const;
        // Gibt zur�ck, ob eine R�ckruffunktion f�r ein MausEreignis gesetzt wurde
        __declspec( dllexport ) bool hatMausAktion() const;
        // Gibt zur�ck, ob eine R�ckruffunktion f�r das Ereignis vor dem Schlie�en des Fensters gesetzt wurde
        __declspec( dllexport ) bool hatVSchlie�Aktion() const;
        // Gibt zur�ck, ob eine R�ckruffunktion f�r das Ereignis nach dem Schlie�en des Fensters gesetzt wurde
        __declspec( dllexport ) bool hatNSchlie�Aktion() const;
        // Gibt zur�ck, ob eine R�ckruffunktion f�r ein TastaturEreignis gesetzt wurde
        __declspec( dllexport ) bool hatTastaturAktion() const;
        // Gibt den Bidschirm zur�ck, an dessen Zeichnungen die Ereignisse Weitergegeben werden
        __declspec( dllexport ) Bildschirm *getBildschirm() const;
        // Gibt den Bildschirm ohne erh�hten Reference Counter zur�ck, an dessen Zeichnungen die Ereignisse Weitergegeben werden
        __declspec( dllexport ) Bildschirm *zBildschirm() const;
        // Gibt zur�ck, ob das Fenster verschiebbar ist
        __declspec( dllexport ) bool istVerschiebbar() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) WFenster *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) WFenster *release();
    };

    // Verwaltet alle Windows API Fenster im Framework
    class WFensterArray
    {
    private:
        WFensterArray *next;
        WFenster *This;

    public:
        // Konstruktor 
        __declspec( dllexport ) WFensterArray();
        // Destruktor 
        __declspec( dllexport ) ~WFensterArray();
        // F�gt ein neues Fenster hinzu
        //  fenster: Das Fenster
        __declspec( dllexport ) bool addFenster( WFenster *fenster );
        // Entfernt ein Fenster
        //  fenster: Das Fenster
        __declspec( dllexport ) bool removeFenster( WFenster *fenster );
        // gibt das n�chste Element zur�ck
        __declspec( dllexport ) WFensterArray* getNext();
        // Setzt das n�chste Element auf 0
        __declspec( dllexport ) void setNext0();
        // L�scht das Element
        __declspec( dllexport ) void del();
        // Sendet das Ereignis, was vor dem Schlie�en aufgerufen wird an ein bestimmtes Fenster
        //  hWnd: Das Handle zum Fenster
        __declspec( dllexport ) bool sendVSchlie�Message( HWND hWnd );
        // Sendet das Ereignis, was nach dem Schlie�en aufgerufen wird an ein bestimmtes Fenster
        //  hWnd: Das Handle zum Fenster
        __declspec( dllexport ) bool sendNSchlie�Message( HWND hwnd );
        // Sendet ein Maus Ereignis an ein bestimmtes Fenster
        //  hWnd: Das Handle zum Fenster
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) bool sendMausMessage( HWND hWnd, MausEreignis &me );
        // Sendet ein Tastatur Ereignis an ein bestimmtes Fenster
        //  hWnd: Das Handle zum Fenster
        //  me: Das Ereignis, was durch die Tastatureingabe ausgel��t wurde
        __declspec( dllexport ) bool sendTastaturMessage( HWND hwnd, TastaturEreignis &te );
        // Sendet das Ereignis, was durch das �ffnen des Fensters ausgel��t wurde an ein bestimmtes Fenster
        //  hWnd: Das Handle zum Fenster
        __declspec( dllexport ) bool sendRestoreMessage( HWND hwnd );
        // Gibt das Fenster dieses Eintrags zur�ck
        __declspec( dllexport ) WFenster *getThis();
    };

    // Erzeugt ein Windows API Popup Fenster, mit einer Meldung
    //  hWnd: Ein Handle zu dem Fenster, was blockiert werden soll, bis das Popup Fenster geschlossen wurde. Kann 0 sein
    //  titel: Der Titel des Popup Fensters
    //  meldung: Die Meldung, die im Fenster angezeigt werden soll
    //  style: Bestimmt das Icon, was im Fenster angezeigt wird. Beispiel: MB_ICONERROR, MB_ICONINFORMATION
    __declspec( dllexport ) void WMessageBox( HWND hWnd, Text *titel, Text *meldung, UINT style );
#endif
    // Fenster Klasse im Programm
    class Fenster : public Zeichnung
    {
    public:
        class Style : public Zeichnung::Style
        {
        public:
            const static __int64 BodyHintergrund = 0x000000008; // Legt fest, ob der K�rper des Fensters einen Hintergrund hat
            const static __int64 BodyHAlpha = 0x000000010; // Legt fest, ob beim zeichnen des K�rperhintergrundes alpha blending verwendet werden soll
            const static __int64 BodyHBild = 0x000000020; // Legt fest, ob ein Bild als Hintergrund des K�rpers verwendet werden soll
            const static __int64 BodyBuffered = 0x000000040; // Legt fest, ob der K�rper einen Farb�bergang besitzt
            const static __int64 Titel = 0x000000080; // Legt fest, ob das Fenster eine Titelleiste hat
            const static __int64 TitelHintergrund = 0x000000100; // Legt fest, ob die titelleiste des Fensters einen Hintergrund hat
            const static __int64 TitelHAlpha = 0x000000200; // Legt fest, ob zum zeichnen des Titel Hintergrundes alpha blending verwendet werden soll
            const static __int64 TitelHBild = 0x000000400; // Legt fest, ob f�r den Titelhintergrund ein Bild verwendet werden soll
            const static __int64 TitelBuffered = 0x000000800; // Legt fest, ob die Titel Leiste einen Farb�bergang besitzt
            const static __int64 Closable = 0x000001000; // Legt fest, ob in der Titelleiste ein Knopf zum Schlie�en des Fensters angezeigt werden soll
            const static __int64 ClosingHintergrund = 0x000002000; // Legt fest, ob der Schlie�en Knopf einen Hintergrund hat
            const static __int64 ClosingHAlpha = 0x000004000; // Legt fest, ob beim Zeichnen des Hintergrunds des Schlie�en Knopfes alpha blending verwendet werden soll
            const static __int64 ClosingHBild = 0x000008000; // Legt fest, ob f�r den Hintergrund des Schlie�en Knopfes ein Bild verwendet werden soll
            const static __int64 ClosingBuffer = 0x000010000; // Legt fest, ob der Schlie�en Knopf einen Farb�bergang besitzt
            const static __int64 ClosingKlickBuffer = 0x000020000; // Legt fest, ob der Schlie�en Knopf einen Farb�bergang besitzt, w�hrend er gedr�ckt wird
            const static __int64 Beweglich = 0x000040000; // Legt fest, ob der Benutzer das Fenster durch gedr�ckt halten der linken Maustaste in der Titelleiste das Fenster verschieben kann
            const static __int64 BreiteChangeable = 0x000080000; // Legt fest, ob der Benutzer die Breite des Fensters durch das gedr�ckt halten der linken Maustaste auf dem rechten oder linken Fensterrand ver�ndern kann
            const static __int64 HeightChangeable = 0x000100000;  // Legt fest, ob der Benutzer die H�he des Fensters durch das gedr�ckt halten der linken Maustaste auf dem oberen oder unteren Fensterrand ver�ndern kann
            const static __int64 TitelHeightChangeable = 0x000200000; // Legt fest, ob der Benutzer die H�he der Titel Leiste durch gedr�ckt halten der linken Maustaste auf dem unteren Rand der Titelleiste ver�ndern kann
            const static __int64 MinBr = 0x000400000; // Legt fest, ob es eine Minimale Breite des Fensters gibt
            const static __int64 MaxBr = 0x000800000; // Legt fest, ob es eine Maximale Breite des Fensters gibt
            const static __int64 MinHi = 0x001000000; // Legt fest, ob es eine Minimale H�he des Fensters gibt
            const static __int64 MaxHi = 0x002000000; // Legt fest, ob es eine Maximale H�he des Fensters gibt
            const static __int64 BodyMinBr = 0x004000000; // Legt fest, ob es eine Minimale Breite des K�rpers gibt
            const static __int64 BodyMaxBr = 0x008000000; // Legt fest, ob es eine Maximale Breite des K�rpers gibt
            const static __int64 BodyMinHi = 0x010000000; // Legt fest, ob es eine Minimale H�he des K�rpers gibt
            const static __int64 BodyMaxHi = 0x020000000; // Legt fest, ob es eine Maximale H�he des K�rpers gibt
            const static __int64 VScroll = 0x040000000; // Legt fest, ob eine ScrollBar am rechten Fensterrand erscheinen soll
            const static __int64 HScroll = 0x080000000; // Legt fest, ob eine ScrollBar am unteren Fensterrand erscheinen soll
            const static __int64 METransparenz = 0x100000000; // Legt fest, ob die Mausereignisse auch noch von Zeichnungen hinter dem Fenster verarbeitet werden sollen
            const static __int64 Rahmen = 0x200000000; // Legt fest, ob das Fenster einen Rahmen haben soll

            const static __int64 min_max = MinHi | MaxHi | MaxBr | MaxHi; // Vereint die Flags MinH�, MaxH�, MaxBr, MaxH�
            const static __int64 body_min_max = BodyMinBr | BodyMaxBr | BodyMinHi | BodyMaxBr; // Vereint die Flags K�rper_minBr, K�rper_maxBr, K�rper_minH�, K�rper_maxBr
            const static __int64 scroll = VScroll | HScroll; // Vereint die Flags VScroll, HScroll
            const static __int64 nichtfixiert = TitelHeightChangeable | HeightChangeable | BreiteChangeable | Beweglich; // Vereint die Flags TitelH�he�nderbar, H�he�nderbar, Breite�nderbar, Beweglich

            const static __int64 normal = Sichtbar | Erlaubt | Rahmen | Titel | TitelBuffered | Closable | ClosingHBild | ClosingKlickBuffer | Beweglich; // Vereint die Flags Sichtbar, Erlaubt, Rahmen, Titel, TitelBuffered, Schlie�bar, Schlie�HBild, Schlie�KlickBuffer, Beweglich
        };
    private:
        bool( *closingMe )( void *, void *, MausEreignis );
        void *closingMeParam;
        LRahmen *rahmen;
        TextFeld *titel;
        ZeichnungArray *members;
        int bgBodyColor;
        Bild *bgBodyPicture;
        AlphaFeld *bodyBuffer;
        int bgClosingFarbe;
        Bild *bgClosingBild;
        AlphaFeld *closeBuffer;
        AlphaFeld *closeKlickBuffer;
        VScrollBar *vScroll;
        HScrollBar *hScroll;
        Punkt min, max;
        Punkt kMin, kMax;
        bool closeKlick, klick;
        int mx, my;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) Fenster();
        // Destruktor 
        __declspec( dllexport ) virtual ~Fenster();
        // Setzt einen Zeiger auf den Rahmen des Fensters
        //  ram: Der Rahmen
        __declspec( dllexport ) void setRahmenZ( LRahmen *ram );
        // Setzt die Farbe des Fensterrahmens
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setRFarbe( int f );
        // Setzt die Breite des Fensterrahmens
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setRBreite( int br );
        // Setzt den Titel des Fensters
        //  txt: Der Text
        __declspec( dllexport ) void setTitel( Text *txt );
        // Setzt einen Zeiger auf den Titel Text
        //  txt: Der neue Text
        __declspec( dllexport ) void setTitelZ( Text *txt );
        // Setzt den Titel des Fensters
        //  txt: Der Textv
        __declspec( dllexport ) void setTitel( const char *txt );
        // Setzt einen Zeiger auf das TextFeld, das den Titeltext zeichnet
        //  tf: Das TextFeld
        __declspec( dllexport ) void setTTextFeldZ( TextFeld *tf );
        // Setzt die Schrift, die f�r den Titel verwendet werden soll
        //  schrift: Die Schrift
        __declspec( dllexport ) void setTSchriftZ( Schrift *schrift );
        // Setzt die Farbe der Schrift, die f�r den Titel verwendet werden soll
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setTSFarbe( int f );
        // Setzt die Gr��e der Schrift, die f�r den Titel verwendet werden soll
        //  gr: Die H�he einer zeile in Pixeln
        __declspec( dllexport ) void setTSSize( int gr );
        // Setzt die Hintergrund Farbe des Titels
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setTBgFarbe( int f );
        // Setzt einen Zeiger auf den Farb�bergang des Titels
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setTAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs des Titels
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setTAfFarbe( int f );
        // Setzt die St�rke des Farb�bergangs des Titels
        //  st: Die St�rke
        __declspec( dllexport ) void setTAfStrength( int st );
        // Setzt das Hintergrund Bild des Titels durch kopieren
        //  b: Das Bild, was kopiert werden soll
        __declspec( dllexport ) void setTBgBild( Bild *b );
        // Setzt einen Zeiger auf das Hintergrund Bild des Titels
        //  b: Das Bild
        __declspec( dllexport ) void setTBgBildZ( Bild *b );
        // Setzt einen Zeiger auf den Rahmen des Titels
        //  ram: Der Rahmen
        __declspec( dllexport ) void setTRahmenZ( LRahmen *ram );
        // Setzt die Farbe des Rahmens des Titels
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setTRFarbe( int f );
        // Setzt die Breite des Rahmens des Titels
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setTRBreite( int br );
        // Setzt die Hintergrundfarbe des K�rpers 
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKBgFarbe( int f );
        // Setzt das Hintergrund Bild des K�rpers durch kopieren
        //  b: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setKBgBild( Bild *b );
        // Setzt einen Zeiger auf das Hintergrund Bild des K�rpers
        //  b: Das Bild
        __declspec( dllexport ) void setKBgBildZ( Bild *b );
        // Setzt einen Zeiger auf den Farb�bergang des K�rpers
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setKAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs des K�rpers
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKAfFarbe( int f );
        // Setzt die St�rke des Farb�bergangs des K�rpers
        //  st: Die St�rke
        __declspec( dllexport ) void setKAfStrength( int st );
        // Setzt den Parameter der R�ckruffunktion, die aufgerufen wird, wenn der Schlie�en Knopf ein MausEreignis erh�lt
        //  param: Der Parameter
        __declspec( dllexport ) void setClosingMeParam( void *param );
        // Setzt die R�ckruffunktion, die Aufgerufen wird, wenn der Schlie�en Knopf ein MausEreignis erh�lt
        // Wenn die R�ckruffunktion 0 zur�ckgiebt, oder nicht gesetzt wurde, wird ein Maus Ereignis von der Zeichnung nicht weiter beachtet
        // Das Fenster wird nicht von selbst geschlossen, sondern sollte in der R�ckruffunktion durch den aufruf von l�scheStyle( Fenster::Style::Sichtbar ); geschlossen werden
        //  ak: Ein Zeiger auf die R�ckruffunktion
        __declspec( dllexport ) void setClosingMe( bool( *closingMe )( void *, void *, MausEreignis ) );
        // Setzt die Hintergrund Farbe des Schlie�en Knopfes
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSBgFarbe( int f );
        // Setzt das Hintergrund Bild des Schlie�en Knopfes durch kopieren
        //  b: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setSBgBild( Bild *b );
        // Setzt einen Zeiger auf das Hintergrund Bild des Schlie�en Knopfes
        //  b: Das Bild
        __declspec( dllexport ) void setSBgBildZ( Bild *b );
        // Setzt einen Zeiger auf den Farb�bergang des Schlie�en Knopfes
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setSAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs des Schlie�en Knopfes
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSAfFarbe( int f );
        // Setzt die St�rke des Farb�bergangs des Schlie�en Knopfes
        //  st: Die St�rke
        __declspec( dllexport ) void setSAfStrength( int st );
        // Setzt einen Zeiger auf den Farb�bergang, der beim Klicken des Schlie�en Knopfes verwendet wird
        //  af: Der Farb�bergnag
        __declspec( dllexport ) void setSKAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs, der beim Klicken des Schlie�en Knopfes verwendet wird
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSKAfFarbe( int f );
        // Setzt die St�rke des Farb�bergangs, der beim Klicken des Schlie�en Knopfes verwendet wird
        //  st: Die St�rke
        __declspec( dllexport ) void setSKAfStrength( int st );
        // Setzt die Minimale Gr��e des Fensters
        //  mx: Die Minimale Breite in Pixeln
        //  my: Die Minimale H�he in Pixeln
        __declspec( dllexport ) void setMin( int mx, int my );
        // Setzt die Minimale Gr��e des Fensters
        //  min: Die Minimale Breite und H�he in Pixeln
        __declspec( dllexport ) void setMin( const Punkt &min );
        // Setzt die Maximale Gr��e des Fensters
        //  mx: Die Maximale Breite in Pixeln
        //  my: Die Maximale H�he in Pixeln
        __declspec( dllexport ) void setMax( int mx, int my );
        // Setzt die Maximale Gr��e des Fensters
        //  min: Die Maximale Breite und H�he in Pixeln
        __declspec( dllexport ) void setMax( const Punkt &max );
        // Setzt die Minimale Gr��e des Fenster K�rpers
        //  mx: Die Minimale Breite in Pixeln
        //  my: Die Minimale H�he in Pixeln
        __declspec( dllexport ) void setKMin( int mx, int my );
        // Setzt die Minimale Gr��e des Fenster K�rpers
        //  min: Die Minimale Breite und H�he in Pixeln
        __declspec( dllexport ) void setKMin( const Punkt &min );
        // Setzt die Maximale Gr��e des Fenster K�rpers
        //  mx: Die Maximale Breite in Pixeln
        //  my: Die Maximale H�he in Pixeln
        __declspec( dllexport ) void setKMax( int mx, int my );
        // Setzt die Maximale Gr��e des Fenster K�rpers
        //  min: Die Maximale Breite und H�he in Pixeln
        __declspec( dllexport ) void setKMax( const Punkt &max );
        // Setzt einen Zeiger auf die Scrollbar am unteren Rand des Fensters
        //  hScroll: Die Scrollbar
        __declspec( dllexport ) void setHScrollBarZ( HScrollBar *hScroll );
        // Setzt einen Zeiger auf die Scrollbar am rechten Rand des Fensters
        //  vScroll: Die Scrollbar
        __declspec( dllexport ) void setVScrollBarZ( VScrollBar *vScroll );
        // Setzt die Maximale Scroll breite des Fenster K�rpers
        //  max: Die Breite in Pixeln
        __declspec( dllexport ) void setHSBMax( int max );
        // Setzt die Maximale Scroll h�he des Fenster K�rpers
        //  max: Die H�he in Pixeln
        __declspec( dllexport ) void setVSBMax( int max );
        // Scrollt zu einer bestimmten x Position im Fenster K�rper
        //  scroll: Die Anzahl der Pixel, die der Inhalt nach links verschoben werden soll
        __declspec( dllexport ) void setHSBScroll( int scroll );
        // Scrollt zu einer bestimmten y Position im Fenster K�rper
        //  scroll: Die Anzahl der Pixel, die der Inhalt nach oben verschoben werden soll
        __declspec( dllexport ) void setVSBScroll( int scroll );
        // F�gt dem Fenster eine Zeichnung hinzu
        //  zObj: Die Zeichnung
        __declspec( dllexport ) void addMember( Zeichnung *zObj );
        // Entfernt eine Zeichnung aus dem Fenster
        //  zObj: Die Zeichnung
        __declspec( dllexport ) void removeMember( Zeichnung *zObj );
        // Aktualisiert das Objekt. Wird vom Framework aufgerufen
        //  tickVal: Die Zeit in sekunden, die seit dem lezten Aufruf dieser Funktion vergangen ist
        //  return: 1, wenn sich etwas ver�ndert hat und das Bild neu gezeichnet werden muss. 0 sonst
        __declspec( dllexport ) bool tick( double tickval ) override;
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Verarbeitet Tastatur Nachrichten
        //  me: Das Ereignis, was durch die Tastatureingabe ausgel��t wurde
        __declspec( dllexport ) void doTastaturEreignis( TastaturEreignis &te ) override;
        // Zeichnet das Fentster nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt den Rahmen des Fensters zur�ck
        __declspec( dllexport ) LRahmen *getRahmen() const;
        // Gibt den Rahmen des Fensters ohne erh�hen Reference Counter zur�ck
        __declspec( dllexport ) LRahmen *zRahmen() const;
        // Gibt die Farbe des Rahmens des Fensters im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getRFarbe() const;
        // Gibt die Breite des Rahmens des Fensters in Pixeln zur�ck
        __declspec( dllexport ) int getRBreite() const;
        // Gibt den Titel des Fensters zur�ck
        __declspec( dllexport ) Text *getTitel() const;
        // Gibt den Titel des Fensters ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Text *zTitel() const;
        // Gibt das TextFeld zur�ck, das zum Zeichnen des Titels verwendet wird
        __declspec( dllexport ) TextFeld *getTTextFeld() const;
        // Gibt das TextFeld ohne erh�hten Reference Counter zur�ck, das zum Zeichnen des Titels verwendet wird
        __declspec( dllexport ) TextFeld *zTTextFeld() const;
        // Gibt die Schrift zur�ck, die f�r den Titel verwendet wird
        __declspec( dllexport ) Schrift *getTSchrift() const;
        // Gibt die Schrift ohne erh�ten Reference Counter zur�ck, die f�r den Titel verwendet wird
        __declspec( dllexport ) Schrift *zTSchrift() const;
        // Gibt die Schrift Farbe des Titels im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getTSFarbe() const;
        // Gibt die H�he einer Zeile des Titels in Pixeln zur�ck
        __declspec( dllexport ) int getTSSize() const;
        // Gibt die Hintergrundfarbe des Titels im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getTBgFarbe() const;
        // Gibt den Farb�bergang des Titels zur�ck
        __declspec( dllexport ) AlphaFeld *getTAlphaFeld() const;
        // Gibt den Farb�bergang des Titels ohne erh�hten Reference COunter zur�ck
        __declspec( dllexport ) AlphaFeld *zTAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs des Titels im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getTAfFarbe() const;
        // Gibt die St�rke des Farb�bergangs des Titels zur�ck
        __declspec( dllexport ) int getTAfStrength() const;
        // Gibt das Hintergrund Bild des titels zur�ck
        __declspec( dllexport ) Bild *getTBgBild() const;
        // Gibt das Hintergrund Bild des titels ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Bild *zTBgBild() const;
        // Gibt den Rahmen des Titels zur�ck
        __declspec( dllexport ) LRahmen *getTRahmen() const;
        // Gibt den Rahmen des Titels ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) LRahmen *zTRahmen() const;
        // Gibt die Farbe des Rahmens des Titels im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getTRFarbe() const;
        // Gibt die St�rke des Rahmens des Titels zur�ck
        __declspec( dllexport ) int getTRBreite() const;
        // Gibt die Hintergrund Farbe des K�rpers zur�ck
        __declspec( dllexport ) int getKBgFarbe() const;
        // Gibt das Hintergrund Bild des K�rpers zur�ck
        __declspec( dllexport ) Bild *getKBgBild() const;
        // Gibt das Hintergrund Bild des K�rpers ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Bild *zKBgBild() const;
        // Gibt den Farb�bergang des K�rpers zur�ck
        __declspec( dllexport ) AlphaFeld *getKAlphaFeld() const;
        // Gibt den Farb�bergang des K�rpers ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) AlphaFeld *zKAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs des K�rpers im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getKAfFarbe() const;
        // Gibt die St�rke des Farb�bergangs des K�rpers zur�ck
        __declspec( dllexport ) int getKAfStrength() const;
        // Gibt die Hintergrund Farbe des Schlie�en Knopfes im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getSBgFarbe() const;
        // Gibt das Hintergrund Bild des Schlie�en Knopfes zur�ck
        __declspec( dllexport ) Bild *getSBgBild() const;
        // Gibt das Hintergrund Bild des Schlie�en Knopfes ohne erh�hten Reference COunter zur�ck
        __declspec( dllexport ) Bild *zSBgBild() const;
        // Gibt den Farb�bergang des Schlie�en Knopfes zur�ck
        __declspec( dllexport ) AlphaFeld *getSAlphaFeld() const;
        // Gibt den Farb�bergang des Schlie�en Knopfes ohne erh�hten Reference COunter zur�ck
        __declspec( dllexport ) AlphaFeld *zSAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs des Schlie�en Knopfes im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getSAfFarbe() const;
        // Gibt die St�rke des Farb�bergangs des Schlie�en Knopfes zur�ck
        __declspec( dllexport ) int getSAfStrength() const;
        // Gibt den Farb�bergang zur�ck, der verwendet wird, wenn auf den Schlie�en Knopf gedr�ckt wird
        __declspec( dllexport ) AlphaFeld *getSKAlphaFeld() const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der verwendet wird, wenn auf den Schlie�en Knopf gedr�ckt wird
        __declspec( dllexport ) AlphaFeld *zSKAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs im A8R8G8B8 Format zur�ck, der verwendet wird, wenn auf den Schlie�en Knopf gedr�ckt wird
        __declspec( dllexport ) int getSKAfFarbe() const;
        // Gibt die St�rke des Farb�bergangs zur�ck, der verwendet wird, wenn auf den Schlie�en Knopf gedr�ckt wird
        __declspec( dllexport ) int getSKAfStrength() const;
        // Gibt die minimale Fenstergr��e in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getMin() const;
        // Gibt die maximale Fenstergr��e in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getMax() const;
        // Gibt die minimale K�rpergr��e in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getKMin() const;
        // Gibt die maximale K�rpergr��e in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getKMax() const;
        // Gibt die Scrollbar vom rechten Fensterrand zur�ck
        __declspec( dllexport ) VScrollBar *getVScrollBar() const;
        // Gibt die Scrollbar vom rechten Fensterrand ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) VScrollBar *zVScrollBar() const;
        // Gibt die Scrollbar vom unteren Fensterrand zur�ck
        __declspec( dllexport ) HScrollBar *getHScrollBar() const;
        // Gibt die Scrollbar vom unteren Fensterrand ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) HScrollBar *zHScrollBar() const;
        // Gibt eine Liste mit Zeichnungen zur�ck, die im Fenster sind
        __declspec( dllexport ) ZeichnungArray *getMembers() const;
        // Erzeugt eine Kopie des Fensters, die ohne Auswirkungen auf das Original ver�ndert werden kann
        __declspec( dllexport ) Zeichnung *dublizieren() const override;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Fenster *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Fenster *release();
    };
}
#endif