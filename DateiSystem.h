#ifndef DateiSystem_H
#define DateiSystem_H

#include <fstream>
#include "Array.h"
#include "Punkt.h"

namespace Framework
{
    class Bild; // Bild.h
    class Text; // Text.h
#ifdef WIN32
    class Buchstabe; // Schrift.h
    class Alphabet; // Schrift.h
    class Schrift; // Schrift.h
    class FBalken; // Fortschritt.h
#else
#define FBalken int
#endif
    class LTDBPixel; // aus dieser Datei
    class LTDBKopf; // aus dieser Datei
    class LTDBK�rper; // aus dieser Datei
    class LTDBDatei; // aus dieser Datei
    class LTDSPixel; // aus dieser Datei
#ifdef WIN32
    class LTDSDateiKopf; // aus dieser Datei
    class LTDSSchriftKopf; // aus dieser Datei
    class LTDSBuchstabenKopf; // aus dieser Datei
    class LTDSBuchstabenK�rper; // aus dieser Datei
    class LTDSDatei; // aus dieser Datei
#endif

    // LTDB Dateivormat --- Dient zum speichern von mehreren Bildern in einer Datei.

    // Dient zum Speichern und Laden eines einzelnen Pixels aus einem Bild im LTDB Dateiformat
    class LTDBPixel // Pixel einer LTDB Datei
    {
    private:
        LTDBPixel *davor; // Letzter Pixel
        char index; // Bitl�nge des Pixels
        char iR, iG, iB, iA;
        char miR, miG, miB, miA;
        char maxIndex; // L�nge des Pixels
        bool �nder : 1; // Ver�ndert sich etwas an den volgenden 5 Variablen
        bool �nderR : 1; // �ndert sich Rot
        bool �nderG : 1; // �ndert sich Gr�n
        bool �nderB : 1; // �ndert sich Blau
        bool �nderA : 1; // �ndert sich Alpha
        unsigned char komp : 3; // Komprimierung der Farbwerte
        unsigned char R; // Rot
        unsigned char G; // Gr�n
        unsigned char B; // Blau
        unsigned char A; // Alpha
        bool addBitZuFarbe( unsigned char bit ); // F�gt den Farbwerten ein Bit hinzu
        bool getNextFarbeBit( char &byte, int i ); // Speichert das n�chste Farbbit in byte
        int ref;

    public:
        // Konstruktor
        //  davor: Der Pixel, der Vorher geladen wurde. 0, falls die� der Erste Pixel ist
        __declspec( dllexport ) LTDBPixel( LTDBPixel *davor );
        // Destruktor 
        __declspec( dllexport ) ~LTDBPixel();
        // zum Laden gedacht. F�gt dem Pixel einiege bits hinzu
        //  byte: Das zuletzt aus der Datei gelesene Byte
        //  begin: Der Index des ersten Bits im byte, wo der Pixel beginnt
        //  return: Der Index des Bits im Byte, wo der Pixel aufgeh�hrt hat. -1, falls der Pixel am ende Des Bytes noch nicht zuende ist
        __declspec( dllexport ) char addByte( char byte, char begin );
        // zum speichern gedacht. Setzt die Farbe, die im Pixel gespeichert werden soll
        //  f: Die zu speichernde Farbe
        __declspec( dllexport ) void setFarbe( int f );
        // Komprimiert den Pixel. Muss vor dem Speichern aufgerufen werden.
        __declspec( dllexport ) void komprimieren();
        // Gibt ein Teil der Bits zur�ck, die den Pixel representieren
        //  byte: Eine Referens auf das Byte, dass als n�chstes gespeichert werden soll
        //  begin: Der Index des ersten Bits im zu speichernden Byte, wo der Pixel gespeichert werden soll
        //  return: Der Index des Bits im zu speichernden Byte, wo der Pixel aufh�hrt. -1, falls der Pixel im n�chsten Byte fortgesetzt werden muss
        __declspec( dllexport ) char getNextByte( char &byte, int begin );
        // Gibt den Farbwert des Pixels zur�ck
        __declspec( dllexport ) int zuFarbe() const;
        // Gibt zur�ck, ob sich der Anteil an Rot in der Farbe im Vergleich zum Pixel davor ge�ndert hat
        __declspec( dllexport ) bool get�nderR() const;
        // Gibt zur�ck, ob sich der Anteil an Gr�n in der Farbe im Vergleich zum Pixel davor ge�ndert hat
        __declspec( dllexport ) bool get�nderG() const;
        // Gibt zur�ck, ob sich der Anteil an Blau in der Farbe im Vergleich zum Pixel davor ge�ndert hat
        __declspec( dllexport ) bool get�nderB() const;
        // Gibt zur�ck, ob sich der Anteil an Alpha in der Farbe im Vergleich zum Pixel davor ge�ndert hat
        __declspec( dllexport ) bool get�nderA() const;
        // Gibt die Komprimierung des Pixels zur�ck
        __declspec( dllexport ) unsigned char getKomp() const;
        // Gibt den Anteil an Rot in der Farbe des Pixels zur�ck
        __declspec( dllexport ) unsigned char getR() const;
        // Gibt den Anteil an Gr�n in der Farbe des Pixels zur�ck
        __declspec( dllexport ) unsigned char getG() const;
        // Gibt den Anteil an Blau in der Farbe des Pixels zur�ck
        __declspec( dllexport ) unsigned char getB() const;
        // Gibt den Anteil an Alpha in der Farbe des Pixels zur�ck
        __declspec( dllexport ) unsigned char getA() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDBPixel *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDBPixel *release();
    };

