#ifndef Knopf_H
#define Knopf_H

#include "TextFeld.h"

namespace Framework
{
    class TextFeld; // TextFeld.h
    class AlphaFeld; // AlphaFeld.h
    class Text; // Text.h
    class Schrift; // Schrift.h
    class LRahmen; // Rahmen.h
    class LTDBDatei; // Dateisystem.h
    class Knopf; // aus dieser Datei
    class KontrollKnopf; // aus dieser Datei

    // Eine Zeichnung des 2D GUI Frameworks, die einen Knopf zeichnet, den der Benutzer dr�cken kann
    class Knopf : public TextFeld
    {
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 MehrfarbigText = 0x0010000; // Legt fest, ob der Text des Knopfes mehrere Farben haben darf
            const static __int64 KlickFarbe = 0x0020000; // Legt fest, ob der Knopf w�hrend er gedr�ckt wird eine Hintergrund Farbe hat
            const static __int64 KlickBild = 0x0040000; // Legt fest, ob der Knopf w�hrend er gedr�ckt wird ein Bild als Hintergrund hat
            const static __int64 KlickAlpha = 0x0080000; // Legt fest, ob der Knopf w�hrend er gedr�ckt wird f�r das Zeichnen des Hintergrundes alpha blending verwendet
            const static __int64 KlickBuffer = 0x0100000; // Legt fest, ob der Knopf w�hrend er gedr�ckt wird einen Farb�bergang besitzt

            const static __int64 Normal = Sichtbar | Erlaubt | Rahmen | Buffered | MehrfarbigText | KlickBuffer; // Vereint di Flags Sichtbar, Erlaubt, Rahmen, Buffered, MehrfarbigText, KlickBuffer
        };

