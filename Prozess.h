#ifndef Prozess_H
#define Prozess_H

#include "Betriebssystem.h"

#ifdef WIN32
#pragma comment( lib, "Psapi.lib" )
#endif

namespace Framework
{
#ifdef WIN32
	struct MemoryInfo; // aus dieser Datei
#endif
	class Prozess; // aus dieser Datei

#ifdef WIN32
	struct MemoryInfo
	{
		unsigned long ausgelagerteFehler;
		__int64 h�chsteAusgelagerterSpeicher;
		__int64 ausgelagerterSpeicher;
		__int64 h�chsterAusgelagerterPool;
		__int64 ausgelagerterPool;
		__int64 h�chsterNichtAusgelagerterPool;
		__int64 nichtAusgelagerterPool;
		__int64 vorreservierterSpeicher;
		__int64 h�chsterVorreservierterSpeicher;
	};
#endif
    // Diese Klasse findet informationen �ber einen laufenden Prozess heraus (CPU, MEM)
    // Bei Ubuntu immer der eigene Prozess
	class Prozess
	{
	private:
#ifdef WIN32
		int numProcessors;
		ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
		void *pHandle;
#endif
		int ref;

	public:
		// Konstruktor 
		__declspec( dllexport ) Prozess();
		// nicht constant 
#ifdef WIN32
        // Setzt den Prozess, der �berwacht werden soll (Nur f�r Windows)
		__declspec( dllexport ) void setProcess( void *pHandle );
#endif
		// Gibt den CPU verbrauch des Prozesses zur�ck
		__declspec( dllexport ) double getCPU() const;
        // Gibt den Speicherverbrauch des Prozesses zur�ck
		__declspec( dllexport ) __int64 getMem() const;
#ifdef WIN32
        // Gibt detailierte Informationen �ber den Speicherverbrauch des Prozesses zur�ck (Nur f�r Windows)
		__declspec( dllexport ) MemoryInfo getMemInfo() const;
        // Gibt die Anzahl der Threads zur�ck (Nur f�r Windows)
		__declspec( dllexport ) int getThreadAnzahl() const;
#endif
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
		__declspec( dllexport ) Prozess *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
		__declspec( dllexport ) Prozess *release();
	};
}

#endif