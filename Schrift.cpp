#include "Schrift.h"
#include "Bild.h"
#include "Text.h"
#include "Scroll.h"
#include "Globals.h"
#include <Windows.h>
#include "FrameworkMath.h"

using namespace Framework;

// Inhalt der Buchstabe Klasse aus Schrift.h
// Konstruktor 
Buchstabe::Buchstabe()
    : gr��e( 0, 0 ),
    pos( 0, 0 ),
    alpha( 0 ),
    schriftGr��e( 0 ),
    drawSg( 0 ),
    ref( 1 )
{}

// Destruktor 
Buchstabe::~Buchstabe()
{
    if( alpha )
        delete[]alpha;
}

// nicht constant 
void Buchstabe::NeuBuchstabe( Punkt &gr��e ) // Initialisierung
{
    this->gr��e = gr��e;
    if( alpha )
        delete[]alpha;
    alpha = new unsigned char[ gr��e.x * gr��e.y ];
    ZeroMemory( alpha, gr��e.x * gr��e.y );
}

void Buchstabe::setPixel( Punkt &pos, unsigned char alpha ) // setzt den alphawert des Pixels
{
    this->alpha[ pos.x + pos.y * gr��e.x ] = alpha;
}

void Buchstabe::setPixel( int x, int y, unsigned char alpha )
{
    this->alpha[ x + y * gr��e.x ] = alpha;
}

void Buchstabe::setPixel( int i, unsigned char alpha )
{
    this->alpha[ i ] = alpha;
}

void Buchstabe::setPosition( Punkt &pos ) // setzt die Buchstabenposition
{
    this->pos = pos;
}

void Buchstabe::setPosition( int x, int y )
{
    pos.x = x;
    pos.y = y;
}

void Buchstabe::setSchriftGr��e( int sg ) // setzt die Schriftgr��e des Buchstaben
{
    schriftGr��e = sg;
}

void Buchstabe::setDrawSchriftGr��e( int dsg ) // setzt die Zeichengr��e des Buchstaben
{
    drawSg = dsg;
}

// constant
const Punkt &Buchstabe::getGr��e() const // gibt die Buchstabenbildgr��e zur�ck
{
    return gr��e;
}

int Buchstabe::getBreite() const // Buchstabenbreite
{
    return (int)( ( (double)gr��e.x / (double)schriftGr��e ) * (double)drawSg + 0.5 );
}

int Buchstabe::getH�he() const // Buchstabenh�he
{
    return (int)( ( (double)gr��e.y / (double)schriftGr��e ) *(double)drawSg + 0.5 );
}

int Buchstabe::getNormH�he() const // Buchstabenh�he
{
    return gr��e.y;
}

unsigned char *Buchstabe::getBuff() const // gibt den Alphabuffer zur�ck
{
    return alpha;
}

