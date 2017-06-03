#ifndef Schrift_H
#define Schrift_H

#include "Critical.h"
#include "Punkt.h"

namespace Framework
{
    class Bild; // Bild.h
    class Text; // Text.h
    struct VScrollData; // Scroll.h
    struct HScrollData; // Scroll.h
    class Buchstabe; // aus dieser Datei
    class Alphabet; // aus dieser Datei
    class Schrift; // aus dieser Datei

    // Speichert die Alphawerte eines Zeichens einer bestimmten Schrift
    // Die anderen Farbwerte werden durch die Schriftfarbe bestimmt. Daher nur die Alpha werte.
    class Buchstabe
    {
    private:
        Punkt size;
        Punkt pos;
        unsigned char *alpha;
        int schriftSize;
        int drawSg;
        int ref;

    public:
        // Erstellt ein neues leeres Zeichnung
        __declspec( dllexport ) Buchstabe();
        // L�scht das Zeichnung
        __declspec( dllexport ) ~Buchstabe();

        // Erstellt einen neuen Buchstaben mit bestimmter Gr��e
        //  size: Die Gr��e des Buchstabens in Pixel
        __declspec( dllexport ) void NeuBuchstabe( Punkt &size );
        // Setzt den Alphawert eines bestimmten Pixels
        //  pos: Die position des Pixels
        //  alpha: Der Wert des Pixels
        __declspec( dllexport ) void setPixel( Punkt &pos, unsigned char alpha );
        // Setzt den Alphawert eines bestimmten Pixels
        //  x: die x Position des Pixels
        //  y: die y Position des Pixels
        //  alpha: Der Wert des Pixels
        __declspec( dllexport ) void setPixel( int x, int y, unsigned char alpha );
        // Setzt den Alphawert eines bestimmten Pixels
        //  i: der Index des Pixels. Er berechnet sich durch x + y * breite und geht von 0 bis breite * h�he - 1
        //  alpha: Der Wert des Pixels
        __declspec( dllexport ) void setPixel( int i, unsigned char alpha );
        // Setzt die Position, an die der Buchstabe gezeichnet werden soll
        //  pos: Die position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setPosition( Punkt &pos );
        // Setzt die Position, an die der Buchstabe gezeichnet werden soll
        //  x: Die x position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        //  y: Die y position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setPosition( int x, int y );
        // Setzt die Schriftgr��e, zu der der Buchstabe geh�rt
        //  sg: Die Schriftgr��e des Buchstabens. Wenn der Buchstabe in einer anderen gr��e gezeichnet werden soll, wird automatisch skalliert
        __declspec( dllexport ) void setSchriftSize( int sg );
        // Setzt die Schriftgr��e, in der der Buchstabe gezeichnet werden soll
        //  dsg: Die Schriftgr��e, in der der Buchstabe gezeichnet werden soll. Ist die ungleich der Schriftgr��e, zu der der Buchstabe geh�rt, so wird automatisch skalliert.
        __declspec( dllexport ) void setDrawSchriftSize( int dsg );

        // Gibt die alpha Werte des Buchstabens als array zur�ck wobei die werte Zeilenweise hintereinander stehen
        __declspec( dllexport ) unsigned char *getBuff() const;
        // Gibt die Gr��e des Buchstabens in Pixeln nicht skalliert zur�ck.
        __declspec( dllexport ) const Punkt &getSize() const;
        // Gibt die Breite des Buchstabens in Pixeln zur�ck (Der Wert wurde bereits mit der Draw Schriftgr��e skalliert)
        __declspec( dllexport ) int getBreite() const;
        // Gibt die H�he des Buchstabens in Pixeln zur�ck (Der Wert wurde bereits mit der Draw Schriftgr��e skalliert)
        __declspec( dllexport ) int getHeight() const;
        // Gibt die nicht skallierte H�he des Buchstabens in Pixeln zur�ck
        __declspec( dllexport ) int getNormHeight() const;
        // Zeichnet den Buchstaben in ein bestimmtes Bild
        // Nutze (setPosition) und (setDrawSchriftGr��e) um die Position und die Gr��e zu ver�ndern
        //  zRObj: Das Bild, in den der Buchstabe gezeichnet werden soll
        //  f: Die Farbe, in der der Buchstabe gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj, int f ) const;

        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Buchstabe *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Buchstabe *release();
    };

