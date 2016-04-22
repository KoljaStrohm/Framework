#ifndef Text_H
#define Text_H

#include "Betriebssystem.h"

namespace Framework
{
    class Text; // aus dieser Datei

    // Ein ersatz f�r String
    class Text
    {
    private:
        char *txt;
        char suchGBeg;
        char suchGEnd;
        int pr�zision;
        int ref;

    public:
        // Erstellt ein neues Text Objekt mit dem Wert ""
        __declspec( dllexport ) Text();
        // Erstellt ein neues Text Objekt indem der Wert aus (txt) kopiert wird
        //  txt: Der Text, der kopiert werden soll
        __declspec( dllexport ) Text( const Text &txt );
        // Erstellt ein neues Text Objekt indem der Wert aus (txt) kopiert wird
        //  txt: Die Zeichenkette, die kopiert werden soll
        __declspec( dllexport ) Text( const char *txt );
        // Erstellt ein neues Text Objekt mit einer zahl als text
        //  zahl: Die Zahl, die im Text sein soll
        __declspec( dllexport ) Text( int zahl );
        // L�scht den Text
        __declspec( dllexport ) ~Text();
        // Legt die Suchgrenzen fest, die von den Suchfunktionen verwendet werden.
        //  gBeg: Das Zeichen, bei dem die Suche beginnen soll
        //  gEnd: Das Zeichen, bei dem die Suche enden soll
        __declspec( dllexport ) void setSuchGrenzen( char gBeg, char gEnd );
        // Setzt den Text, den das Zeichnung speichert
        //  t: Eine Zeichenkette, deren Inhalt kopiert wird
        __declspec( dllexport ) void setText( const char *t );
        // Setzt den Text, den das Zeichnung speichert
        //  t: Eine Zeichenkette, deren Inhalt kopiert wird
        //  l: Die L�nge des Textes, der aus (t) kopiert werden soll
        __declspec( dllexport ) void setText( const char *t, int l );
        // Setzt den Text, den das Zeichnung speichert
        //  t: Das TextZeichnung, dessen Inahlt kopiert werden soll
        __declspec( dllexport ) void setText( Text *t );
        // H�ngt eine Zeichenfolge ans Ende des Textes an, die von der Schrift Klasse beim zeichnen interpretiert wird, so dass der nachfolgende Text in einer anderen Farbe gezeichnet wird.
        //  fc: Der Farbcode im A8R8G8B8 Format
        __declspec( dllexport ) void farbeAnh�ngen( int fc );
        // H�ngt die �bergebene Zahl als Hex Text (0-F) ans Ende des Textes an.
        //  num: Die Zahl, die ins Hex System umgewandelt und angeh�ngt werden soll
        __declspec( dllexport ) void hexAnh�ngen( int num );
        // F�gt den �bergebenen Buchtaben der Zeichenkette hinzu
        //  c: Der Buchstabe, der angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( char c );
        // H�ngt die �bergebene Zeichenkette ans Ende des Textes an
        //  t: Die Zeichenkette, deren Kopie ans Ende des Textes angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( const char *t );
        // H�ngt einen Teil der �bergebenen Zeichenkette ans Ende des Textes an
        //  t: Die Zeichenkette, deren Kopie angeh�ngt werden soll
        //  l: Die L�nge des Textabschnittes der angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( const char *t, int l );
        // H�ngt den Inhalt des eines Textes ans Ende des Textes an
        //  t: Der Text, dessen Kopie ans Ende des Textes angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( Text *t );
        // H�ngt eine Zahl ans Ende Des Textes an
        //  num: Die Zahl, die in einen Text umgewandelt und am Ende angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( int num );
        // H�ngt eine Zahl ohne Vorzeichenbit am Ende des Textes an
        //  num: Die Zahl, die in einen Text umgewandelt und am Ende angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( unsigned int num );
        // H�ngt eine Kommazahl am Ende des Textes an
        //  num: Die Kommazahl, die am Ende des Textes angeh�ngt werden soll
        __declspec( dllexport ) void anh�ngen( double num );
        // F�gt an einer Bestimmten Stelle ein Zeichen in den Text ein
        //  p: Die position im Text bei der das Zeichen eingef�gt werden soll
        //  c: Das Zeichen, das eingef�gt werden soll
        __declspec( dllexport ) void einf�gen( int p, char c );
        // F�gt an einer Bestimmten Stelle im Text eine Zeichenkette ein
        //  p: Die position im Text bei der die Zeichenkette eingef�gt werden soll
        //  t: Die Zeichenkette, deren Kopie an eingef�gt werden soll
        __declspec( dllexport ) void einf�gen( int p, const char *t );
        // F�gt den Inhalt eines Textes an einer Bestimmten Stelle im Text ein
        //  p: Die Position im Text, bei der der inhalt des Textest eingef�gt werden soll
        //  t: Der Text, dessen Kopie an der Stelle eingef�gt werden soll
        __declspec( dllexport ) void einf�gen( int p, Text *t );
        // Ersetzt einen bestimmten Textabschnitt mit einer anderen Zeichenkette
        //  p1: Die Startposition des zu ersetzenden Textabschnittes
        //  p2: Die Endposition des zu ersetzenden Textabschnittes
        //  t: Die Zeichenkette, die an die entsprechende Stelle kopiert werden soll
        // Beispiel: ( "Hallo Welt" ).ersetzen( 2, 5, "lt" ); ergibt: "Halt Welt"
        __declspec( dllexport ) void ersetzen( int p1, int p2, const char *t );
        // Ersetzt einen bestimmten Textabschnitt mit dem Inhalt eines anderen Textes
        //  p1: Die Startposition des zu ersetzenden Textabschnittes
        //  p2: Die Endposition des zu ersetzenden Textabschnittes
        //  t: Der Text, dessen Inhalt an die entsprechende Stelle kopiert werden soll
        // Beispiel: ( "Hallo Welt" ).ersetzen( 2, 5, new Text( "lt" ) ); ergibt: "Halt Welt"
        __declspec( dllexport ) void ersetzen( int p1, int p2, Text *t );
        // Sucht und erstetzt jedes Vorkommen eines bestimmten Buchstaben durch einen anderen
        //  c1: Der Buchstabe der ersetzt werden soll
        //  c2: Der Buchstabe, durch den der Andere ersetzt werden soll
        __declspec( dllexport ) void ersetzen( char c1, char c2 );
        // Sucht und erstetzt jedes Vorkommen einer bestimmten Zeichenkette durch eine andere
        //  t1: Die Zeichenkette, die ersetzt werden soll
        //  t2: Die Zeichenkette, durch welche die Andere ersetzt werden soll
        __declspec( dllexport ) void ersetzen( const char *t1, const char *t2 );
        // Sucht und erstetzt jedes Vorkommen des Inhalts eines Textes durch eine andere Zeichenkette
        //  t1: Der Text, dessen Inhalt gesucht und ersetzt wird
        //  t2: Die Zeichenkette, durch welche das Vorkommen des Textes ersetzt werden soll
        __declspec( dllexport ) void ersetzen( Text *t1, const char *t2 );
        // Sucht und erstetzt jedes Vorkommen einer Zeichenkette durch den Inhalt eines Textes
        //  t1: Die Zeichenkette, die ersetzt werden soll
        //  t2: Der Text, dessen Inhalt das Vorkommen der Zeichenkette ersetzten soll
        __declspec( dllexport ) void ersetzen( const char *t1, Text *t2 );
        // Sucht und erstetzt jedes Vorkommen des Inhalts eines Textes durch den Inhalt eines anderen Textes
        //  t1: Der Text, dessen Vorkommen ersetzt werden sollen
        //  t2: Der Text, dessen Inhalt das Vorkommen der Zeichenkette ersetzten soll
        __declspec( dllexport ) void ersetzen( Text *t1, Text *t2 );
        // Ersetzt das i-te auftreten eines bestimmten Buchstaben mit einem anderen Buchstaben
        //  i: Das wie vielte Auftreten des Buchstabens ersetzt werden soll
        //  c1: Der Buchstabe, dessen i-tes Auftreten erstetzt werden soll
        //  c2: Der Buchstabe, der das i-te Auftreten des anderen Buchstabens ersetzen soll
        __declspec( dllexport ) void ersetzen( int i, char c1, char c2 );
        // Ersetzt das i-te auftreten einer bestimmten Zeichenkette mit einer anderen Zeichenkette
        //  i: Das wie vielte Auftreten der Zeichenkette ersetzt werden soll
        //  c1: Die Zeichenkette, dessen i-tes Auftreten erstetzt werden soll
        //  c2: Die Zeichenkette, die das i-te Auftreten der anderen Zeichenkette ersetzen soll
        __declspec( dllexport ) void ersetzen( int i, const char *t1, const char *t2 );
        // Ersetzt das i-te auftreten des Inhalts eines Textes mit einer Zeichenkette
        //  i: Das wie vielte Auftreten des Textes ersetzt werden soll
        //  c1: Der Text, dessen i-tes Auftreten erstetzt werden soll
        //  c2: Die Zeichenkette, die das i-te Auftreten des Textes ersetzen soll
        __declspec( dllexport ) void ersetzen( int i, Text *t1, const char *t2 );
        // Ersetzt das i-te auftreten einer bestimmten Zeichenkette mit dem Inhalt eines Textes
        //  i: Das wie vielte Auftreten der Zeichenkette ersetzt werden soll
        //  c1: Die Zeichenkette, dessen i-tes Auftreten erstetzt werden soll
        //  c2: Der Text, dessen Inhalt das i-te Auftreten der Zeichenkette ersetzen soll
        __declspec( dllexport ) void ersetzen( int i, const char *t1, Text *t2 );
        // Ersetzt das i-te auftreten eines bestimmten Textes mit dem Inhalt eines anderen Textes
        //  i: Das wie vielte Auftreten des Textes ersetzt werden soll
        //  c1: Der Text, dessen i-tes Auftreten erstetzt werden soll
        //  c2: Der Text, dessen Inhalt das i-te Auftreten des anderen Textes ersetzen soll
        __declspec( dllexport ) void ersetzen( int i, Text *t1, Text *t2 );
        // L�scht den bisherigen Text und erzeugt einen Text, der aus einem Bestimten Buchstaben besteht, mit einer bestimmten L�nge
        //  c: Der Buchstabe, aus dem der Text bestehen soll
        //  l�n: Die L�nge des Textes
        __declspec( dllexport ) void f�llText( char c, int l�n );
        // L�scht ein Bestimmtes Zeichen aus dem Text
        //  p: Die Position des zu l�schenden Zeichens
        __declspec( dllexport ) void l�schen( int p );
        // L�scht einen Bestimmten Textabschnitt
        //  p1: Die Startposition des zu l�schenden Abschnittes
        //  p2: Die Endposition des zu l�schenden Abschnittes (Das Zeichen bei p2 bleibt erhalten)
        __declspec( dllexport ) void l�schen( int p1, int p2 );
        // L�scht jedes Vorkommen eines bestimmten Buchsaben
        //  c: Der Buchstabe, dessen Vorkommen gel�scht werden soll
        __declspec( dllexport ) void l�schen( char c );
        // L�scht jedes Vorkommen einer bestimmten Zeichenkette
        //  t: Die Zeichenkette, deren Vorkommen entfernt werden sollen
        __declspec( dllexport ) void l�schen( const char *t );
        // L�scht jedes Vorkommen des Inhalts eines Textes
        //  t: Der text, dessen Inhalt gel�scht werden soll
        __declspec( dllexport ) void l�schen( Text *t );
        // L�scht das i-te Vorkommen eines bestimmten Buchstaben
        //  i: Das wie vielte Vorkommen des Buchstabens gel�scht werden soll
        //  c: Der Buchstabe, dessen i-tes Vorkommen gel�scht werden soll
        __declspec( dllexport ) void l�schen( int i, char c );
        // L�scht das i-te Vorkommen einer bestimmten Zechenkette
        //  i: Das wie vielte Vorkommen der Zeichenkette gel�scht werden soll
        //  t: Die Zeichenkette, dessen i-tes Vorkommen gel�scht werden soll
        __declspec( dllexport ) void l�schen( int i, const char *t );
        // L�scht das i-te Vorkommen eines bestimmten Textinhaltes
        //  i: Das wie vielte Vorkommen des Textinhaltes gel�scht werden soll
        //  t: Der Text, dessen i-tes Vorkommen gel�scht werden soll
        __declspec( dllexport ) void l�schen( int i, Text *t );
        // Setzt die Anzahl der Nachkommastellen beim Anh�ngen von Kommazahlen
        //  p: Die Anzahl der Stellen nach dem Komma
        __declspec( dllexport ) void setPr�zision( int p );
        // Gibt die L�nge des Textes zur�ck
        __declspec( dllexport ) int getL�nge() const;
        // Ermittelt die neue Curserposition nachdem Dr�cken der 'Links' Pfeiltaste
        //  pos: Die alte Curserposition
        __declspec( dllexport ) int getLKick( int pos ) const;
        // Ermittelt die neue Curserposition nachdem Dr�cken der 'Oben' Pfeiltaste
        //  pos: Die alte Curserposition
        __declspec( dllexport ) int getOKick( int pos ) const;
        // Ermittelt die neue Curserposition nachdem Dr�cken der 'Rechts' Pfeiltaste
        //  pos: Die alte Curserposition
        __declspec( dllexport ) int getRKick( int pos ) const;
        // Ermittelt die neue Curserposition nachdem Dr�cken der 'Unten' Pfeiltaste
        //  pos: Die alte Curserposition
        __declspec( dllexport ) int getUKick( int pos ) const;
        // �berpr�ft, ob im Text der Inhalt eines anderen Textes vorkommt
        //  t: Der Text, nach dessen Inhalt gesucht werden soll
        //  return: (true), wenn der Inhalt des Textes vorkommt. (false) sonnst
        __declspec( dllexport ) bool hat( Text *t ) const;
        // �berpr�ft, ob im Text eine bestimmte Zeichenkette vorkommt
        //  t: Die Zeichenkette, nach der gesucht werden soll
        //  return: (true), wenn die Zeichenkette vorkommt. (false) sonnst
        __declspec( dllexport ) bool hat( const char *t ) const;
        // �berpr�ft, ob im Text ein bestimmtes Zeichen vorkommt
        //  c: Das Zeichen, nach dem gesucht werden soll
        //  return: (true), wenn das Zeichen vorkommt. (false) sonnst
        __declspec( dllexport ) bool hat( char c ) const;
        // �berprft, ob der Text den selben Inhalt wie eine Zeichenkette hat
        //  t: Die Zeichenkette, die verglichen werden soll
        //  return: (true), wenn der Inhalt des Textes gleich der Zeichenkette ist. (false) sonst
        __declspec( dllexport ) bool istGleich( const char *t ) const;
        // �berprft, ob der Text den selben Inhalt wie ein anderer Text hat
        //  t: Der Text, dessen Inhalt verglichen werden soll
        //  return: (true), wenn die Inhalte der Texte �bereinstimmen. (false) sonst
        __declspec( dllexport ) bool istGleich( Text *t ) const;
        // Gibt den Inhalt des Textes als Zeichenkette zur�ck
        __declspec( dllexport ) char *getText() const;
        // Z�hlt, wie oft ein bestimmter Buchstabe im Text vorkomt
        //  c: Der Buchstabe, der gez�hlt werden soll
        //  return: Die Anzahl des Buchstabens im Text
        __declspec( dllexport ) int anzahlVon( char c ) const;
        // Z�hlt, wie oft eine bestimmte Zeichenkette im Text vorkommt
        //  t: Die Zeichenkette, die gez�hlt werden soll
        //  return: Die Anzahl der Zeichenkette im Text
        __declspec( dllexport ) int anzahlVon( const char *t ) const;
        // Z�hlt, wie oft der Inhalt eines Textest im Text vorkommt
        //  t: Der Text, dessen Inhalt gez�hlt werden soll
        //  return: Die Anzahl des Textinhaltes im Text
        __declspec( dllexport ) int anzahlVon( Text *t ) const;
        // Gibt die erste Position eines bestimmten Buchstabens im Text zur�ck
        //  c: Der Buchstabe, der gefunden werden soll
        //  return: Die Position des ersten Vorkommens des Buchstabens
        __declspec( dllexport ) int positionVon( char c ) const;
        // Gibt die erste Position einer bestimmten Zeichenkette im Text zur�ck
        //  t: Die Zeichenkette, die gefunden werden soll
        //  return: Die Position des ersten Vorkommens der Zeichenkette
        __declspec( dllexport ) int positionVon( const char *t ) const;
        // Gibt die erste Position eines Textinhaltes im Text zur�ck
        //  t: Der Text, dessen Inhalt gefunden werden soll
        //  return: Die Position des ersten Vorkommens des Textinhaltes
        __declspec( dllexport ) int positionVon( Text *t ) const;
        // Gibt die i-te Position eines bestimmten Buchstabens im Text zur�ck
        //  c: Der Buchstabe, der gefunden werden soll
        //  i: Das wievielte Vorkommen gefunden werden soll
        //  return: Die Position des i-ten Vorkommens des Buchstabens
        __declspec( dllexport ) int positionVon( char c, int i ) const;
        // Gibt die i-te Position einer bestimmten Zeichenkette im Text zur�ck
        //  t: Die Zeichenkette, die gefunden werden soll
        //  i: Das wievielte Vorkommen gefunden werden soll
        //  return: Die Position des i-ten Vorkommens der Zeichenkette
        __declspec( dllexport ) int positionVon( const char *t, int i ) const;
        // Gibt die i-te Position eines Textinhaltes im Text zur�ck
        //  t: Der Text, dessen Inhalt gefunden werden soll
        //  i: Das wievielte Vorkommen gefunden werden soll
        //  return: Die Position des i-ten Vorkommens des Textinhaltes
        __declspec( dllexport ) int positionVon( Text *t, int i ) const;
        // Gibt einen Text zur�ck, der eine Kopie eines bestimmten Textabschnittes enth�lt
        //  p1: Die Startposition des Textabschnittes
        //  p2: Die Endposition des Textabschnittes (nicht enthalten)
        __declspec( dllexport ) Text *getTeilText( int p1, int p2 ) const;
        // Gibt einen Text zur�ck, der eine Kopie eines bestimmten Textabschnittes enth�lt
        //  p1: Die Startposition des Textabschnittes (Der Textabschnitt geht bis ans Ende des Textes)
        __declspec( dllexport ) Text *getTeilText( int p ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Text *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Text *release();
        // H�ngt eine Zahl ans Ende des Textes an
        __declspec( dllexport ) Text &operator+=( const int num );
        // H�ngt eine Kommazahl ans Ende des Textes an
        __declspec( dllexport ) Text &operator+=( const double num );
        // H�ngt eine Zeichenkette ans Ende des Textes an
        __declspec( dllexport ) Text &operator+=( const char *txt );
        // H�ngt eine Kopie des Inhalts eines Textes ans Ende des Textes an
        __declspec( dllexport ) Text &operator+=( const Text &txt );
        // Setzt den Inhalt des Textes gleich einer Zahl
        __declspec( dllexport ) Text &operator=( const int num );
        // Setzt den Inhalt des Textes gleich einer Kommazahl
        __declspec( dllexport ) Text &operator=( const double num );
        // Setzt den Inahlt des Textes gleich einer Zeichenkette
        __declspec( dllexport ) Text &operator=( const char *txt );
        // Setzt den Inhalt des Textes gleich einer Kopie des Inhalts eines anderen Textes
        __declspec( dllexport ) Text &operator=( const Text &txt );
        // Gibt den Inhalt des Textes als Zeichenkette zur�ck
        __declspec( dllexport ) operator char*( ) const;
        // Konviertiert den Inhalt des Textes zu einer Zahl
        __declspec( dllexport ) operator int() const;
        // Konviertiert den Inhalt des Textes zu einer Kommazahl
        __declspec( dllexport ) operator double() const;
        // Pr�ft, ob der Inhalt des Textes nach alphabetischer Ordnung sp�ter kommt als der Inhalt eines anderen Textes
        __declspec( dllexport ) bool operator>( Text &t ) const;
        // Pr�ft, ob der Inhalt des Textes nach alphabetischer Ordnung fr�her kommt als der Inhalt eines anderen Textes
        __declspec( dllexport ) bool operator<( Text &t ) const;
    };

