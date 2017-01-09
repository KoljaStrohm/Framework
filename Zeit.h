#ifndef Zeit_H
#define Zeit_H

#include "Betriebssystem.h"
#include <time.h>

namespace Framework
{
    class Text; // Text.h
    class Uhrzeit; // Aus dieser Datei
    class Datum; // Aus dieser Datei
    class Zeit; // Aus dieser Datei
    class ZeitMesser; // Aus dieser Datei

    // Diese Klasse speichert eine Uhrzeit in form von Stunden, Minuten und Sekunden
    class Uhrzeit
    {
    private:
        int stunde, minute, sekunde;
        int ref;
        int update();

    public:
        //Erzeugt ein neues Uhrzeit Zeichnung mit den Standartwerten 00:00:00
        __declspec( dllexport ) Uhrzeit();

        //Setzt die Uhrzeit durch kopieren.
        //  zeit: Aus diesem Zeichnung werden die Werte f�r Stunde, Minute und Sekunde kopiert.
        __declspec( dllexport ) int setUhrzeit( Uhrzeit *zeit );
        //Setzt die Uhrzeit.
        //  stunde: Die Stunde der neuen Uhrzeit.
        //  minute: Die Minute der neuen Uhrzeit.
        //  sekunde: Die Sekunde der neuen Uhrzeit.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: setUhrzeit( 30, 30, 30 ); return: 1, gespeichert: 6:30:30
        __declspec( dllexport ) int setUhrzeit( int stunde, int minute, int sekunde );
        //Setzt die Uhrzeit.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: setUhrzeit( "h:i:s", "05:30:00" );
        // Beispiel: setUhrzeit( "h:i:s", "30:30:00" ); return: 1, gespeichert: 6:30:00
        __declspec( dllexport ) int setUhrzeit( const char *format, const char *zeit );
        //Setzt die Uhrzeit.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, dass die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: setUhrzeit( "h:i:s", new Text( "05:30:00" ) );
        // Beispiel: setUhrzeit( "h:i:s", new Text( "30:30:00" ) ); return: 1, gespeichert: 6:30:00
        __declspec( dllexport ) int setUhrzeit( const char *format, Text *zeit );
        // setzt die Stunde.
        //  stunde: Die Stunde, die gespeichert werden soll.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: setStunde( 30 ); return: 1 Tag, gespeicherte Stunden: 6
        __declspec( dllexport ) int setStunde( int stunde );
        // setzt die Minute.
        //  minute: Die Minute, die gespeichert werden soll.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 23:50:10, setMinute( 80 ); return: 1, gespeicherte Zeit: 01:10:10
        __declspec( dllexport ) int setMinute( int minute );
        // setzt die Sekunde.
        //  minute: Die Sekunde, die gespeichert werden soll.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 23:59:10, setSekunde( 80 ); return: 1, gespeicherte Zeit: 00:00:30
        __declspec( dllexport ) int setSekunde( int sekunde );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  zeit: Die Uhrzeit, deren Werte addiert werden sollen.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 19:40:18, plusZeit( (10:05:30) ); return 1, gespeicherte Zeit: 05:45:48
        __declspec( dllexport ) int plusUhrzeit( Uhrzeit *zeit );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  stunde: Die Stunden die Werte addiert werden sollen.
        //  minute: Die Minute die Werte addiert werden sollen.
        //  sekunde: Die Sekunde die Werte addiert werden sollen.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 19:40:18, plusZeit( 10, 5, 30 ); return 1, gespeicherte Zeit: 05:45:48
        __declspec( dllexport ) int plusUhrzeit( int stunde, int minute, int sekunde );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: plusUhrzeit( "h:i:s", "05:20:00" );
        // Beispiel: Alte Zeit: 19:40:18, plusZeit( "h:i:s", "10:05:30" ); return 1, gespeicherte Zeit: 05:45:48
        __declspec( dllexport ) int plusUhrzeit( const char *format, const char *zeit );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: plusUhrzeit( "h:i:s", new Text( "05:20:00" ) );
        // Beispiel: Alte Zeit: 19:40:18, plusZeit( "h:i:s", new Text( "10:05:30" ) ); return 1, gespeicherte Zeit: 05:45:48
        __declspec( dllexport ) int plusUhrzeit( const char *format, Text *zeit );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  stunde: die draufzurechnenden Stunden.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 20:50:30, plusStunde( 10 ); return 1, gespeicherte Zeit: 6:50:30
        __declspec( dllexport ) int plusStunde( int stunde );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  minute: die draufzurechnenden Minuten.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 23:50:30, plusMinute( 11 ); return 1, gespeicherte Zeit: 00:01:30
        __declspec( dllexport ) int plusMinute( int minute );
        // errechnet die Summe von dieser und einer anderen Uhrzeit und speichert diese.
        //  sekunde: die draufzurechnenden Sekunden.
        //  return: Die Anzahl �briger Tage.
        // Beispiel: Alte Zeit: 23:59:30, plusSekunde( 40 ); return 1, gespeicherte Zeit: 00:00:10
        __declspec( dllexport ) int plusSekunde( int sekunde );
        // zieht eine gegebene Uhrzeit von dieser ab und speichert das Ergebnis.
        //  zeit: Die Uhrzeit, die von dieser abgezogen werden soll.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 10:40:18, minusUhrzeit( (19:05:30) ); return -1, gespeicherte Zeit: 15:34:48
        __declspec( dllexport ) int minusUhrzeit( Uhrzeit *zeit );
        // zieht eine gegebene Uhrzeit von dieser ab und speichert das Ergebnis.
        //  stunde: Die Stunden, die von dieser Uhrzeit abgezogen werden sollen.
        //  minute: Die Minuten, die von dieser Uhrzeit abgezogen werden sollen.
        //  sekunde: Die Sekunden, die von dieser Uhrzeit abgezogen werden sollen.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 10:40:18, minusUhrzeit( 19, 05, 30 ); return -1, gespeicherte Zeit: 15:34:48
        __declspec( dllexport ) int minusUhrzeit( int stunde, int minute, int sekunde );
        // zieht eine gegebene Uhrzeit von dieser ab und speichert das Ergebnis.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 10:40:18, minusUhrzeit( "h:i:s", "19:05:30" ); return -1, gespeicherte Zeit: 15:34:48
        __declspec( dllexport ) int minusUhrzeit( const char *format, const char *zeit );
        // zieht eine gegebene Uhrzeit von dieser ab und speichert das Ergebnis.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die neue Uhrzeit enth�lt.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 10:40:18, minusUhrzeit( "h:i:s", new Text( "19:05:30" ) ); return -1, gespeicherte Zeit: 15:34:48
        __declspec( dllexport ) int minusUhrzeit( const char *format, Text *zeit );
        // zieht eine gegebene Zeit von dieser ab und speichert das Ergebnis.
        //  stunde: Die abzuziehenden Stunden.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 10:40:18, minusStunde( 19 ); return -1, gespeicherte Zeit: 15:40:18
        __declspec( dllexport ) int minusStunde( int stunde );
        // zieht eine gegebene Zeit von dieser ab und speichert das Ergebnis.
        //  minute: Die abzuziehenden Minuten.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 00:40:18, minusStunde( 50 ); return -1, gespeicherte Zeit: 23:50:18
        __declspec( dllexport ) int minusMinute( int minute );
        // zieht eine gegebene Zeit von dieser ab und speichert das Ergebnis.
        //  sekunde: Die abzuziehenden Sekunden.
        //  return: Die Anzahl �briger Tage.
        // Beispiel Alte Zeit: 00:00:20, minusStunde( 50 ); return -1, gespeicherte Zeit: 23:59:30
        __declspec( dllexport ) int minusSekunde( int sekunde );

