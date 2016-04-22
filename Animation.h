#ifndef Animation_H
#define Animation_H

#include "Zeichnung.h"

namespace Framework
{
    class Bild; // Bild.h
    class LTDBDatei; // DateiSystem.h
    class InitDatei; // InitDatei.h
    class LRahmen; // Rahmen.h

    // Enth�lt alle Bilder einer Video Animation
    class Animation2DData
    {
    private:
        Bild **bilder;
        int bildAnzahl;
        int fps;
        bool wiederhohlen;
        bool transparent;
        CRITICAL_SECTION cs;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Animation2DData();
        // Destruktor
        __declspec( dllexport ) ~Animation2DData();
        // Dies ist notwendig, falls mehrere Threads gleichzeitig dieses Objekt benutzen.
        // Wenn lock() von zwei threads aufgerufen wird, wartet der letzte so lange, bis der erste unlock() aufgerufen hat.
        __declspec( dllexport ) void lock();
        // Dies ist notwendig, falls mehrere Threads gleichzeitig dieses Objekt benutzen.
        // Wenn lock() von zwei threads aufgerufen wird, wartet der letzte so lange, bis der erste unlock() aufgerufen hat.
        __declspec( dllexport ) void unlock();
        // L�dt alle Bilder aus einer InitDatei ein. Auch die Werte 'fps', 'wiederhohlen' (true, false), 'transparent' (true, false) werden interpretiert.
        // Die Bilder m�ssen in der richtiegen Reihenfolge in der Datei stehen. Der Name der Werte ist egal undder Wert ist der Pfad zur ltdb Datei mit /bildname hinten drann
        // Beispiel: fps=30
        //           x=a.ltdb\aaaa.jpg
        //           y=a.ltdb\aaab.jpg
        //  datei: Die bereits eingelesene InitDatei
        __declspec( dllexport ) void ladeAnimation( InitDatei *datei );
        // L�dt alle Bilder aus einer LTDB Datei der reihenfolge nach ein, in der sie gespeichert sind.
        //  datei: Die LTDB Datei
        __declspec( dllexport ) void ladeAnimation( LTDBDatei *datei );
        // Setzt die Bilder pro Sekunde der Video Animation
        //  fps: Die Anzahl an Bildern pro Sekunde
        __declspec( dllexport ) void setFPS( int fps );
        // Legt fest, ob die Animation sich wiederhohlt, wenn sie am ende angelangt ist
        //  wh: 1, wenn sich die Animation wiederhohlen soll
        __declspec( dllexport ) void setWiederhohlend( bool wh );
        // Legt fest, ob beim Zeichnen der Bilder Alphablending benutzt werden soll
        //  trp: 1, wenn Alphablending benutzt werden soll
        __declspec( dllexport ) void setTransparent( bool trp );
        // L�scht alle Bilder aus der Animation und setzt alle Werte auf die Standartwerte zur�ck
        __declspec( dllexport ) void reset();
        // Gibt ein Bestimmtes Bild der Animation zur�ck
        //  i: Der Index des Bildes
        __declspec( dllexport ) Bild *getBild( int i ) const;
        // Gibt ein Bestimmtes Bild der Animation ohne erh�hten Reference Counter zur�ck
        //  i: Der Index des Bildes
        __declspec( dllexport ) Bild *zBild( int i ) const;
        // Gibt die Anzahl der Bilder in der Animation zur�ck
        __declspec( dllexport ) int getBildAnzahl() const;
        // Gibt die Anzahl an Bildern pro Sekunde zur�ck
        __declspec( dllexport ) int getFPS() const;
        // Gibt zur�ck, ob sich die Animation wiederhohlt, wenn sie beim letzten Bild angelangt ist
        __declspec( dllexport ) bool istWiederhohlend() const;
        // Gibt zur�ck, ob beim Zeichnen der Bilder Alphablending benutzt wird
        __declspec( dllexport ) bool istTransparent() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Animation2DData *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Animation2DData *release();
    };

    // Eine Zeichnung, die eine Video Animation zeichnet
    class Animation2D : public Zeichnung
    {
    private:
        Animation2DData *data;
        int jetzt;
        double ausgleich;
        unsigned char alpha;
        unsigned char maxAlpha;
        bool rahmen;
        LRahmen *ram;
        int aps;
        bool sichtbar;
        bool rend;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Animation2D();
        // Destruktor
        __declspec( dllexport ) ~Animation2D();
        // Legt fest, ob ein Rahmen um die Animation gezeichnet werden soll
        //  ram: 1, wenn ein Rahmen gezeichnet werden soll
        __declspec( dllexport ) void setRahmen( bool ram );
        // Setzt einen Zeiger auf den verfenteten Rahmen
        //  ram: Der Rahmen
        __declspec( dllexport ) void setRahmenZ( LRahmen *ram );
        // Setzt die Breite des Rahmens
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setRahmenBreite( int br );
        // Setzt die Farbe des Rahmens
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setRahmenFarbe( int fc );
        // Setzt die Animation, die Angezeigt werden soll
        //  data: Die Animationsdaten
        __declspec( dllexport ) void setAnimationDataZ( Animation2DData *data );
        // Setzt die Transparenz der gesammten Animation
        //  alpha: Die Transparenz
        __declspec( dllexport ) void setAlphaMaske( unsigned char alpha );
        // Setzt die Geschwindigkeit, in der die Animation ein und ausgeblendet wird
        //  aps: Alpha pro sekunde
        __declspec( dllexport ) void setAPS( int aps );
        // Setzt die Sichtbarkeit der Animation
        //  sichtbar: 1, wenn die Animation eingeblendet werden soll. 0, wenn sie ausgeblendet werden soll
        __declspec( dllexport ) void setSichtbar( bool sichtbar );
        // Verarbeitet die Zeit, die seit dem letzten aufruf dieser Funktion vergangen ist
        //  zeit: Die vergangene Zeit in Sekunden
        __declspec( dllexport ) bool tick( double zeit ) override;
        // Zeichnet die Animation in ein bestimmtes Bild
        //  zRObj: Das Bild, in das gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt die Animationsdaten zur�ck
        __declspec( dllexport ) Animation2DData *getAnimationData() const;
        // Gibt die Animationsdaten ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Animation2DData *zAnimationData() const;
        // Gibt zur�ck ob die Animation sichtbar ist
        __declspec( dllexport ) bool istSichtbar() const;
        // Gibt den Index des aktuell angezeigten Bildes zur�ck
        __declspec( dllexport ) int getJetzt() const;
        // Gibt die Transparenz der Animation zur�ck
        __declspec( dllexport ) unsigned char getAlphaMaske() const;
        // Gibt zur�ck, ob ein Rahmen um die Animation gezeichnet wird
        __declspec( dllexport ) bool hatRahmen() const;
        // Gibt den Rahmen der Animation zur�ck
        __declspec( dllexport ) LRahmen *getRahmen() const;
        // Gibt den Rahmen der Animation ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) LRahmen *zRahmen() const;
        // Gibt die Breite des Rahmens in Pixeln zur�ck
        __declspec( dllexport ) int getRahmenBreite() const;
        // Gibt die Farbe des Rahmens im A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getRahmenFarbe() const;
        // Kopiert die Animation, so dass sie ohne auswirkungen auf das Original ver�ndert werden kann
        __declspec( dllexport ) Zeichnung *dublizieren() const override;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Animation2D *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Animation2D *release();
    };
}

#endif