    // Speichert alle Buchstaben der selben Schriftgr��e.
    // Wird von der Schrift klasse verwendet
    class Alphabet
    {
    private:
        Buchstabe **zeichen;
        int schriftSize;
        int drawSchriftSize;
        Punkt pos;
        int zeilenHeight;
        int zeilenAbstand;
        int ref;

    public:
        // Erzeugt ein leeres Zeichnung
        __declspec( dllexport ) Alphabet();
        // L�scht ein Zeichnung
        __declspec( dllexport ) ~Alphabet();

        // L�scht alle gespeicherten Zeichen
        __declspec( dllexport ) void NeuAlphabet();
        // F�gt dem Alphabet einen Buchstaben hinzu
        // Wenn der hinzugef�gte Buchstabe bereits existiert wird er �berschrieben
        //  i: Der ASCII code des Buchstaben, der hinzugef�gt werden soll
        //  buchstabe: Der Buchstabe, der hinzugef�gt wird
        __declspec( dllexport ) void setBuchstabe( unsigned char i, Buchstabe *buchstabe );
        // Setzt die Schriftgr��e des Alphabets und die der gespeicherten buchstaben
        //  gr: Die Schriftgr��e des Alphabets
        __declspec( dllexport ) void setSchriftSize( int gr );
        // Setzt die Schriftgr��e, in der die gespeicherten Buchstaben gezeichnet werden sollen.
        //  gr: Die Zeichen Schriftgr��e. Wenn sie ungleich der Schriftgr��e des Alphabets ist, wird automatisch skalliert
        __declspec( dllexport ) void setDrawSchriftSize( int gr );
        // Setzt den Zeilenabstand beim Zeichnen eines Textes
        //  za: Der Abschtand zum unteren Ende der Zeile dar�ber in Pixeln
        __declspec( dllexport ) void setZeilenAbstand( int za );
        // Setzt die Position, an die der Erste buchstabe gezeichnet werden soll
        //  pos: Die position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setDrawPosition( Punkt &pos );
        // Setzt die Position, an die der Erste buchstabe gezeichnet werden soll
        //  x: Die x Position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        //  y: Die y Position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setDrawPosition( int x, int y );

        // Gibt den gespeicherten Buchstaben zu einem bestimmten ASCII Zeichen zur�ck
        //  i: Der ASCII code des Zeichens
        //  return: Ein Zeiger zu dem Buchstaben mit erh�htem Reference Counter
        __declspec( dllexport ) Buchstabe *getBuchstabe( unsigned char i ) const;
        // Gibt den gespeicherten Buchstaben zu einem bestimmten ASCII Zeichen zur�ck
        //  i: Der ASCII code des Zeichens
        //  return: Ein Zeiger zu dem Buchstaben ohne erh�htem Reference Counter
        __declspec( dllexport ) Buchstabe *zBuchstabe( unsigned char i ) const;
        // Pr�ft, ob zu einem bestimmten ASCII code ein Zeichen vorhanden ist
        //  b: Der zu pr�fende ASCII code
        //  return: (true), wenn ein Zeichen zu dem Code gefunden wurde. (false) sonnst
        __declspec( dllexport ) bool hatBuchstabe( unsigned char b ) const;
        // Gibt die Schriftgr��e zur�ck, deren Zeichen in diesem Alphabet gespeichert werden
        __declspec( dllexport ) int getSchriftSize() const;
        // Gibt die Schriftgr��e zur�ck, in der die gespeicherten Zeichen gezeichnet werden
        __declspec( dllexport ) int getDrawSchriftSize() const;
        // Gibt den Abstand in Pixeln zum unteren Ende der dar�ber ligenden Zeile zur�ck
        __declspec( dllexport ) int getZeilenAbstand() const;
        // Gibt die skallierte H�he zur�ck, die eine gezeichnete Zeile in Pixeln ben�tigt
        __declspec( dllexport ) int getZeilenHeight() const;
        // gibt die Position zur�ck, an der der erste Buchstabe gezeichnet wird
        __declspec( dllexport ) const Punkt &getPosition() const;
        // Ermittelt, wie viele Pixel ben�tigt werden, um einen Bestimmten Text vollst�ndig darzustellen
        //  zTxt: Der Text, von dem die Breite in Pixeln ermitelt werden soll
        __declspec( dllexport ) int getTextBreite( Text *zTxt ) const;
        // Ermittelt, wie viele Pixel ben�tigt werden, um einen Bestimmten Text vollst�ndig darzustellen
        //  zTxt: Der Text, von dem die H�he in Pixeln ermitelt werden soll
        __declspec( dllexport ) int getTextHeight( Text *zTxt ) const;
        // Ermittelt das Zeichen im Text, auf das die Maus zeigt
        //  zTxt: Der Text, auf den die Maus Zeigt
        //  mausX: Die X Position der Maus in Pixeln Relativ zur Position des ersten Zeichens
        //  mausY: Die Y Position der Maus in Pixeln Relativ zur Position des ersten Zeichens
        __declspec( dllexport ) int textPos( Text *zTxt, int mausX, int mausY ) const;
        // F�gt Zeilenumbr�che in den Text ein, so dass er bei einer vorgegebenen Breite follst�ndig angezeigt wird
        //  zText: Der text, in den die Zeilenumbr�che eingef�gt werden sollen
        //  maxBreite: Die Breite in Pixeln auf der der Text follst�ndig angezeigt werden soll
		//  schriftSize: Die Schriftgr��e, in der der Text passend dargestellt werden soll
        __declspec( dllexport ) void textFormatieren( Text *zText, int maxBreite, int schriftSize );
        // Zeichnet einen Bestimmten Text auf ein Bild
        // Nutze (setDrawPosition) und (setDrawSchriftGr��e) um die Position und die Gr��e zu ver�ndern
        //  zText: Der Text, der gezeichnet werden soll
        //  zRObj: Das Bild, auf das gezeichnet werden soll
        //  f: Die Farbe, in der der Text gezeichnet werden soll
        __declspec( dllexport ) void render( Text *zTxt, Bild &zRObj, int f ) const;
        // Zeichnet einen Bestimmten Text mit Cursor und einf�rbung auf ein Bild
        // Nutze (setPosition) und (setDrawSchriftGr��e) um die Position und die Gr��e zu ver�ndern
        //  zText: Der Text, der gezeichnet werden soll
        //  zRObj: Das Bild, auf das gezeichnet werden soll
        //  cpos: Die position des Cursors im Text
        //  cf: Die Farbe des Cursors
        //  fbeg: Die Position des Zeichens im Text, wo die Einf�rbung beginnen soll. Der Text wird von dort bis zur Cursorposition eingef�rbt
        //  ff: Die Hintergrund Farbe des eingef�rbten Textes
        //  f: Die Farbe, in der der Text gezeichnet werden soll
        __declspec( dllexport ) void render( Text *zTxt, Bild &zRObj, int cpos, int cf, int fbeg, int ff, int f ) const;

        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Alphabet *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Alphabet *release();
    };

