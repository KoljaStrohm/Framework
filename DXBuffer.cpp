#include "DXBuffer.h"
#include "Render3D.h"
#include <iostream>
#include <d3d11.h>

using namespace Framework;

// Inhalt der DXBuffer Klasse

// Konstruktor
//  bind: Der verwendungszweck des Buffers. Beispiel: D3D11_BIND_INDEX_BUFFER, D3D11_BIND_VERTEX_BUFFER.
//  eL�n: L�nge eines einzelnen Elements in Bytes
DXBuffer::DXBuffer( D3D11_BIND_FLAG bind, int eL�n )
{
    buffer = 0;
    bf = bind;
    data = 0;
    ge�ndert = 0;
    l�n = 0;
    altL�n = 0;
    elL�n = eL�n;
    ref = 1;
}

// Destruktor
DXBuffer::~DXBuffer()
{
    if( buffer )
        buffer->Release();
}

// Setzt den ge�ndert fl�g, so das beim n�chsten auruf von 'kopieren' die daten neu kopiert werden
void DXBuffer::setGe�ndert()
{
    ge�ndert = 1;
}

// �ndert die l�nge des Buffers beim n�chsten aufruf von 'kopieren'
//  l�n: Die L�nge in Bytes
void DXBuffer::setL�nge( int l�n )
{
    this->l�n = l�n;
    ge�ndert = 1;
}

// Legt fest, was beim n�chsten aufruf von 'kopieren' kopiert wird
//  data: Ein zeiger auf die Daten
void DXBuffer::setData( void *data )
{
    this->data = data;
    ge�ndert = 1;
}

// Kopiert die Daten in den Buffer, fals sie sich ver�ndert haben
//  zRObj: Das Objekt, mit dem die Grafikkarte angesprochen wird
void DXBuffer::copieren( Render3D *zRObj )
{
    if( !ge�ndert || !l�n || !data )
        return;
    if( l�n != altL�n )
    {
        if( buffer )
            buffer->Release();
        buffer = 0;
    }
    if( !buffer )
    {
        D3D11_BUFFER_DESC desk;
        memset( &desk, 0, sizeof( desk ) );
        desk.Usage = D3D11_USAGE_DYNAMIC;
        desk.ByteWidth = l�n;
        desk.BindFlags = bf;
        desk.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        D3D11_SUBRESOURCE_DATA ini;
        memset( &ini, 0, sizeof( ini ) );
        ini.pSysMem = data;

        zRObj->zDevice()->CreateBuffer( &desk, &ini, &buffer );
        altL�n = l�n;
    }
    else if( ge�ndert )
    {
        D3D11_MAPPED_SUBRESOURCE map;
        zRObj->zContext()->Map( buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &map );
        memcpy( map.pData, data, l�n );
        zRObj->zContext()->Unmap( buffer, 0 );
        ge�ndert = 0;
    }
}

// Gibt die L�nge eines Elementes in bytes zur�ck
int DXBuffer::getElementL�nge() const
{
    return elL�n;
}

// Gibt den Buffer zur�ck
ID3D11Buffer *DXBuffer::zBuffer() const
{
    return buffer;
}

// Gibt die Anzahl der Elemente im Buffer zur�ck
int DXBuffer::getElementAnzahl() const
{
    return altL�n / elL�n;
}

// Erh�ht den Reference Counting Z�hler.
//  return: this.
DXBuffer *DXBuffer::getThis()
{
    ref++;
    return this;
}

// Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
//  return: 0.
DXBuffer *DXBuffer::release()
{
    ref--;
    if( !ref )
        delete this;
    return 0;
}


// Inhalt der DXVertexBuffer Klasse

// Konstruktor
// eSize: Die L�nge eines Elementes in Bytes
DXVertexBuffer::DXVertexBuffer( int eSize )
    : DXBuffer( D3D11_BIND_VERTEX_BUFFER, eSize )
{}

// Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
//  return: 0.
DXBuffer *DXVertexBuffer::release()
{
    ref--;
    if( !ref )
        delete this;
    return 0;
}


// Inhalt der DXIndexBuffer Klasse

// Konstruktor
// eSize: Die L�nge eines Elementes in Bytes
DXIndexBuffer::DXIndexBuffer( int eSize )
    : DXBuffer( D3D11_BIND_INDEX_BUFFER, eSize )
{}

// Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
//  return: 0.
DXBuffer *DXIndexBuffer::release()
{
    ref--;
    if( !ref )
        delete this;
    return 0;
}