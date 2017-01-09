#ifndef InitDatei_H
#define InitDatei_H

#include "Array.h"

namespace Framework
{
    class Text; // Text.h

    // Verwaltet Initialisierungsdateien in denen Bestimmte Variablen im Format name=Wert gespeichert sind
    class InitDatei
    {
    private:
        Text *pfad;
        int feldAnzahl;
        RCArray< Text > *name;
        RCArray< Text > *wert;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) InitDatei();
        // Konstruktor
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) InitDatei( Text *pfad );
        // Konstruktor
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) InitDatei( const char *pfad );
        // Destruktor
        __declspec( dllexport ) ~InitDatei();
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) void setPfad( Text *pfad );
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) void setPfad( const char *pfad );
        // L�hdt die Werte aus der Datei
        //  return: 1, falls das Laden erfolgreich war. 0, wenn ein fehler aufgetreten ist.
        __declspec( dllexport ) bool laden();
        // F�gt der Datei einen Wert hinzu
        //  name: Der Name des Wertes
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert erfolgreich hinzugef�gt wurde
        __declspec( dllexport ) bool addWert( Text *name, Text *wert );
        // F�gt der Datei einen Wert hinzu
        //  name: Der Name des Wertes
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert erfolgreich hinzugef�gt wurde
        __declspec( dllexport ) bool addWert( const char *name, const char *wert );
        // �ndert einen bestimmten Wert
        //  name: Der Name des Wertes
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich ge�ndert werden konnte
        __declspec( dllexport ) bool setWert( Text *name, Text *wert );
        // �ndert einen bestimmten Wert
        //  name: Der Name des Wertes
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich ge�ndert werden konnte
        __declspec( dllexport ) bool setWert( const char *name, const char *wert );
        // �ndert einen bestimmten Wert
        //  num: Der Index des Wertes der ge�ndert werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich ge�ndert werden konnte
        __declspec( dllexport ) bool setWert( int num, Text *wert );
        // �ndert einen bestimmten Wert
        //  num: Der Index des Wertes der ge�ndert werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich ge�ndert werden konnte
        __declspec( dllexport ) bool setWert( int num, const char *wert );
        // L�scht einen bestimmten Wert
        //  name: Der Name des Wertes, der gel�scht werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich gel�scht werden konnte
        __declspec( dllexport ) bool removeWert( Text *name );
        // L�scht einen bestimmten Wert
        //  name: Der Name des Wertes, der gel�scht werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich gel�scht werden konnte
        __declspec( dllexport ) bool removeWert( const char *name );
        // L�scht einen bestimmten Wert
        //  num: Der Index des Wertes der gel�scht werden soll
        //  return: 1, falls der Wert vorhanden war und erfolgreich gel�scht werden konnte
        __declspec( dllexport ) bool removeWert( int num );
        // L�scht alle Werte aus der Datei
        __declspec( dllexport ) void removeAlle();
        // Speichert alle Werte in der Datei
        //  return: 1, falls das Speichern erfolgreich war
        __declspec( dllexport ) bool speichern();
        // Gibt die Anzahl der gespeicherten Werte zur�ck
        __declspec( dllexport ) int getWertAnzahl() const;
        // �berpr�ft, ob ein bestimmter Wert existiert
        //  name: Der Name, nach dem gesucht werden soll
        //  return: 1, falls der Wert gefunden wurde
        __declspec( dllexport ) bool wertExistiert( Text *name );
        // �berpr�ft, ob ein bestimmter Wert existiert
        //  name: Der Name, nach dem gesucht werden soll
        //  return: 1, falls der Wert gefunden wurde
        __declspec( dllexport ) bool wertExistiert( const char *name );
        // Gibt den Index eines Bestimmten Wertes zur�ck
        //  name: Der Name des Wertes, nach dem gesucht werden soll
        //  return: -1, falls der Wert nicht gefunden wurde. Der Index des Wertes.
        __declspec( dllexport ) int getWertNummer( Text *name );
        // Gibt den Index eines Bestimmten Wertes zur�ck
        //  name: Der Name des Wertes, nach dem gesucht werden soll
        //  return: -1, falls der Wert nicht gefunden wurde. Der Index des Wertes.
        __declspec( dllexport ) int getWertNummer( const char *name );
        // Gibt einen bestimmten Wert zur�ck
        //  name: Der Name des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde.
        __declspec( dllexport ) Text *getWert( Text *name );
        // Gibt einen bestimmten Wert zur�ck
        //  name: Der Name des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde.
        __declspec( dllexport ) Text *getWert( const char *name );
        // Gibt einen bestimmten Wert zur�ck
        //  num: Der Index des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde.
        __declspec( dllexport ) Text *getWert( int num );
        // Gibt einen bestimmten Wert zur�ck
        //  name: Der Name des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde. Der Wert ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zWert( Text *name );
        // Gibt einen bestimmten Wert zur�ck
        //  name: Der Name des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde. Der Wert ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zWert( const char *name );
        // Gibt einen bestimmten Wert zur�ck
        //  num: Der Index des Wertes, der zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde. Der Wert ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zWert( int num );
        // Gibt den Namen eines bestimmten Wertes zur�ck
        //  num: Der Index des Wertes, dessen Namen zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde.
        __declspec( dllexport ) Text *getName( int num );
        // Gibt den Namen eines bestimmten Wertes zur�ck
        //  num: Der Index des Wertes, dessen Namen zur�ckgegeben werden soll
        //  return: 0, falls der Wert nicht gefunden wurde. Der Name ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zName( int num );
        // Gibt den Pfad zur Datei zur�ck
        __declspec( dllexport ) Text *getPfad() const;
        // Gibt den Pfad zur Datei ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Text *zPfad() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) InitDatei *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) InitDatei *release();
    };
}

#endif