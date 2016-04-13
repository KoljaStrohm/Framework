#include "Schluessel.h"

using namespace Framework::Verschl�sselung;

// Inhalt der Bytes Klasse aus Schl�ssel.h
// Konstruktor
Bytes::Bytes()
	: bytes( 0 ),
	  del( 1 ),
	  l�n( 0 ),
	  ref( 1 )
{
}

Bytes::Bytes( int l�n )
	: bytes( new char[ l�n ] ),
	  del( 1 ),
	  l�n( l�n ),
	  ref( 1 )
{
}

Bytes::Bytes( const char *daten, int l�n )
	: bytes( new char[ l�n ] ),
	  del( 1 ),
	  l�n( l�n ),
	  ref( 1 )
{
	setBytes( daten );
}

// Destruktor
Bytes::~Bytes()
{
	if( del )
	    delete[] bytes;
}

// nicht constant
void Bytes::setBytes( const char *daten )
{
	if( !bytes || !daten )
		return;
	char *end = bytes + l�n;
	for( char *c = bytes; c < end; c++, ++daten )
		*c = *daten;
}

void Bytes::setBytes( const char *daten, int l�n )
{
	if( !daten || !l�n )
		return;
	if( del )
	    delete[] bytes;
	del = 1;
	bytes = new char[ l�n ];
	this->l�n = l�n;
	setBytes( daten );
}

void Bytes::setBytesZ( char *daten, int l�n )
{
	if( del )
	    delete[] bytes;
	del = 0;
	bytes = daten;
	this->l�n = l�n;
}

void Bytes::f�ll( const char c )
{
	if( !bytes )
		return;
	char *end = bytes + l�n;
	for( char *b = bytes; b < end; ++b )
		*b = c;
}

void Bytes::f�ll( const char c, int l�n )
{
	if( !bytes )
		bytes = new char[ l�n ];
	l�n = l�n > this->l�n ? this->l�n : l�n;
	char *end = bytes + l�n;
	for( char *b = bytes; b < end; ++b )
		*b = c;
}

void Bytes::f�ll( const char c, int beg, int end )
{
	if( beg >= l�n )
		return;
	if( !bytes )
		bytes = new char[ end - beg ];
	end = end > this->l�n ? this->l�n : end;
	char *endB = bytes + end;
	for( char *b = bytes + beg; b < endB; ++b )
		*b = c;
}

void Bytes::f�ll( const char *c, int cL�n )
{
	if( !c || !cL�n || !bytes )
		return;
	char *endB = bytes + l�n;
	const char *endC = c + cL�n;
	const char *d = c;
	for( char *b = bytes; b < endB; b++, d = d < endC - 1 ? d + 1 : c )
		*b = *d;
}

void Bytes::set( const char c, int pos )
{
	if( !bytes || pos >= l�n )
		return;
	bytes[ pos ] = c;
}

// constant
int Bytes::getL�nge() const
{
	return l�n;
}

char *Bytes::getBytes() const
{
	return bytes;
}

// Reference Counting
Bytes *Bytes::getThis()
{
	++ref;
	return this;
}

Bytes *Bytes::release()
{
	--ref;
	if( !ref )
		delete this;
	return 0;
}


// Inhalt der Schl�ssel Klasse aus Schl�ssel.h
// Konstruktor
Schl�ssel::Schl�ssel()
	: schl�ssel( 0 ),
	  l�n( 0 ),
	  pos( 0 ),
	  ref( 1 )
{
}

Schl�ssel::Schl�ssel( const char *s, int l�n )
	: schl�ssel( new unsigned char[ l�n ] ),
	  l�n( l�n ),
	  pos( 0 ),
	  ref( 1 )
{
	for( int i = 0; i < l�n; ++i )
		schl�ssel[ i ] = s[ i ];
}

// Destruktor
Schl�ssel::~Schl�ssel()
{
	delete[] schl�ssel;
}

// nicht constant
void Schl�ssel::setPos( int p )
{
	if( p < 0 )
		p = 0;
	pos = p > l�n ? 0 : p;
}

void Schl�ssel::setSchl�ssel( const char *s, int l�n )
{
	delete[] schl�ssel;
	schl�ssel = new unsigned char[ l�n ];
	for( int i = 0; i < l�n; ++i )
		schl�ssel[ i ] = s[ i ];
	pos = 0;
	this->l�n = l�n;
}

void Schl�ssel::codieren( Bytes *daten )
{
	if( !schl�ssel || !l�n )
	{
		daten->release();
		return;
	}
	int dL�n = daten->getL�nge();
	char *bytes = daten->getBytes();
	char *bEnd = bytes + dL�n;
	for( char *c = bytes; c < bEnd; ++c )
	{
		*c = *c + schl�ssel[ pos ];
		++pos;
		if( pos >= l�n )
			pos = 0;
	}
	daten->release();
}

void Schl�ssel::decodieren( Bytes *daten )
{
	if( !schl�ssel || !l�n )
	{
		daten->release();
		return;
	}
	int dL�n = daten->getL�nge();
	char *bytes = daten->getBytes();
	char *bEnd = bytes + dL�n;
	for( char *c = bytes; c < bEnd; ++c )
	{
		*c = *c - schl�ssel[ pos ];
		++pos;
		if( pos >= l�n )
			pos = 0;
	}
	daten->release();
}

// Reference Counting
Schl�ssel *Schl�ssel::getThis()
{
	++ref;
	return this;
}

Schl�ssel *Schl�ssel::release()
{
	--ref;
	if( !ref )
		delete this;
	return 0;
}