        // gibt die Stunde zur�ck.
        __declspec( dllexport ) int getStunde() const;
        // gibt die Minute zur�ck.
        __declspec( dllexport ) int getMinute() const;
        // gibt die Sekunde zur�ck.
        __declspec( dllexport ) int getSekunde() const;
        // gibt die Uhrzeit als Text formatiert zur�ck.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit zur�ckgegeben werden soll. h=Stunde, i=Minute,s=Sekunde.
        // Beispiel: Zeit: 5:40:39, getUhrzeit( "h:i:s" ); return: "5:40:39"
        __declspec( dllexport ) Text *getUhrzeit( const char *format ) const;
        // pr�ft, ob die Uhrzeit gleich zeit ist.
        //  zeit: Die Uhrzeit, mit der diese verglichen werden soll.
        //  return: (true), wenn die beiden Zeiten geich sind. (false), wenn die Zeiten nicht gleich sind.
        __declspec( dllexport ) bool istGleich( Uhrzeit *zeit ) const;
        // pr�ft, ob die Uhrzeit gleich zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die andere Uhrzeit enth�lt.
        //  return: (true), wenn die beiden Zeiten geich sind. (false), wenn die Zeiten nicht gleich sind.
        __declspec( dllexport ) bool istGleich( const char *format, const char *zeit ) const;
        // pr�ft, ob die Uhrzeit gleich zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die andere Uhrzeit enth�lt.
        //  return: (true), wenn die beiden Zeiten geich sind. (false), wenn die Zeiten nicht gleich sind.
        __declspec( dllexport ) bool istGleich( const char *format, Text *zeit ) const;
        // pr�ft, ob die Uhrzeit gleich der �bergebenen Zeit ist. Hier wird nicht beachtet, ob die gegebene Zeit eine g�ltige Uhrzeit ist.
        //  stunde: Die Stunden der zu �berpr�fenden Uhrzeit
        //  minute: Die Minuten der zu �berpr�fenden Uhrzeit
        //  sekunde: Die Sekunden der zu �berpr�fenden Uhrzeit
        //  return: (true), wenn die beiden Zeiten geich sind. (false), wenn die Zeiten nicht gleich sind.
        __declspec( dllexport ) bool istGleich( int stunde, int minute, int sekunde ) const;
        // pr�ft, ob die Stunde gleich der gegebenen Stunde ist.
        //  stunde: die zu pr�fende Stunde.
        //  return: (true), wenn die Stunden gleich sind. (false), wenn sie nicht gleich sind.
        __declspec( dllexport ) bool stundeGleich( int stunde ) const;
        // pr�ft, ob die Minute gleich der gegebenen Minute ist.
        //  minute: die zu pr�fende Minute.
        //  return: (true), wenn die Minuten gleich sind. (false), wenn sie nicht gleich sind.
        __declspec( dllexport ) bool minuteGleich( int minute ) const;
        // pr�ft, ob die Sekunde gleich der gegebenen Sekunde ist.
        //  sekunde: die zu pr�fende Sekunde.
        //  return: (true), wenn die Sekunden gleich sind. (false), wenn sie nicht gleich sind.
        __declspec( dllexport ) bool sekundeGleich( int sekunde ) const;
        // pr�ft, ob die Uhrzeit kleiner als zeit ist.
        //  zeit: Die zu pr�fende Uhrzeit.
        //  return: (true), wenn die gespeicherte Zeit kleiner als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istKleiner( (10:40:29) ); return true
        __declspec( dllexport ) bool istKleiner( Uhrzeit *zeit ) const;
        // pr�ft, ob die Uhrzeit kleiner als die �bergebene Zeit ist.
        //  stunde: Die Stunden der zu pr�fenden Zeit.
        //  minute: Die Minute der zu pr�fenden Zeit.
        //  sekunde: Die Sekunde der zu pr�fenden Zeit.
        //  return: (true), wenn die gespeicherte Zeit kleiner als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istKleiner( 10, 40, 29 ); return true
        __declspec( dllexport ) bool istKleiner( int stunde, int minute, int sekunde ) const;
        // pr�ft, ob die Uhrzeit kleiner als die �bergebene Zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die andere Uhrzeit enth�lt.
        //  return: (true), wenn die gespeicherte Zeit kleiner als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istKleiner( "h:i:s", "10:40:29" ); return true
        __declspec( dllexport ) bool istKleiner( const char *format, const char *zeit ) const;
        // pr�ft, ob die Uhrzeit kleiner als die �bergebene Zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die andere Uhrzeit enth�lt.
        //  return: (true), wenn die gespeicherte Zeit kleiner als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istKleiner( "h:i:s", "10:40:29" ); return true
        __declspec( dllexport ) bool istKleiner( const char *format, Text *zeit ) const;
        // pr�ft, ob die Uhrzeit gr��er als zeit ist.
        //  zeit: Die zu pr�fende Uhrzeit.
        //  return: (true), wenn die gespeicherte Zeit gr��er als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istGr��er( (10:40:29) ); return false
        __declspec( dllexport ) bool istLater( Uhrzeit *zeit ) const;
        // pr�ft, ob die Uhrzeit gr��er als die �bergebene Zeit ist.
        //  stunde: Die Stunden der zu pr�fenden Zeit.
        //  minute: Die Minute der zu pr�fenden Zeit.
        //  sekunde: Die Sekunde der zu pr�fenden Zeit.
        //  return: (true), wenn die gespeicherte Zeit gr��er als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istGr��er( 10, 40, 29 ); return false
        __declspec( dllexport ) bool istLater( int stunde, int minute, int sekunde ) const;
        // pr�ft, ob die Uhrzeit gr��er als die �bergebene Zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Eine Zeichenfolge die die andere Uhrzeit enth�lt.
        //  return: (true), wenn die gespeicherte Zeit gr��er als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istGr��er( "h:i:s", "10:40:29" ); return false
        __declspec( dllexport ) bool istLater( const char *format, const char *zeit ) const;
        // pr�ft, ob die Uhrzeit gr��er als die �bergebene Zeit ist.
        //  format: Eine Zeichenfolge, die bestimmt in welcher Form die Uhrzeit in (zeit) vorliegt. h=Stunde, i=Minute,s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die andere Uhrzeit enth�lt.
        //  return: (true), wenn die gespeicherte Zeit gr��er als die �bergebene Zeit ist. (false) sonst.
        // Beispiel: (5:30:00).istGr��er( "h:i:s", "10:40:29" ); return false
        __declspec( dllexport ) bool istLater( const char *format, Text *zeit ) const;
        // Erh�ht den Reference Counting Z�hler
        //  return: this
        __declspec( dllexport ) Uhrzeit *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht
        //  return: 0
        __declspec( dllexport ) Uhrzeit *release();
    };

