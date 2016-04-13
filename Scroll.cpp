#include "Scroll.h"
#include "Bild.h"
#include "MausEreignis.h"

using namespace Framework;

// Inhalt der VScrollBar Klasse aus Scroll.h
// Konstruktor 
VScrollBar::VScrollBar()
	: data(new VScrollData()),
	  knopfdruck( 0 ),
	  farbe( 0xFF808080),
	  bgFarbe( 0xFF000000 ),
	  bg( 0 ),
	  klickScroll( 10 ),
	  mx( -1 ),
	  my( -1 ),
	  mp( 0 ),
	  rend( 0 ),
	  ref( 1 )
{
}

// Destruktor 
VScrollBar::~VScrollBar()
{
	delete data;
}

// nicht constant
void VScrollBar::setFarbe( int fc )
{
	farbe = fc;
	rend = 1;
}

void VScrollBar::setBgFarbe( int fc, bool bgF )
{
	bgFarbe = fc;
	bg = bgF;
	rend = 1;
}

void VScrollBar::update( int maxH�he, int anzeigeH�he )
{
	if( data->maxH�he != maxH�he || data->anzeigeH�he != anzeigeH�he )
	{
		data->maxH�he = maxH�he, data->anzeigeH�he = anzeigeH�he;
		rend = 1;
	}
	if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he && data->maxH�he - data->anzeigeH�he >= 0 )
	{
		data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
		rend = 1;
	}
	if( data->anzeigeBeginn < 0 )
	{
		data->anzeigeBeginn = 0;
		rend = 1;
	}
}

void VScrollBar::setKlickScroll( int ks )
{
	klickScroll = ks;
	rend = 1;
}

void VScrollBar::scroll( int h�he )
{
	data->anzeigeBeginn = h�he;
	if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
		data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
	if( data->anzeigeBeginn < 0 )
		data->anzeigeBeginn = 0;
	rend = 1;
}

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
		data->anzeigeBeginn -= klickScroll;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		rend = 1;
		return ret;
	}
	if( me.id == ME_DScroll )
	{
		data->anzeigeBeginn += klickScroll;
		if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
			data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
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
				data->anzeigeBeginn -= klickScroll;
			}
			else if( my > h� - br )
			{
				knopfdruck = 2;
				data->anzeigeBeginn += klickScroll;
			}
			else
				data->anzeigeBeginn = (int)( ( data->maxH�he / ( h� - 2.0 * br ) ) * ( my - br ) ) - data->anzeigeH�he / 2;
			if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
				data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
			if( data->anzeigeBeginn < 0 )
				data->anzeigeBeginn = 0;
			rend = 1;
		}
	}
    return ret;
}

bool VScrollBar::getRend()
{
	if( knopfdruck == 1 )
	{
		int tmp = data->anzeigeBeginn;
		data->anzeigeBeginn -= klickScroll;
		if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
			data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		if( tmp != data->anzeigeBeginn )
			rend = 1;
	}
	if( knopfdruck == 2 )
	{
		int tmp = data->anzeigeBeginn;
		data->anzeigeBeginn += klickScroll;
		if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
			data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		if( tmp != data->anzeigeBeginn )
			rend = 1;
	}
	bool ret = rend;
	rend = 0;
	return ret;
}

// const 
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
	int st = (int)( data->anzeigeBeginn / ( data->maxH�he / ( h� - br * 2.0 ) ) );
	int end = (int)( ( h� - 2.0 * br ) / ( (double)data->maxH�he / data->anzeigeH�he ) );
	if( data->anzeigeBeginn > data->maxH�he - data->anzeigeH�he )
		data->anzeigeBeginn = data->maxH�he - data->anzeigeH�he;
	if( data->anzeigeBeginn < 0 )
	{
		data->anzeigeBeginn = 0;
		end = h� - br * 2;
	}
	zRObj.f�llRegion( x + 1, y + br + st, br - 1, end, farbe );
}

VScrollData *VScrollBar::getScrollData() const
{
	return data;
}

int VScrollBar::getKlickScroll() const
{
	return klickScroll;
}

int VScrollBar::getFarbe() const
{
	return farbe;
}

int VScrollBar::getBgFarbe() const
{
	return bg ? bgFarbe : 0;
}

int VScrollBar::getScroll() const
{
    return data->anzeigeBeginn;
}

// Reference Counting
VScrollBar *VScrollBar::getThis()
{
	++ref;
	return this;
}

VScrollBar *VScrollBar::release()
{
	--ref;
	if( ref == 0 )
		delete this;
	return 0;
}

