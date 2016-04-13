#ifndef Globals_H
#define Globals_H

#include "Punkt.h"

#ifndef Global
#define Global extern
#endif

namespace Framework
{
	class Maus; // Maus.h
	class WFensterArray; // Fenster.h
    class Thread; // Thread.h
    class ThreadRegister; // Thread.h
    class Model3DList; // Model3DList.h
    class TexturList; // TexturList.h

	Global WFensterArray WFensterA;
	Global bool MausTrack;
	Global bool MausStand[ 3 ];
	Global bool TastenStand[ 255 ];
	Global Maus MausZeiger;
	Global bool istInitialisiert;
	Global bool msgExit;
	Global Punkt mausPos;
    Global ThreadRegister *thRegister;
    Global Model3DList *m3dRegister;
    Global TexturList *texturRegister;

    // Gibt die Koordinaten der Maus auf dem Bildschirm zur�ck
	__declspec( dllexport ) const Punkt &getMausPos();
    // Gibt zur�ck, ob eine Taste der Maus momentan gedr�ckt wird
    //  taste: Die Taste, die gepr�ft werden soll
    // Beispiel: getMausStand( M_Links ); (Ben�tigt include <MausEreignis.h>
	__declspec( dllexport ) bool getMausStand( int taste );
    // Gibt zur�ck, ob eine Taste auf der tastatur momentan gedr�ckt wird
    //  taste: Die Taste, die �berpr�ft werden soll
    // Beispiel: getTastenStand( T_Enter ); (Ben�togt include <TastaturEreignis.h>
	__declspec( dllexport ) bool getTastenStand( unsigned char taste );
    // Legt fest, ob eine Taste auf der tastatur momentan gedr�ckt wird
    // Der Tastenstand wird vom Framework selbst verwaltet und muss nicht mit dieser Funktion gesetzt werden
    //  taste: Die Taste, deren Status gesetzt werden soll
    //  st: Ob die Taste momentan gedr�ckt wird. (true), wenn ja. (false) sonnst.
	__declspec( dllexport ) void setTastenStand( unsigned char taste, bool st );
    // Initialisiert das Framework
    // Wird in der (WinMain) des Frameworks automatisch aufgerufen
	__declspec( dllexport ) void initFramework();
    // Gibt den duch (initFramework) benutzten Arbeitsspeicher wieder frei
    // Wird in der (WinMain) des Frameworks automatisch aufgerufen
	__declspec( dllexport ) void releaseFramework();
    // �berpr�ft, ob ein bestimmter Zeiger auf ein G�ltiges Thread Objekt zeigt
    //  t: Der zeiger, der �berpr�ft werden soll
    //  return: 1, falls der Zeiger in Ordnung ist. 0, falls der Zeiger auf kein existentes Thread Objekt zeigt
    __declspec( dllexport ) bool istThreadOk( Thread *t );
    // Gibt das Model3DData Register des Frameworks ohne erh�hten reference Counter zur�ck
    __declspec( dllexport ) Model3DList *zM3DRegister();
    // Gibt das Textur Register des Frameworks ohne erh�hten reference Counter zur�ck
    __declspec( dllexport ) TexturList *zTexturRegister();
}

#endif