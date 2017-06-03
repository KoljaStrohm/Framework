#pragma once

#include "Critical.h"

namespace Framework
{
    class Zeichnung3DArray; // Zeichnung3D.h
    class Zeichnung3D; // Zeichnung.h
    class Render3D; // Render3D.h
    struct MausEreignis3D; // MausEreignis.h

    // Speichert alle 3D Zeichnungen einer Szene ab
    class Welt3D
    {
    private:
        Zeichnung3D **members;
        Zeichnung3D **membersAlpha;
        float *distSq;
        float *distSqSort;
        Zeichnung3D **alphaVS;
        Zeichnung3D **elementsSort;
        int arraySize;
        int arraySizeAlpha;
        bool rend;
        bool upd;
        Critical cs;
        int ref;

    public:
        // Konstructor
        __declspec( dllexport ) Welt3D();
        // Destruktor
        __declspec( dllexport ) virtual ~Welt3D();
        // F�gt der Welt ein Objekt hinzu
        //  obj: Das Objekt, was hinzugef�gt werden soll
        __declspec( dllexport ) void addZeichnung( Zeichnung3D *obj );
        // Entfernt ein Objekt aus der Welt
        //  obj: Das Objekt, das entwernt werden soll
        __declspec( dllexport ) void removeZeichnung( Zeichnung3D *obj );
        // Verarbeitet ein Mausereignis
        //  me: Das Mausereignis, das verarbeitet werden soll
        __declspec( dllexport ) void doMausEreignis( MausEreignis3D &me );
        // Verarbeitet die vergangene Zeit
        //  tickval: Die zeit in sekunden, die seit dem letzten Aufruf der Funktion vergangen ist
        //  return: true, wenn sich das Objekt ver�ndert hat, false sonnst.
        __declspec( dllexport ) virtual bool tick( double tickval );
        // Zeichnet einen ausschnitt der Welt
        //  zRObj: Enth�llt alle Werkzeuge, die zum Zeichnen verwendet werden
        __declspec( dllexport ) void render( Render3D *zRObj );
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Welt3D *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Welt3D *release();
    };
}