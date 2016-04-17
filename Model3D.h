#pragma once

#include "vec2.h"
#include "Array.h"
#include "Mat4.h"
#include "Zeichnung3D.h"

struct ID3D11Buffer;

namespace Framework
{
    struct Polygon2D; // Model2D.h
    class Textur; // Textur.h
    class Model2DData; // Model2D.h
    class DXIndexBuffer; // DXBuffer.h
    class DXVertexBuffer; // DXBuffer.h
    class Render3D; // Render3D.h
    class Model3DTextur; // Model3D.h
    class Model3DList; // Model3DList.h

    // Repr�sentiert einen Knochen eines 3D Models. Kann annimiert werden
    class Knochen
    {
    private:
        Vec3< float > pos;
        Vec3< float > winkel;
        Knochen *geschwister;
        Knochen *kinder;
        int id;

        // F�gt dem Knochen ein Geschwister Knochen hinzu
        //  k: Der Knochen, der hinzugef�gt werden soll
        void addGeschwisterKnochen( Knochen *k );

    public:
        // Konstruktor
        __declspec( dllexport ) Knochen( int id );
        // Destruktor
        __declspec( dllexport ) ~Knochen();
        // Setzt die Position des Knochens relativ zum Model Ursprung
        //  pos: Die Position
        __declspec( dllexport ) void setPosition( Vec3< float > &pos );
        // Setzt die Drehung des Knochens relativ zum Model Ursprung
        //  winkel: Ein Vektor der die Drehung um die verschiedenen Achsen als Komponenten hat
        __declspec( dllexport ) void setDrehung( Vec3< float > &winkel );
        // F�gt einem bestimmten Knochen ein Kind Knochen hinzu
        //  id: Die id des Knochens, wo der Knochen als Kind hinzugef�gt werden soll
        //  k: Der Knochen, der hinzugef�gt werden soll
        __declspec( dllexport ) void addKind( int id, Knochen *k );
        // Berechnet die Matrizen des Knochen und die von all seinen Geschwister Knochen und Kind Knochen
        //  elternMat: Die fertig berechnete Matrix des Elternknochens
        //  matBuffer: Ein Array, in dem alle berechneten Matrizen gespeichert werden sollen
        //  kamMatrix: Die vereiniegung der view und projektions Matrizen
        __declspec( dllexport ) void kalkulateMatrix( Mat4< float > &elternMat, Mat4< float > *matBuffer, Mat4< float > &kamMat );
        // Kopiert den Knochen mit allen Geschwister Knochen und Kind Knochen
        __declspec( dllexport ) Knochen *kopiereKnochen() const;
        // Gibt die Id des Knochens zur�ck
        __declspec( dllexport ) int getId() const;
    };

    // Repr�sentiert alle Knochen eines Models, mit denen es Annimiert werden kann
    class Skelett
    {
    private:
        Knochen *k;
        int nextId;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Skelett();
        // Destruktor
        __declspec( dllexport ) ~Skelett();
        // Gibt die Id des n�chsten Knochens zur�ck und berechnet die neue Id f�r den Knochen danach
        // Es k�nnen maximal 128 Knochen f�r ein Skelett existieren. Wenn diese Zahl �berschritten wird, so wird -1 zur�ckgegeben
        __declspec( dllexport ) int getNextKnochenId();
        // F�gt dem Skellet einen Knochen hinzu
        //  k: Der Knochen
        //  elternId: Die Id des Eltern Knochens. Wenn der Knochen kein Elternknochen besitzt, kannder Parameter weggelassen werden.
        __declspec( dllexport ) void addKnochen( Knochen *k, int elternId = -1 );
        // Berechnet die Matrizen der Knochen
        //  modelMatrix: Die Matrix, die das Skelett in den Raum der Welt transformiert
        //  matBuffer: Ein Array von Matrizen, der durch die Knochen Matrizen gef�llt wird
        //  return: gibt die Anzahl der verwendeten Matrizen zur�ck
        //  kamMatrix: Die vereiniegung der view und projektions Matrizen
        __declspec( dllexport ) int kalkulateMatrix( Mat4< float > &modelMatrix, Mat4< float > *matBuffer, Mat4< float > &kamMatrix );
        // Kopiert das Skelett
        __declspec( dllexport ) Skelett *kopiereSkelett() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Skelett *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Skelett *release();
    };