// Inhalt der HScrollBar Klasse aus Scroll.h
// Konstruktor 
HScrollBar::HScrollBar()
	: data( new HScrollData() ),
	  knopfdruck( 0 ),
	  farbe( 0xFF808080),
	  bgFarbe( 0 ),
	  bg( 0 ),
	  klickScroll( 10 ),
	  mx( -1 ),
	  my( -1 ),
	  mp( 0 ),
	  rend( 0 ),
	  ref( 1 )
{
}

// Destruktor 
HScrollBar::~HScrollBar()
{
	delete data;
}

// nicht constant
void HScrollBar::setFarbe( int fc )
{
	farbe = fc;
	rend = 1;
}

void HScrollBar::setBgFarbe( int fc, bool bgF )
{
	bgFarbe = fc;
	bg = bgF;
	rend = 1;
}

void HScrollBar::update( int maxBreite, int anzeigeBreite )
{
	if( data->maxBreite != maxBreite || data->anzeigeBreite != anzeigeBreite )
	{
		data->maxBreite = maxBreite, data->anzeigeBreite = anzeigeBreite;
		rend = 1;
	}
	if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite && data->maxBreite - data->anzeigeBreite >= 0 )
	{
		data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
		rend = 1;
	}
	if( data->anzeigeBeginn < 0 )
	{
		data->anzeigeBeginn = 0;
		rend = 1;
	}
}

void HScrollBar::setKlickScroll( int ks )
{
	klickScroll = ks;
	rend = 1;
}

void HScrollBar::scroll( int breite )
{
	data->anzeigeBeginn = breite;
	if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
		data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
	if( data->anzeigeBeginn < 0 )
		data->anzeigeBeginn = 0;
	rend = 1;
}

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
		data->anzeigeBeginn -= klickScroll;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		rend = 1;
		return ret;
	}
	if( me.id == ME_RScroll )
	{
		data->anzeigeBeginn += klickScroll;
		if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
			data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
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
				data->anzeigeBeginn -= klickScroll;
			}
			else if( mx > br - h� )
			{
				knopfdruck = 2;
				data->anzeigeBeginn += klickScroll;
			}
			else
				data->anzeigeBeginn = (int)( ( data->maxBreite / ( br - 2.0 * h� ) ) * ( mx - h� ) ) - data->anzeigeBreite / 2;
			if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
				data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
			if( data->anzeigeBeginn < 0 )
				data->anzeigeBeginn = 0;
			rend = 1;
		}
	}
    return ret;
}

bool HScrollBar::getRend()
{
	if( knopfdruck == 1 )
	{
		int tmp = data->anzeigeBeginn;
		data->anzeigeBeginn -= klickScroll;
		if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
			data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		if( tmp != data->anzeigeBeginn )
			rend = 1;
	}
	if( knopfdruck == 2 )
	{
		int tmp = data->anzeigeBeginn;
		data->anzeigeBeginn += klickScroll;
		if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
			data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
		if( data->anzeigeBeginn < 0 )
			data->anzeigeBeginn = 0;
		if( tmp != data->anzeigeBeginn )
			rend = 1;
	}
	bool ret = rend;
	rend = 0;
	return ret;
}

// const 
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
	int st = (int)( data->anzeigeBeginn / ( data->maxBreite / ( br - h� * 2.0 ) ) );
	int end = (int)( ( br - 2.0 * h� ) / ( (double)data->maxBreite / data->anzeigeBreite ) );
	if( data->anzeigeBeginn > data->maxBreite - data->anzeigeBreite )
		data->anzeigeBeginn = data->maxBreite - data->anzeigeBreite;
	if( data->anzeigeBeginn < 0 )
	{
		data->anzeigeBeginn = 0;
		end = br - h� * 2;
	}
	zRObj.f�llRegion( x + h� + st, y + 1, end, h� - 1, farbe );
}

HScrollData *HScrollBar::getScrollData() const
{
	return data;
}

int HScrollBar::getKlickScroll() const
{
	return klickScroll;
}

int HScrollBar::getFarbe() const
{
	return farbe;
}

int HScrollBar::getBgFarbe() const
{
	return bg ? bgFarbe : 0;
}

int HScrollBar::getScroll() const
{
    return data->anzeigeBeginn;
}

// Reference Counting
HScrollBar *HScrollBar::getThis()
{
	++ref;
	return this;
}

HScrollBar *HScrollBar::release()
{
	--ref;
	if( ref == 0 )
		delete this;
	return 0;
}