#include "Scroll.h"
#include "Bild.h"
#include "MausEreignis.h"

using namespace Framework;

// Inhalt der VScrollBar Klasse aus Scroll.h
// Konstruktor 
ScrollBar::ScrollBar()
    : data( new ScrollData() ),
    knopfdruck( 0 ),
    farbe( 0xFF808080 ),
    bgFarbe( 0xFF000000 ),
    bg( 0 ),
    klickScroll( 10 ),
    mx( -1 ),
    my( -1 ),
    mp( 0 ),
    rend( 0 ),
    ref( 1 )
{}

// Destruktor 
ScrollBar::~ScrollBar()
{
    delete data;
}

// nicht constant
void ScrollBar::setFarbe( int fc )
{
    farbe = fc;
    rend = 1;
}

void ScrollBar::setBgFarbe( int fc, bool bgF )
{
    bgFarbe = fc;
    bg = bgF;
    rend = 1;
}

void ScrollBar::update( int maxGr, int anzeigeGr )
{
    if( data->max != maxGr || data->anzeige != anzeigeGr )
    {
        data->max = maxGr, data->anzeige = anzeigeGr;
        rend = 1;
    }
    if( data->scrollPos > data->max - data->anzeige && data->max - data->anzeige >= 0 )
    {
        data->scrollPos = data->max - data->anzeige;
        rend = 1;
    }
    if( data->scrollPos < 0 )
    {
        data->scrollPos = 0;
        rend = 1;
    }
}

void ScrollBar::setKlickScroll( int ks )
{
    klickScroll = ks;
    rend = 1;
}

void ScrollBar::scroll( int h�he )
{
    data->scrollPos = h�he;
    if( data->scrollPos > data->max - data->anzeige )
        data->scrollPos = data->max - data->anzeige;
    if( data->scrollPos < 0 )
        data->scrollPos = 0;
    rend = 1;
}

bool ScrollBar::getRend()
{
    if( knopfdruck == 1 )
    {
        int tmp = data->scrollPos;
        data->scrollPos -= klickScroll;
        if( data->scrollPos > data->max - data->anzeige )
            data->scrollPos = data->max - data->anzeige;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        if( tmp != data->scrollPos )
            rend = 1;
    }
    if( knopfdruck == 2 )
    {
        int tmp = data->scrollPos;
        data->scrollPos += klickScroll;
        if( data->scrollPos > data->max - data->anzeige )
            data->scrollPos = data->max - data->anzeige;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        if( tmp != data->scrollPos )
            rend = 1;
    }
    bool ret = rend;
    rend = 0;
    return ret;
}

// const 
ScrollData *ScrollBar::getScrollData() const
{
    return data;
}

int ScrollBar::getKlickScroll() const
{
    return klickScroll;
}

int ScrollBar::getFarbe() const
{
    return farbe;
}

int ScrollBar::getBgFarbe() const
{
    return bg ? bgFarbe : 0;
}

int ScrollBar::getScroll() const
{
    return data->scrollPos;
}

// Reference Counting
ScrollBar *ScrollBar::getThis()
{
    ++ref;
    return this;
}

ScrollBar *ScrollBar::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}

// Inhalt der VScrollBar Klasse
VScrollBar::VScrollBar()
    : ScrollBar()
{}

bool VScrollBar::doMausMessage( int x, int y, int br, int h�, MausEreignis &me )
{
    bool ret = me.mx >= x && me.mx <= x + br && me.my >= y && me.my <= y + h�;
    knopfdruck = 0;
    if( me.verarbeitet )
    {
        mx = -1, my = -1;
        mp = 0;
        return ret;
    }
    if( me.id == ME_UScroll )
    {
        data->scrollPos -= klickScroll;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        rend = 1;
        return ret;
    }
    if( me.id == ME_DScroll )
    {
        data->scrollPos += klickScroll;
        if( data->scrollPos > data->max - data->anzeige )
            data->scrollPos = data->max - data->anzeige;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        rend = 1;
        return ret;
    }
    if( ret )
        mx = me.mx - x, my = me.my - y;
    else
        mx = -1, my = -1;
    if( me.id == ME_PLinks )
        mp = 1;
    if( me.id == ME_RLinks )
        mp = 0;
    if( mp )
    {
        if( mx >= 0 && my >= 0 )
        {
            if( my < br )
            {
                knopfdruck = 1;
                data->scrollPos -= klickScroll;
            }
            else if( my > h� - br )
            {
                knopfdruck = 2;
                data->scrollPos += klickScroll;
            }
            else
                data->scrollPos = (int)( ( data->max / ( h� - 2.0 * br ) ) * ( my - br ) ) - data->anzeige / 2;
            if( data->scrollPos > data->max - data->anzeige )
                data->scrollPos = data->max - data->anzeige;
            if( data->scrollPos < 0 )
                data->scrollPos = 0;
            rend = 1;
        }
    }
    return ret;
}

