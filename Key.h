#ifndef Key_H
#define Key_H

#include "Betriebssystem.h"

namespace Framework
{
    namespace Encryption
    {
        // Speichert einen Array von bytes
        class Bytes
        {
        private:
            char *bytes;
            bool del;
            int length;
            int ref;

        public:
            // Erzeugt einen lehren Byte Array
            __declspec( dllexport ) Bytes();
            // Erzeugt einen neuen Byte Array mit bestimmter L�nge
            //  length: Die L�nge des Arrays
            __declspec( dllexport ) Bytes( int length );
            // Erzeugt ein neuen Byte Array durch kopieren der bytes
            //  daten: Die Bytes, die kopiert werden sollen
            //  length: Die Anzahl der Bytes die kopiert werden sollen
            __declspec( dllexport ) Bytes( const char *daten, int length );
            // L�scht den Array
            __declspec( dllexport ) ~Bytes();
            // Bef�llt den Bytearray durch kopieren der Bytes
            //  daten: Die Bytes, die kopiert werden sollen
            __declspec( dllexport ) void setBytes( const char *daten );
            // L�scht den Array und erzeugt einen neuen
            //  daten: Die Bytes, die kopiert werden sollen
            //  length: Die n�nge des Arrays
            __declspec( dllexport ) void setBytes( const char *daten, int length );
            // L�scht den Array und �bernimmt den �bergebenen ohne zu kopieren
            //  daten: Der neue Byte Array
            //  length: Die n�nge des Arrays
            __declspec( dllexport ) void setBytesZ( char *daten, int length );
            // Setzt alle Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            __declspec( dllexport ) void fill( const char c );
            // Setzt eine bestimmte Anzahl von Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            //  len: Die Anzahl der Bytes die gesetzt werden sollen
            __declspec( dllexport ) void fill( const char c, int len );
            // Setzt einen bestimmte Abschnitt von Bytes des Arrays auf einen bestimmten Wert
            //  c: Der Wert, auf den die Bytes gesetzt werden sollen
            //  beg: Die Startposition des zu setzenden Abschnittes
            //  end: Die Endposition des zu setzenden Abschnittes (nicht enthalten)
            __declspec( dllexport ) void fill( const char c, int beg, int end );
            // Kopiert bestimmte bytes in den Array
            //  c: Die Bytes, die kopiert werden sollen
            //  cLength: Die Anzahl an Bytes, die gesetzt werden sollen
            __declspec( dllexport ) void fill( const char *c, int cLength );
            // Setzt ein bestimmtes Byte auf einen Wert
            //  c: Der Wert, auf den das Byte gesetzt werden soll
            //  pos: Die Position des Bytes im Array
            __declspec( dllexport ) void set( const char c, int pos );
            // Gibt die L�nge des Arrays zur�ck
            __declspec( dllexport ) int getLength() const;
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
        class Key
        {
        private:
            unsigned char *key;
            int length;
            int pos;
            int ref;

        public:
            // Erzeugt ein leeres Zeichnung
            __declspec( dllexport ) Key();
            // Erzeugt ein neues Zeichnung mi einem Schl�ssel
            //  s: Der Schl�ssel, der zum verschl�sseln und entchl�sseln verwendet werden soll
            //  length: Die L�nge des Schl�ssels
            __declspec( dllexport ) Key( const char *s, int length );
            // L�scht das Zeichnung
            __declspec( dllexport ) ~Key();
            // Setzt die Position im Schl�ssel, wo mit dem verschl�sseln und entschl�sseln begonnen werden soll
            //  p: Die Position im Schl�ssel
            __declspec( dllexport ) void setPos( __int64 p );
            // Setzt den Schl�ssel, der zum ver- und entschl�sseln verwendet werden soll
            //  s: Der Schl�ssel
            //  length: Die L�nge des Schl�ssels
            __declspec( dllexport ) void setKey( const char *s, int length );
            // Verschl�sselt einen Byte Array mit dem gesetzten Schl�ssel
            //  daten: Der Byte Array, der verschl�sselt werden soll. Wird von der Funktion ver�ndert
            __declspec( dllexport ) void codieren( Bytes *daten );
            // Entschl�sselt einen Byte Array mit dem gesetzten Schl�ssel
            //  daten: Der Byte Array, der entschl�sselt werden soll. Wird von der Funktion ver�ndert
            __declspec( dllexport ) void decodieren( Bytes *daten );
            // Erh�ht den Reference Counting Z�hler.
            //  return: this.
            __declspec( dllexport ) Key *getThis();
            // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
            //  return: 0.
            __declspec( dllexport ) Key *release();
        };
    }
}

#endif