    // Specihert eine Liste von Alphabeten mit verschiedener Schriftgr��e.
    // Wird von der Schrift Klasse verwendet, um alle Zeichen der Schriftgr��e nach sortiert zu speichern.
    class AlphabetArray
    {
    private:
        AlphabetArray *next;
        Alphabet *This;

    public:
        // Erzeugt eine neue Liste
        __declspec( dllexport ) AlphabetArray();
        // L�scht eine Liste
        __declspec( dllexport ) ~AlphabetArray();

        // F�gt der Liste ein Alphabet hinzu
        // Wenn bereits ein Alphabet mit der selben Schriftgr��e existiert, wird das Alphabet nicht hinzugef�gt
        //  alphabet: Das Alphabet, welches hinzugef�gt werden soll
        //  return: (true), wenn das Alphabet hinzugef�gt wurde. (false) sonnst.
        __declspec( dllexport ) bool addAlphabet( Alphabet *alphabet );
        // L�scht ein Alphabet bestimmter Schriftgr��e aus der Liste
        //  sg: Die Schriftgr��e des Alphabets, welches entfernt werden soll
        //  return: (true), wenn ein Alphabet entfernt wurde. (false) sonnst
        __declspec( dllexport ) bool removeAlphabet( int sg );
        // Setzt die Schriftgr��e, in der gezeichnet werden soll
        //  sg: Die Schriftgr��e
        __declspec( dllexport ) void setDrawSchriftSize( int sg );
        // Setzt den Zeilenabstand, der zum zeichnen verwendet werden soll
        //  za: Der Zeilenabstand zum unteren Ende der dar�ber liegenden zeile in Pixeln
        __declspec( dllexport ) void setZeilenAbstand( int za );
        // Setzt den Zeiger auf das n�chste Element der Liste auf 0
        __declspec( dllexport ) void setNext0();