    // Der Kopf des LTDB Dateiformates. Hier werden informationen �ber alle Abgespeicherten Bilder verwaltet
    class LTDBDateiKopf
    {
    private:
        RCArray< Text > *bilder;
        Array< __int64 > *pos;
        int bAnzahl;
        int ref;

    public:
        // konstructor
        __declspec( dllexport ) LTDBDateiKopf();
        // destructor 
        __declspec( dllexport ) ~LTDBDateiKopf();
        // Entfernt ein Bild aus dem Dateikopf
        //  i: Der Index des Bildes, welches entfernt werden soll
        __declspec( dllexport ) void removeBild( int i );
        // Entfernt ein Bild aus dem Dateikopf
        //  txt: Der Name des Bildes, welches entfernt werden soll
        __declspec( dllexport ) void removeBild( Text *txt );
        // F�gt dem Dateikopf ein Bild hinzu
        //  txt: Der Name des Bildes.
        __declspec( dllexport ) void addBild( Text *txt );
        // Legt den Index des Bytes aus der Datei fest, wo das Bild anf�ngt
        //  i: Der index Des Bildes
        //  pos: Die Position des Bildes in der Datei
        __declspec( dllexport ) void setBildPos( int i, __int64 pos );
        // Legt den Index des Bytes aus der Datei fest, wo das Bild anf�ngt
        //  txt: Der Name Des Bildes
        //  pos: Die Position des Bildes in der Datei
        __declspec( dllexport ) void setBildPos( Text *txt, __int64 pos );
        // L�dt den Dateikopf einer LTDB Datei
        //  f: Ein Zeiger auf einen Fortschrittsbalken, der zum Laden verwendet werden soll. Kann 0 sein.
        //  inF: Der ge�ffnete ifstream der LTDB Datei, bei dem die Leseposition bereits auf das erste Byte des Dateiopfes zeigt.
        __declspec( dllexport ) void laden( FBalken *f, std::ifstream *inF );
        // Speichert den Dateikopf in einer LTDB Datei
        //  outF: Der ge�ffnete ofstream der LTDB Datei, bei dem die Schreibposition bereits auf das erste Byte des Dateikopfes zeigt.
        __declspec( dllexport ) void speichern( std::ofstream *outF ) const;
        // Gibt den Namen eines bestimmten Bildes zur�ck
        //  i: Der Index des Bildes, dessen Namen zur�ckgegeben werden soll
        //  return: Der Name des bildes
        __declspec( dllexport ) Text *getBild( int i ) const;
        // Gibt den Namen eines bestimmten Bildes zur�ck
        //  i: Der Index des Bildes, dessen Namen zur�ckgegeben werden soll
        //  return: Der Name des bildes ohne erh�hten Reference Counter
        __declspec( dllexport ) Text *zBild( int i ) const;
        // Gibt den Index des Ersten Bytes eines Bildes in der Datei zur�ck
        //  txt: Der Name des Bildes, dessen Beginn gefunden werden soll
        //  return: -1, falls das Bild nicht gefunden wurde.
        __declspec( dllexport ) __int64 getBildPosition( Text *txt ) const;
        // Gibt den Index des Ersten Bytes eines Bildes in der Datei zur�ck
        // Fals der Index nicht existiert wird die Exception std::out_of_range geworfen.
        //  indes: Der Indes des Bildes, dessen Beginn gefunden werden soll
        __declspec( dllexport ) __int64 getBildPosition( int index ) const;
        // Gibt den Index eines Bestimmten Bildes zur�ck
        //  txt: Der Name des Bildes
        //  return: -1, falls das Bild nicht gefunden wurde
        __declspec( dllexport ) int getBildIndex( Text *txt ) const;
        // Gibt die Anzahl der Bilder in der Datei zur�ck
        __declspec( dllexport ) int getbAnzahl() const;
        // Gibt eine Liste mit Bildern in der Datei ohne erh�hten Reference Counter zur�ck.
        // Die Liste sollte nicht ver�ndert werden
        __declspec( dllexport ) RCArray< Text > *zBildListe() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDBDateiKopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDBDateiKopf *release();
    };