    // Diese Klasse speichert ein Datum in Form von Jahr, Monat und Tagen
    class Datum
    {
    private:
        int jahr, monat, tag;
        int ref;
        int *maxTage;
        void update();

    public:
        // Erzeugt ein neues Datum Zeichnung mit den Standartwerten 0.0.0.
        __declspec( dllexport ) Datum();
        // L�scht das Datum.
        __declspec( dllexport ) ~Datum();

        // Setzt das Datum durch kopieren.
        //  datum: Das zu speichernde Datum.
        __declspec( dllexport ) void setDatum( Datum *datum );
        // Setzt das Datum zu den �bergebenen Werten.
        //  jahr: Das Jahr des neuen Datums.
        //  monat: Der Monat des neuen Datums.
        //  tag: Der Tag des neuen Datums.
        __declspec( dllexport ) void setDatum( int jahr, int monat, int tag );
        // Setzt das Datum zu dem �bergebenen Wert.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das neue Datum enth�lt.
        // Beispiel: setDatum( "y-m-d", "2016-01-25" );
        __declspec( dllexport ) void setDatum( const char *format, const char *datum );
        // Setzt das Datum zu dem �bergebenen Wert.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das neue Datum enth�lt.
        // Beispiel: setDatum( "y-m-d", new Text(  "2016-01-25" ) );
        __declspec( dllexport ) void setDatum( const char *format, Text *datum );
        // �ndert das Jahr des Datums.
        //  jahr: Das neue Jahr.
        __declspec( dllexport ) void setJahr( int jahr );
        // �ndert den Monat des Datums.
        //  monat: Der neue Monat.
        __declspec( dllexport ) void setMonat( int monat );
        // �ndert den Tag des Datums.
        //  tag: Der neue Tag.
        __declspec( dllexport ) void setTag( int tag );
        // Addiert zum aktuellen Datum das �bergebene Datum dazu und speichert das Ergebnis.
        //  datum: Das zu addierende Datum.
        // Beispiel: ( 1.11.1995 ).plusDatum( ( 5.2.7 ) ); neues Datum: 6.1.2003
        __declspec( dllexport ) void plusDatum( Datum *datum );
        // Addiert zum aktuellen Datum das �bergebene Datum dazu und speichert das Ergebnis.
        //  jahr: Das zu addierende Jahr.
        //  monat: Der zu addierende Monat.
        //  tag: Der zu addierende Tag.
        // Beispiel: ( 1.11.1995 ).plusDatum( ( 7, 2, 5 ) ); neues Datum: 6.1.2003
        __declspec( dllexport ) void plusDatum( int jahr, int monat, int tag );
        // Addiert zum aktuellen Datum das �bergebene Datum dazu und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das zu addierende Datum enth�lt.
        // Beispiel: ( 1.11.1995 ).plusDatum( "d.m.y", "5.2.7" ); neues Datum: 6.1.2003
        __declspec( dllexport ) void plusDatum( const char *format, const char *datum );
        // Addiert zum aktuellen Datum das �bergebene Datum dazu und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das zu addierende Datum enth�lt.
        // Beispiel: ( 1.11.1995 ).plusDatum( "d.m.y", new Text( "5.2.7" ) ); neues Datum: 6.1.2003
        __declspec( dllexport ) void plusDatum( const char *format, Text *datum );
        // Addiert zum aktuellen Datum das �bergebene Jahr dazu und speichert das Ergebnis.
        //  jahr: Das zu addierende Jahr.
        // Beispiel: ( 1.11.1995 ).plusJahr( 21 ); neues Datum: 1.11.2016
        __declspec( dllexport ) void plusJahr( int jahr );
        // Addiert zum aktuellen Datum den �bergebenen Monat dazu und speichert das Ergebnis.
        //  monat: Der zu addierende Monat.
        // Beispiel: ( 1.11.1995 ).plusMonat( 13 ); neues Datum: 1.12.1996
        __declspec( dllexport ) void plusMonat( int monat );
        // Addiert zum aktuellen Datum den �bergebenen Tag dazu und speichert das Ergebnis.
        //  tag: Der zu addierende Tag.
        // Beispiel: ( 1.1.2000 ).plusTag( 32 ); neues Datum: 2.2.2000
        __declspec( dllexport ) void plusTag( int tag );
        // Zieht vom aktuellen Datum das �bergebene Datum ab und speichert das Ergebnis.
        //  datum: Das abzuzuehende Datum.
        // Beispiel: ( 2.12.1996 ).minusDatum( ( 1.1.1 ) ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusDatum( Datum *datum );
        // Zieht vom aktuellen Datum das �bergebene Datum ab und speichert das Ergebnis.
        //  jahr: Das abzuzuehende Jahr.
        //  monat: Der abzuzuehende Monat.
        //  tag: Der abzuzuehende Tag.
        // Beispiel: ( 2.12.1996 ).minusDatum( 1, 1, 1 ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusDatum( int jahr, int monat, int tag );
        // Zieht vom aktuellen Datum das �bergebene Datum ab und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das abzuziehende Datum enth�lt.
        // Beispiel: ( 2.12.1996 ).minusDatum( "d.m.y", "1.1.1" ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusDatum( const char *format, const char *datum );
        // Zieht vom aktuellen Datum das �bergebene Datum ab und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das abzuziehende Datum enth�lt.
        // Beispiel: ( 2.12.1996 ).minusDatum( "d.m.y", new Text( "1.1.1" ) ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusDatum( const char *format, Text *datum );
        // Zieht vom aktuellen Datum das �bergebene Jahr ab und speichert das Ergebnis.
        //  jahr: Das abzuzuehende Jahr.
        // Beispiel: ( 1.11.1996 ).minusJahr( 1 ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusJahr( int jahr );
        // Zieht vom aktuellen Datum den �bergebenen Monat ab und speichert das Ergebnis.
        //  monat: Der abzuzuehende Monat.
        // Beispiel: ( 1.12.1996 ).minusMonat( 13 ); neues Datum: 1.11.1995
        __declspec( dllexport ) void minusMonat( int monat );
        // Zieht vom aktuellen Datum den �bergebenen Tag ab und speichert das Ergebnis.
        //  monat: Der abzuzuehende Tag.
        // Beispiel: ( 5.2.2016 ).minusMonat( 11 ); neues Datum: 25.1.2016
        __declspec( dllexport ) void minusTag( int tag );

