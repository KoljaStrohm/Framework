#ifndef Datei_H
#define Datei_H

#include "Array.h"
#include <fstream>

namespace Framework
{
    class Text; // Text.h
    class Zeit; // Zeit.h
	namespace Encryption
	{
		class Key; // Schl�ssel.h
	}
    class Datei; // aus dieser Datei

    // Lie�t und schreibt in eine Datei
    class Datei
    {
    public:
        class Style
        {
        public:
            const static int lesen = 0x01; // datei wird zum lesen ge�ffnet
            const static int schreiben = 0x02; // datei wirt zum schreiben ge�ffnet
            const static int ende = 0x04; // setzt dateizeiger ans Ende der Datei
        };
    private:
        int ref;
        std::fstream *stream;
        Text *pfad;
        __int64 gr;
        char tmpLByte;
        char tmpLBPos;
        char tmpSByte;
        char tmpSBPos;
		Encryption::Key *key;

    public:
        // Konstruktor 
        __declspec( dllexport ) Datei();
        // Destruktor 
        __declspec( dllexport ) ~Datei();
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad
        __declspec( dllexport ) void setDatei( const char *pfad );
        // Setzt den Pfad zur Datei
        //  pfad: Der Pfad
        __declspec( dllexport ) void setDatei( Text *pfad );
        // Benennt die Datei um oder verschiebt sie
        //  pfad: Der neue Pfad zur Datei. Wenn sich nur der Name �ndert, wird sie nur umbenannt
        //  return: 1, wenn das umbenennen erfolgreich war. 0, sonst
        __declspec( dllexport ) bool umbenennen( const char *pfad );
        // Benennt die Datei um oder verschiebt sie
        //  pfad: Der neue Pfad zur Datei. Wenn sich nur der Name �ndert, wird sie nur umbenannt
        //  return: 1, wenn das umbenennen erfolgreich war. 0, sonst
        __declspec( dllexport ) bool umbenennen( Text *pfad );
        // L�scht die Datei
        //  return: 1, wenn das l�schen erfolgreich war. 0 sonst
        __declspec( dllexport ) bool remove();
        // Erstellt die Datei neu. Wenn im Pfad Ordner vorkommen, die nicht existieren, so werden sie erstellt
        //  return 1: wenn das erstellen erfolgreich war. 0, sonst
        __declspec( dllexport ) bool erstellen();
        // �ffnet die Datei
        //  style: Legt fest, ob die Datei zum lesen und/oder schreiben ge�ffnet wird. Alle Elemente aus Datei::Style:: sin m�glich
        //  return 1: wenn die datei erfolgreich ge�ffnet werden konnte. 0 sonnst
        __declspec( dllexport ) bool open( int style );
        // Setzt die Position des Bytes, das als n�chstes gelesen werden soll
        //  pos: Der Index des Bytes
        //  ende: 1, wenn der Index vom ende der Datei z�hlt. 0, wenn der Index vom Beginn der Datei z�hlt
        __declspec( dllexport ) void setLPosition( __int64 pos, bool ende );
        // Setzt die Position des Bytes, das als n�chstes �berschrieben wird
        //  pos: Der Index des Bytes
        //  ende: 1, wenn der Index vom ende der Datei z�hlt. 0, wenn der Index vom Beginn der Datei z�hlt
        __declspec( dllexport ) void setSPosition( __int64 pos, bool ende );
        // Schreibt in die Datei
        //  bytes: Ein Array von bytes, die geschrieben werden sollen.
        //  len: Wie viele Bytes in die Datei geschrieben werden sollen
        __declspec( dllexport ) void schreibe( char *bytes, int len );
        // Lie�t aus der Datei
        //  bytes: Ein Array, der mit Bytes aus der Datei gef�llt werden soll
        //  len: Wie viele Bytes aus der Datei gelesen werden sollen
        __declspec( dllexport ) void lese( char *bytes, int len );
        // Lie�t die n�chste zeile der Datei ein
        //  return: Die gelesene Zeile als Text mit zeilenumbruch
        __declspec( dllexport ) Text *leseZeile();
        // Schlie�t die datei
        __declspec( dllexport ) void close();
		// Setzt den Schl�ssel f�r die Datei
		__declspec( dllexport ) void setKey( char *s, int l );
#ifdef WIN32
        // Setzt den Zeitpunkt der letzten �nderung der Datei (nur f�r Windows)
        //  zeit: den Zeitpunkt der letzten �nderung
        //  return: 1, wenn der Zeitpunkt gesetzt wurde. 0 sonst
        __declspec( dllexport ) bool setLetzte�nderung( Zeit *zeit );
#endif
        // Lie�t das n�chste Bit aus der Datei
        //  bit: Eine Referenz auf deinen bool, in dem das Bit gespeichert wird
        //  return 1, falls das lesen erfolgreich war. 0, sonst
        __declspec( dllexport ) bool getNextBit( bool &bit );
        // Speichert ein einzelnes Bit in der Datei
        //  bit: Das bit, welches gespeichert werden soll
        //  return 1, falls das speichern erfolgreich war
        __declspec( dllexport ) bool setNextBit( bool bit );
        // Pr�ft, ob die Datei ein Verzeichnis ist
        //  return 1, falls die Datei ein Verzeichnis ist. 0, sonst
        __declspec( dllexport ) bool istOrdner() const;
        // Pr�ft, ob die Datei bereits ge�ffnet wurde
        //  return: 1, wenn die Datei ge�ffnet ist. 0 sonnst
        __declspec( dllexport ) bool istOffen() const;
        // Gibt die Anzahl an Unterdateien von dem Verzeichnis zur�ck
        //  return: 0, falls die Datei kein Verzeichnis ist. Sonst die Anzahl der Unterdateien
        __declspec( dllexport ) int getUnterdateiAnzahl() const;
        // Gibt eine Liste mit unterdateien zur�ck
        //  return 0, falls die Datei kein Verzeichnis ist. Eine Liste mit den Namen der Unterdateien
        __declspec( dllexport ) RCArray< Text > *getDateiListe() const;
        // Gibt die Gr��e der Datei zur�ck
        // return -1, falls die Datei ein Verzeichnis ist oder ein Fehler auftrat. Sonst die gr��e der Datei
        __declspec( dllexport ) __int64 getSize() const;
        // Gibt den Zeitpunkt der letzten �nderung zur�ck
        //  return: 0, falls ein Fehler aufgetreten ist. Der Zeitpunkt der letzten �nderung sonst
        __declspec( dllexport ) Zeit *getLastChange() const;
        // Pr�ft, ob die Datei existiert
        //  return: 1, falls die Datei existiert. 0 sonnst
        __declspec( dllexport ) bool existiert() const;
        // Gibt den Index des Bytes aus der Datei zur�ck, welches als n�chstes gelesen werden w�rde
        // return -1, falls ein Fehler aufgetreten ist. Sonst die Position des Lesezeigers
        __declspec( dllexport ) __int64 getLPosition() const;
        // Gibt den Index des Bytes aus der Datei zur�ck, welches als n�chstes �berschrieben werden w�rde
        // return -1, falls ein Fehler aufgetreten ist. Sonst die Position des Schreibzeigers
        __declspec( dllexport ) __int64 getSPosition() const;
        // Pr�ft, ob die Datei vollst�ndig gelesen wurde
        //  return 1, wenn die Datei vollst�ndig gelesen wurde. 0, sonst
        __declspec( dllexport ) bool istEnde() const;
        // Gibt den Pfad zur Datei zur�ck
        __declspec( dllexport ) Text *getPfad() const;
        // Gibt den Pfad zur Datei ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Text *zPfad() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Datei *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Datei *release();
    };

