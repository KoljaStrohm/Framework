#ifndef Thread_H
#define Thread_H

#include "Array.h"

namespace Framework
{
    class Thread;

    // Ein neuer Thread wie die Thread Klasse aus Java
    class Thread
    {
    protected:
#ifdef WIN32
        void *threadHandle;
        unsigned long threadId;
#else
        pthread_t threadHandle;
#endif
        bool run;

    public:
        // Konstruktor 
        __declspec( dllexport ) Thread();
        // Destruktor 
        __declspec( dllexport ) ~Thread();
        // Startet den neuen Thread 
        __declspec( dllexport ) void start();
#ifdef WIN32
        // Pausiert den Thread (Nur f�r Windows)
        __declspec( dllexport ) void pause();
        // Setzt den Thread Fort (Nur f�r Windows)
        __declspec( dllexport ) void fortsetzen();
#endif
        // Beendet den Thread
        __declspec( dllexport ) void ende();
        // Diese Funktion wird von dem neuen Thread ausgef�hrt.
        __declspec( dllexport ) virtual void thread();
        // Diese Funktion wird eufgerufen, nachdem die thread Funktion zuende ist
        __declspec( dllexport ) virtual void threadEnd();
        // pr�ft, ob der Thrad aktiv ist
        // return: true, falls der Thread l�uft. 
        //         false, wenn der Thread beendet, pausiert oder noch nicht gestartet wurde.
        __declspec( dllexport ) bool l�uft() const;
        // wartet zeit lang auf den Thread
        // zeit: Die Zeit, die auf den Thread gewartet werden soll. 1000 = 1 Sekunde
        __declspec( dllexport ) int warteAufThread( int zeit ) const;
#ifdef WIN32
        // Gibt ein Handle auf den Thread zur�ck (Nur f�r Windows)
        __declspec( dllexport ) void *getThreadHandle() const;
#endif
    };

#ifdef WIN32
    // Diese Funktion wird fon der Thread Klasse benutzt um einen thread zu starten
    __declspec( dllexport ) unsigned long __stdcall threadStart( void *param );
#else
    // Diese Funktion wird fon der Thread Klasse benutzt um einen thread zu starten
    void *threadStart( void *param ); // startet thread
#endif

    // Eine Klasse, die alle aktuell laufenden Thread Objekte speichert
    class ThreadRegister
    {
    private:
        Array< Thread* > threads;

    public:
        // F�gt einen neuen Thread hinzu
        //  t: Der Thread, der hinzugef�gt werden soll
        void add( Thread *t );
        // Entfernt einen neuen Thread
        //  t: Der Thread, der entfernt werden soll
        void remove( Thread *t );
        // �berpr�ft, ob ein Zeiger auf ein g�ltiges Thread Objekt zeigt, oder ob es schon gel�scht wurde
        //  t: Der Zeiger, der gepr�ft werden soll
        bool isThread( Thread *t ) const;
    };
}

#endif