    // Die im LTDB Dateikopf gespeicherten Informationen f�r ein einzelnes Bild
    class LTDBKopf
    {
    private:
        __int64 a; // Det LTDB Dateikopf ist maximal 104 Bits lang
        __int32 b; // - bis zu 75 Bits f�r den Titel
        __int8 c;  // - 12 Bits f�r breite
        int ref;   // - 12 Bits f�r h�he

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDBKopf();
        // L�hdt die Informationen �ber ein Bild
        //  f: Der ge�ffnette und an die richtiege Stelle zeigende ifstream der LTDB Datei
        __declspec( dllexport ) void laden( std::ifstream *f );
        // Setzt die Informationen die gespeichert werden sollen
        //  titel: Der Titel des Bildes
        //  gr��e: Die Gr��e des Bildes
        //  return: Die Anzahl der Buchstaben aus dem Titel, die im LTDB Dateiformat nicht gespeichert werden k�nnen. Erlaubt ist nur a-z und A-Z und � � � � und � � � und .
        // Alle gro�buchstaben im Titel werden in Kleinbuchstaben umgewandelt
        __declspec( dllexport ) int Init( Text *titel, const Punkt &gr��e );
        // L�hd informationen aus geladenen Bits. Wird von der laden( std::ifstream ) Funktion verwendet.
        //  BeginBit: Der Index des ersten Bits, welches ausgewertet werden soll
        //  EndBit: Der Index des letzten Bits, welches nichtmehr ausgewertet werden soll
        //  bits: Die Bits, von denen alle von BeginBit bis EndBit ausgewertet werden sollen
        // Insgesamt m�ssen 104 Bits gesetzt werden. Hierauf bezihen sich BeginBit und EndBit
        __declspec( dllexport ) void setBits( int BeginBit, int EndBit, __int16 bits );
        // Speichert die Informationen in eine Datei
        //  f: Der ge�ffnete und an die richtiege Stelle zeigende ofstream der LTDB Datei
        __declspec( dllexport ) void speichern( std::ofstream *f ) const;
        // Gibt die L�nge des Titels zur�ck
        __declspec( dllexport ) int getTitelL�nge() const;
        // Gibt den Titel des Bildes zur�ck
        __declspec( dllexport ) Text *getTitel() const;
        // Gibt die Gr��e des Bildes zur�ck
        __declspec( dllexport ) Punkt getGr��e() const;
        // Gibt die n�chsten zu speichernden Bits zur�ck
        //  begin: Der Index des ersten Bits, in das gespeichert werden soll
        //  end: Der Index des letzten Bits, in das gespeichert werden soll
        //  return: 16 Bits, in denen die Informationen zwischen begin und end stehen
        // Insgesamt m�ssen 104 Bits gelesen werden. Hierauf bezihen sich BeginBit und EndBit
        __declspec( dllexport ) __int16 getBits( int begin, int end )const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDBKopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDBKopf *release();
    };