    // Eine struktor um f�r eine Ecke eines 3D Models die Raum Position, die Textur Koordinaten und den zugeh�rigen Knochen speichert
    struct Vertex3D
    {
        Vec3< float > pos; // Die Position der Ecke basierend zur Position des Knochens
        Vec2< float > tPos; // Die Textur Koordinaten der Ecke
        int knochenId; // Die Id des Knochens, mit dem sich die Ecke bei einer Annimation mitbewegt
    };

    // Eine Struktur, die alle Dreiecke eines 3D Polygons speichert
    struct Polygon3D
    {
        int *indexList; // Die Liste mit den IDs der Ecken
        int indexAnz; // Die L�nge der Liste mit den Ids der Ecken
        DXIndexBuffer *indexBuffer; // Die DirectX11 Struktur, die die Liste mit IDs der Ecken verwaltet

        // Konstruktor
        __declspec( dllexport ) Polygon3D();
        // Destruktor
        __declspec( dllexport ) ~Polygon3D();
    };

    // Speichert alle Geometrischen Daten eines Modells, also
    // Raum - und Textur Koordinaten und Knochenzugeh�rigkeit aller Eckpunkte
    class Model3DData
    {
    private:
        Skelett *skelett;
        Vertex3D *vertexList;
        DXVertexBuffer *vertexBuffer;
        Array< Polygon3D* > *polygons;
        float radius;
        int id;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Model3DData();
        // Destruktor
        __declspec( dllexport ) ~Model3DData();
        // L�scht alle Model daten
        __declspec( dllexport ) void clearModel();
        // Setzt den Zeiger auf ein standartm��ig verwendete Skelett
        //  s: Das Skelett, das verwendet werden soll
        __declspec( dllexport ) void setSkelettZ( Skelett *s );
        // Setzt einen Zeiger auf eine Liste mit allen Vertecies des Models
        //  vertexList: Ein Array mit Vertecies
        //  anz: Die Anzahl der Vertecies im Array
        __declspec( dllexport ) void setVertecies( Vertex3D *vertexList, int anz );
        // F�gt ein Polygon zum Model hinzu
        //  polygon: Das Polygon, das hinzugef�gt erden soll
        __declspec( dllexport ) void addPolygon( Polygon3D *polygon );
        // Konvertiert ein 2d Model zu 3D
        //  model: Das 2d Model, das zu 3d konvertiert werden soll
        //  z: Die z koordinate aller punkte des Models
        __declspec( dllexport ) void copyModel2D( Model2DData *model, float z );
        // Entfernt ein Polygon
        //  index: Der Index des Polygons
        __declspec( dllexport ) void removePolygon( int index );
        // Aktualisiert die Vertecies
        __declspec( dllexport ) void aktualisiereVertecies( Render3D *zRObj );
        // Berechnet die Matrizen der Knochen des Standart Skeletts
        //  modelMatrix: Die Matrix, die das Skelett in den Raum der Welt transformiert
        //  matBuffer: Ein Array von Matrizen, der durch die Knochen Matrizen gef�llt wird
        //  return: gibt die Anzahl der verwendeten Matrizen zur�ck. 0, falls kein Standart Skelett gesetzt wurde
        //  kamMatrix: Die vereiniegung der view und projektions Matrizen
        int kalkulateMatrix( Mat4< float > &modelMatrix, Mat4< float > *matBuffer, Mat4< float > &kamMatrix ) const;
        // Zeichnet alle Polygons
        //  world: Die Welt Matrix, die das Model in die Welt transformiert
        //  zTxt: Eine Liste mit Texturen der einzelnen Polygone
        //  zRObj: Das Objekt, mit dem gezeichnet werden soll
        __declspec( dllexport ) void render( Mat4< float > &welt, const Model3DTextur *zTxt, Render3D *zRObj );
        // Gibt die Anzahl an Polygonen zur�ck
        __declspec( dllexport ) int getPolygonAnzahl() const;
        // Gibt ein bestimmtes Polygon zur�ck
        //  index: Der Index des Polygons
        __declspec( dllexport ) Polygon3D *getPolygon( int index ) const;
        // Gibt den radius einer Kugel zur�ck, die das gesammte Model umschlie�t
        __declspec( dllexport ) float getRadius() const;
        // Gibt die Id der Daten zur�ck, wenn sie in einer Model3DList registriert wurden. (siehe Framework::zM3DRegister())
        __declspec( dllexport ) int getId() const;
        // Gibt einen Buffer mit allen Vertecies des Models zur�ck
        __declspec( dllexport ) const DXVertexBuffer *zVertexBuffer() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Model3DData *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Model3DData *release();