        // Gibt ein bestimmtes Alphabet mit erh�htem Reference Counter zur�ck
        //  sg: Die Schriftgr��e, dessen Alphabet gesucht werden soll
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *getAlphabet( unsigned char sg ) const;
        // Gibt ein bestimmtes Alphabet ohne erh�htem Reference Counter zur�ck
        //  sg: Die Schriftgr��e, dessen Alphabet gesucht werden soll
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *zAlphabet( unsigned char sg ) const;
        // Gibt ein bestimmtes Alphabet mit erh�htem Reference Counter zur�ck
        //  index: Der Index des gesuchten Alphabets in der Reihenfolge wie sie der Liste hinzugef�gt wurden
        //  count: Hier sollte 0 �bergeben werden. Gibt an auf dem wievielten Element der Liste die Funktion aufgerufen wird.
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *getAlphabetI( int index, int count ) const;
        // Gibt ein bestimmtes Alphabet ohne erh�htem Reference Counter zur�ck
        //  index: Der Index des gesuchten Alphabets in der Reihenfolge wie sie der Liste hinzugef�gt wurden
        //  count: Hier sollte 0 �bergeben werden. Gibt an auf dem wievielten Element der Liste die Funktion aufgerufen wird.
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *zAlphabetI( int index, int count ) const;
        // Gibt einen Zeiger auf das n�chste Element der Liste zur�ck
        __declspec( dllexport ) AlphabetArray *getNext() const;
    };

    // Speichert alle Buchstaben einer Schrift in verschiedenen Schriftgr��en
    class Schrift
    {
    private:
        unsigned char alphabetAnzahl;
        AlphabetArray *alphabet;
        int schriftSize;
        int zeilenAbstand;
        Punkt drawPos;
        Critical cs;
        int ref;

    public:
        // Erzeugt eine leere Schrift
        __declspec( dllexport ) Schrift();
        // L�scht ein Zeichnung
        __declspec( dllexport ) ~Schrift();

