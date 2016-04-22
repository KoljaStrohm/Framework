#ifndef Punkt_H
#define Punkt_H
//---Include---

#include "Vec2.h"

namespace Framework
{
    // ben�tigte includes
    class WFenster; // aus Fenster.h

    typedef Vec2< int > Punkt; // Speichert die ganzzahligen Koordinaten eines Punktes


#ifdef WIN32
    // Gibt die Gr��e des Bildschirms zur�ck
    __declspec( dllexport ) Punkt BildschirmGr��e();
    // Giebt die Mitte des Bildschirms zur�ck
    __declspec( dllexport ) Punkt Bildschirmmitte();
    // Giebt einen Punkt zur�ck, der als Fensterposition verwendet werden kann um das Fenster zu zentrieren
    //  f: Das Fenster, welches Zentriert werden soll
    __declspec( dllexport ) Punkt Bildschirmmitte( WFenster *f );
#endif
    // Pr�ft, ob ein Punkt weiter rechts unten ist als ein anderer
    //  return: (true), wenn der linke Punkt weiter rechts und weiter unten ist. (false) sonnst
    __declspec( dllexport ) bool operator >( const Punkt &a, const Punkt &b );
    // Pr�ft, ob ein Punkt weiter links obem ist als ein anderer
    //  return: (true), wenn der linke Punkt weiter links und weiter oben ist. (false) sonnst
    __declspec( dllexport ) bool operator <( const Punkt &a, const Punkt &b );
    // Pr�ft, ob ein Punkt weiter links obem ist als ein anderer
    //  return: (true), wenn der linke Punkt weiter links und weiter oben oder gleich ist. (false) sonnst
    __declspec( dllexport ) inline bool operator <=( const Punkt &a, const Punkt &b );
    // Pr�ft, ob ein Punkt weiter rechts unten ist als ein anderer
    //  return: (true), wenn der linke Punkt weiter rechts und weiter unten oder gleich ist. (false) sonnst
    __declspec( dllexport ) inline bool operator >=( const Punkt &a, const Punkt &b );
}
#endif