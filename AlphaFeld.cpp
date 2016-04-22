#include "AlphaFeld.h"
#include "Punkt.h"
#include "Bild.h"
#include "Scroll.h"
#include "ToolTip.h"
#include "Text.h"

using namespace Framework;

// Inhalt der AlphaFeld Klasse aus AlphaFeld.h
// Konstruktor 
AlphaFeld::AlphaFeld()
    : Zeichnung(),
    st�rke( 5 ),
    farbe( 0x9B000000 ),
    ref( 1 )
{}

// nicht constant 
void AlphaFeld::setSt�rke( int st ) // setzt die St�rke
{
    st�rke = st;
    rend = 1;
}

void AlphaFeld::setFarbe( int f ) // setzt die Farbe
{
    farbe = f;
    rend = 1;
}

void AlphaFeld::render( Bild &zRObj ) // zeichnet nach zRObj
{
    __super::render( zRObj );
    int br = gr.x - 1;
    int h� = gr.y - 1;
    int xp = pos.x, yp = pos.y;
    int a = ( farbe >> 24 ) & 0xFF;
    int index = ( br / 2 ) * ( br <= h� ) + ( h� / 2 ) * ( br > h� );
    int fc = farbe & 0x00FFFFFF;
    int fc2 = farbe;
    if( st�rke > 0 )
        index = index > ( a / st�rke ) ? a / st�rke : index;
    if( st�rke < 0 )
        index = index > ( ( 255 - a ) / -st�rke ) ? ( ( 255 - a ) / -st�rke ) : index;
    for( int i = 0; i < index; ++i )
    {
        a -= st�rke;
        fc2 = ( a << 24 ) | fc;
        int i2 = i << 1;
        zRObj.drawLinieHAlpha( xp + i + 1, yp + i, br - i2, fc2 );		// oben links --- oben rechts
        zRObj.drawLinieVAlpha( xp + br - i, yp + i + 1, h� - i2, fc2 );	// oben rechts -- unten rechts
        zRObj.drawLinieHAlpha( xp + i, yp + h� - i, br - i2, fc2 );		// unten rechts - unten links
        zRObj.drawLinieVAlpha( xp + i, yp + i, h� - i2, fc2 );			// unten links -- oben links
    }
    if( index == br / 2 )
    {
        for( int i = index; i <= index + ( br - index ) - index; ++i )
            zRObj.drawLinieVAlpha( xp + i, yp + index, h� - ( index << 1 ) + 1, fc2 ); // rest Fl�che senkrecht
    }
    else
    {
        for( int i = index; i <= index + ( h� - index ) - index; ++i )
            zRObj.drawLinieHAlpha( xp + index, yp + i, br - ( index << 1 ) + 1, fc2 ); // rest Fl�che waagerecht
    }
}

// constant 
int AlphaFeld::getSt�rke() const // gibt die St�rke zur�ck
{
    return st�rke;
}

int AlphaFeld::getFarbe() const // gibt die Farbe zur�ck
{
    return farbe;
}

Zeichnung *AlphaFeld::dublizieren() const // Kopiert das Zeichnung
{
    AlphaFeld *obj = new AlphaFeld();
    obj->setPosition( pos );
    obj->setGr��e( gr );
    obj->setMausEreignisParameter( makParam );
    obj->setTastaturEreignisParameter( takParam );
    obj->setMausEreignis( Mak );
    obj->setTastaturEreignis( Tak );
    if( toolTip )
        obj->setToolTipText( toolTip->zText()->getText(), toolTip->zBildschirm() );
    obj->setSt�rke( st�rke );
    obj->setFarbe( farbe );
    return obj;
}

// Reference Counting 
AlphaFeld *AlphaFeld::getThis()
{
    ++ref;
    return this;
}

AlphaFeld *AlphaFeld::release()
{
    --ref;
    if( !ref )
        delete this;
    return 0;
}