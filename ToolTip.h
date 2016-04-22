#ifndef ToolTip_H
#define ToolTip_H

#include "TextFeld.h"

namespace Framework
{
    class Schrift; // Schrift.h
    class Bild; // Bild.h
    class AlphaFeld; // AlphaFeld.h
    class Text; // Text.h
    class LRahmen; // Rahmen.h
    struct MausEreignis; // MausEreignis.h
    class Bildschirm; // Bildschirm.h

    // Verwaltet ein automatisch ausfahrendes Fenster an der Mausposition, wo hilfe Texte eingeblendet werden
    class ToolTip : public TextFeld
    {
    public:
        class Style : public TextFeld::Style
        {};
    private:
        Punkt gr��e;
        double animationSpeed;
        double warten;
        double wartenCount;
        double tval;
        bool mausIn;
        unsigned char alpha;
        bool sichtbar;
        bool zeichnen;
        Bildschirm *bildschirm;

    public:
        // Konstruktor
        __declspec( dllexport ) ToolTip( Bildschirm *zSceen );
        // Destruktor
        __declspec( dllexport ) ~ToolTip();
        // Setzt die ausgeklappte Gr��e.
        //  breite: Die Breite in Pixeln
        //  h�he: Die H�he in Pixeln
        // Die Gr��e wird beim rendern �berschrieben
        __declspec( dllexport ) void setGr��e( int breite, int h�he );
        // Setzt die ausgeklappte Gr��e.
        //  gr: Die Gr��e in Pixeln
        // Die Gr��e wird beim rendern �berschrieben
        __declspec( dllexport ) void setGr��e( Punkt &gr );
        // Setzt die anzahl an Seunden, de gewartet wird bis der Tipp erscheint
        //  warten: Die Anzahl an Sekunden
        __declspec( dllexport ) void setWarten( double warten );
        // Legt fest, wie schnell der Tipp erscheint
        //  speed: Anzahl der Pixel, die pro Sekunde eingeblendet werden. (Standart: 250)
        __declspec( dllexport ) void setAnimationSpeed( double speed );
        // Legt Fest, ob die Maus in dem Zeichnung ist, zu dem der Tip geh�rt
        //  mausIn: 1, wenn die Maus in dem Zeichnung ist. 0 sonst
        __declspec( dllexport ) void setMausIn( bool mausIn );
        // Setzt den Counter zur�ck, der z�hlt, wann der Tipp eingeblendet wird.
        __declspec( dllexport ) void wartenReset();
        // Legt fest, das das Zeichnung, zu dem der Tip geh�rt gezeichnet wurde, so dass der Tip auch gezeichnet werden k�nnte
        __declspec( dllexport ) void setZeichnen();
        // Aktualisiert den Tip. Wird vom Framework aufgerufen
        //  tickVal: Die Zeit in sekunden, die seit dem lezten Aufruf dieser Funktion vergangen ist
        //  return: 1, wenn sich etwas ver�ndert hat und das Bild neu gezeichnet werden muss. 0 sonst
        __declspec( dllexport ) bool tick( double tickVal ) override;
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Zeichnet den Tip nach zRObj, falls er sichtbar ist und das zugeh�rige Zeichnung ebenfalls gezeichnet wurde
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt einen Zeiger auf den Bildschirm ohne erh�hten Reference Counter zur�ck, so dem der Tooltip geh�rt.
        __declspec( dllexport ) Bildschirm *zBildschirm() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) TextFeld *getThis() override;
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) TextFeld *release() override;
    };
}

#endif