        friend Model3DList;
    };

    // Speichert eine Liste mit Texturen und f�r welche Polygone welche Textur benutzt werden soll
    class Model3DTextur
    {
    private:
        RCArray< Textur > *textures;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Model3DTextur();
        // Destruktor
        __declspec( dllexport ) ~Model3DTextur();
        // Legt fest, welche Textur f�r welches Polygon ist
        //  pI: Der Index des Polygons
        //  txt: Die Textur des Polygons
        __declspec( dllexport ) void setPolygonTextur( int pI, Textur *txt );
        // Gibt einen Zeiger auf die Textur eines Polygons zur�ck ohne erh�hten Reference Counter
        //  i: Der Index des Polygons
        __declspec( dllexport ) Textur *zPolygonTextur( int i ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Model3DTextur *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) Model3DTextur *release();
    };

    // Eine Zeichnung des 3D Frameworks, die ein 3D Model mit Textur und Animation darstellen kann
    class Model3D : public Zeichnung3D
    {
    protected:
        Model3DData *model;
        Skelett *skelett;
        Model3DTextur *textur;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) Model3D();
        // Destruktor
        __declspec( dllexport ) ~Model3D();
        // Setzt den Zeiger auf das zum Annimieren verwendete Skelett
        //  s: Das Skelett, das verwendet werden soll
        __declspec( dllexport ) void setSkelettZ( Skelett *s );
        // Setzt die Daten des Models
        //  data: Die Daten
        __declspec( dllexport ) void setModelDaten( Model3DData *data );
        // Setzt die zum Zeichnen zu benutzenden Texturen
        //  txt: Ein Liste mit Texturen zu den verschiedenen Polygonen zugeordnet
        __declspec( dllexport ) void setModelTextur( Model3DTextur *txt );
        // Errechnet die Matrizen aller Knochen des Skeletts des Models
        //  viewProj: Die miteinander multiplizierten Kameramatrizen
        //  matBuffer: Ein Array mit Matrizen, der gef�llt werden soll
        //  return: Die Anzahl der Matrizen, die das Model ben�tigt
        __declspec( dllexport ) int errechneMatrizen( Mat4< float > &viewProj, Mat4< float > *matBuffer ) override;
        // Verarbeitet die vergangene Zeit
        //  tickval: Die zeit in sekunden, die seit dem letzten Aufruf der Funktion vergangen ist
        //  return: true, wenn sich das Objekt ver�ndert hat, false sonnst.
        __declspec( dllexport ) virtual bool tick( double tickval ) override;
        // Zeichnet das Model
        //  zRObj: Ein Zeiger auf das Objekt, das zum Zeichnen verwendet werden soll (ohne erh�hten Reference Counter)
        __declspec( dllexport ) void render( Render3D *zRObj ) override;
        // Gibt die Id der Daten zur�ck, wenn sie in einer Model3DList registriert wurden. (siehe Framework::zM3DRegister())
        __declspec( dllexport ) int getDatenId() const;
        // Gibt einen Buffer mit allen Vertecies des Models zur�ck
        __declspec( dllexport ) const DXVertexBuffer *zVertexBuffer() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) Model3D *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) virtual Model3D *release();
    };
}