void VScrollBar::render( int x, int y, int br, int h�, Bild &zRObj ) const
{
    if( bg )
        zRObj.alphaRegion( x, y, br, h�, bgFarbe );
    --br;
    --h�;
    zRObj.drawLinieH( x, y, br + 1, farbe );
    zRObj.drawLinieH( x, y + h�, br + 1, farbe );
    zRObj.drawLinieV( x, y + 1, h� - 1, farbe );
    zRObj.drawLinieV( x + br, y + 1, h� - 1, farbe );
    zRObj.drawLinieH( x + 1, y + br, br - 1, farbe );
    zRObj.drawLinieH( x + 1, y + h� - br, br - 1, farbe );
    ++br;
    ++h�;
    int st = (int)( data->scrollPos / ( data->max / ( h� - br * 2.0 ) ) );
    int end = (int)( ( h� - 2.0 * br ) / ( (double)data->max / data->anzeige ) );
    if( data->scrollPos > data->max - data->anzeige )
        data->scrollPos = data->max - data->anzeige;
    if( data->scrollPos < 0 )
    {
        data->scrollPos = 0;
        end = h� - br * 2;
    }
    zRObj.f�llRegion( x + 1, y + br + st, br - 1, end, farbe );
}

ScrollBar *VScrollBar::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}

// Inhalt der HScrollBar Klasse aus Scroll.h
// Konstruktor 
HScrollBar::HScrollBar()
    : ScrollBar()
{}

// nicht constant
bool HScrollBar::doMausMessage( int x, int y, int br, int h�, MausEreignis &me )
{
    bool ret = me.mx >= x && me.mx <= x + br && me.my >= y && me.my <= y + h�;
    knopfdruck = 0;
    if( me.verarbeitet )
    {
        mx = -1, my = -1;
        mp = 0;
        return ret;
    }
    if( me.id == ME_LScroll )
    {
        data->scrollPos -= klickScroll;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        rend = 1;
        return ret;
    }
    if( me.id == ME_RScroll )
    {
        data->scrollPos += klickScroll;
        if( data->scrollPos > data->max - data->anzeige )
            data->scrollPos = data->max - data->anzeige;
        if( data->scrollPos < 0 )
            data->scrollPos = 0;
        rend = 1;
        return ret;
    }
    if( ret )
        mx = me.mx - x, my = me.my - y;
    else
        mx = -1, my = -1;
    if( me.id == ME_PLinks )
        mp = 1;
    if( me.id == ME_RLinks )
        mp = 0;
    if( mp )
    {
        if( mx >= 0 && my >= 0 )
        {
            if( mx < h� )
            {
                knopfdruck = 1;
                data->scrollPos -= klickScroll;
            }
            else if( mx > br - h� )
            {
                knopfdruck = 2;
                data->scrollPos += klickScroll;
            }
            else
                data->scrollPos = (int)( ( data->max / ( br - 2.0 * h� ) ) * ( mx - h� ) ) - data->anzeige / 2;
            if( data->scrollPos > data->max - data->anzeige )
                data->scrollPos = data->max - data->anzeige;
            if( data->scrollPos < 0 )
                data->scrollPos = 0;
            rend = 1;
        }
    }
    return ret;
}

void HScrollBar::render( int x, int y, int br, int h�, Bild &zRObj ) const
{
    if( bg )
        zRObj.alphaRegion( x, y, br, h�, bgFarbe );
    --br;
    --h�;
    zRObj.drawLinieV( x, y, h� + 1, farbe );
    zRObj.drawLinieV( x + br, y, h� + 1, farbe );
    zRObj.drawLinieH( x + 1, y, br - 1, farbe );
    zRObj.drawLinieH( x + 1, y + h�, br - 1, farbe );
    zRObj.drawLinieV( x + h�, y + 1, h� - 1, farbe );
    zRObj.drawLinieV( x + br - h�, y + 1, h� - 1, farbe );
    ++br;
    ++h�;
    int st = (int)( data->scrollPos / ( data->max / ( br - h� * 2.0 ) ) );
    int end = (int)( ( br - 2.0 * h� ) / ( (double)data->max / data->anzeige ) );
    if( data->scrollPos > data->max - data->anzeige )
        data->scrollPos = data->max - data->anzeige;
    if( data->scrollPos < 0 )
    {
        data->scrollPos = 0;
        end = br - h� * 2;
    }
    zRObj.f�llRegion( x + h� + st, y + 1, end, h� - 1, farbe );
}

ScrollBar *HScrollBar::release()
{
    --ref;
    if( ref == 0 )
        delete this;
    return 0;
}