void Buchstabe::render( Bild &zRObj, int f ) const // Zeichnet nach zRObj
{
    if( alpha )
    {
        const Punkt &zRObjGr = zRObj.getDrawGr();
        const Punkt &zRObjPos = zRObj.getDrawPos();
        const Punkt &zRObjOff = zRObj.getDrawOff();
        int xp = pos.x + zRObjOff.x, yp = pos.y + zRObjOff.y;
        int xs = xp < zRObjPos.x ? ( zRObjPos.x - xp ) : 0, ys = yp < zRObjPos.y ? ( zRObjPos.y - yp ) : 0;
        int b = gr��e.x, h = gr��e.y;
        unsigned char a2 = ( 255 - ( f >> 24 ) );
        f &= 0x00FFFFFF;
        if( schriftGr��e == drawSg )
        {
            if( xp >= zRObjGr.x || yp >= zRObjGr.y || xp + b < zRObjPos.x || yp + h < zRObjPos.y )
                return;
            b = ( xp + b ) > zRObjGr.x ? ( zRObjGr.x - xp ) : b;
            h = ( yp + h ) > zRObjGr.y ? ( zRObjGr.y - yp ) : h;
            if( !a2 )
            {
                int xx, ygr = ( ys - 1 ) * gr��e.x, ygr2 = ( yp + ys - 1 ) * zRObj.getBreite();
                for( int yy = ys; yy < h; ++yy )
                {
                    ygr += gr��e.x;
                    ygr2 += zRObj.getBreite();
                    for( xx = xs; xx < b; ++xx )
                        zRObj.alphaPixel( xp + xx + ygr2, f | ( alpha[ xx + ygr ] << 24 ) );
                }
            }
            else
            {
                int a;
                int xx, ygr = ( ys - 1 ) * gr��e.x, ygr2 = ( yp + ys - 1 ) * zRObj.getBreite();
                for( int yy = ys; yy < h; ++yy )
                {
                    ygr += gr��e.x;
                    ygr2 += zRObj.getBreite();
                    for( xx = xs; xx < b; ++xx )
                    {
                        a = alpha[ xx + ygr ] - a2;
                        if( a > 0 )
                            zRObj.alphaPixel( xp + xx + ygr2, f | ( a << 24 ) );
                    }
                }
            }
        }
        else
        {
            double xoff = (double)schriftGr��e / (double)drawSg,
                yoff = (double)schriftGr��e / (double)drawSg;
            double x = xs * xoff, y = ys * yoff;
            int maxX = getBreite(), maxY = getH�he();
            maxX = ( xp + maxX ) >= zRObjGr.x ? ( zRObjGr.x - xp ) : maxX;
            maxY = ( yp + maxY ) >= zRObjGr.y ? ( zRObjGr.y - yp ) : maxY;
            if( !a2 )
            {
                int dx, ygr, ygr2;
                for( int dy = ys; dy < maxY; ++dy )
                {
                    ygr2 = ( yp + dy ) * zRObj.getBreite();
                    ygr = (int)y * b;
                    for( dx = xs; dx < maxX; ++dx )
                    {
                        zRObj.alphaPixel( xp + dx + ygr2, f | ( alpha[ (int)x + ygr ] << 24 ) );
                        x += xoff;
                    }
                    x = xs;
                    y += yoff;
                }
            }
            else
            {
                int a, dx, ygr, ygr2;
                for( int dy = ys; dy < maxY; ++dy )
                {
                    ygr2 = ( yp + dy ) * zRObj.getBreite();
                    ygr = (int)y * b;
                    for( dx = xs; dx < maxX; ++dx )
                    {
                        a = alpha[ (int)x + ygr ] - a2;
                        zRObj.alphaPixel( xp + dx + ygr2, f | ( a << 24 ) );
                        x += xoff;
                    }
                    x = xs;
                    y += yoff;
                }
            }
        }
    }
}

// Reference Counting 
Buchstabe *Buchstabe::getThis()
{
    ++ref;
    return this;
}

Buchstabe *Buchstabe::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}

// Inhalt der Alphabet Klasse aus Schrift.h
// Konstruktor 
Alphabet::Alphabet()
    : zeichen( new Buchstabe*[ 256 ] ),
    schriftGr��e( 12 ),
    drawSchriftGr��e( 12 ),
    pos( 0, 0 ),
    zeilenH�he( 0 ),
    zeilenAbstand( 5 ),
    ref( 1 )
{
    for( int i = 0; i < 256; ++i )
        zeichen[ i ] = 0;
}

// Destruktor 
Alphabet::~Alphabet()
{
    for( int i = 0; i < 256; ++i )
    {
        if( zeichen[ i ] )
            zeichen[ i ]->release();
    }
    delete[]zeichen;
}

// nicht constant 
void Alphabet::NeuAlphabet() // Initialisierung 
{
    for( int i = 0; i < 256; ++i )
    {
        if( zeichen[ i ] )
            zeichen[ i ]->release();
    }
    for( int i = 0; i < 256; ++i )
        zeichen[ i ] = 0;
    zeilenH�he = 0;
}