    // Datei Funktionen

    // Sucht einen unbenutzten Dateinamen
    //  zPfad: Ein Zeiger zu dem Pfad, in dem ein unbenutzter Dateiname gefunden werden soll. Ohne erh�hten Reference Counter.
    //          Wird auch als r�ckgabewert benutzt
    __declspec( dllexport ) void GetFreePfad( Text *zPfad );
    // Erstellt den vollst�ndigen Pfad mit Datei
    //  pfad: Der Pfad zur Datei
    //  return: 1, falls das erstellen erfolgreich war.
    __declspec( dllexport ) bool DateiPfadErstellen( Text* pfad );
    // L�scht die angegebene Datei
    //  pfad: Der Pfad zur Datei
    //  return: 1, falls die Datei gel�scht wurde
    __declspec( dllexport ) bool DateiRemove( Text *pfad );
    // Benennt eine Datei um oder verschiebt sie
    //  pfad_alt: Der Pfad zur Datei, die umbenannt werden soll.
    //  pfad_neu: Der neue Pfad zur Datei. Wenn sich nur der Name �ndert, wird sie nur umbenannt
    //  return: 1, wenn das umbenennen erfolgreich war. 0, sonst
    __declspec( dllexport ) bool DateiUmbenennen( Text *pfad_alt, Text *pfad_neu );
    // Pr�ft, ob Datei existiert
    //  pfad: Der Pfad zur Datei
    //  return: 1, wenn die Datei existiert. 0, wenn die Datei nicht gefunden wurde
    __declspec( dllexport ) bool DateiExistiert( Text *pfad );
    // pr�ft, ob pfad ein Verzeichnis ist
    //  pfad: Der Pfad zur Datei
    //  return: 1, wenn die Datei ein Verzeichnis ist. 0 sonst
    __declspec( dllexport ) bool DateiIstVerzeichnis( Text *pfad );
    // Erstellt den vollst�ndigen Pfad mit Datei
    //  pfad: Der Pfad zur Datei
    //  return: 1, falls das erstellen erfolgreich war.
    __declspec( dllexport ) bool DateiPfadErstellen( const char *pfad );
    // L�scht die angegebene Datei
    //  pfad: Der Pfad zur Datei
    //  return: 1, falls die Datei gel�scht wurde
    __declspec( dllexport ) bool DateiRemove( const char *pfad );
    // Benennt eine Datei um oder verschiebt sie
    //  pfad_alt: Der Pfad zur Datei, die umbenannt werden soll.
    //  pfad_neu: Der neue Pfad zur Datei. Wenn sich nur der Name �ndert, wird sie nur umbenannt
    //  return: 1, wenn das umbenennen erfolgreich war. 0, sonst
    __declspec( dllexport ) bool DateiUmbenennen( const char *pfad_alt, const char *pfad_neu );
    // Pr�ft, ob Datei existiert
    //  pfad: Der Pfad zur Datei
    //  return: 1, wenn die Datei existiert. 0, wenn die Datei nicht gefunden wurde
    __declspec( dllexport ) bool DateiExistiert( const char *pfad );
    // pr�ft, ob pfad ein Verzeichnis ist
    //  pfad: Der Pfad zur Datei
    //  return: 1, wenn die Datei ein Verzeichnis ist. 0 sonst
    __declspec( dllexport ) bool DateiIstVerzeichnis( const char *pfad );
}

#endif