    // Verwaltet die Pixeldaten eines einzelnen Bildes einer LTDB Datei
    class LTDBK�rper
    {
    private:
        Punkt gr;
        Bild *b;
        int dateiL�nge;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDBK�rper();
        // Konstruktor
        //  k: Der LTDB Kopf des Bildes, der Informationen �ber die Gr��e des Bildes enth�lt
        __declspec( dllexport ) LTDBK�rper( LTDBKopf *k );
        // Destruktor 
        __declspec( dllexport ) ~LTDBK�rper();
        // Setzt die Informationen �ber die Gr��e des Bildes. Wird zum Laden ben�tigt.
        //  k: Der LTDB Kopf des Bildes
        __declspec( dllexport ) void init( LTDBKopf k );
        // Setzt die Informationen �ber die Gr��e des Bildes. Wird zum Laden ben�tigt.
        //  k: Der LTDB Kopf des Bildes
        __declspec( dllexport ) void init( LTDBKopf *k );
        // L�dt die Pixeldaten aus der Datei
        //  zF: Ein Fortschrittsbalken, der 0 sein kann
        //  inF: Der ge�ffnete und an die richtiege Stelle zeigende ifstream der LTDB Datei
        __declspec( dllexport ) void laden( FBalken *zF, std::ifstream *inF );
        // Setzt das Bild, welches gespeichert werden soll
        //  b: Das zu speichernde Bild
        __declspec( dllexport ) void setBild( Bild *b );
        // Speichert die Pixeldaten des Bildes in einer LTDB Datei
        //  zF: Ein Fortschrittsbalken, der 0 sein kann
        //  outF: Der ge�ffnete und an die richtiege Stelle zeigende ofstream der LTDB Datei
        __declspec( dllexport ) void speichern( FBalken *zF, std::ofstream *outF ) const;
        // Gibt das geladene Bild zur�ck
        __declspec( dllexport ) Bild *getBild() const;
        // Gibt die Gr��e des Bildes zur�ck
        __declspec( dllexport ) const Punkt &getGr��e() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDBK�rper *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDBK�rper *release();
    };

    // Verwaltet eine LTDB Datei
    class LTDBDatei
    {
    private:
        Text *pfad;
        LTDBDateiKopf *datKpf;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDBDatei();
        // Destruktor 
        __declspec( dllexport ) ~LTDBDatei();
        // Setzt den Pfad zu Datei
        //  pfad: Der Pfad
        __declspec( dllexport ) void setDatei( Text *pfad );
        // Erstellt eine neue LTDB Datei
        __declspec( dllexport ) void erstellen();
        // Lie�t grundlegende Informationen aus der Datei.
        // Wird ben�tigt, bevor mit der Datei gearbeitet wird
        //  zF: Ein Fortschrittsbalken, der 0 sein kann
        __declspec( dllexport ) void leseDaten( FBalken *zF );
        // L�scht die LTDB Datei
        __declspec( dllexport ) void l�schen();
        // L�scht ein Bild aus der LTDB Datei
        //  zF: Ein Fortschrittsbalken der 0 sein kann
        //  name: Der Name des zu l�schenden Bildes
        __declspec( dllexport ) void l�schen( FBalken *zF, Text *name );
        // L�dt ein Bild aus der LTDB Datei
        //  zF: Ein Fortschrittsbalken, der 0 sein kann
        //  name: Der Name des Bildes, welches geladen werden soll
        //  return: Das geladene Bild. 0, falls das Bild nicht gefunden wurde
        __declspec( dllexport ) Bild *laden( FBalken *zF, Text *name );
        // Speichert ein neues Bild in der LTDB Datei
        //  zF: Ein Fortscrittsbalken, der 0 sein kann
        //  bild: Das Bild, welches gel�scht werden soll
        //  name: Der Name, unter dem das Bild gespeichert werden soll
        //  return: Anzahl der Warnungen, die beim Konvertieren des Namens in einen g�ltigen Namen aufgetreten sind. -1, falls bereis ein Bild mit dem selben Namen existiert
        __declspec( dllexport ) int speichern( FBalken *zF, Bild *bild, Text *name );
        // Gibt eine Liste mit gespeicherten Bildern zur�ck
        // Die Liste sollte nicht ver�ndert werden
        __declspec( dllexport ) RCArray< Text > *zBildListe();
        // Gibt den Pfad zur LTDB Datei zur�ck
        __declspec( dllexport ) Text *getPfad() const;
        // Gibt die Anzahl der Bilder in der LTDB Datei zur�ck
        __declspec( dllexport ) int getBildAnzahl() const;
        // Pr�ft, ob die LTDB Datei existiert
        __declspec( dllexport ) bool istOffen() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDBDatei *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDBDatei *release();
    };

#ifdef WIN32
    // LTDS Dateivormat --- Dient zum speichern von Schriftarten