void Alphabet::setBuchstabe( unsigned char i, Buchstabe *buchstabe ) // setzt einen Buchstaben
{
    if( zeichen[ i ] )
        zeichen[ i ]->release();
    zeichen[ i ] = buchstabe;
    if( zeichen[ i ] )
    {
        zeichen[ i ]->setSchriftGr��e( schriftGr��e );
        zeichen[ i ]->setDrawSchriftGr��e( drawSchriftGr��e );
    }
    zeilenH�he = 0;
    for( int i = 0; i < 256; ++i )
    {
        if( zeichen[ i ] != 0 )
            zeilenH�he = maxInt( zeichen[ i ]->getH�he(), zeilenH�he );
    }
}

void Alphabet::setSchriftgr��e( int gr ) // setzt die Schriftgr��e
{
    schriftGr��e = gr;
    for( int i = 0; i < 256; ++i )
    {
        if( zeichen[ i ] )
            zeichen[ i ]->setSchriftGr��e( gr );
    }
}

void Alphabet::setDrawSchriftgr��e( int gr ) // setzt die Zeichengr��e
{
    drawSchriftGr��e = gr;
    for( int i = 0; i < 256; ++i )
    {
        if( zeichen[ i ] )
            zeichen[ i ]->setDrawSchriftGr��e( gr );
    }
}

void Alphabet::setZeilenAbstand( int za ) // setzt die Zeilenh�he( Zeilenabstand )
{
    zeilenAbstand = za;
}

void Alphabet::setDrawPosition( Punkt &pos ) // setzt die Draw Position
{
    this->pos = pos;
}

void Alphabet::setDrawPosition( int x, int y )
{
    pos.x = x;
    pos.y = y;
}

// constant 
Buchstabe *Alphabet::getBuchstabe( unsigned char i ) const // gibt einen Buchstaben zur�ck
{
    if( zeichen[ i ] )
        return zeichen[ i ]->getThis();
    return 0;
}

Buchstabe *Alphabet::zBuchstabe( unsigned char i ) const
{
    return zeichen[ i ];
}

bool Alphabet::hatBuchstabe( unsigned char b ) const
{
    return zeichen[ b ] != 0;
}

int Alphabet::getSchriftgr��e() const // gibt die Schriftgr��e zur�ck
{
    return schriftGr��e;
}

int Alphabet::getDrawSchriftGr��e() const // gibt die Zeichengr��e zur�ck
{
    return drawSchriftGr��e;
}

int Alphabet::getZeilenAbstand() const // gibt den Zeilenabstand zur�ck
{
    return zeilenAbstand;
}

int Alphabet::getZeilenH�he() const // gibt die H�he des h�chsten Zeichens zur�ck
{
    return (int)( (double)zeilenH�he / schriftGr��e * drawSchriftGr��e + 0.5 );
}

const Punkt &Alphabet::getPosition() const // gibt die DrawPosition zur�ck
{
    return pos;
}

int Alphabet::getTextBreite( Text *zTxt ) const // gibt die Breite des Textes zur�ck
{
    int ret = 0;
    int l�n = zTxt->getL�nge();
    char *buff = zTxt->getText();
    unsigned char c = 0;
    int tmp = 0;
    for( int i = 0; i < l�n; ++i )
    {
        c = (unsigned char)buff[ i ];
        if( buff[ i ] == '\n' )
        {
            if( tmp > ret )
                ret = tmp;
            tmp = 0;
        }
        else if( buff[ i ] == '\r' )
        {
            i += 10;
            continue;
        }
        else if( buff[ i ] == '\t' )
            tmp += drawSchriftGr��e;
        else if( buff[ i ] == ' ' )
            tmp += drawSchriftGr��e / 2;
        else if( zeichen[ c ] )
            tmp += zeichen[ c ]->getBreite();
    }
    if( tmp > ret )
        ret = tmp;
    return ret;
}

int Alphabet::getTextH�he( Text *zTxt ) const // gibt die H�he des Textes zur�ck
{
    int h� = getZeilenH�he();
    return h� + ( ( h� + zeilenAbstand ) * zTxt->anzahlVon( '\n' ) );
}

