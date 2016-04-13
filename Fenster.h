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

	// Erzeugen einer normalen Fensterklasse
	__declspec( dllexport ) WNDCLASS F_Normal( HINSTANCE hInst );
	__declspec( dllexport ) WNDCLASSEX F_NormalEx( HINSTANCE hInst );

	__declspec( dllexport ) LRESULT CALLBACK WindowProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
	__declspec( dllexport ) void StartNachrichtenSchleife();
	__declspec( dllexport ) void StopNachrichtenSchleife( HWND hwnd );

	__declspec( dllexport ) unsigned char VirtualZuChar( int Virtual );
	// Klasse f�r ein Fenster in Windows
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
		__declspec( dllexport ) WFenster( HWND hWnd );
		//--Destruktor--
		__declspec( dllexport ) ~WFenster();
		// nicht constant
		__declspec( dllexport ) void erstellen( int style, WNDCLASS wc ); // Das Fenster Erstellen
		__declspec( dllexport ) void erstellenEx( int exStyle, int style, WNDCLASSEX wc ); // Das Fenster Erstellen
		__declspec( dllexport ) void setAnzeigeModus( int mod ); // Zeigt das Fenster im �bergebenen Modus an
		__declspec( dllexport ) bool setFokus(); // Setzt den Fokus auf das Fenster
		__declspec( dllexport ) void setPosition( Punkt &pos ); // Bildschirmposition des Fensters setzen
		__declspec( dllexport ) void setGr��e( Punkt &gr��e ); // Die gr��e des Fensters setzen
		__declspec( dllexport ) void setGr��e( int breite, int h�he );
		__declspec( dllexport ) void setBounds( Punkt &pos, Punkt &gr��e ); // Gr��e und Porition in einem
		__declspec( dllexport ) void setBildschirm( Bildschirm *screen );
		__declspec( dllexport ) void zerst�ren(); // Zerst�rt das Fenster
		__declspec( dllexport ) void doMausAktion( MausEreignis &me ); // ruft MausAktion auf
		__declspec( dllexport ) void doVSchlie�Aktion(); // ruft VSchlie�Aktion auf
		__declspec( dllexport ) void doNSchlie�Aktion(); // ruft NSchlie�Aktion auf
		__declspec( dllexport ) void doTastaturAktion( TastaturEreignis &et ); // ruft TastaturAktion auf
		__declspec( dllexport ) void doRestoreMessage(); // macht den Rahmen sichtbar
		__declspec( dllexport ) void setMausEreignisParameter( void *p ); // setzt den Parameter vom Maus Ereignis
		__declspec( dllexport ) void setSchlie�EreignisParameter( void *p ); // setzt den Parameter vom Schlie� Ereignis
		__declspec( dllexport ) void setTastaturEreignisParameter( void *p ); // setzt den Parameter vom Tastatur Ereignis
		__declspec( dllexport ) void setMausAktion( bool( *MausAk )( void *, void *, MausEreignis ) ); // setzt das MausEreignis
		__declspec( dllexport ) void setVSchlie�Aktion( void( *vSchlie�Ak )( void *, void * ) ); // setzt v schlie� Aktion
		__declspec( dllexport ) void setNSchlie�Aktion( void( *nSchlie�Ak )( void *, void * ) ); // setzt n schlie� Aktion
		__declspec( dllexport ) void setTastaturAktion( bool( *TastaturAk )( void *, void *, TastaturEreignis ) ); // setzt das TastaturEreignis
		__declspec( dllexport ) void setFensterHandle( HWND hWnd ); // setzt das operationsfenster
		__declspec( dllexport ) void setVerschiebbar( bool verschiebbar ); // legt fest, ob das Fenster durch ziehen mit Maus verschoben werden kann
		__declspec( dllexport ) void ladeRahmenFenster( Bild *zBild, HINSTANCE hinst ); // setzt einen Transpatenten Rahmen um das Fenster
		// constant
		__declspec( dllexport ) HWND getFensterHandle() const; // gibt das Fenster Handle zur�ck
		__declspec( dllexport ) Punkt getPosition() const; // gibt die Fensterposition zur�ck
		__declspec( dllexport ) Punkt getK�rperPosition() const; // gibt die Fenster K�rperposition zur�ck
		__declspec( dllexport ) Punkt getGr��e() const; // gibt die Fenstergr��e zur�ck
		__declspec( dllexport ) Punkt getK�rperGr��e() const; // gibt die Fenster K�rpergr��e zur�ck
		__declspec( dllexport ) int getK�rperBreite() const; // gibt die Fenster K�rperbreite zur�ck
		__declspec( dllexport ) int getK�rperH�he() const; // gibt die Fenster K�rperh�he zur�ck
		__declspec( dllexport ) bool hatMausAktion() const; // Pr�ft, ob eine Aktion bei MausEreignis festgelegt wurde
		__declspec( dllexport ) bool hatVSchlie�Aktion() const; // Pr�ft, ob eine Aktion vor Fensterschlie�en festgelegt wurde
		__declspec( dllexport ) bool hatNSchlie�Aktion() const; // Pr�ft, ob eine Aktion nach Fensterschlie�en festgelegt wurde
		__declspec( dllexport ) bool hatTastaturAktion() const; // Pr�ft, ob eine Aktion bei TastaturEreignis festgelegt wurde
		__declspec( dllexport ) Bildschirm *getBildschirm() const;
		__declspec( dllexport ) Bildschirm *zBildschirm() const;
		__declspec( dllexport ) bool istVerschiebbar() const; // pr�ft, ob das Fenster durch ziehen mit Maus verschoben werden kann
		// Reference Counting
		__declspec( dllexport ) WFenster *getThis();
		__declspec( dllexport ) WFenster *release();
	};

	// Verwaltung der WFenster im Framework
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
		// add und remove 
		__declspec( dllexport ) bool addFenster( WFenster *fenster );
		__declspec( dllexport ) bool removeFenster( WFenster *fenster );
		__declspec( dllexport ) WFensterArray* getNext();
		__declspec( dllexport ) void setNext0();
		__declspec( dllexport ) void del();
		// Messages 
		__declspec( dllexport ) bool sendVSchlie�Message( HWND hWnd );
		__declspec( dllexport ) bool sendNSchlie�Message( HWND hwnd );
		__declspec( dllexport ) bool sendMausMessage( HWND hWnd, MausEreignis &me );
		__declspec( dllexport ) bool sendTastaturMessage( HWND hwnd, TastaturEreignis &te );
		__declspec( dllexport ) bool sendRestoreMessage( HWND hwnd );
		__declspec( dllexport ) WFenster *getThis();
	};

	// WMessageBox
	__declspec( dllexport ) void WMessageBox( HWND hWnd, Text *titel, Text *meldung, UINT style );

	// Fenster Klasse im Programm
	class Fenster : public Zeichnung
	{
    public:
        class Style : public Zeichnung::Style
        {
        public:
            const static __int64 K�rperHintergrund = 0x000000008;
            const static __int64 K�rperHAlpha = 0x000000010;
            const static __int64 K�rperHBild = 0x000000020;
            const static __int64 K�rperBuffered = 0x000000040;
            const static __int64 Titel = 0x000000080;
            const static __int64 TitelHintergrund = 0x000000100;
            const static __int64 TitelHAlpha = 0x000000200;
            const static __int64 TitelHBild = 0x000000400;
            const static __int64 TitelBuffered = 0x000000800;
            const static __int64 Schlie�bar = 0x000001000;
            const static __int64 Schlie�Hintergrund = 0x000002000;
            const static __int64 Schlie�HAlpha = 0x000004000;
            const static __int64 Schlie�HBild = 0x000008000;
            const static __int64 Schlie�Buffer = 0x000010000;
            const static __int64 Schlie�KlickBuffer = 0x000020000;
            const static __int64 Beweglich = 0x000040000;
            const static __int64 Breite�nderbar = 0x000080000;
            const static __int64 H�he�nderbar = 0x000100000;
            const static __int64 TitelH�he�nderbar = 0x000200000;
            const static __int64 MinBr = 0x000400000;
            const static __int64 MaxBr = 0x000800000;
            const static __int64 MinH� = 0x001000000;
            const static __int64 MaxH� = 0x002000000;
            const static __int64 K�rper_minBr = 0x004000000;
            const static __int64 K�rper_maxBr = 0x008000000;
            const static __int64 K�rper_minH� = 0x010000000;
            const static __int64 K�rper_maxH� = 0x020000000;
            const static __int64 VScroll = 0x040000000;
            const static __int64 HScroll = 0x080000000;
            const static __int64 METransparenz = 0x100000000;
            const static __int64 Rahmen = 0x200000000;

            const static __int64 min_max = MinH� | MaxH� | MaxBr | MaxH�;
            const static __int64 k�rper_min_max = K�rper_minBr | K�rper_maxBr | K�rper_minH� | K�rper_maxBr;
            const static __int64 scroll = VScroll | HScroll;
            const static __int64 nichtfixiert = TitelH�he�nderbar | H�he�nderbar | Breite�nderbar | Beweglich;

            const static __int64 normal = Sichtbar | Erlaubt | Rahmen | Titel | TitelBuffered | Schlie�bar | Schlie�HBild | Schlie�KlickBuffer | Beweglich;
        };
	private:
		bool( *schlie�enMe )( void *, void *, MausEreignis );
		void *schlie�enMeParam;
		LRahmen *rahmen;
		TextFeld *titel;
		ZeichnungArray *members;
		int bgK�rperFarbe;
		Bild *bgK�rperBild;
		AlphaFeld *k�rperBuffer;
		int bgSchlie�Farbe;
		Bild *bgSchlie�Bild;
		AlphaFeld *schlie�Buffer;
		AlphaFeld *schlie�KlickBuffer;
		VScrollBar *vScroll;
		HScrollBar *hScroll;
		Punkt min, max;
		Punkt kMin, kMax;
		bool schlie�Klick, klick;
		int mx, my;
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) Fenster();
		// Destruktor 
		__declspec( dllexport ) ~Fenster();
		// nicht const 
		// -- Rahmen -- 
		__declspec( dllexport ) void setRahmenZ( LRahmen *ram ); // setzt den rahmen
		__declspec( dllexport ) void setRFarbe( int f ); // setzt die Rahmen Farbe
		__declspec( dllexport ) void setRBreite( int br ); // setzt die Breite des Rahmens
		// -- Titel -- 
		__declspec( dllexport ) void setTitel( Text *txt ); // setzt den Titel
		__declspec( dllexport ) void setTitelZ( Text *txt );
		__declspec( dllexport ) void setTitel( const char *txt );
		__declspec( dllexport ) void setTTextFeldZ( TextFeld *tf ); // setzt das Titel TextFeld
		// -- Schrift -- 
		__declspec( dllexport ) void setTSchriftZ( Schrift *schrift ); // setzt die Titel Schrift
		__declspec( dllexport ) void setTSFarbe( int f ); // setzt die Titel Schrift Farbe
		__declspec( dllexport ) void setTSGr��e( int gr ); // setzt die Titel Schrift Gr��e
		// -- Titel Hintergrund -- 
		__declspec( dllexport ) void setTBgFarbe( int f ); // setzt Titel Hintergrund farbe
		// -- Titel AlphaFeld -- 
		__declspec( dllexport ) void setTAlphaFeldZ( AlphaFeld *af ); // setzt das Titel AlphaFeld
		__declspec( dllexport ) void setTAfFarbe( int f ); // setzt die Titel AlphFeld Farbe
		__declspec( dllexport ) void setTAfSt�rke( int st ); // setzt die St�rke des Titel AlphaFeldes
		// -- Titel Hintergrund Bild -- 
		__declspec( dllexport ) void setTBgBild( Bild *b ); // setzt das Titel Hintergrund Bild
		__declspec( dllexport ) void setTBgBildZ( Bild *b );
		// -- Titel Rahmen -- 
		__declspec( dllexport ) void setTRahmenZ( LRahmen *ram ); // set Titel Rahmen
		__declspec( dllexport ) void setTRFarbe( int f ); // setzt die Titel Rahmen Farbe
		__declspec( dllexport ) void setTRBreite( int br ); // setzt die Titel Rahmen Breite
		// -- K�rper Hintergrund -- 
		__declspec( dllexport ) void setKBgFarbe( int f ); // setzt die K�rper Hintergrund Farbe
		// -- K�rper Hintergrund Bild -- 
		__declspec( dllexport ) void setKBgBild( Bild *b ); // setzt das K�rper Hintergrund Bild
		__declspec( dllexport ) void setKBgBildZ( Bild *b );
		// -- K�rper AlphaFeld -- 
		__declspec( dllexport ) void setKAlphaFeldZ( AlphaFeld *af ); // setzt das K�rper AlphaFeld
		__declspec( dllexport ) void setKAfFarbe( int f ); // setzt K�rper AlphaFeld Farbe
		__declspec( dllexport ) void setKAfSt�rke( int st ); // setzt die St�rke des K�rper AlphaFeldes
		// -- Schlie�en --
		__declspec( dllexport ) void setSchlie�enMeParam( void *param );
		__declspec( dllexport ) void setSchlie�enMe( bool( *schlie�enMe )( void *, void *, MausEreignis ) ); // setzt das Schlie�en Mausereignis
		// -- Schlie�en Hintergrund -- 
		__declspec( dllexport ) void setSBgFarbe( int f ); // setzt die Schlie� Hintergrund Farbe
		// -- Schlie�en Hintergrund Bild -- 
		__declspec( dllexport ) void setSBgBild( Bild *b ); // setzt das Schlie� Hintergrund Bild
		__declspec( dllexport ) void setSBgBildZ( Bild *b );
		// -- Schlie�en AlphaFeld -- 
		__declspec( dllexport ) void setSAlphaFeldZ( AlphaFeld *af ); // setzt das Schlie� AlphaFeld
		__declspec( dllexport ) void setSAfFarbe( int f ); // setzt die Farbe des Schlie� AlphaFeldes
		__declspec( dllexport ) void setSAfSt�rke( int st ); // setzt die St�rke des Schlie� AlphaFeldes
		// -- Schlie�en Klick AlphaFeld -- 
		__declspec( dllexport ) void setSKAlphaFeldZ( AlphaFeld *af ); // setzt das Schlie� klick AlphaFeld
		__declspec( dllexport ) void setSKAfFarbe( int f ); // setzt die Farbe des Schlie� klick AlphaFeldes
		__declspec( dllexport ) void setSKAfSt�rke( int st ); // setzt die St�rke des Schlie� klick AlphaFeldes
		// -- min max -- 
		__declspec( dllexport ) void setMin( int mx, int my ); // setzt die Mindest Fenster Gr��e
		__declspec( dllexport ) void setMin( const Punkt &min );
		__declspec( dllexport ) void setMax( int mx, int my ); // setzt die Maximale Fenster Gr��e
		__declspec( dllexport ) void setMax( const Punkt &max );
		__declspec( dllexport ) void setKMin( int mx, int my ); // setzt die Mindest K�rper Gr��e
		__declspec( dllexport ) void setKMin( const Punkt &min );
		__declspec( dllexport ) void setKMax( int mx, int my ); // setzt die Maximale K�rper Gr��e
		__declspec( dllexport ) void setKMax( const Punkt &max );
		// -- scroll -- 
		__declspec( dllexport ) void setHScrollBarZ( HScrollBar *hScroll ); // setzt die Horizontale Scroll Bar
		__declspec( dllexport ) void setVScrollBarZ( VScrollBar *vScroll ); // setzt die Vertikale Scroll BAr
		__declspec( dllexport ) void setHSBMax( int max ); // setzt das Scroll Maximum
		__declspec( dllexport ) void setVSBMax( int max );
		__declspec( dllexport ) void setHSBScroll( int scroll ); // setzt die momentane Scroll Position
		__declspec( dllexport ) void setVSBScroll( int scroll );
		// -- Members -- 
		__declspec( dllexport ) void addMember( Zeichnung *zOobj ); // f�gt einen Member hinzu
		__declspec( dllexport ) void removeMember( Zeichnung *zObj ); // entfernt einen Member
		// -- Messages -- 
		__declspec( dllexport ) bool tick( double tickval ) override; // tick
		__declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
		__declspec( dllexport ) void doTastaturEreignis( TastaturEreignis &te ) override;
		// -- Render -- 
		__declspec( dllexport ) void render( Bild &zRObj ) override; // zeichent nach zRObj
		// constant 
		// -- Rahmen -- 
		__declspec( dllexport ) LRahmen *getRahmen() const; // gibt den Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zRahmen() const;
		__declspec( dllexport ) int getRFarbe() const; // gibt die Farbe des Rahmens zur�ck
		__declspec( dllexport ) int getRBreite() const; // gibt die breite des Rahmens zur�ck
		// -- Titel  -- 
		__declspec( dllexport ) Text *getTitel() const; // gibt den Titel zur�ck
		__declspec( dllexport ) Text *zTitel() const;
		__declspec( dllexport ) TextFeld *getTTextFeld() const; // gibt das Titel TextFeld zur�ck
		__declspec( dllexport ) TextFeld *zTTextFeld() const;
		// -- Titel Schrift -- 
		__declspec( dllexport ) Schrift *getTSchrift() const; // gibt die Titel Schrift zur�ck
		__declspec( dllexport ) Schrift *zTSchrift() const;
		__declspec( dllexport ) int getTSFarbe() const; // gibt die Titel Schrift Farbe zur�ck
		__declspec( dllexport ) int getTSGr��e() const; // gibt die Titel Schrift Gr��e zur�ck
		// -- Titel Hintergrund -- 
		__declspec( dllexport ) int getTBgFarbe() const; // gibt die Titel Hintergrund Farbe zur�ck
		// -- Titel AlphaFeld -- 
		__declspec( dllexport ) AlphaFeld *getTAlphaFeld() const; // gibt das Titel AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zTAlphaFeld() const;
		__declspec( dllexport ) int getTAfFarbe() const; // gibt die Farbe des Titel AlphaFeldes zur�ck
		__declspec( dllexport ) int getTAfSt�rke() const; // gibt die St�rke des TitelAlphaFeldes zur�ck
		// -- Titel Hintergrund Bild -- 
		__declspec( dllexport ) Bild *getTBgBild() const; // gibt das Titel Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zTBgBild() const;
		// -- Titel Rahmen -- 
		__declspec( dllexport ) LRahmen *getTRahmen() const; // gibt den Titel Rahmen zur�ck
		__declspec( dllexport ) LRahmen *zTRahmen() const;
		__declspec( dllexport ) int getTRFarbe() const; // gibt die Farbe des Titel Rahmens zur�ck
		__declspec( dllexport ) int getTRBreite() const; // gibt die Breite des Titel Rahmens zur�ck
		// -- K�rper Hintergrund -- 
		__declspec( dllexport ) int getKBgFarbe() const; // gibt die K�rper Hintergrund Farbe zur�ck
		// -- K�rper Hintergrund Bild -- 
		__declspec( dllexport ) Bild *getKBgBild() const; // gibt das K�rper Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zKBgBild() const;
		// -- K�rper AlphaFeld -- 
		__declspec( dllexport ) AlphaFeld *getKAlphaFeld() const; // gibt das K�rper AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zKAlphaFeld() const;
		__declspec( dllexport ) int getKAfFarbe() const; // gibt die Farbe des K�rper AlphaFeldes zur�ck
		__declspec( dllexport ) int getKAfSt�rke() const; // gibt die St�rke des K�rper AlphaFeldes zur�ck
		// -- Schlie�en Hintergrund -- 
		__declspec( dllexport ) int getSBgFarbe() const; // gibt die Schlie� Hintergrund Farbe zur�ck
		// -- Schlie�en Hintergrund Bild -- 
		__declspec( dllexport ) Bild *getSBgBild() const; // gibt das Schlie� Hintergrund Bild zur�ck
		__declspec( dllexport ) Bild *zSBgBild() const;
		// -- Schlie�en AlphaFeld -- 
		__declspec( dllexport ) AlphaFeld *getSAlphaFeld() const; // gibt das Schlie� AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zSAlphaFeld() const;
		__declspec( dllexport ) int getSAfFarbe() const; // gibt die Farbe des Schlie� AlphaFeldes zur�ck
		__declspec( dllexport ) int getSAfSt�rke() const; // gibt die St�rke des Schlie� AlphaFeldes zur�ck
		// -- Schlie�en Klick AlphaFeld -- 
		__declspec( dllexport ) AlphaFeld *getSKAlphaFeld() const; // gibt das Schlie� Klick AlphaFeld zur�ck
		__declspec( dllexport ) AlphaFeld *zSKAlphaFeld() const;
		__declspec( dllexport ) int getSKAfFarbe() const; // gibt die Farbe des Schlie� Klick AlphaFeldes zur�ck
		__declspec( dllexport ) int getSKAfSt�rke() const; // gibt die St�rke des Schlie� Klick AlphaFeldes zur�ck
		// -- min max -- 
		__declspec( dllexport ) const Punkt &getMin() const; // gibt die minimale Fenstergr��e zur�ck
		__declspec( dllexport ) const Punkt &getMax() const; // gibt die maximale Fenstergr��e zur�ck
		__declspec( dllexport ) const Punkt &getKMin() const; // gibt die minimale Fenstergr��e zur�ck
		__declspec( dllexport ) const Punkt &getKMax() const; // gibt die maximale Fenstergr��e zur�ck
		// -- scroll -- 
		__declspec( dllexport ) VScrollBar *getVScrollBar() const; // gibt die Vertikale Scroll Bar zur�ck
		__declspec( dllexport ) VScrollBar *zVScrollBar() const;
		__declspec( dllexport ) HScrollBar *getHScrollBar() const; // gibt die Horizontale Scroll Bar zur�ck
		__declspec( dllexport ) HScrollBar *zHScrollBar() const;
		// -- Members -- 
		__declspec( dllexport ) ZeichnungArray *getMembers() const; // gibt die Members zur�ck
		// -- Kopie --
		__declspec( dllexport ) Zeichnung *dublizieren() const override; // Erzeugt eine Kopie des Fensters
		// Reference Counting 
		__declspec( dllexport ) Fenster *getThis();
		__declspec( dllexport ) Fenster *release();
	};
}
#endif