    // Verwaltet einen einzelnen Pixel von einem Buchstaben
    class LTDSPixel
    {
    private:
        int ref;
        char index;
        char iA;
        char miA;
        char maxIndex; // L�nge des Pixels
        bool �nder;
        bool �nderA;
        unsigned char komp : 3; // Komprimierung der Farbwerte
        unsigned char alpha;
        LTDSPixel *davor;
        bool addBitZuFarbe( unsigned char bit ); // F�gt den Farbwerten ein Bit hinzu
        bool getNextFarbeBit( char &byte, int i ); // Speichert das n�chste Farbbit in byte

    public:
        // Konstruktor
        //  davor: Der Pixel, der vor diesem geladen wurde. 0, fals die� der erste Pixel ist
        __declspec( dllexport ) LTDSPixel( LTDSPixel *davor );
        // Destruktor 
        __declspec( dllexport ) ~LTDSPixel();
        // F�gt dem Pixel einiege geladene Bits hinzu. Zum Laden gedacht.
        //  byte: Das letzte aus der Datei geladene Byte.
        //  begin: Der Index des ersten Bits im Byte, wo der Pixel beginnt
        //  return: Der Index des Letzten Bits in Byte, wo der Pixel aufh�hrt. -1, falls der Pixel im n�chsten Byte weitergeht
        __declspec( dllexport ) char addByte( char byte, char begin );
        // Setzt den Alpha Wert des Pixels. Zum speichern gedacht.
        //  alpha: Der Alpha Wert des Pixels.
        __declspec( dllexport ) void setAlpha( unsigned char alpha );
        // Komprimiert den Pixel. Muss vor dem Speichern aufgerufen werden.
        __declspec( dllexport ) void Komp();
        // Gibt ein Teil der Bits zur�ck, die den Pixel representieren
        //  byte: Eine Referens auf das Byte, dass als n�chstes gespeichert werden soll
        //  begin: Der Index des ersten Bits im zu speichernden Byte, wo der Pixel gespeichert werden soll
        //  return: Der Index des Bits im zu speichernden Byte, wo der Pixel aufh�hrt. -1, falls der Pixel im n�chsten Byte fortgesetzt werden muss
        __declspec( dllexport ) char getNextByte( char &byte, int bbegin );
        // Gibt die Komprimierung des Pixels zur�ck
        __declspec( dllexport ) unsigned char getKomp() const;
        // Gibt zur�ck, ob sich der Alpha Wert im Vergleich zu dem Pixel davor ge�ndert hat
        __declspec( dllexport ) bool get�nderA() const;
        // Gibt den Alpha Wert des Pixels zur�ck
        __declspec( dllexport ) unsigned char getA() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSPixel *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSPixel *release();
    };