        // gibt das Jahr zur�ck.
        __declspec( dllexport ) int getJahr() const;
        // gibt der Monat zur�ck.
        __declspec( dllexport ) int getMonat() const;
        // gibt der Tag zur�ck.
        __declspec( dllexport ) int getTag() const;
        // Gibt das Datum als Text Zeichnung zur�ck.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum zur�ckgegeben werden soll. y=Jahr, m=Monat, d=Tag.
        // Beispiel: ( 1.11.1995 ).getDatum( "y-m-d" ); return: "1995-11-1"
        __declspec( dllexport ) Text *getDatum( const char *format ) const;
        // Pr�ft, ob das Datum gleich dem �bergebenen Datum ist.
        //  datum: das zu pr�fende Datum.
        //  return: (true), wenn das �bergebene Datum dem gespeicherten entspricht. (false) sonnst.
        __declspec( dllexport ) bool istGleich( Datum *datum ) const;
        // Pr�ft, ob das Datum gleich dem �bergebenen Datum ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das �bergebene Datum dem gespeicherten entspricht. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGleich( "y-m-d", "1995-11-1" ); return: true
        __declspec( dllexport ) bool istGleich( const char *format, const char *datum ) const;
        // Pr�ft, ob das Datum gleich dem �bergebenen Datum ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das �bergebene Datum dem gespeicherten entspricht. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGleich( "y-m-d", new Text( "1995-11-1" ) ); return: true
        __declspec( dllexport ) bool istGleich( const char *format, Text *datum ) const;
        // Pr�ft, ob das Datum gleich dem �bergebenen Datum ist.
        //  jahr: Das Jahr des zu �berpr�fenden Datums.
        //  monat: Der Monat des zu �berpr�fenden Datums.
        //  tag: Der Tag des zu �berpr�fenden Datums.
        //  return: (true), wenn das �bergebene Datum dem gespeicherten entspricht. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGleich( 1995, 11, 1 ); return: true
        __declspec( dllexport ) bool istGleich( int jahr, int monat, int tag ) const;
        // Pr�ft, ob das Jahr gleich dem �bergebenen Jahr ist.
        //  jahr: Das zu pr�fende Jahr.
        //  return: (true), wenn das �bergebene Jahr dem gespeicherten entspricht. (false) sonnst.
        __declspec( dllexport ) bool jahrGleich( int jahr ) const;
        // Pr�ft, ob der Monat gleich dem �bergebenen Monat ist.
        //  monat: Der zu pr�fende Monat.
        //  return: (true), wenn der �bergebene Monat dem gespeicherten entspricht. (false) sonnst.
        __declspec( dllexport ) bool monatGleich( int monat ) const;
        // Pr�ft, ob der Tag gleich dem �bergebenen Tag ist.
        //  tag: Der zu pr�fende Tag.
        //  return: (true), wenn der �bergebene Tag dem gespeicherten entspricht. (false) sonnst.
        __declspec( dllexport ) bool tagGleich( int tag ) const;
        // Pr�ft, ob das gespeicherte Datum kleiner als das �bergebene ist.
        //  datum: Das zu pr�fende Datum.
        //  return: (true), wenn das gespeicherte Datum vor dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istKleiner( ( 23.1.2016 ) ); return true
        __declspec( dllexport ) bool istKleiner( Datum *datum ) const;
        // Pr�ft, ob das gespeicherte Datum kleiner als das �bergebene ist.
        //  jahr: Das Jahr des zu pr�fenden Datums.
        //  monat: Der Monat des zu pr�fenden Datums.
        //  tag: Der Tag des zu pr�fenden Datums.
        //  return: (true), wenn das gespeicherte Datum vor dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istKleiner( 2016, 1, 23 ); return true
        __declspec( dllexport ) bool istKleiner( int jahr, int monat, int tag ) const;
        // Pr�ft, ob das gespeicherte Datum kleiner als das �bergebene ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das gespeicherte Datum vor dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istKleiner( "y, m, d", "2016, 1, 23" ); return true
        __declspec( dllexport ) bool istKleiner( const char *format, const char *datum ) const;
        // Pr�ft, ob das gespeicherte Datum kleiner als das �bergebene ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das gespeicherte Datum vor dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istKleiner( "y, m, d", new Text( "2016, 1, 23" ) ); return true
        __declspec( dllexport ) bool istKleiner( const char *format, Text *datum ) const;
        // Pr�ft, ob das gespeicherte Datum gr��er als das �bergebene ist.
        //  datum: Das zu pr�fende Datum.
        //  return: (true), wenn das gespeicherte Datum hinter dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGr��er( ( 23.1.2016 ) ); return false
        __declspec( dllexport ) bool istLater( Datum *datum ) const;
        // Pr�ft, ob das gespeicherte Datum gr��er als das �bergebene ist.
        //  jahr: Das Jahr des zu pr�fenden Datums.
        //  monat: Der Monat des zu pr�fenden Datums.
        //  tag: Der Tag des zu pr�fenden Datums.
        //  return: (true), wenn das gespeicherte Datum hinter dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGr��er( 2016, 1, 23 ); return false
        __declspec( dllexport ) bool istLater( int jahr, int monat, int tag ) const;
        // Pr�ft, ob das gespeicherte Datum gr��er als das �bergebene ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Eine Zeichenkette, die das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das gespeicherte Datum hinter dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGr��er( "y, m, d", "2016, 1, 23" ); return false
        __declspec( dllexport ) bool istLater( const char *format, const char *datum ) const;
        // Pr�ft, ob das gespeicherte Datum gr��er als das �bergebene ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form das Datum in (datum) vorhanden ist. y=Jahr, m=Monat, d=Tag.
        //  datum: Ein Text Zeichnung, welches das zu �berpr�fende Datum enth�lt.
        //  return: (true), wenn das gespeicherte Datum hinter dem �bergebenen liegt. (false) sonnst.
        // Beispiel: ( 1.11.1995 ).istGr��er( "y, m, d", new Text( "2016, 1, 23" ) ) ); return true
        __declspec( dllexport ) bool istLater( const char *format, Text *datum ) const;
        // Erh�ht den Reference Counting Z�hler
        //  return: this
        __declspec( dllexport ) Datum *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht
        //  return: 0
        __declspec( dllexport ) Datum *release();
    };

