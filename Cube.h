#pragma once

#include "Model3D.h"

namespace Framework
{
    class Bild;

    enum CubeSeite
    {
        VORNE, 
        HINTEN, 
        RECHTS, 
        LINKS, 
        OBEN, 
        UNTEN
    };

    // Ein Model eines W�rfels
    class Cube : public Model3D
    {
    public:
        // Konstruktor
        //  size: Die Gr��e des W�rfels
        __declspec( dllexport ) Cube( float size );
        // Setzt die Textur des W�rfels, so dass sie an allen Seiten gleich ist
        //  textur: Die Textur als Bild
        __declspec( dllexport ) void setTextur( Bild *textur );
        // Setzt die Textur des W�rfels, so dass sie an allen Seiten gleich ist
        //  id: Die id der Textur. Sie muss im Textur Register des Frameworks registriert sein
        __declspec( dllexport ) void setTextur( int id );
        // Setzt die Textur von einer bestimmten Seite des W�rfels
        //  textur: Die Textur als Bild
        //  s: Die Seite, die gesetzt werden soll
        __declspec( dllexport ) void setTextur( Bild *textur, CubeSeite s );
        // Setzt die Textur von einer bestimmten Seite des W�rfels
        //  id: Die id der Textur. Sie muss im Textur Register des Frameworks registriert sein
        //  s: Die Seite, die gesetzt werden soll
        __declspec( dllexport ) void setTextur( int id, CubeSeite s );
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Model3D *release() override;
    };
}