    // Verwaltet den Kopf einer LTDS Datei. Er enth�lt Informationen �ber die in der Datei gespeicherten Schriftgr��en
    class LTDSDateiKopf
    {
    private:
        int ref;
        unsigned char sganzahl;
        unsigned char *gr;
        int *pos;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDSDateiKopf();
        // Destruktor 
        __declspec( dllexport ) ~LTDSDateiKopf();
        // L�dt den Kopf aus der LTDS Datei
        //  inF: Der ge�ffnete und an die richtige Stelle zeigende ifstream der LTDS Datei
        __declspec( dllexport ) void laden( std::ifstream *inF );
        // F�gt eine Schriftgr��e hinzu
        //  sg: Die Schriftgr��e, die hinzugef�gt werden soll
        __declspec( dllexport ) void addSG( char sg );
        // L�scht eine Schriftgr��e
        //  sg: Die Schriftgr��e, die gel�scht werden soll
        __declspec( dllexport ) void removeSG( char sg );
        // Speichert den LTDS Kopf in der Datei
        //  outF: Der ge�ffnete und an die richtiege Stelle zeigende ofstream der LTDS Datei
        __declspec( dllexport ) void speichern( std::ofstream *outF ) const;
        // Gibt einen Array von gespeicherten Schriftgr��en zur�ck
        // Der Array sollte nicht ver�dert werden
        __declspec( dllexport ) unsigned char *getSchriftGr��eList() const;
        // Gibt einen Array mit positionen der ersten Bytes f�r jede Schriftgr��e aus der Datei zur�ck
        __declspec( dllexport ) int *getPositionList() const;
        // Gibt die Anzahl der gespeicherten Schriftgr��en zur�ck
        __declspec( dllexport ) int getSchriftGr��eAnzahl() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSDateiKopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSDateiKopf *release();
    };

    // Der Kopf einer Schriftgr��e. Enth�lt Informationen �ber die gespeicherten Zeichen
    class LTDSSchriftKopf
    {
    private:
        int ref;
        unsigned char schriftGr��e;
        unsigned char *zeichen;
        int *pos;
        unsigned char zeichenAnzahl;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDSSchriftKopf();
        // Destruktor 
        __declspec( dllexport ) ~LTDSSchriftKopf();
        // L�dt den Kopf einer Schriftgr��e aus der Datei
        //  inF: Der ge�ffnete und an de richtiege Stelle zeigende ifstream der LTDS Datei
        __declspec( dllexport ) void laden( std::ifstream *inF );
        // Setzt die Schriftgr��e. Zum speichern gedacht
        //  gr: Die Schriftgr��e
        __declspec( dllexport ) void setSchriftgr��e( unsigned char gr );
        // Setzt das Alphabet, welches in der Schriftgr��e gespeichert werden soll
        //  alphabet: Das Alphabet, welches alle zu speichernden Zeichen in der Schriftgr��e enth�lt
        __declspec( dllexport ) void setZeichenAlphabet( Alphabet *alphabet );
        // F�gt der Schriftgr��e ein Zeichen hinzu, welches gespeichert werden soll
        //  zeichen: Der ASCII code des Zeichens, welches hinzugef�gt werden soll
        __declspec( dllexport ) void addZeichen( unsigned char zeichen );
        // L�scht ein Zeichen aus der Schriftgr��e
        //  zeich: Der ASCII code des Zeichens, welches gel�scht werden soll
        __declspec( dllexport ) void removeZeichen( unsigned char zeich );
        // Speichert den Kopf der Schriftgr��e in der LTDS Datei
        //  outF: Der ge�ffnete und an die richtiege Stelle zeigende ofstream der LTDS Datei
        __declspec( dllexport ) void speichern( std::ofstream *outF ) const;
        // Gibt die Schriftgr��e zur�ck, zu der dieser Kopf geh�hrt
        __declspec( dllexport ) unsigned char getSchriftGr��e() const;
        // Gibt die Anzahl der in der Schriftgr��e gespeicherten Zeichen zur�ck
        __declspec( dllexport ) unsigned char getZeichenAnzahl() const;
        // Gibt einen Array mit den Positionen der ersten Bytes von den gespeicherten Zeichen aus der LTDS Datei zur�ck 
        __declspec( dllexport ) int *getPositionen() const;
        // Gibt einen Array mit den ASCII codes der Gespeicherten Zeichen zur�ck
        __declspec( dllexport ) unsigned char *getZeichen() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSSchriftKopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSSchriftKopf *release();
    };