    // Durchsucht eine Zeichenkette nach dem num-ten Vorkommen eines bestimmten Buchstabens
    //  string: Die zu durchsuchende Zeichenkette
    //  c: Der zu suchende Buchstabe
    //  num: Das wievielte Vorkommen des Buchtaben gefunden werden soll
    //  return: (-1), wenn es kein num-tes Vorkommen des Buchstaben gibt. Sonst die Position des num-ten Vorkommens in der Zeichenkette
    __declspec( dllexport ) int stringPositionVonChar( char *string, char c, int num ); // sucht die position des num-ten c-s in string, -1 bei nicht gefunden
    // Durchsucht eine Zeichenkette nach einer Anderen Zeichenkette
    //  string: Die zu durchsuchende Zeichenkette
    //  suche: Die Zeichenkette, nach der gesucht werden soll
    //  sBegPos: Die Position, ab der die Suche begonnen werden soll
    //  return: Die Position, an der die zu suchende Zeichenkette erstmals gefunden wurde. (-1) Wenn nichts gefunden wurde.
    __declspec( dllexport ) int stringPositionVonString( char *string, char *suche, int sBegPos );

    // Kopiert eine bestimmte Zeichenkette in die Zwischenablage des Betriebssystems
    //  txt: Die Zeichenkette, die kopiert werden soll
    __declspec( dllexport ) void TextKopieren( const char *txt );
    // Ermittelt, ob in der Zwischenablage des Betriebssystems eine Zeichenkette steht.
    //  return: Die Zeichenkette aus der Zwischenablage. Wenn keine Zeichenkette kopiert wurde, wird eine lehre Zeichenkette zur�ckgegeben.
    __declspec( dllexport ) char *TextEinf�gen();
    // Wandelt einen bestimmten schreibbaren Buchstaben in einen Gro�- oder Kleinbuchstaben um
    //  c: Der Buchstabe, der umgewandelt werden soll
    //  gro�: Wenn (true), so wird der Buchstabe in einen Gro�buchstaben umgewandelt. Wenn (false), wird er in einen Kleinbuchstaben umgewandelt.
    //  return: Den umgewandelten Buchstaben
    __declspec( dllexport ) char KleinOrGro�( char c, bool gro� );
    // Ermittelt, ob ein Buchstabe ein schreibbares Zeichen ist
    //  zeichen: Der Buchstabe, der gepr�ft werden soll
    //  return: (true), wenn der Buchstabe gezeichnet werden kann. (false) sonnst
    __declspec( dllexport ) bool istSchreibbar( unsigned char zeichen );
    // Konvertiert eine Zahl aus einer Zeichenkette in belibiger Basis zu einer Zahl
    //  c: Die Zeichenkette, in der Die Zahl steht
    //  system: Die Basis der Zahl
    //  return: Die Zahl, die im Text stand
    __declspec( dllexport ) unsigned int TextZuInt( char *c, int system );
    // Konvertiert eine Zahl aus einer Zeichenkette in belibiger Basis zu einer Zahl
    //  c: Die Zeichenkette, in der Die Zahl steht
    //  c_ende: Wird duch die Funktion gesetzt und darf 0 sein. Zeigt auf das n�chste Zeichen in der Zeichenkette, das nach der Zah steht
    //  system: Die Basis der Zahl
    //  return: Die Zahl, die im Text stand
    __declspec( dllexport ) unsigned int TextZuInt( char *c, char **c_ende, int system );
    // Konvertiert eine Zeichenkette zu einem Double
    //  c: Die Zeichenkette, die konvertiert werden soll
    //  return: Das double, was in der Zeichenkette stand
    __declspec( dllexport ) double TextZuDouble( char *c );
    // Konvertiert eine Zeichenkette zu einem Double
    //  c: Die Zeichenkette, die konvertiert werden soll
    //  c_ende: Wird duch die Funktion gesetzt und darf 0 sein. Ein Zeiger auf das n�chste Zeichen nach dem Double in der Zeichenkette
    //  return: Das double, was in der Zeichenkette stand
    __declspec( dllexport ) double TextZuDouble( char *c, char **c_ende );
    // Ermittelt die L�nge einer bestimmten Zeichenkette
    //  txt: Die Zeichenkette, deren L�nge ermittelt werden soll
    //  return: Die L�nge der Zeichenkette
    __declspec( dllexport ) int textL�nge( const char *txt );
}
#endif