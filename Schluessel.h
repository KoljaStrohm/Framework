#ifndef Schluessel_H
#define Schluessel_H

#include "Betriebssystem.h"

namespace Framework
{
    namespace Verschl�sselung
    {
        // Speichert einen Array von bytes
        class Bytes
        {
        private:
            char *bytes;
            bool del;
            int l�n;
            int ref;

        public:
            // Erzeugt einen lehren Byte Array
            __declspec( dllexport ) Bytes();
            // Erzeugt einen neuen Byte Array mit bestimmter L�nge
            //  l�n: Die L�nge des Arrays
            __declspec( dllexport ) Bytes( int l�n );
            // Erzeugt ein neuen Byte Array durch kopieren der bytes
            //  daten: Die Bytes, die kopiert werden sollen
            //  l�n: Die Anzahl der Bytes die kopiert werden sollen
            __declspec( dllexport ) Bytes( const char *daten, int l�n );
            // L�scht den Array
            __declspec( dllexport ) ~Bytes();
            // Bef�llt den Bytearray durch kopieren der Bytes
            //  daten: Die Bytes, die kopiert werden sollen
            __declspec( dllexport ) void setBytes( const char *daten );
            // L�scht den Array und erzeugt einen neuen
            //  daten: Die Bytes, die kopiert werden sollen
            //  l�n: Die n�nge des Arrays
            __declspec( dllexport ) void setBytes( const char *daten, int l�n );
            // L�scht den Array und �bernimmt den �bergebenen ohne zu kopieren
            //  daten: Der neue Byte Array
            //  l�n: Die n�nge des Arrays
            __declspec( dllexport ) void setBytesZ( char *daten, int l�n );
            // Setzt alle Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            __declspec( dllexport ) void f�ll( const char c );
            // Setzt eine bestimmte Anzahl von Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            //  l�n: Die Anzahl der Bytes die gesetzt werden sollen
            __declspec( dllexport ) void f�ll( const char c, int l�n );
            // Setzt einen bestimmte Abschnitt von Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            //  beg: Die Startposition des zu setzenden Abschnittes
            //  end: Die Endposition des zu setzenden Abschnittes (nicht enthalten)
            __declspec( dllexport ) void f�ll( const char c, int beg, int end );
            // Kopiert bestimmte bytes in den Array
            //  c: Die Bytes, die kopiert werden sollen
            //  cL�n: Die Anzahl an Bytes, die gesetzt werden sollen
            __declspec( dllexport ) void f�ll( const char *c, int cL�n );
            // Setzt ein bestimmtes Byte auf einen Wert
            //  c: Der Wert, auf den das Byte gesetzt werden soll
            //  pos: Die Position des Bytes im Array
            __declspec( dllexport ) void set( const char c, int pos );
            // Gibt die L�nge des Arrays zur�ck
            __declspec( dllexport ) int getL�nge() const;
            // Gibt den Array von Bytes zur�ck
            __declspec( dllexport ) char *getBytes() const;
            // Erh�ht den Reference Counting Z�hler.
            //  return: this.
            __declspec( dllexport ) Bytes *getThis();
            // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
            //  return: 0.
            __declspec( dllexport ) Bytes *release();
        };

        // Kann Bytesequenzen mit bestimmten Schl�sseln verschl�sseln und entschl�sseln
        class Schl�ssel
        {
        private:
            unsigned char *schl�ssel;
            int l�n;
            int pos;
            int ref;

        public:
            // Erzeugt ein leeres Zeichnung
            __declspec( dllexport ) Schl�ssel();
            // Erzeugt ein neues Zeichnung mi einem Schl�ssel
            //  s: Der Schl�ssel, der zum verschl�sseln und entchl�sseln verwendet werden soll
            //  l�n: Die L�nge des Schl�ssels
            __declspec( dllexport ) Schl�ssel( const char *s, int l�n );
            // L�scht das Zeichnung
            __declspec( dllexport ) ~Schl�ssel();
            // Setzt die Position im Schl�ssel, wo mit dem verschl�sseln und entschl�sseln begonnen werden soll
            //  p: Die Position im Schl�ssel
            __declspec( dllexport ) void setPos( int p );
            // Setzt den Schl�ssel, der zum ver- und entschl�sseln verwendet werden soll
            //  s: Der Schl�ssel
            //  l�n: Die L�nge des Schl�ssels
            __declspec( dllexport ) void setSchl�ssel( const char *s, int l�n );
            // Verschl�sselt einen Byte Array mit dem gesetzten Schl�ssel
            //  daten: Der Byte Array, der verschl�sselt werden soll. Wird von der Funktion ver�ndert
            __declspec( dllexport ) void codieren( Bytes *daten );
            // Entschl�sselt einen Byte Array mit dem gesetzten Schl�ssel
            //  daten: Der Byte Array, der entschl�sselt werden soll. Wird von der Funktion ver�ndert
            __declspec( dllexport ) void decodieren( Bytes *daten );
            // Erh�ht den Reference Counting Z�hler.
            //  return: this.
            __declspec( dllexport ) Schl�ssel *getThis();
            // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
            //  return: 0.
            __declspec( dllexport ) Schl�ssel *release();
        };
    }
}

#endif