    // Der Kopf eines einzelnen Zeichens aus der LTDS Datei. Enth�lt informationen �ber die Pixelgr��e des Zeichens
    class LTDSBuchstabenKopf
    {
    private:
        int ref;
        unsigned char zeichen;
        Punkt gr��e;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDSBuchstabenKopf();
        // L�dt die Daten aus der LTDS Datei
        //  inF: Der ge�ffnete und an die richtiege Stelle zeigende ifstream der LTDS Datei
        __declspec( dllexport ) void laden( std::ifstream *inF );
        // Setzt die Daten, die gespeichert werden sollen.
        //  zeichen: Der ASCII code des Zeichens
        //  gr��e: Die Gr��e des Zeichens in Pixeln
        __declspec( dllexport ) void init( unsigned char zeichen, const Punkt &gr��e );
        // Setzt die Daten, die gespeichert werden sollen.
        //  zeichen: Der ASCII code des Zeichens
        //  br: Die Breite des Zeichens in Pixeln
        //  h�: Die H�he des Zeichens in Pixeln
        __declspec( dllexport ) void init( unsigned char zeichen, int br, int h� );
        // Speichert die Daten in der LTDS Datei
        //  outF: Der ge�ffnete und auf die richtiege Stelle zeigende ofstream der LTDS Datei
        __declspec( dllexport ) void speichern( std::ofstream *outF ) const;
        // Gibt den ASCII code des Zeichens zur�ck
        __declspec( dllexport ) unsigned char getZeichen() const;
        // Gibt die Breite des Zeichens in Pixeln zur�ck
        __declspec( dllexport ) int getBreite() const;
        // Gibt die H�he des Zeichens in Pixeln zur�ck
        __declspec( dllexport ) int getH�he() const;
        // Gib t die Gr��e des Zeichens in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getGr��e() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSBuchstabenKopf *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSBuchstabenKopf *release();
    };

    // Verwaltet die Pixeldaten eines Zeichens
    class LTDSBuchstabenK�rper
    {
    private:
        int ref;
        Punkt gr��e;
        unsigned char zeichen;
        Buchstabe *buchstabe;

    public:
        // Konstruktor
        //  kopf: Der Kopf des Zeichens
        __declspec( dllexport ) LTDSBuchstabenK�rper( LTDSBuchstabenKopf *kopf );
        // Destruktor 
        __declspec( dllexport ) ~LTDSBuchstabenK�rper();
        // Setzt den Buchstaben, der gespeichert werden soll
        //  zeichen: Der zu speichernde Buchstabe
        __declspec( dllexport ) void setBuchstabe( Buchstabe *zeichen );
        // L�dt die Pixel aus der LTDS Datei
        //  inF: Der ge�ffnete und auf die richtiege Stelle zeigende ifstream der LTDS Datei
        __declspec( dllexport ) void laden( std::ifstream *inF );
        // Speichert die Pixel in die LTDS Datei
        //  outF: der ge�ffnete und an die richtiege Stelle zeigende ofstream der LTDS Datei
        __declspec( dllexport ) void speichern( std::ofstream *outF ) const;
        // Gibt den geladenen Buchstaben zur�ck
        __declspec( dllexport ) Buchstabe *getBuchstabe() const;
        // Gibt den ASCII code des Buchstabens zur�ck
        __declspec( dllexport ) unsigned char getZeichen() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSBuchstabenK�rper *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSBuchstabenK�rper *release();
    };

    // Verwaltet eine LTDS Datei
    class LTDSDatei
    {
    private:
        int ref;
        Text *pfad;
        LTDSDateiKopf *dateiKopf;