    private:
        int klickFarbe;
        Bild *klickBild;
        AlphaFeld *klickBuffer;
        int klickIndex;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) Knopf();
        // Destruktor 
        __declspec( dllexport ) virtual ~Knopf();
        // Setzt die Farbe, die als Hintergrund verwendet wird, wenn der Knopf gedr�ckt wird
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKlickFarbe( int fc );
        // Setzt das Hintergrund Bild durch kopieren, das verwendet wird, wenn der Knopf gedr�ckt wird
        //  bild: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setKlickBild( Bild *bild );
        // Setzt einen Zeiger auf das Hintergrund Bild, das verwendet wird, wenn der Knopf gedr�ckt wird
        //  bild: Das neue Bild
        __declspec( dllexport ) void setKlickBildZ( Bild *bild );
        // Setzt einen Zeiger auf den Farb�bergang, der verwendet wird, wenn der Knopf gedr�ckt wird
        //  af: Der neue Farb�bergang
        __declspec( dllexport ) void setKBZ( AlphaFeld *af );
        // Setzt die St�rke des Farb�bergangs, der verwendet wird, wenn der Knopf gedr�ckt wird
        //  st: Die St�rke
        __declspec( dllexport ) void setKBStrength( int st );
        // Setzt die Farbe des Farb�bergangs, der verwendet wird, wenn der Knopf gedr�ckt wird
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKBFarbe( int fc );
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Zeichnet das Objekt nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) int getKlickFarbe() const;
        // Gibt das Hintergrund Bild zur�ck, das verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) Bild *getKlickBild() const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) Bild *zKlickBild() const;
        // Gibt den Farb�bergang zur�ck, der verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) AlphaFeld *getKB() const;
        // Gibt den Farb�bergang ohne erh�hten Reference Counter zur�ck, der verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) AlphaFeld *zKB() const;
        // Gibt die Farbe des Farb�bergangs im A8R8G8B8 Format zur�ck, der verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) int getKBFarbe() const;
        // Gibt die St�rke des Farb�bergangs zur�ck, der verwendet wird, wenn der Knopf gedr�ckt wird
        __declspec( dllexport ) int getKBStrength() const;
        // Kopiert den Knopf, so das er ohne auswirkungen auf das Original ver�ndert werden kann
        __declspec( dllexport ) Zeichnung *dublizieren() const override;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Knopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Knopf *release();
    };

    // Eine Zeichnung des 2D GUI Frameworks, die einen Ausw�hlbares K�stchen mit beschriftung zeichnet
    class KontrollKnopf : public ZeichnungHintergrund
    {
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 Selected = 0x00004; // Legt fest, ob das K�stchen ausgew�hlt ist

            const static __int64 MehrfarbigText = 0x001000; // Legt Fest, ob der Beschriftungs Text mehrfarbig sein kann
            const static __int64 KlickFarbe = 0x002000; // Legt fest, ob das K�stchen w�hrend ed gedr�ckt wird eine Hintergrund Farbe hat
            const static __int64 KlickBild = 0x004000; // Legt fest, ob das K�stchen beim Klicken ein Hintergrund Bild hat
            const static __int64 KlickAlpha = 0x008000; // Legt fest, ob f�r den Hintergrund des K�stchens beim Klicken alpha blending verwendet wird
            const static __int64 KlickBuffer = 0x010000; // Legt fest, ob das K�stchen beim Klicken einen Farb�bergang hat
            const static __int64 SelectFarbe = 0x020000; // Legt fest, ob das K�stchen w�rhend es ausgew�hlt ist eine Hintergrund Farbe hat
            const static __int64 SelectBild = 0x040000; // Legt fest, ob das K�stchen w�rhend es ausgew�hlt ist ein Hintergrund Bild hat
            const static __int64 SelectAlpha = 0x080000; // Legt fest, ob das K�stchen w�rhend es ausgew�hlt ist f�r den Hintergrund alpha blending verwendet
            const static __int64 SelectBuffer = 0x100000; // Legt fest, ob das K�stchen w�rhend es ausgew�hlt ist einen Farb�bergang hat
            const static __int64 SelectText = 0x200000; // Legt fest, ob das K�stchen w�rhend es ausgew�hlt ist eine andere Beschriftung hat
            const static __int64 MehrzeiligText = 0x400000; // Legt fest, ob das K�stchen eine Mehrzeilige Beschriftung haben kann

            const static __int64 MausKlick = 0x800000; // Legt fest, ob gerade mit der Maus auf das K�stchen geklickt wird. (Wird vom K�stchen selbst verwaltet)

            const static __int64 Normal = Sichtbar | Erlaubt | Rahmen | KlickBuffer; // Vereint die Flags Sichtbar, Erlaubt, Rahmen, KlickBuffer
        };

    private:
        Text *txt;
        Text *sTxt;
        int sBgF;
        int kBgF;
        Bild *sBgB;
        Bild *kBgB;
        AlphaFeld *sAf;
        AlphaFeld *kAf;
        Bild *kasten;
        Bild *sKasten;
        Schrift *schrift;
        int sF;
        int sGr;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) KontrollKnopf();
        // Destruktor 
        __declspec( dllexport ) virtual ~KontrollKnopf();
        // Setzt den Zeiger auf den Beschriftungs Text
        //  txt: Der Text
        __declspec( dllexport ) void setTextZ( Text *txt );
        // Setzt den Beschriftungs Text
        //  txt: Der Text
        __declspec( dllexport ) void setText( Text *txt );
        // Setzt den Beschriftungs Text
        //  txt: Der Text
        __declspec( dllexport ) void setText( const char *txt );
        // Setzt den Zeiger auf den Beschriftungs Text, der angezeigt wird, w�hrend das K�stchen ausgew�hlt ist
        //  txt: Der Text
        __declspec( dllexport ) void setSTextZ( Text *txt );
        // Setzt den Beschriftungs Text, der angezeigt wird, w�hrend das K�stchen ausgew�hlt ist
        //  txt: Der Text
        __declspec( dllexport ) void setSText( Text *txt );
        // Setzt den Beschriftungs Text, der angezeigt wird, w�hrend das K�stchen ausgew�hlt ist
        //  txt: Der Text
        __declspec( dllexport ) void setSText( const char *txt );
        // Setzt die Schrift, die f�r die Beschriftung verwendet werden soll
        //  schrift: Die Schrift
        __declspec( dllexport ) void setSchriftZ( Schrift *schrift );
        // Setzt die Farbe der Schrift, die f�r die Beschriftung verwendet werden soll
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSFarbe( int f );
        // Setzt die Gr��e der Schrift, die f�r die Beschriftung verwendet werden soll
        //  f: Die H�he einer Zeile in Pixeln
        __declspec( dllexport ) void setSSize( int gr );
        // Setzt die Hintergrund Farbe, die verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSBgFarbe( int f );
        // Setzt die Hintergrund Farbe, die verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKBgFarbe( int f );
        // Setzt einen Zeiger auf das Hintergrund Bild, das verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  b: Das Bild
        __declspec( dllexport ) void setSBgBildZ( Bild *b );
        // Setzt das Hintergrund Bild durch kopieren, das verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  b: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setSBgBild( Bild *b );
        // Setzt einen Zeiger auf das Hintergrund Bild, das verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  b: Das Bild
        __declspec( dllexport ) void setKBgBildZ( Bild *b );
        // Setzt das Hintergrund Bild durch kopieren, das verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  b: Das Bild, das kopiert werden soll
        __declspec( dllexport ) void setKBgBild( Bild *b );
        // Setzt einen Zeiger auf den Farb�bergang, der verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setSAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs, der verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setSAFFarbe( int f );
        // Setzt die St�rke des Farb�bergangs, der verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        //  st: Die St�rke
        __declspec( dllexport ) void setSAFStrength( int st );
        // Setzt einen Zeiger auf den Farb�bergang, der verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setKAlphaFeldZ( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs, der verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setKAFFarbe( int f );
        // Setzt die St�rke des Farb�bergangs, der verwendet wird, w�hrend auf das K�stchen geklickt wird
        //  st: Die St�rke
        __declspec( dllexport ) void setKAFStrength( int st );
        // L�dt die Bilder "kasten.gif" und "skasten.gif" aus einer LTDB Datei
        // Das Bild kasten.gif wird gezeichnet, wenn das K�stchen nicht ausgew�hlt ist. Das Bild skasten.gif wird gezeichnet, wenn das K�stchen ausgew�hlt wird
        //  zDat: Die LTDB Datei
        __declspec( dllexport ) void loadData( LTDBDatei *zDat );
        // L�dt die Bilder "kasten.gif" und "skasten.gif" aus einer LTDB Datei
        // Das Bild kasten.gif wird gezeichnet, wenn das K�stchen nicht ausgew�hlt ist. Das Bild skasten.gif wird gezeichnet, wenn das K�stchen ausgew�hlt wird
        //  ltdb: Der Pfad zur LTDB Datei
        __declspec( dllexport ) void loadData( const char *ltdb );
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Zeichnet das Objekt nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt die beschriftung zur�ck
        __declspec( dllexport ) Text *getText() const;
        // Gibt die beschriftung ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Text *zText() const;
        // Gibt die beschriftung zur�ck, die verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) Text *getSText() const;
        // Gibt die beschriftung ohne erh�hten Reference Counter zur�ck, die verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) Text *zSText() const;
        // Gibt die verwendete Schrift zur�ck
        __declspec( dllexport ) Schrift *getSchrift() const;
        // Gibt die verwendete Schrift ohne Reference Counter zur�ck
        __declspec( dllexport ) Schrift *zSchrift() const;
        // Gibt die Schrift Farbe im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getSFarbe() const;
        // Gibt die Schrift Gr��e zur�ck
        __declspec( dllexport ) int getSSize() const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) int getSBgFarbe() const;
        // Gibt die Hintergrund Farbe im A8R8G8B8 Format zur�ck, die verwendet wird, w�hrend auf das K�stchen geklickt wird
        __declspec( dllexport ) int getKBgFarbe() const;
        // Gibt das Hintergrund Bild zur�ck, das verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) Bild *getSBgBild() const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) Bild *zSBgBild() const;
        // Gibt das Hintergrund Bild zur�ck, das verwendet wird, w�hrend auf das K�stchen geklickt wird
        __declspec( dllexport ) Bild *getKBgBild() const;
        // Gibt das Hintergrund Bild ohne erh�hten Reference Counter zur�ck, das verwendet wird, w�hrend auf das K�stchen geklickt wird
        __declspec( dllexport ) Bild *zKBgBild() const;
        // Gibt den Farb�bergang zur�ck, der verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) AlphaFeld *getSAlphaFeld() const;
        // Gibt den Farb�bergang ohne erh�hten Reference COunter zur�ck, der verwendet wird, w�hrend das K�stchen ausgew�hlt ist
        __declspec( dllexport ) AlphaFeld *zSAlphaFeld() const;
        // Gibt den Farb�bergang zur�ck, der verwendet wird, w�hrend auf das K�stchen geklickt wird
        __declspec( dllexport ) AlphaFeld *getKAlphaFeld() const;
        // Gibt den Farb�bergang ohne erh�hten Reference COunter zur�ck, der verwendet wird, w�hrend auf das K�stchen geklickt wird
        __declspec( dllexport ) AlphaFeld *zKAlphaFeld() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) KontrollKnopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) KontrollKnopf *release();
    };
}

#endif