int Alphabet::textPos( Text *zText, int mausX, int mausY ) const // gibt den Buchstaben zur�ck, auf den die Maus zeigt
{
    char *buffer = zText->getText();
    int l�n = zText->getL�nge();
    int tx = 0;
    int ty = 0;
    int sh = getZeilenH�he();
    if( mausX < 0 || mausY < 0 )
        return -1;
    for( int i = 0; i < l�n; ++i )
    {
        if( buffer[ i ] == '\n' )
        {
            ty += sh + zeilenAbstand;
            tx = 0;
            if( mausY < ty )
                return i;
        }
        if( buffer[ i ] == '\t' )
            tx += drawSchriftGr��e;
        if( buffer[ i ] == ' ' )
            tx += drawSchriftGr��e / 2;
        if( zeichen[ (unsigned char)buffer[ i ] ] )
            tx += zeichen[ (unsigned char)buffer[ i ] ]->getBreite();
        int txpl = 0;
        if( zeichen[ (unsigned char)buffer[ i + 1 ] ] )
            txpl = zeichen[ (unsigned char)buffer[ i + 1 ] ]->getBreite() / 2;
        if( mausX < tx - txpl && mausY < ty + sh + zeilenAbstand )
            return i;
    }
    if( mausY < ty + sh + zeilenAbstand )
        return l�n;
    return -1;
}

void Alphabet::textFormatieren( Text *zText, int maxBreite, int schriftGr��e ) // f�gt zeilenumbr�che ein 
{
    int sg = drawSchriftGr��e;
    setDrawSchriftgr��e( schriftGr��e );
    int zeilenH�he = getZeilenH�he() + getZeilenAbstand();
    int lastPos = -1;
    int l�n = zText->getL�nge();
    char *txt = zText->getText();
    int x = 0;
    Text result = zText->getText();
    for( int i = 0; i < l�n; ++i )
    {
        char c = txt[ i ];
        if( c == ' ' )
        {
            lastPos = i;
            x += schriftGr��e / 2;
            continue;
        }
        if( c == '\t' )
        {
            lastPos = i;
            x += schriftGr��e;
            continue;
        }
        if( c == '\n' )
        {
            x = 0;
            lastPos = -1;
            continue;
        }
        if( c == '\r' && l�n - i >= 11 )
        {
            i += 10;
            continue;
        }
        Buchstabe *b = getBuchstabe( (unsigned)c );
        if( b )
        {
            x += b->getBreite();
            if( x > maxBreite && lastPos > -1 )
            {
                result.ersetzen( lastPos, lastPos + 1, "\n" );
                x = 0;
                i = lastPos;
                lastPos = -1;
            }
            b = b->release();
        }
    }
    zText->setText( result );
    setDrawSchriftgr��e( sg );
}

void Alphabet::render( Text *zTxt, Bild &rendezRObj, int f ) const // Zeichnet txt nach rendezRObj
{
    int zRObjBr = rendezRObj.getBreite();
    int zRObjH� = rendezRObj.getH�he();
    int xp = pos.x;
    int yp = pos.y;
    int zh = getZeilenH�he();
    if( yp + ( zh + zeilenAbstand ) * zTxt->anzahlVon( '\n' ) + zh < 0 || xp >= zRObjBr || yp >= zRObjH� )
        return;
    char *text = zTxt->getText();
    int l�n = zTxt->getL�nge();
    for( int i = 0; i < l�n; ++i )
    {
        unsigned char c = text[ i ];
        if( c == ' ' )
        {
            xp += drawSchriftGr��e / 2;
            continue;
        }
        if( c == '\t' )
        {
            xp += drawSchriftGr��e;
            continue;
        }
        if( c == '\n' )
        {
            yp += zh + zeilenAbstand;
            xp = pos.x;
            continue;
        }
        if( c == '\r' && l�n - i >= 11 )
        {
            i += 3;
            Text *hex1 = zTxt->getTeilText( i, i + 6 );
            Text *hex2 = zTxt->getTeilText( i + 6, i + 8 );
            f = ( TextZuInt( hex1->getText(), 16 ) << 8 ) |
                ( TextZuInt( hex2->getText(), 16 ) );
            hex1->release();
            hex2->release();
            i += 7;
            continue;
        }
        if( zeichen[ c ] )
        {
            if( xp >= zRObjBr )
                continue;
            zeichen[ c ]->setPosition( xp, yp );
            zeichen[ c ]->render( rendezRObj, f );
            xp += zeichen[ c ]->getBreite();
        }
    }
}