        // Bereitet die Schrift auf das zeichnen eines Textes vor.
        // Dies ist notwendig, falls mehrere Threads gleichzeitig die Schrift benutzen
        __declspec( dllexport ) void lock();
        // Beendet den Zeichenforgang der Schrift
        // Muss f�r jeden aufruf von (lock();) einmal vom selben Thread aufgerufen werden,
        // damit die Schrift wieder von anderen Threads verwendet werden kann
        __declspec( dllexport ) void unlock();
        // F�gt der Schrift ein Alphabet hinzu. Sollte bereits ein Alphabet der selben Schriftgr��e existieren, wird das Alphabet nicht hinzugef�gt
        //  alphabet: Das Alphabet, welches hinzugef�gt werden soll
        //  return: (true), wenn das Alphabet hinzugef�gt wurde. (false) sonnst
        __declspec( dllexport ) bool addAlphabet( Alphabet *alphabet );
        // L�scht ein bestimmtes Alphabet aus der Schrift
        //  sg: Die Schriftgr��e, deren Alphabet entfernt werden soll
        __declspec( dllexport ) void removeAlphabet( int sg );
        // Setzt die Position, an die der Erste buchstabe gezeichnet werden soll
        //  x: Die x Position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        //  y: Die y Position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setDrawPosition( int x, int y );
        // Setzt die Position, an die der Erste buchstabe gezeichnet werden soll
        //  pos: Die Position relativ zu der Draw Position im zeichen Bild (siehe Bild::setDrawOptions)
        __declspec( dllexport ) void setDrawPosition( Punkt &pos );
        // Setzt die Schriftgr��e, in der gezeichnet werden soll. Die Schrift w�hlt automatisch das passende Alphabet zum Zeichnen
        //  sg: Die Schriftgr��e
        __declspec( dllexport ) void setSchriftSize( int sg );
        // Setzt den Zeilenabstand, der zum zeichnen verwendet werden soll
        //  za: Der Zeilenabstand zum unteren Ende der dar�ber liegenden zeile in Pixeln
        __declspec( dllexport ) void setZeilenAbstand( int za );
        // F�gt Zeilenumbr�che in den Text ein, so dass er bei einer vorgegebenen Breite follst�ndig angezeigt wird
        //  zText: Der text, in den die Zeilenumbr�che eingef�gt werden sollen
        //  maxBreite: Die Breite in Pixeln auf der der Text follst�ndig angezeigt werden soll
        //  schriftSize: Die Schriftgr��e, die verwendet werden soll
        __declspec( dllexport ) void textFormatieren( Text *zText, int maxBreite, int schriftSize );
        // Zeichnet einen Bestimmten Text auf ein Bild
        // Nutze (setDrawPosition) und (setSchriftGr��e) um die Position und die Gr��e zu ver�ndern
        //  zText: Der Text, der gezeichnet werden soll
        //  zRObj: Das Bild, auf das gezeichnet werden soll
        //  f: Die Farbe, in der der Text gezeichnet werden soll
        __declspec( dllexport ) void renderText( Text *zTxt, Bild &zRObj, int f );
        // Zeichnet einen Bestimmten Text mit Cursor und einf�rbung auf ein Bild
        // Nutze (setPosition) und (setDrawSchriftGr��e) um die Position und die Gr��e zu ver�ndern
        //  zText: Der Text, der gezeichnet werden soll
        //  zRObj: Das Bild, auf das gezeichnet werden soll
        //  cpos: Die position des Cursors im Text
        //  cf: Die Farbe des Cursors
        //  fbeg: Die Position des Zeichens im Text, wo die Einf�rbung beginnen soll. Der Text wird von dort bis zur Cursorposition eingef�rbt
        //  ff: Die Hintergrund Farbe des eingef�rbten Textes
        //  f: Die Farbe, in der der Text gezeichnet werden soll
        __declspec( dllexport ) void renderText( Text *zTxt, Bild &zRObj, int cpos, int cf, int fbeg, int ff, int f );
        // Gibt ein bestimmtes Alphabet mit erh�htem Reference Counter zur�ck
        //  sg: Die Schriftgr��e, dessen Alphabet gesucht werden soll
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *getAlphabet( int sg ) const;
        // Gibt ein bestimmtes Alphabet ohne erh�htem Reference Counter zur�ck
        //  sg: Die Schriftgr��e, dessen Alphabet gesucht werden soll
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *zAlphabet( int sg ) const;
        // Gibt ein bestimmtes Alphabet mit erh�htem Reference Counter zur�ck
        //  index: Der Index des gesuchten Alphabets in der Reihenfolge wie sie der Liste hinzugef�gt wurden
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *getAlphabetI( int index ) const;
        // Gibt ein bestimmtes Alphabet ohne erh�htem Reference Counter zur�ck
        //  index: Der Index des gesuchten Alphabets in der Reihenfolge wie sie der Liste hinzugef�gt wurden
        //  return: (0), fals kein passendes Alphabet gefunden wurde
        __declspec( dllexport ) Alphabet *zAlphabetI( int index ) const;
        // Gibt zur�ck, wie viele Alphabete (und damit Schriftgr��en) in der Schrift enthalten sind
        __declspec( dllexport ) unsigned char getAlphabetAnzahl() const;
        // Gibt die Schriftgr��e zur�ck, die zum Zeichnen verwendet wird
        __declspec( dllexport ) int getSchriftSize() const;
        // Gibt den Abstand in Pixeln zum unteren Ende der dar�ber ligenden Zeile zur�ck
        __declspec( dllexport ) int getZeilenabstand() const;
        // Gibt die x Koordinate des ersten Zeichens, dass gezeichnet wird, in Pixeln zur�ck
        __declspec( dllexport ) int getDrawX() const;
        // Gibt die y Koordinate des ersten Zeichens, dass gezeichnet wird, in Pixeln zur�ck
        __declspec( dllexport ) int getDrawY() const;
        // Gibt die Position des ersten Zeichens, dass gezeichnet wird, in Pixeln zur�ck
        __declspec( dllexport ) const Punkt &getDrawPosition() const;
        // Ermittelt, wie viele Pixel ben�tigt werden, um einen Bestimmten Text vollst�ndig darzustellen
        //  zTxt: Der Text, von dem die Breite in Pixeln ermitelt werden soll
        __declspec( dllexport ) int getTextBreite( Text *zTxt ) const;
        // Ermittelt, wie viele Pixel ben�tigt werden, um einen Bestimmten Text vollst�ndig darzustellen
        //  zTxt: Der Text, von dem die H�he in Pixeln ermitelt werden soll
        __declspec( dllexport ) int getTextHeight( Text *zTxt ) const;
        // Ermittelt das Zeichen im Text, auf das die Maus zeigt
        //  zTxt: Der Text, auf den die Maus Zeigt
        //  mausX: Die X Position der Maus in Pixeln Relativ zur Position des ersten Zeichens
        //  mausY: Die Y Position der Maus in Pixeln Relativ zur Position des ersten Zeichens
        __declspec( dllexport ) int textPos( Text *zTxt, int mausX, int mausY ) const;

        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Schrift *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Schrift *release();
    };
}

#endif