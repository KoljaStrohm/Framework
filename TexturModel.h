#pragma once

#include "Model3D.h"

namespace Framework
{
    class Bild; // Bild.h

    // Ein 3D Modell, das zur Darstellung einer Textur im dreidimensionalen Raum verwendet werden kann
    class TexturModel : public Model3D
    {
    public:
        // Konstruktor
        __declspec( dllexport ) TexturModel();
        // Setzt die Textur die angezeigt werden soll
        //  textur: Die Textur als Bild
        __declspec( dllexport ) void setTextur( Bild *textur );
        // Setzt die Textur die angezeigt werden soll 
        //  id: Die id der Textur. Sie muss im Textur Register des Frameworks registriert sein
        __declspec( dllexport ) void setTextur( int id );
        // Setzt die Gr��e, in der Die Textur angezeigt wird
        //  gr: Ein Vektor, der f�r x und y die breite und h�he beinhaltet
        __declspec( dllexport ) void setGr��e( Vec2< float > gr );
        // Setzt die Gr��e, in der die Textur angezeigt wird
        //  b: Die Breite, in der die Textur angezeigt wird
        //  h: Die H�he, in der die Textur angezeigt wird
        __declspec( dllexport ) void setGr��e( float b, float h );
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Model3D *release() override;
    };
}