    // Diese Klasse vereint die beiden Klassen Datum und Uhrzeit und speichert somit einen Zeitstempel mit Jahr, Monat, Tag, Stunde, Minute und Sekunde
    class Zeit
    {
    private:
        Datum *datum;
        Uhrzeit *uhrzeit;
        int ref;

    public:
        // Erzeugt ein neues Zeichnung mit den Standartwerten 0.0.0 0:0:0.
        __declspec( dllexport ) Zeit();
        // L�scht das aktuelle Zeichnung.
        __declspec( dllexport ) ~Zeit();
        // �ndert die gespeicherte Zeit durch kopieren der Werte aus (zeit).
        //  zeit: Die neue Zeit.
        __declspec( dllexport ) void setZeit( Zeit *zeit );
        // �ndert die gespeicherte Zeit.
        //  jahr: Das neue Jahr.
        //  monat: Der neue Monat.
        //  tag: Det neue Tag.
        //  stunde: Die neue Stunde.
        //  minute: Die neue Minute.
        //  sekunde: Die neue Sekunde.
        __declspec( dllexport ) void setZeit( int jahr, int monat, int tag, int stunde, int minute, int sekunde );
        // �ndert die gespeicherte Zeit.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die neue Zeit enth�lt.
        // Beispiel: setZeit( "y-m-d h:i:s", "2016-1-25 21:59:30" );
        __declspec( dllexport ) void setZeit( const char *format, const char *zeit );
        // �ndert die gespeicherte Zeit.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die neue Zeit enth�lt.
        // Beispiel: setZeit( "y-m-d h:i:s", new Text( "2016-1-25 21:59:30" ) );
        __declspec( dllexport ) void setZeit( const char *format, Text *zeit );
        // �ndert das gespeicherte Jahr.
        //  jahr: Das neue Jahr.
        __declspec( dllexport ) void setJahr( int jahr );
        // �ndert den gespeicherten Monat.
        //  monat: Der neue Monat.
        __declspec( dllexport ) void setMonat( int monat );
        // �ndert den gespeicherten Tag.
        //  tag: Der neue Tag.
        __declspec( dllexport ) void setTag( int tag );
        // �ndert die gespeicherte Stunde.
        //  stunde: Die neue Stunde.
        __declspec( dllexport ) void setStunde( int stunde );
        // �ndert die gespeicherte Minute.
        //  minute: Die neue Minute.
        __declspec( dllexport ) void setMinute( int minute );
        // �ndert die gespeicherte Sekunde.
        //  sekunde: Die neue Sekunde.
        __declspec( dllexport ) void setSekunde( int sekunde );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  zeit: Die zu Addierende Zeit.
        __declspec( dllexport ) void plusZeit( Zeit *zeit );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  jahr: Das zu addierende Jahr.
        //  monat: Der zu addierende Monat.
        //  tag: Der zu addierende Tag.
        //  stunde: Die zu addierende Stunde.
        //  minute: Die zu addierende Minute.
        //  sekunde: Die zu addierende Sekunde.
        __declspec( dllexport ) void plusZeit( int jahr, int monat, int tag, int stunde, int minute, int sekunde );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die zu addierende Zeit enth�lt.
        __declspec( dllexport ) void plusZeit( const char *format, const char *zeit );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die zu addierende Zeit enth�lt.
        __declspec( dllexport ) void plusZeit( const char *format, Text *zeit );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  jahr: Das zu addierende Jahr.
        __declspec( dllexport ) void plusJahr( int jahr );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  monat: Der zu addierende Monat.
        __declspec( dllexport ) void plusMonat( int monat );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  tag: Der zu addierende Tag.
        __declspec( dllexport ) void plusTag( int tag );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  stunde: Die zu addierende Stunde.
        __declspec( dllexport ) void plusStunde( int stunde );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  minute: Die zu addierende Minute.
        __declspec( dllexport ) void plusMinute( int minute );
        // Addiert die �bergebene Zeit und speichert das Ergebnis.
        //  sekunde: Die zu addierende Sekunde.
        __declspec( dllexport ) void plusSekunde( int sekunde );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  zeit: Die abzuziehende Zeit.
        __declspec( dllexport ) void minusZeit( Zeit *zeit );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  jahr: Das abzuziehende Jahr.
        //  monat: Der abzuziehende Monat.
        //  tag: Der abzuziehende Tag.
        //  stunde: Die abzuziehende Stunde.
        //  minute: Die abzuziehende Minute.
        //  sekunde: Die abzuziehende Sekunde.
        __declspec( dllexport ) void minusZeit( int jahr, int monat, int tag, int stunde, int minute, int sekunde );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die abzuziehende Zeit enth�lt.
        __declspec( dllexport ) void minusZeit( const char *format, const char *zeit );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Ein Text Zeichnung, welches die abzuziehende Zeit enth�lt.
        __declspec( dllexport ) void minusZeit( const char *format, Text *zeit );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  jahr: Das abzuziehende Jahr.
        __declspec( dllexport ) void minusJahr( int jahr );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  monat: Der abzuziehende Monat.
        __declspec( dllexport ) void minusMonat( int monat );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  tag: Der abzuziehende Tag.
        __declspec( dllexport ) void minusTag( int tag );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  stunde: Die abzuziehende Stunde.
        __declspec( dllexport ) void minusStunde( int stunde );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  minute: Die abzuziehende Minute.
        __declspec( dllexport ) void minusMinute( int minute );
        // Zieht die �bergebene Zeit ab und speichert das Ergebnis.
        //  sekunde: Die abzuziehende Sekunde.
        __declspec( dllexport ) void minusSekunde( int sekunde );
        // Gibt die gespeicherte Zeit als Text zur�ck.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit zur�ckgegeben werden soll. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        __declspec( dllexport ) Text *getZeit( const char *format ) const;
        // �berpr�ft, ob die Zeit gleich der �bergebenen Zeit ist.
        //  zeit: die zu �berpr�fende Zeit.
        //  return: (true), wenn die Zeiten gleich sind. (false) sonst.
        __declspec( dllexport ) bool istGleich( Zeit *zeit ) const;
        // �berpr�ft, ob die Zeit gleich der �bergebenen Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die zu �berpr�fende Zeit enth�lt.
        //  return: (true), wenn die Zeiten gleich sind. (false) sonst.
        __declspec( dllexport ) bool istGleich( const char *format, const char *zeit ) const;
        // �berpr�ft, ob die Zeit gleich der �bergebenen Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Text Zeichnung, welches die zu �berpr�fende Zeit enth�lt.
        //  return: (true), wenn die Zeiten gleich sind. (false) sonst.
        __declspec( dllexport ) bool istGleich( const char *format, Text *zeit ) const;
        // �berpr�ft, ob die Zeit gleich der �bergebenen Zeit ist.
        //  jahr: Das zu �berpr�fende Jahr.
        //  monat: Der zu �berpr�fende Monat.
        //  tag: Der zu �berpr�fende Tag.
        //  stunde: Die zu �berpr�fende Stunde.
        //  minute: Die zu �berpr�fende Minute.
        //  sekunde: Die zu �berpr�fende Sekunde.
        //  return: (true), wenn die Zeiten gleich sind. (false) sonst.
        __declspec( dllexport ) bool istGleich( int jahr, int monat, int tag, int stunde, int minute, int sekunde ) const;
        // Gibt das Zeichnung zur�ck, in dem das Datum gespeichert wird mit erh�htem Reference Counter.
        __declspec( dllexport ) Datum *getDatum() const;
        // Gibt das Zeichnung zur�ck, in dem das Datum gespeichert wird ohne erh�hten Reference Counter.
        __declspec( dllexport ) Datum *zDatum() const;
        // Gibt das Zeichnung zur�ck, in dem die Uhrzeit gespeichert wird mit erh�htem Reference Counter.
        __declspec( dllexport ) Uhrzeit *getUhrzeit() const;
        // Gibt das Zeichnung zur�ck, in dem die uhrzeit gespeichert wird ohne erh�hten Reference Counter.
        __declspec( dllexport ) Uhrzeit *zUhrzeit() const;
        // �berpr�ft, ob die gespeicherte Zeit kleiner als die �bergebene Zeit ist.
        //  zeit: Die zu �berpr�fende Zeit.
        //  return: (true) wenn die gespeicherte Zeit vor der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istKleiner( Zeit *zeit ) const;
        // �berpr�ft, ob die gespeicherte Zeit kleiner als die �bergebene Zeit ist.
        //  jahr: Das zu �berpr�fende Jahr.
        //  monat: Der zu �berpr�fende Monat.
        //  tag: Der zu �berpr�fende Tag.
        //  stunde: Die zu �berpr�fende Stunde.
        //  minute: Die zu �berpr�fende Minute.
        //  sekunde: Die zu �berpr�fende Sekunde.
        //  return: (true) wenn die gespeicherte Zeit vor der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istKleiner( int jahr, int monat, int tag, int stunde, int minute, int sekunde ) const;
        // �berpr�ft, ob die gespeicherte Zeit kleiner als die �bergebene Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die zu �berpr�fende Zeit enth�lt.
        //  return: (true) wenn die gespeicherte Zeit vor der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istKleiner( const char *format, const char *zeit ) const;
        // �berpr�ft, ob die gespeicherte Zeit kleiner als die �bergebene Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Text Zeichnung, welches die zu �berpr�fende Zeit enth�lt.
        //  return: (true) wenn die gespeicherte Zeit vor der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istKleiner( const char *format, Text *zeit ) const;
        // �berpr�ft, ob die gespeicherte Zeit gr��er als die �bergebene Zeit ist.
        //  zeit: Die zu �berpr�fende Zeit.
        //  return: (true) wenn die gespeicherte Zeit nach der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istLater( Zeit *zeit ) const;
        // �berpr�ft, ob die gespeicherte Zeit gr��er als die �bergebene Zeit ist.
        //  jahr: Das zu �berpr�fende Jahr.
        //  monat: Der zu �berpr�fende Monat.
        //  tag: Der zu �berpr�fende Tag.
        //  stunde: Die zu �berpr�fende Stunde.
        //  minute: Die zu �berpr�fende Minute.
        //  sekunde: Die zu �berpr�fende Sekunde.
        //  return: (true) wenn die gespeicherte Zeit nach der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istLater( int jahr, int monat, int tag, int stunde, int minute, int sekunde ) const;
        // �berpr�ft, ob die gespeicherte Zeit gr��er als die �bergebene Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Zeichenkette, die die zu �berpr�fende Zeit enth�lt.
        //  return: (true) wenn die gespeicherte Zeit nach der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istLater( const char *format, const char *zeit ) const;
        // �berpr�ft, ob die gespeicherte Zeit gr��er als die �bergebene Zeit ist.
        //  format: Eine Zeichenkette, die angibt in welcher Form die neue Zeit in (zeit) vorhanden ist. y=Jahr, m=Monat, d=Tag, h=Stunde, i=Minute, s=Sekunde.
        //  zeit: Eine Text Zeichnung, welches die zu �berpr�fende Zeit enth�lt.
        //  return: (true) wenn die gespeicherte Zeit nach der �bergebenen Zeit liegt. (false) sonnst.
        __declspec( dllexport ) bool istLater( const char *format, Text *zeit ) const;
        // Erh�ht den Reference Counting Z�hler
        //  return: this
        __declspec( dllexport ) Zeit *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht
        //  return: 0
        __declspec( dllexport ) Zeit *release();
    };

