#pragma once

#include "Betriebssystem.h"

struct ID3D11Buffer;
enum D3D11_BIND_FLAG;

namespace Framework
{
    class Render3D;

    // Eine Schnittstelle zwischen dem Arbeitsspeicher und dem Grafikspeicher
    class DXBuffer
    {
    private:
        ID3D11Buffer *buffer;
        D3D11_BIND_FLAG bf;
        void *data;
        bool ge�ndert;
        int l�n;
        int altL�n;
        int elL�n;

    protected:
        int ref;

    public:
        // Konstruktor
        //  bind: Der verwendungszweck des Buffers. Beispiel: D3D11_BIND_INDEX_BUFFER, D3D11_BIND_VERTEX_BUFFER.
        //  eL�n: L�nge eines einzelnen Elements in Bytes
        __declspec( dllexport ) DXBuffer( D3D11_BIND_FLAG bind, int eL�n );
        // Destruktor
        __declspec( dllexport ) ~DXBuffer();
        // Setzt den ge�ndert fl�g, so das beim n�chsten auruf von 'kopieren' die daten neu kopiert werden
        __declspec( dllexport ) void setGe�ndert();
        // �ndert die l�nge des Buffers beim n�chsten aufruf von 'kopieren'
        //  l�n: Die L�nge in Bytes
        __declspec( dllexport ) void setL�nge( int l�n );
        // Legt fest, was beim n�chsten aufruf von 'kopieren' kopiert wird
        //  data: Ein zeiger auf die Daten
        __declspec( dllexport ) void setData( void *data );
        // Kopiert die Daten in den Buffer, fals sie sich ver�ndert haben
        //  zRObj: Das Objekt, mit dem die Grafikkarte angesprochen wird
        __declspec( dllexport ) void copieren( Render3D *zRObj );
        // Gibt die L�nge eines Elementes in bytes zur�ck
        __declspec( dllexport ) int getElementL�nge() const;
        // Gibt den Buffer zur�ck
        __declspec( dllexport ) ID3D11Buffer *zBuffer() const;
        // Gibt die Anzahl der Elemente im Buffer zur�ck
        __declspec( dllexport ) int getElementAnzahl() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) DXBuffer *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) virtual DXBuffer *release();
    };

    // Ein Buffer von Eckpunkten eines 3D Models
    class DXVertexBuffer : public DXBuffer
    {
    public:
        // Konstruktor
        // eSize: Die L�nge eines Elementes in Bytes
        __declspec( dllexport ) DXVertexBuffer( int eSize );
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) virtual DXBuffer *release();
    };

    // Ein Buffer von Indizes aus dem Buffer mit Eckpunkten, wovon immer drei ein Dreieck ergeben, das gezeichnet wird
    class DXIndexBuffer : public DXBuffer
    {
    public:
        // Konstruktor
        // eSize: Die L�nge eines Elementes in Bytes
        __declspec( dllexport ) DXIndexBuffer( int eSize );
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) virtual DXBuffer *release();
    };
}