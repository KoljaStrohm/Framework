#ifndef KSGTDatei_H
#define KSGTDatei_H

#include "Array.h"

namespace Framework
{
    class Text;

    // Verwaltet eine Datei in der Daten tabellarisch abgespeichert werden
    class KSGTDatei
    {
    private:
        Text *pfad;
        RCArray< RCArray< Text > > *data;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) KSGTDatei();
        // Konstruktor
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) KSGTDatei( const char *pfad );
        // Konstruktor
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) KSGTDatei( Text *pfad );
        // Destruktor
        __declspec( dllexport ) ~KSGTDatei();
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) void setPfad( const char *pfad );
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad zur Datei
        __declspec( dllexport ) void setPfad( Text *pfad );
        // l�hdt alle Daten aus der angegebenen Datei
        //  return: 1, falls das laden erfolgreich war. 0, wenn ein Fehler beim laden aufgetreten ist
        __declspec( dllexport ) bool laden();
        // F�gt eine Zeile zur Tabelle hinzu
        //  feldAnzahl: Die Anzahl der Felder in der Zeile
        //  zWert: Einen Zeiger auf die Werte in der Zeile ohne erh�hten Reference Counter
        //  return: 1, wenn kein Fehler aufgetreten ist
        __declspec( dllexport ) bool addZeile( int feldAnzahl, RCArray< Text > *zWert );
        // Ersetzt eine existierende Zeile
        //  zeile: Der Index der Zeile, die ersetzt werden soll
        //  feldAnzahl: Die Anzahl der Felder in der Zeile
        //  zWert: Einen Zeiger auf die Werte in der Zeile ohne erh�hten Reference Counter
        //  return: 1, wenn die Zeile existierte und ersetzt wurde. 0, wenn die angegebene Zeile nicht existierte
        __declspec( dllexport ) bool setZeile( int zeile, int feldAnzahl, RCArray< Text > *zWert );
        // L�scht eine Zeile
        //  zeile: Der Index der Zeile, die gel�scht werden soll
        //  return: 1, wenn die Zeile gel�scht wurde. 0, wenn die Zeile nicht gefunden wurde
        __declspec( dllexport ) bool l�scheZeile( int zeile );
        // F�gt einer Bestimmten Zeile einen Wert hinzu
        //  zeile: Der Index der Zeile, der ein Wert hinzugef�gt werden soll
        //  pos: Die Position in der Zeile, an der der Wert hinzugef�gt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich hinzugef�gt wurde. 0, falls die Zeile nicht existiert, oder pos zu gro� ist
        __declspec( dllexport ) bool addFeld( int zeile, int pos, Text *wert );
        // F�gt einer Bestimmten Zeile einen Wert hinzu
        //  zeile: Der Index der Zeile, der ein Wert hinzugef�gt werden soll
        //  pos: Die Position in der Zeile, an der der Wert hinzugef�gt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich hinzugef�gt wurde. 0, falls die Zeile nicht existiert, oder pos zu gro� ist
        __declspec( dllexport ) bool addFeld( int zeile, int pos, const char *wert );
        // F�gt einer Bestimmten Zeile am Ende einen Wert hinzu
        //  zeile: Der Index der Zeile, der ein Wert hinzugef�gt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich hinzugef�gt wurde. 0, falls die Zeile nicht existiert
        __declspec( dllexport ) bool addFeld( int zeile, Text *wert );
        // F�gt einer Bestimmten Zeile am Ende einen Wert hinzu
        //  zeile: Der Index der Zeile, der ein Wert hinzugef�gt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich hinzugef�gt wurde. 0, falls die Zeile nicht existiert
        __declspec( dllexport ) bool addFeld( int zeile, const char *wert );
        // Setzt einen Bestimmten Wert in einer Zeile
        //  zeile: Der Index der Zeile, in der ein Wert ver�ndert werden soll
        //  feld: Die Position in der Zeile, an der der Wert gesetzt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich ersetzt wurde. 0, falls die Zeile oder der Wert nicht existiert
        __declspec( dllexport ) bool setFeld( int zeile, int feld, Text *wert );
        // Setzt einen Bestimmten Wert in einer Zeile
        //  zeile: Der Index der Zeile, in der ein Wert ver�ndert werden soll
        //  feld: Die Position in der Zeile, an der der Wert gesetzt werden soll
        //  wert: Der Wert, der gespeichert werden soll
        //  return: 1, falls Der Wert erfolgreich ersetzt wurde. 0, falls die Zeile oder der Wert nicht existiert
        __declspec( dllexport ) bool setFeld( int zeile, int feld, const char *wert );
        // Entfernt einen bestimmten Wert
        //  zeile: Der Index der Zeile, aus der ein Wert gel�scht werden soll
        //  feld: Die Position in der Zeile, an der der Wert gel�scht werden soll
        //  return: 1, falls Der Wert erfolgreich gel�scht wurde. 0, falls die Zeile oder der Wert nicht existiert
        __declspec( dllexport ) bool l�scheFeld( int zeile, int feld );
        // Speichert die Tabelle in der Datei
        //  return: 1, falls die Tabbelle erfolgreich gespeichert wurde
        __declspec( dllexport ) bool speichern();
        // Gibt die Anzahl der Zeilen zur�ck
        __declspec( dllexport ) int getZeilenAnzahl() const;
        // Gibt die Anzahl der Werte (Spalten) in einer Zeile zur�ck
        //  zeile: Der Index der Zeile, von der die Anzahl Werte ermittelt werden soll
        __declspec( dllexport ) int getFeldAnzahl( int zeile ) const;
        // Gibt einen bestimmten gespeicherten Wert zur�ck
        //  zeile: Der Index der Zeile, in der der Wert gespeichert wird
        //  feld: Der Index des Wertes in der Zeile
        //  return: Den gespeicherten Wert mit erh�htem Reference Counter
        __declspec( dllexport ) Text *getFeld( int zeile, int feld ) const;
        // Gibt einen bestimmten gespeicherten Wert zur�ck
        //  zeile: Der Index der Zeile, in der der Wert gespeichert wird
        //  feld: Der Index des Wertes in der Zeile
        //  return: Den gespeicherten Wert ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zFeld( int zeile, int feld ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) KSGTDatei *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) KSGTDatei *release();
    };
}

#endif