void Alphabet::render( Text *zTxt, Bild &rendezRObj, int cpos, int cf, int fbeg, int ff, int f ) const
{
    int zRObjBr = rendezRObj.getBreite();
    int zRObjH� = rendezRObj.getH�he();
    int xp = pos.x;
    int yp = pos.y;
    int zh = getZeilenH�he();
    if( yp + ( zh + zeilenAbstand ) * zTxt->anzahlVon( '\n' ) + zh < 0 || xp >= zRObjBr || yp >= zRObjH� )
        return;
    char *text = zTxt->getText();
    int l�n = zTxt->getL�nge();
    bool f�rb = 0;
    for( int i = 0; i < l�n; ++i )
    {
        unsigned char c = text[ i ];
        if( i == fbeg )
            f�rb = !f�rb;
        if( i == cpos )
        {
            rendezRObj.drawLinieVAlpha( xp, yp, zh, cf );
            f�rb = !f�rb;
        }
        if( c == ' ' )
        {
            if( f�rb )
                rendezRObj.alphaRegion( xp, yp, drawSchriftGr��e / 2, zh, ff );
            xp += drawSchriftGr��e / 2;
            continue;
        }
        if( c == '\t' )
        {
            if( f�rb )
                rendezRObj.alphaRegion( xp, yp, drawSchriftGr��e, zh, ff );
            xp += drawSchriftGr��e;
            continue;
        }
        if( c == '\n' )
        {
            yp += zh + zeilenAbstand;
            xp = pos.x;
            continue;
        }
        if( c == '\r' && l�n - i >= 11 )
        {
            i += 3;
            Text *hex1 = zTxt->getTeilText( i, i + 6 );
            Text *hex2 = zTxt->getTeilText( i + 6, i + 8 );
            f = ( TextZuInt( hex1->getText(), 16 ) << 8 ) |
                ( TextZuInt( hex2->getText(), 16 ) );
            hex1->release();
            hex2->release();
            i += 7;
            continue;
        }
        if( zeichen[ c ] )
        {
            if( xp >= zRObjBr )
                continue;
            if( f�rb )
            {
                int br = zeichen[ c ]->getBreite();
                rendezRObj.alphaRegion( xp, yp, br, zh, ff );
            }
            zeichen[ c ]->setPosition( xp, yp );
            zeichen[ c ]->render( rendezRObj, f );
            xp += zeichen[ c ]->getBreite();
        }
    }
    if( l�n == cpos )
        rendezRObj.drawLinieVAlpha( xp, yp, zh, cf );
}

// Reference Counting 
Alphabet *Alphabet::getThis()
{
    ++ref;
    return this;
}

Alphabet *Alphabet::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}

// Inhalt der AlphabetArray Klasse aus Schrift.h
// Konstruktor 
AlphabetArray::AlphabetArray()
    : next( 0 ),
    This( 0 )
{}

// Destruktor 
AlphabetArray::~AlphabetArray()
{
    if( This )
        This->release();
    delete next;
}

// nicht constant 
bool AlphabetArray::addAlphabet( Alphabet *alphabet ) // F�gt ein Alphabet hinzu
{
    if( This )
    {
        if( This->getSchriftgr��e() == alphabet->getSchriftgr��e() )
        {
            alphabet->release();
            return false;
        }
    }
    else
    {
        This = alphabet;
        return true;
    }
    if( !next )
        next = new AlphabetArray();
    return next->addAlphabet( alphabet );
}

