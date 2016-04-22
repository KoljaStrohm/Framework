//---Include---
#include "Text.h"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#ifndef WIN32
#include <string.h>
#endif

using namespace Framework;

// inhalt der Text Klasse aus Text.h
// Konstruktor 
Text::Text()
    : txt( 0 ),
    suchGBeg( 0 ),
    suchGEnd( 0 ),
    pr�zision( 0 ),
    ref( 1 )
{
    setText( "" );
}

Text::Text( const Text &txt )
    : txt( 0 ),
    suchGBeg( 0 ),
    suchGEnd( 0 ),
    pr�zision( 0 ),
    ref( 1 )
{
    setText( txt );
}

Text::Text( const char *t )
    : txt( 0 ),
    suchGBeg( 0 ),
    suchGEnd( 0 ),
    pr�zision( 0 ),
    ref( 1 )
{
    setText( t ); // Text setzen
}

Text::Text( int zahl )
    : txt( 0 ),
    suchGBeg( 0 ),
    suchGEnd( 0 ),
    pr�zision( 0 ),
    ref( 1 )
{
    *this = zahl;
}

// Destruktor 
Text::~Text()
{
    delete[]txt;
}

// nicht constant
void Text::setSuchGrenzen( char gBeg, char gEnd ) // sucht bei jeder suchfunktion nicht zwischen den Zeichen gBeg und gEnd
{
    suchGBeg = gBeg;
    suchGEnd = gEnd;
}

void Text::setText( const char *t ) // ersetzt den Text
{
    delete[]txt; // alter Text l�schen
    int l = (int)strlen( t ); // L�nge des neuen Textes ermitteln
    txt = new char[ l + 1 ]; // neuen Text erstellen
    for( int i = 0; i < l; ++i ) // Text bef�llen
        txt[ i ] = t[ i ];
    txt[ l ] = '\0'; // Textende Festlegen
}

// unconstant 
void Text::setText( const char *t, int l ) // ersetzt den Text
{
    delete[]txt; // alter Text l�schen
    txt = new char[ l + 1 ]; // neuen Text erstellen
    for( int i = 0; i < l; ++i ) // Text bef�llen
        txt[ i ] = t[ i ];
    txt[ l ] = '\0'; // Textende Festlegen
}

void Text::setText( Text *t )
{
    setText( t->getText() ); // Text setzen
    t = t->release(); // �bergabe loslassen
}

void Text::anh�ngen( char c ) // h�ngt an den Text an
{
    anh�ngen( &c, 1 );
}

void Text::anh�ngen( const char *t ) // h�ngt an den Text an
{
    int tl = (int)strlen( t ); // l�nge der �bergabe
    int txl = getL�nge(); // l�nge des Textes
    char *res = new char[ tl + txl + 1 ]; // neuen Text erstellen
    for( int i = 0; i < txl; ++i ) // mit jetzigem Text f�llen
        res[ i ] = txt[ i ];
    for( int i = 0; i < tl; ++i ) // �bergabe anh�ngen
        res[ txl + i ] = t[ i ];
    res[ txl + tl ] = '\0'; // Textende festlegen
    setText( res ); // Test setzen
    delete[] res; // Speicher freigeben
}

void Text::hexAnh�ngen( int num ) // h�ngt die zahl in hex anden Text an
{
    int l = getL�nge();
    char *res = new char[ l + 9 ];
    for( int i = 0; i < l; ++i )
        res[ i ] = txt[ i ];
    std::stringstream stream;
    stream << std::setfill( '0' ) << std::setw( sizeof( int ) * 2 ) << std::hex << num;
    std::string str = stream.str();
    for( int i = l; i < l + 8; ++i )
        res[ i ] = str.c_str()[ i - l ];
    res[ l + 8 ] = 0;
    setText( res );
    delete[] res;
}

void Text::farbeAnh�ngen( int fc ) // setzt die Farbe des folgenden Textes
{
    int l = getL�nge();
    char *res = new char[ l + 12 ];
    for( int i = 0; i < l; ++i )
        res[ i ] = txt[ i ];
    res[ l ] = '\r';
    res[ l + 1 ] = '0';
    res[ l + 2 ] = 'x';
    std::stringstream stream;
    stream << std::setfill( '0' ) << std::setw( sizeof( int ) * 2 ) << std::hex << fc;
    std::string str = stream.str();
    for( int i = l + 3; i < l + 11; ++i )
        res[ i ] = str.c_str()[ i - ( l + 3 ) ];
    res[ l + 11 ] = 0;
    setText( res );
    delete[] res;
}

