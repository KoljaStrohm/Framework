#pragma once

#include "Punkt.h"

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;

namespace Framework
{
    class Bild; // Bild.h
    class Render3D; // Render3D.h
    class TexturList; // TexturList.h

    // Wandelt ein Bild in eine Textur um, die an die Grafikkarte zum rendern �bergeben werden kann
    class Textur
    {
    private:
        Bild *bild;
        ID3D11Texture2D *txt;
        ID3D11ShaderResourceView *view;
        Punkt lastGr;
        int id;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Textur();
        // Destruktor
        __declspec( dllexport ) ~Textur();
        // Setzt einen Zeiger auf das Bild, welches die Textur enth�lt
        //  b: Der Zeiger auf das Bild
        __declspec( dllexport ) void setBildZ( Bild *b );
        // Setzt das Bild welches die Textur enth�lt, indem es kopiert wird
        //  b: Das Bild, was kopiert werden soll
        __declspec( dllexport ) void setBild( Bild *b );
        // Aktualisiert die Textur. Die Pixel des aktuellen Bildes werden in den Graphikspeicher kopiert
        //  zRObj: Das Objekt, mit dem die Graphikkarte angesprochen wird
        __declspec( dllexport ) bool updateTextur( Render3D *zRObj );
        // Gibt true zur�k, wenn updateTextur aufgerufen werden muss
        __declspec( dllexport ) bool brauchtUpdate() const;
        // Gibt einen Zeiger auf das Bild zur�ck
        __declspec( dllexport ) Bild *getBild() const;
        // Gibt einen Zeiger auf das Bild ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Bild *zBild() const;
        // Gibt die Id der Textur zur�ck, wenn sie in einer TexturList registriert wurde. (siehe Framework::zTexturRegister())
        __declspec( dllexport ) int getId() const;
        // Gibt die verwendtete Shader Resource View zur�ck
        __declspec( dllexport ) operator ID3D11ShaderResourceView*() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Textur *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Textur *release();

        friend TexturList;
    };
}