bool AlphabetArray::removeAlphabet( int sg ) // entfernt ein Alphabet
{
    if( This )
    {
        if( This->getSchriftgr��e() == sg )
            This = This->release();
        return 1;
    }
    if( !next )
        return 0;
    if( next->removeAlphabet( sg ) )
    {
        AlphabetArray *tmp = next->getNext();
        next->setNext0();
        delete next;
        next = tmp;
    }
    return 0;
}

void AlphabetArray::setDrawSchriftGr��e( int sg ) // Setzt die Draw Schriftgr��e aller Alphabete
{
    if( This )
        This->setDrawSchriftgr��e( sg );
    if( next )
        next->setDrawSchriftGr��e( sg );
}

void AlphabetArray::setZeilenAbstand( int za ) // setzt den Zeilenabstant aller Alphabete
{
    if( This )
        This->setZeilenAbstand( za );
    if( next )
        next->setZeilenAbstand( za );
}

void AlphabetArray::setNext0() // setzt den next Zeiger zu 0
{
    next = 0;
}

// constant 
Alphabet *AlphabetArray::getAlphabet( unsigned char sg ) const // gibt getThis von einem Alphabet zur�ck
{
    if( !This )
        return 0;
    if( This->getSchriftgr��e() == sg )
        return This->getThis();
    if( next )
        return next->getAlphabet( sg );
    return 0;
}

Alphabet *AlphabetArray::zAlphabet( unsigned char sg ) const // gibt ein Alphabet zur�ck
{
    if( !This )
        return 0;
    if( This->getSchriftgr��e() == sg )
        return This;
    if( next )
        return next->zAlphabet( sg );
    return 0;
}

Alphabet *AlphabetArray::getAlphabetI( int index, int count ) const
{
    if( count == index )
        return This->getThis();
    if( next )
        return next->getAlphabetI( index, count + 1 );
    return 0;
}

Alphabet *AlphabetArray::zAlphabetI( int index, int count ) const
{
    if( count == index )
        return This;
    if( next )
        return next->zAlphabetI( index, count + 1 );
    return 0;
}

AlphabetArray *AlphabetArray::getNext() const // gibt das n�chste Alphabet zur�ck
{
    return next;
}

// Inhalt der Schrift Klasse aus Schrift.h
// Konstruktor 
Schrift::Schrift()
    : alphabetAnzahl( 0 ),
    alphabet( new AlphabetArray() ),
    schriftGr��e( 12 ),
    zeilenAbstand( 5 ),
    drawPos( 0, 0 ),
    ref( 1 )
{
    InitializeCriticalSection( &cs );
}

// Destruktor 
Schrift::~Schrift()
{
    delete alphabet;
    DeleteCriticalSection( &cs );
}

// nicht constant 
void Schrift::lock() // lockt die Schrift
{
    EnterCriticalSection( &cs );
}

void Schrift::unlock() // unlockt die Schrift
{
    LeaveCriticalSection( &cs );
}

bool Schrift::addAlphabet( Alphabet *alphabet ) // F�gt der Schrift ein Alphabet hinzu
{
    lock();
    if( this->alphabet->addAlphabet( alphabet ) )
    {
        ++alphabetAnzahl;
        alphabet->setDrawSchriftgr��e( schriftGr��e );
        unlock();
        return true;
    }
    unlock();
    return false;
}

void Schrift::removeAlphabet( int sg ) // Entfernt ein Alphabet
{
    lock();
    if( alphabet->removeAlphabet( sg ) )
        --alphabetAnzahl;
    unlock();
}

void Schrift::setDrawPosition( int x, int y ) // setzt die Zeichenposition
{
    lock();
    drawPos.x = x;
    drawPos.y = y;
    unlock();
}

void Schrift::setDrawPosition( Punkt &pos )
{
    lock();
    drawPos = pos;
    unlock();
}