void Text::anh�ngen( const char *t, int l ) // h�ngt an den Text an
{
    int txl = getL�nge(); // l�nge des Textes
    char *res = new char[ l + txl + 1 ]; // neuen Text erstellen
    for( int i = 0; i < txl; ++i ) // mit jetzigem Text f�llen
        res[ i ] = txt[ i ];
    for( int i = 0; i < l; ++i ) // �bergabe anh�ngen
        res[ txl + i ] = t[ i ];
    res[ txl + l ] = '\0'; // Textende festlegen
    setText( res, txl + l ); // Test setzen
    delete[] res; // Speicher freigeben
}

void Text::anh�ngen( Text *t )
{
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        anh�ngen( t->getText() ); // Text anh�ngen
    t = t->release(); // �bergabe loslassen
}

void Text::anh�ngen( int num )
{
    std::stringstream ss;
    ss << num;
    anh�ngen( ss.str().c_str() );
}

void Text::anh�ngen( unsigned int num )
{
    std::stringstream ss;
    ss << num;
    anh�ngen( ss.str().c_str() );
}

void Text::anh�ngen( double num )
{
    std::stringstream ss;
    ss.precision( pr�zision );
    ss << num;
    anh�ngen( ss.str().c_str() );
}

void Text::einf�gen( int p, char c ) // F�gt an stelle p ein
{
    if( p > getL�nge() || p < 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    int txl = getL�nge(); // L�nge des Textes
    char *res = new char[ txl + 2 ]; // neuer Text erstellen
    for( int i = 0; i < p; ++i ) // Text f�llen
        res[ i ] = txt[ i ];
    res[ p ] = c;
    for( int i = p; i < txl; ++i ) // Text f�llen
        res[ i + 1 ] = txt[ i ];
    res[ txl + 1 ] = '\0'; // Text ende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::einf�gen( int p, const char *t ) // F�gt an stelle p ein
{
    if( p > getL�nge() || p < 0 || strlen( t ) <= 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    char *res = new char[ tl + txl + 1 ]; // neuer Text erstellen
    for( int i = 0; i < p; ++i ) // Text f�llen
        res[ i ] = txt[ i ];
    for( int i = 0; i < tl; ++i ) // Text einf�gen
        res[ i + p ] = t[ i ];
    for( int i = p; i < txl; ++i ) // Text f�llen
        res[ i + tl ] = txt[ i ];
    res[ tl + txl ] = '\0'; // Text ende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::einf�gen( int p, Text *t )
{
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        einf�gen( p, t->getText() ); // Text einf�gen
    t = t->release(); // �bergabe loslassen
}

void Text::ersetzen( int p1, int p2, const char *t ) // Ersetzt den Text von p1 bis p2
{
    if( p1 > p2 )
    {
        int x = p1; // p1 und p2 tauschen
        p1 = p2;
        p2 = x;
    }
    l�schen( p1, p2 ); // Textabschnitt von p1 zu p2 l�schen
    einf�gen( p1, t ); // �bergabe bei p1 einf�gen
}

void Text::ersetzen( int p1, int p2, Text *t )
{
    if( t->getL�nge() >= 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( p1, p2, t->getText() ); // Text ersetzen
    t = t->release(); // �bergabe loslassen
}

void Text::ersetzen( char c1, char c2 ) // ersetzt jedes c1 durch c2
{
    if( c1 == '\0' || c2 == '\0' ) // Auf unsinnige �bergabe pr�fen
        return;
    if( !hat( c1 ) ) // pr�fen ob c1 vorhanden
        return;
    int l = getL�nge(); // Text L�nge
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // Text durchsuchen
    {
        bool b = suchGCount != 0;
        if( txt[ i ] == c1 && !suchGCount )
            txt[ i ] = c2; // Text ersetzen
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( txt[ i ] == c1 && !suchGCount && b )
            txt[ i ] = c2; // Text ersetzen
    }
}

void Text::ersetzen( const char *t1, const char *t2 ) // ersetzt jedes t1 durch t2
{
    int txl = getL�nge(); // Text L�nge
    int t1l = (int)strlen( t1 ); // L�nge der �bergaben
    int t2l = (int)strlen( t2 );
    if( t1l > txl || t1l <= 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    if( !hat( t1 ) ) // pr�fen ob t1 vorhanden
        return;
    int anz = anzahlVon( t1 ); // Anzahl von t1 im Text
    int *begin = new int[ anz ];
    int *end = new int[ anz ];
    for( int i = 0; i < anz; ++i ) // Positionen von t1 speichern
    {
        begin[ i ] = positionVon( t1, i );
        end[ i ] = begin[ i ] + t1l;
    }
    int resl = ( txl - ( anz * t1l ) ) + ( anz * t2l ) + 1; // L�nge des Ergebneses
    char *res = new char[ resl ]; // neuer Text erstellen
    int rep = 0; // Speichert bei welchen t1 man sich befindet
    int last = 0; // F�llposition von txt
    int neu = 0; // F�llporition von res
    for( ; neu < resl; ++neu ) // Text bef�llen
    {
        if( rep < anz && last == begin[ rep ] ) // Text ersetzen
        {
            last = end[ rep ];
            ++rep;
            for( int ii = 0; ii < t2l; ++ii )
            {
                if( neu >= resl )
                    break;
                res[ neu ] = t2[ ii ];
                ++neu;
            }
            if( neu >= resl )
                break;
            --neu;
        }
        else // Text Kopieren
        {
            res[ neu ] = txt[ last ];
            ++last;
        }
    }
    res[ resl - 1 ] = '\0'; // Textende festlegen
    setText( res ); // Text setzen
    delete[]begin; // Speicher freigeben
    delete[]end;
    delete[] res;
}

void Text::ersetzen( Text *t1, const char *t2 )
{
    if( t1->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( t1->getText(), t2 ); // ersetzen
    t1 = t1->release(); // �bergabe loslassen
}

void Text::ersetzen( const char *t1, Text *t2 )
{
    if( t2->getL�nge() >= 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( t1, t2->getText() ); // ersetzen
    t2 = t2->release(); // �bergabe loslassen
}

void Text::ersetzen( Text *t1, Text *t2 )
{
    if( t1->getL�nge() > 0 && t2->getL�nge() >= 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( t1->getText(), t2->getText() ); // ersetzen
    t1 = t1->release(); // �bergaben loslassen
    t2 = t2->release();
}

void Text::ersetzen( int index, char c1, char c2 ) // ersetzt das i-te c1 durch c2
{
    if( c1 == '\0' || c2 == '\0' || index < 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    if( !hat( c1 ) ) // pr�fen ob c1 vorhanden
        return;
    int anz = anzahlVon( c1 );
    if( index >= anz ) // pr�fen ob es ein i-tes c1 gibt
        return;
    txt[ positionVon( c1, index ) ] = c2;
}

void Text::ersetzen( int index, const char *t1, const char *t2 ) // ersetzt das i-te t1 durch t2
{
    int txl = getL�nge(); // Text L�nge
    int t1l = (int)strlen( t1 ); // L�nge der �bergaben
    if( t1l >= txl || t1l <= 0 || index < 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    if( !hat( t1 ) ) // pr�fen ob t1 vorhanden
        return;
    int anz = anzahlVon( t1 ); // Anzahl von t1 im Text
    if( index >= anz ) // pr�fen ob es ein i-tes t1 gibt
        return;
    int begin = positionVon( t1, index );
    int end = begin + t1l;
    ersetzen( begin, end, t2 ); // ersetzen
}

void Text::ersetzen( int i, Text *t1, const char *t2 )
{
    if( t1->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( i, t1->getText(), t2 ); // ersetzen
    t1 = t1->release(); // �bergabe loslassen
}

void Text::ersetzen( int i, const char *t1, Text *t2 )
{
    if( t2->getL�nge() >= 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( i, t1, t2->getText() ); // ersetzen
    t2 = t2->release(); // �bergabe loslassen
}

void Text::ersetzen( int i, Text *t1, Text *t2 )
{
    if( t1->getL�nge() > 0 || t2->getL�nge() >= 0 ) // Auf unsinnige �bergabe pr�fen
        ersetzen( i, t1->getText(), t2->getText() ); // ersetzen
    t1 = t1->release(); // �bergaben loslassen
    t2 = t2->release();
}

void Text::f�llText( char c, int l�n ) // setzt den Text zu so vielen c wie l�n gro� ist
{
    char *res = new char[ l�n + 1 ];
    for( int i = 0; i < l�n; ++i )
        res[ i ] = c;
    res[ l�n ] = '\0';
    setText( res );
    delete[] res;
}

void Text::l�schen( int p ) // l�scht p
{
    int l = getL�nge(); // Text L�nge
    if( p < 0 || p >= l ) // Auf unsinnige �bergabe pr�fen
        return;
    char *res = new char[ l ]; // neuen Text anlegen
    for( int i = 0; i < p && i < l; ++i ) // Text bef�llen
        res[ i ] = txt[ i ];
    for( int i = p + 1; i < l; ++i )
        res[ i - 1 ] = txt[ i ];
    res[ l - 1 ] = 0;
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::l�schen( int p1, int p2 ) // l�scht von p1 zu p2 ( p2 bleibt )
{
    if( p1 > p2 ) // p1 und p2 tauschen
    {
        int x = p1;
        p1 = p2;
        p2 = x;
    }
    int l = getL�nge(); // L�nge des Testes
    if( p1 < 0 || p2 > l ) // Auf unsinnige �bergabe pr�fen
        return;
    int resl = l - ( p2 - p1 ); // L�nge vom Ergebnis
    char *res = new char[ resl + 1 ]; // Neuen Text erstellen
    for( int i = 0; i < p1; ++i ) // Text f�llen
        res[ i ] = txt[ i ];
    for( int i = p2; i < l; ++i )
        res[ i - ( p2 - p1 ) ] = txt[ i ];
    res[ resl ] = '\0'; // Testende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::l�schen( char c ) // l�scht jetes c
{
    if( !hat( c ) ) // pr�fen ob c vorhanden
        return;
    int l = getL�nge(); // L�nge des Textes
    int anz = anzahlVon( c ); // Anzahl von c
    char *res = new char[ l - anz + 1 ]; // neuen Text erstellen
    int anz2 = 0;
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // Text bef�llen
    {
        bool b = suchGCount != 0;
        if( txt[ i ] == c && !suchGCount )
            ++anz2;
        else
            res[ i - anz2 ] = txt[ i ];
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( b )
        {
            if( txt[ i ] == c && !suchGCount )
                ++anz2;
            else
                res[ i - anz2 ] = txt[ i ];
        }
    }
    res[ l - anz ] = '\0'; // Textende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::l�schen( const char *t ) // l�scht jetes t
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return;
    if( !hat( t ) ) // pr�fen ob Text ein t enth�lt
        return;
    int anz = anzahlVon( t ); // anzahl von t
    int *begin = new int[ anz ];
    for( int i = 0; i < anz; ++i ) // begin aller t-s finden
        begin[ i ] = positionVon( t, i );
    int resl = txl - ( anz * tl ); // L�nge vom Ergebnes
    char *res = new char[ resl + 1 ]; // neuen Text erzeugen
    int del = 0;
    for( int i = 0; i < txl; ++i ) // Text bef�llen
    {
        if( del < anz && i == begin[ del ] ) // Text auslassen
        {
            i += tl - 1;
            ++del;
        }
        else
            res[ i - ( del * tl ) ] = txt[ i ]; // Text bef�llen
    }
    res[ resl ] = '\0'; // Text ende festlegen
    setText( res ); // Text setzen
    delete[]begin;
    delete[] res; // Speicher freigeben
}

void Text::l�schen( Text *t )
{
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        l�schen( t->getText() ); // l�schen
    t = t->release(); // �bergabe loslassen
}

void Text::l�schen( int index, char c )
{
    if( index < 0 || !hat( c ) ) // Auf unsinnige �bergabe pr�fen
        return;
    int anz = anzahlVon( c ); // anzahl der i-s
    if( index >= anz ) // pr�fen ob ein i-tes c vorhanden ist
        return;
    int pos = positionVon( c, index ); // Position vom i-ten c
    if( pos < 0 )
        return;
    int l = getL�nge(); // L�nge des Textes
    if( !l )
        return;
    char *res = new char[ l ]; // neuen Text erzeugen
    for( int i = 0; i < pos && i < l; ++i ) // Text bef�llen
        res[ i ] = txt[ i ];
    for( int i = pos + 1; i < l; ++i )
        res[ i - 1 ] = txt[ i ];
    res[ l - 1 ] = '\0'; // Text ende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::l�schen( int index, const char *t ) // l�scht das i-te t
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    if( index < 0 || !hat( t ) || tl <= 0 ) // Auf unsinnige �bergabe pr�fen
        return;
    int anz = anzahlVon( t ); // anzahl der i-s
    if( index >= anz ) // pr�fen ob ein i-tes c vorhanden ist
        return;
    int pos = positionVon( t, index ); // Position vom i-ten c
    if( pos < 0 )
        return;
    int l = getL�nge(); // L�nge des Textes
    if( !l )
        return;
    char *res = new char[ l - tl + 1 ]; // neuen Text erzeugen
    for( int i = 0; i < pos && i < l - tl + 1; ++i ) // Text bef�llen
        res[ i ] = txt[ i ];
    for( int i = pos + tl; i < l; ++i )
        res[ i - tl ] = txt[ i ];
    res[ l - tl ] = '\0'; // Text ende festlegen
    setText( res ); // Text setzen
    delete[] res; // Speicher freigeben
}

void Text::l�schen( int i, Text *t )
{
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        l�schen( i, t->getText() ); // l�schen
    t = t->release(); // �bergabe loslassen
}

void Text::setPr�zision( int p ) // setzt die Anzahl der Nachkommastellen bei doubles
{
    pr�zision = p;
}

// constant 
int Text::getL�nge() const // gibt die Text l�nge zur�ck
{
    if( !txt )
        return -1;
    int ret = 0;
    for( ; txt[ ret ] != '\0'; ++ret ); // z�hlen
    return ret;
}

int Text::getLKick( int pos ) const
{
    if( txt[ pos - 1 ] == ' ' )
    {
        int ret = 1;
        for( ; ret < pos && txt[ pos - ret - 1 ] == ' ' && txt[ pos - ret - 1 ] != '\n'; ++ret );
        return pos - ret;
    }
    else
    {
        int ret = 1;
        for( ; ret < pos && txt[ pos - ret - 1 ] != ' ' && txt[ pos - ret - 1 ] != '\n'; ++ret );
        return pos - ret;
    }
}

int Text::getOKick( int pos ) const
{
    if( !hat( '\n' ) )
        return 0;
    int lpos = 0;
    while( pos - lpos - 1 > 0 && txt[ pos - lpos - 1 ] != '\n' )
        ++lpos;
    int vll�n = 1;
    while( pos - lpos - vll�n - 1 >= 0 && txt[ pos - lpos - vll�n - 1 ] != '\n' )
        ++vll�n;
    if( vll�n > lpos )
        return pos - vll�n;
    else
        return pos - lpos - 1;
}

int Text::getRKick( int pos ) const
{
    int tl = getL�nge();
    if( txt[ pos ] == ' ' )
    {
        int ret = 1;
        for( ; ret + pos < tl && txt[ pos + ret ] == ' ' && txt[ pos + ret ] != '\n'; ++ret );
        return pos + ret;
    }
    else
    {
        int ret = 1;
        for( ; ret + pos < tl && txt[ pos + ret ] != ' '&& txt[ pos + ret ] != '\n'; ++ret );
        return pos + ret;
    }
}

int Text::getUKick( int pos ) const
{
    if( !hat( '\n' ) )
        return getL�nge();
    int lpos = 0;
    while( pos - lpos > 0 && txt[ pos - lpos - 1 ] != '\n' )
        ++lpos;
    int ll�n = 1;
    while( pos + ll�n - 1 < getL�nge() && txt[ pos + ll�n - 1 ] != '\n' )
        ++ll�n;
    int vll�n = 1;
    while( pos + ll�n + vll�n - 1 < getL�nge() && txt[ pos + ll�n + vll�n - 1 ] != '\n' )
        ++vll�n;
    if( vll�n == 1 )
        return pos + ll�n < getL�nge() ? pos + ll�n : getL�nge();
    if( vll�n < lpos )
        return pos + ll�n + vll�n - 1;
    return pos + ll�n + lpos;
}

bool Text::hat( Text *t ) const // enth�lt der Text t
{
    bool ret = 0;
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        ret = hat( t->getText() ); // pr�fen
    t = t->release(); // �bergabe loslassen
    return ret;
}

bool Text::hat( const char *t ) const
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return 0;
    int suchGCount = 0;
    for( int i = 0; i + tl <= txl; ++i ) // Text durchsuchen
    {
        if( !suchGCount )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // Text �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                return 1;
        }
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( !suchGCount )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // Text �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                return 1;
        }
    }
    return 0;
}

bool Text::hat( char c ) const // enth�lt c
{
    int l = getL�nge(); // Text L�nge
    bool ret = 0;
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( !suchGCount ) // �berpr�fen
            ret |= txt[ i ] == c;
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( !suchGCount && b ) // �berpr�fen
            ret |= txt[ i ] == c;
    }
    return ret;
}

bool Text::istGleich( const char *t ) const // pr�ft ob det Text gleich t ist
{
    int txl = getL�nge(); // Text L�nge
    int tl = (int)strlen( t ); // L�nge der �bergabe
    if( txl != tl ) // Auf unsinniege �bergabe pr�fen
        return 0;
    if( txl == -1 )
        return 1;
    bool ret = true;
    for( int i = 0; i < tl; ++i ) // pr�fen
        ret &= txt[ i ] == t[ i ];
    return ret;
}

bool Text::istGleich( Text *t ) const
{
    bool ret = istGleich( t->getText() ); // pr�fen
    t->release(); // �bergabe loslassen
    return ret;
}

char *Text::getText() const // gibt Text zur�ck
{
    return txt;
}

int Text::anzahlVon( char c ) const // gibt die Anzahl von c im Text zur�ck
{
    int ret = 0;
    int l = getL�nge(); // Text L�nge
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        ret += txt[ i ] == c && !suchGCount; // z�hlen
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        ret += txt[ i ] == c && !suchGCount && b; // z�hlen
    }
    return ret;
}

int Text::anzahlVon( const char *t ) const // gibt die Anzahl von t im Text zur�ck
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return 0;
    int ret = 0;
    int suchGCount = 0;
    for( int i = 0; i + tl <= txl; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( !suchGCount )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                ++ret; // z�hlen
        }
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( !suchGCount && b )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                ++ret; // z�hlen
        }
    }
    return ret;
}

int Text::anzahlVon( Text *t ) const
{
    int ret = 0;
    if( t->getL�nge() > 0 )  // Auf unsinnige �bergabe pr�fen
        ret = anzahlVon( t->getText() ); // z�hlen
    t = t->release(); // �bergabe loslassen
    return ret;
}

int Text::positionVon( char c ) const // gibt die Position des ersten c zur�ck
{
    int l = getL�nge(); // Text L�nge
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( txt[ i ] == c && !suchGCount ) // �berpr�fen
            return i;
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( txt[ i ] == c && !suchGCount && b ) // �berpr�fen
            return i;
    }
    return -1;
}

int Text::positionVon( const char *t ) const // gibt die Position des ersten t zur�ck
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return -1;
    int suchGCount = 0;
    for( int i = 0; i + tl <= txl; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( !suchGCount )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                return i;
        }
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( !suchGCount && b )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
                return i;
        }
    }
    return -1;
}

int Text::positionVon( Text *t ) const
{
    int ret = 0;
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        ret = positionVon( t->getText() ); // position ermitteln
    t = t->release(); // �bergabe loslassen
    return ret;
}

int Text::positionVon( char c, int index ) const // gibt die Position des i-ten c zur�ck
{
    int l = getL�nge(); // Text L�nge
    int ii = 0;
    int suchGCount = 0;
    for( int i = 0; i < l; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( txt[ i ] == c && !suchGCount ) // �berpr�fen
        {
            if( ii == index )
                return i;
            else
                ++ii;
        }
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( txt[ i ] == c && !suchGCount && b ) // �berpr�fen
        {
            if( ii == index )
                return i;
            else
                ++ii;
        }
    }
    return -1;
}

int Text::positionVon( const char *t, int index ) const // gibt die Position des i-ten t zur�ck
{
    int tl = (int)strlen( t ); // L�nge der �bergabe
    int txl = getL�nge(); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return 0;
    int i2 = 0;
    int suchGCount = 0;
    for( int i = 0; i + tl <= txl; ++i ) // suchen
    {
        bool b = suchGCount != 0;
        if( !suchGCount )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
            {
                if( i2 == index )
                    return i;
                else
                    ++i2;
            }
        }
        if( txt[ i ] == suchGBeg )
            ++suchGCount;
        if( txt[ i ] == suchGEnd )
            --suchGCount;
        if( !suchGCount && b )
        {
            bool b = 1;
            for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
                b &= txt[ i + ii ] == t[ ii ];
            if( b )
            {
                if( i2 == index )
                    return i;
                else
                    ++i2;
            }
        }
    }
    return -1;
}

int Text::positionVon( Text *t, int i ) const
{
    int ret = 0;
    if( t->getL�nge() > 0 ) // Auf unsinnige �bergabe pr�fen
        ret = positionVon( t->getText(), i ); // position ermitteln
    t = t->release(); // �bergabe loslassen
    return ret;
}

Text *Text::getTeilText( int p1, int p2 ) const // gibt den Text von p1 bis p2 zur�ck
{
    if( p1 > p2 ) // p1 und p2 tauschen
    {
        int x = p1;
        p1 = p2;
        p2 = x;
    }
    int l = getL�nge(); // Text L�nge
    if( p1 < 0 || p2 > l ) // Auf unsinnige �bergabe pr�fen
        return new Text( "" );
    char *cp = new char[ p2 - p1 + 1 ]; // neuen Text erstellen
    for( int i = p1; i < p2; ++i ) // Text bef�llen
    {
        cp[ i - p1 ] = txt[ i ];
    }
    cp[ p2 - p1 ] = '\0';
    Text *t = new Text( cp ); // Text zur�ckgeben
    delete[]cp;
    return t;
}

Text *Text::getTeilText( int p ) const // gibt den Text von p bis zum Ende zur�ck
{
    return getTeilText( p, getL�nge() ); // Text zur�ckgeben
}

// Reference Counting
Text *Text::getThis()
{
    ++ref;
    return this;
}

Text *Text::release()
{
    --ref;
    if( ref < 1 )
        delete this;
    return 0;
}

// Operatoren
Text &Text::operator+=( const int num )
{
    anh�ngen( num );
    return *this;
}

Text &Text::operator+=( const double num )
{
    anh�ngen( num );
    return *this;
}

Text &Text::operator+=( const char *txt )
{
    anh�ngen( txt );
    return *this;
}

Text &Text::operator+=( const Text &txt )
{
    anh�ngen( txt.getText() );
    return *this;
}

Text &Text::operator=( const int num )
{
    setText( "" );
    anh�ngen( num );
    return *this;
}

Text &Text::operator=( const double num )
{
    setText( "" );
    anh�ngen( num );
    return *this;
}

Text &Text::operator=( const char *txt )
{
    setText( txt );
    return *this;
}

Text &Text::operator=( const Text &txt )
{
    setText( txt.getText() );
    return *this;
}

Text::operator char*( ) const
{
    return txt;
}

Text::operator int() const
{
    if( txt[ 0 ] == '0' && txt[ 1 ] == 'x' )
        return TextZuInt( ( txt + 2 ), 16 );
    return TextZuInt( txt, 10 );
}

Text::operator double() const
{
    if( txt[ 0 ] == '0' && txt[ 1 ] == 'x' )
        return TextZuInt( ( txt + 2 ), 16 );
    return TextZuDouble( txt );
}

bool Text::operator>( Text &t ) const
{
    int l�n1 = getL�nge();
    int l�n2 = t.getL�nge();
    char *txt2 = t;
    for( int i = 0; i < l�n1 && i < l�n2; ++i )
    {
        if( txt[ i ] > txt2[ i ] )
            return 1;
        if( txt[ i ] < txt2[ i ] )
            return 0;
    }
    if( l�n1 > l�n2 )
        return 1;
    return 0;
}

bool Text::operator<( Text &t ) const
{
    int l�n1 = getL�nge();
    int l�n2 = t.getL�nge();
    char *txt2 = t;
    for( int i = 0; i < l�n1 && i < l�n2; ++i )
    {
        if( txt[ i ] < txt2[ i ] )
            return 1;
        if( txt[ i ] > txt2[ i ] )
            return 0;
    }
    if( l�n1 < l�n2 )
        return 1;
    return 0;
}

// char* operationen
int Framework::stringPositionVonChar( char *string, char c, int num ) // sucht die position des num-ten c-s in string, -1 bei nicht gefunden
{
    int gef = 0;
    int p = 0;
    for( char cc = *string; *string; ++string )
    {
        if( cc == c )
        {
            if( gef == num )
                return p;
            else
                ++gef;
        }
        ++p;
    }
    return -1;
}

int Framework::stringPositionVonString( char *string, char *suche, int sBegPos ) // sucht die position von 'suche' in 'string' ab der Position 'sBegPos', -1 bei nicht gefunden
{
    for( int i = 0; i < sBegPos; ++i )
    {
        if( !*string )
            return -1;
        ++string;
    }
    int tl = textL�nge( suche ); // L�nge der �bergabe
    int txl = textL�nge( string ); // L�nge des Textes
    if( tl <= 0 || tl > txl ) // Auf unsinnige �bergabe pr�fen
        return -1;
    for( int i = 0; i + tl <= txl; ++i ) // suchen
    {
        bool b = 1;
        for( int ii = 0; ii < tl; ++ii ) // �berpr�fen
            if( b )
                b = string[ i + ii ] == suche[ ii ];
        if( b )
            return i + sBegPos;
    }
    return -1;
}

//---Andere Funktionen---
void Framework::TextKopieren( const char *txt ) // kopiert den Text in den Zwischenspeicher
{
#ifdef WIN32
    int l�n = textL�nge( txt ) + 1;
    if( l�n == 1 )
        return;
    HGLOBAL hMem = GlobalAlloc( GMEM_MOVEABLE, l�n );
    if( !hMem )
        return;
    memcpy( GlobalLock( hMem ), txt, l�n );
    GlobalUnlock( hMem );
    OpenClipboard( 0 );
    EmptyClipboard();
    SetClipboardData( CF_TEXT, hMem );
    CloseClipboard();
#endif
}

char *Framework::TextEinf�gen() // gibt den Text aus der Zwischenablage zur�ck
{
#ifdef WIN32
    if( !OpenClipboard( 0 ) )
        return "";
    HANDLE hClipData = GetClipboardData( CF_TEXT );
    char *cBuffer = (char*)GlobalLock( hClipData );
    GlobalUnlock( hClipData );
    CloseClipboard();
    return cBuffer;
#else
    return 0;
#endif
}

char Framework::KleinOrGro�( char c, bool gr )
{
    int ret = c;
    if( gr )
    {
        if( c >= 'a' && c <= 'z' )
            ret -= 32;
        else
        {
            switch( c )
            {
            case '^':
                return '�';
            case '1':
                return '!';
            case '<':
                return '>';
            case '2':
                return '\"';
            case '3':
                return '�';
            case '4':
                return '$';
            case '5':
                return '%';
            case '6':
                return '&';
            case '7':
                return '/';
            case '8':
                return '(';
            case '9':
                return ')';
            case '0':
                return '=';
            case ',':
                return ';';
            case '.':
                return ':';
            case '�':
                return '?';
            case '-':
                return '_';
            case '�':
                return '`';
            case '+':
                return '*';
            case '#':
                return '\'';
            case '�':
                return '�';
            case '�':
                return '�';
            case '�':
                return '�';
            }
        }
    }
    else
    {
        if( c >= 'A' && c <= 'Z' )
            ret += 32;
        else
        {
            switch( c )
            {
            case '�':
                return '^';
            case '!':
                return '1';
            case '>':
                return '<';
            case '\"':
                return '2';
            case '�':
                return '3';
            case '$':
                return '4';
            case '%':
                return '5';
            case '&':
                return '6';
            case '/':
                return '7';
            case '(':
                return '8';
            case ')':
                return '9';
            case '=':
                return '0';
            case ';':
                return ',';
            case ':':
                return '.';
            case '?':
                return '�';
            case '_':
                return '-';
            case '`':
                return '�';
            case '*':
                return '+';
            case '\'':
                return '#';
            case '�':
                return '�';
            case '�':
                return '�';
            case '�':
                return '�';
            }
        }
    }
    return ret;
}

bool Framework::istSchreibbar( unsigned char zeichen ) // pr�ft, ob zeichen ein Schreibbarer Buchstabe ist
{
    if( zeichen > 32 && zeichen < 127 )
        return 1;
    if( zeichen == 128 || zeichen == 181 || zeichen == 178 || zeichen == 179 )
        return 1;
    if( zeichen > 191 && zeichen < 198 )
        return 1;
    if( zeichen > 199 && zeichen < 208 )
        return 1;
    if( zeichen > 209 && zeichen < 215 )
        return 1;
    if( zeichen > 216 && zeichen < 221 )
        return 1;
    if( zeichen > 222 && zeichen < 230 )
        return 1;
    if( zeichen > 231 && zeichen < 240 )
        return 1;
    if( zeichen > 241 && zeichen < 247 )
        return 1;
    if( zeichen > 248 && zeichen < 253 )
        return 1;
    if( zeichen == ' ' || zeichen == '\t' )
        return 1;
    return 0;
}

unsigned int Framework::TextZuInt( char *c, int system ) // Konvertiert c zu int
{
    if( system == 16 )
        return strtoul( c, 0, system );
    return strtol( c, 0, system );
}

unsigned int Framework::TextZuInt( char *c, char **c_ende, int system )
{
    if( system == 16 )
        return strtoul( c, c_ende, system );
    return strtol( c, c_ende, system );
}

double Framework::TextZuDouble( char *c ) // Konvertiert c zu double
{
    return strtod( c, 0 );
}

double Framework::TextZuDouble( char *c, char **c_ende )
{
    return strtod( c, c_ende );
}

int Framework::textL�nge( const char *txt ) // gibt die L�nge von txt zur�ck
{
    if( !txt )
        return 0;
    int ret = 0;
    for( ; txt[ ret ] != 0; ++ret );
    return ret;
}