    public:
        // Konstruktor 
        __declspec( dllexport ) LTDSDatei();
        // Destruktor 
        __declspec( dllexport ) ~LTDSDatei();
        // Setzt den Pfad zur Datei
        //  txt: Der Pfad
        __declspec( dllexport ) void setPfad( Text *txt );
        // L�dt wichtiege Informationen aus der Datei. Muss vor dem Verwenden der Datei aufgerufen werden
        __declspec( dllexport ) void leseDaten();
        // F�gt der Datei eine Schriftgr��e hinzu, fals diese noch nicht existiert
        //  alphabet: Das Alphabet, welches die Zeichen in der gew�nschten Schriftgr�0e enth�lt
        __declspec( dllexport ) void addSchriftgr��e( Alphabet *alphabet );
        // F�gt einer Schriftgr��e einen Buchstaben hinzu
        //  gr: Die Schriftgr��e des Buchstabens
        //  zeich: Der Buchstabe, der gespeichert werden soll
        //  zeichen: Der ASCII code des Buchstabens
        __declspec( dllexport ) void addBuchstabe( int gr, Buchstabe *zeich, unsigned char zeichen );
        // L�scht eine bestimmte Schriftgr��e aus der Datei
        //  gr: Die Schriftgr��e, die entfernt werden soll
        __declspec( dllexport ) void l�scheSchrifrGr��e( int gr );
        // L�scht einen Buchstaben aus einer Schriftgr��e
        //  gr: Die Schriftgr��e, aus der der Buchstabe entfernt werden soll
        //  zeichen: Der ASCII code des Zeichens, welches gel�scht werden soll
        __declspec( dllexport ) void l�scheBuchstabe( int gr, unsigned char zeichen );
        // L�scht die LTDS Datei
        __declspec( dllexport ) void l�scheDatei();
        // Erstellt die LTDS Datei
        __declspec( dllexport ) void erstelleDatei();
        // Speichert eine gesammte Schrift in der Datei
        //  schrift: Die schrift, die gespeichert werden soll
        __declspec( dllexport ) void speicherSchrift( Schrift *schrift );
        // L�dt die gesammte Schrift aus der Datei
        //  return: Die geladene Schrift. 0, falls ein Fehler beim Laden aufgetreten ist
        __declspec( dllexport ) Schrift *ladeSchrift();
        // L�dt eine einzelne Schriftgr��e aus der Datei
        //  schriftgr��e: Die zu ladende Schriftgr��e
        //  return: Ein Alphabet mit den Zeichen in der Schriftgr��e. 0, falls die Schriftgr��e nicht gefunden wurde
        __declspec( dllexport ) Alphabet *ladeAlphabet( int schriftgr��e );
        // L�dt ein bestimmtes Zeichen einer bestimmten Schriftgr��e
        //  schriftgr��e: Die Schriftgr��e, zu dem das Zeichen geh�rt
        //  zeichen: Der ASCII code des zu ladenden Zeichens
        //  return: Der geladene Buchstabe. 0, falls das Zeichen nicht gefunden wurde.
        __declspec( dllexport ) Buchstabe *ladeBuchstabe( int schriftgr��e, unsigned char zeichen );
        // Gibt den Pfad zur LTDS Datei zur�ck
        __declspec( dllexport ) Text *getPfad() const;
        // Gibt die Anzahl der gespeicherten Schriftgr��en zur�ck
        __declspec( dllexport ) int getAnzahlSchriftgr��en() const;
        // Gibt einen Array mit den gespeicherten Schriftgr��en zur�ck
        // Der Array sollte nicht ver�ndert werden
        __declspec( dllexport ) unsigned char *getSchriftGr��en() const;
        // Gibt die Anzahl an gespeicherten Zeichen in einer Schriftgr��e zur�ck
        //  sg: Die Schriftgr��e, von der die Anzahl der ZEichen ermittelt werden soll
        //  return: Die Anzahl der Zeichen.
        __declspec( dllexport ) unsigned char getAnzahlBuchstaben( int sg );
        // Gibt einen Array mit Buchstaben einer bestimmten Schriftgr��e zur�ck
        //  sg: Die Schriftgr��e
        //  return: Der Array mit den ASCII codes der Zeichen. 0, falls die Schriftgr��e nicht gefunden wurde.
        __declspec( dllexport ) unsigned char *getBuchstaben( int sg );
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) LTDSDatei *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) LTDSDatei *release();
    };
#endif
    // Bit Funktionen 

    // gibt 1-bits in gewinschter anzahl zur�ck.
    //  a: Die Anzahl der Bits, die 1 sein sollen
    //  return: 32 Bits, wobei die einser Bits von rechts beginnen
    __declspec( dllexport ) int Bits( int a );
    // Gibt zur�ck, wie viele Bits ben�tigt werden um eine Zahl darzustellen
    //  c: Die Zahl, die dargestellt werden soll
    //  return: Die Anzahl der ben�tigten Bits
    __declspec( dllexport ) int getBits( char c );
}
#endif