void Schrift::setSchriftGr��e( int sg ) // setzt die Schriftgr��e
{
    lock();
    schriftGr��e = sg;
    alphabet->setDrawSchriftGr��e( sg );
    unlock();
}

void Schrift::setZeilenAbstand( int za ) // setzt den Zeilenabstand
{
    lock();
    zeilenAbstand = za;
    alphabet->setZeilenAbstand( za );
    unlock();
}

void Schrift::textFormatieren( Text *zText, int maxBreite, int schriftGr��e ) // f�gt zeilenumbr�che ein
{
    lock();
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( drawAlphabet )
        drawAlphabet->textFormatieren( zText, maxBreite, schriftGr��e );
    unlock();
}

void Schrift::renderText( Text *zTxt, Bild &zRObj, int f ) // zeichnet txt nach zRObj
{
    lock();
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( drawAlphabet )
    {
        drawAlphabet->setDrawPosition( drawPos.x, drawPos.y );
        drawAlphabet->render( zTxt, zRObj, f );
    }
    unlock();
}

void Schrift::renderText( Text *zTxt, Bild &zRObj, int cpos, int cf, int fbeg, int ff, int f )
{
    lock();
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( drawAlphabet )
    {
        drawAlphabet->setDrawPosition( drawPos.x, drawPos.y );
        drawAlphabet->render( zTxt, zRObj, cpos, cf, fbeg, ff, f );
    }
    unlock();
}

// constant 
Alphabet *Schrift::getAlphabet( int sg ) const // gibt einen Alphaberarray zur�ck
{
    return alphabet->getAlphabet( sg );
}

Alphabet *Schrift::zAlphabet( int sg ) const
{
    return alphabet->zAlphabet( sg );
}

Alphabet *Schrift::getAlphabetI( int index ) const
{
    return alphabet->getAlphabetI( index, 0 );
}

Alphabet *Schrift::zAlphabetI( int index ) const
{
    return alphabet->zAlphabetI( index, 0 );
}

unsigned char Schrift::getAlphabetAnzahl() const // gibt die anzahl von in der Schrift enthaltenen Alphabeten zur�ck
{
    return alphabetAnzahl;
}

int Schrift::getSchriftGr��e() const // gibt die Schriftgr��e zur�ck
{
    return schriftGr��e;
}

int Schrift::getZeilenabstand() const // gibt den Zeilenabstand zur�ck
{
    return zeilenAbstand;
}

int Schrift::getDrawX() const // gibt die Zeichenposition zur�ck
{
    return drawPos.x;
}

int Schrift::getDrawY() const
{
    return drawPos.y;
}

const Punkt &Schrift::getDrawPosition() const
{
    return drawPos;
}

int Schrift::getTextBreite( Text *zTxt ) const // gibt die Breite des Textes zur�ck
{
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( !drawAlphabet )
        return 0;
    return drawAlphabet->getTextBreite( zTxt );
}

int Schrift::getTextH�he( Text *zTxt ) const // gibt die H�he des Textes zur�ck
{
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( !drawAlphabet )
        return 0;
    return drawAlphabet->getTextH�he( zTxt );
}

int Schrift::textPos( Text *zTxt, int mausX, int mausY ) const // gibt den Buchstaben zur�ck, auf den die Maus zeigt
{
    Alphabet *drawAlphabet = alphabet->zAlphabet( schriftGr��e );
    if( !drawAlphabet )
    {
        for( int i = 0; i < 256; ++i )
        {
            drawAlphabet = alphabet->zAlphabet( schriftGr��e - i );
            if( drawAlphabet )
                break;
            drawAlphabet = alphabet->zAlphabet( schriftGr��e + i );
            if( drawAlphabet )
                break;
        }
    }
    if( !drawAlphabet )
        return 0;
    return drawAlphabet->textPos( zTxt, mausX, mausY );
}

// Reference Counting 
Schrift *Schrift::getThis()
{
    ++ref;
    return this;
}

Schrift *Schrift::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}