    // Diese Klasse kann messen, wie viel Zeit zwischen zwei Zeitpunkten verstrichen ist
    class ZeitMesser
    {
    private:
        double start;
        double ende;
        double messung;
        int ref;

    public:
        // Erzeugt ein neues ZeitMesser Zeichnung
        __declspec( dllexport ) ZeitMesser();
        // L�scht das aktuelle Zeichnung
        __declspec( dllexport ) ~ZeitMesser();
        // legt den Startpunkt des zeitstoppens fest
        __declspec( dllexport ) void messungStart();
        // legt des Endpunkt der Zeitmessung fest
        __declspec( dllexport ) void messungEnde();
        // gibt den Abstand zwischen start und ende der Messung in Sekunden zur�ck
        __declspec( dllexport ) double getSekunden() const;
        // gibt den Abstand zwischen start und ende der Messung in Minuten zur�ck
        __declspec( dllexport ) double getMinuten() const;
        // gibt den Abstand zwischen start und ende der Messung in Stunden zur�ck
        __declspec( dllexport ) double getStunden() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) ZeitMesser *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) ZeitMesser *release();
    };

    // gibt die aktuelle Uhrzeit zur�ck.
    __declspec( dllexport ) Uhrzeit *getUhrzeit();
    // gibt das aktuelle Datum zur�ck.
    __declspec( dllexport ) Datum *getDatum();
    // gibt die aktuelle Zeit( Datum und Uhrzeit ) zur�ck.
    __declspec( dllexport ) Zeit *getZeit();
    // pr�ft, ob jahr ein Schaltjahr ist.
    //  jahr: Das zu �berpr�fende Jahr.
    //  return: (true), wenn das �bergebene jahr ein Schaltjahr ist. (false) sonst.
    __declspec( dllexport ) bool istSchaltjahr( int jahr );
}

#endif