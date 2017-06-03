#pragma once

#include "Array.h"
#include "Critical.h"

namespace Framework
{
    class Model3DData; // Model3D.h
    class Text; // Text.h
    class Model3D; // Model3D.h

    namespace Standart3DTypes
    {
        extern const char *cube; // = "f_w�rfel"; Die Modeldaten eines W�rfels der 100 * 100 * 100 gro� ist
    };

    // Verwaltet alle geladenen Modeldaten, so dass mehrere Zeichnungen die selben Daten benutzen k�nnen
    class Model3DList
    {
    private:
        static int id;
        static Critical cs;
        RCArray< Model3DData > *models;
        RCArray< Text > *names;
        int ref;

    public:
        // Konstruktor
        Model3DList();
        // Destruktor
        ~Model3DList();
        // F�gt der Liste ein Model Hinzu
        //  mdl: Das Model
        //  name: Der name, unter dem das Model in der Liste gespeichert wird
        bool addModel( Model3DData *mdl, const char *name );
        // Entfernt ein Model aus der Liste
        //  name: Der Name des Models
        void removeModel( const char *name );
        // �berpr�ft, ob unter einem bestimmten Namen ein Model abgespeichert wurde
        //  name: Der Name
        //  return: true, wenn ein Model mit dem Namen existiert
        bool hatModel( const char *name ) const;
        // Gibt ein bestimmtes Model zur�ck
        //  name: Der Name des Models
        Model3DData *getModel( const char *name ) const;
        // Gibt ein bestimmtes Model ohne erh�hten Reference Counter zur�ck
        //  name: Der Name des Models
        Model3DData *zModel( const char *name ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        Model3DList *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        Model3DList *release();
        // Initialisiert statische private member. Wird vom Framework automatisch aufgerufen.
        static void init();
        // L�scht statische private member. Wird vom Framework automatisch aufgerufen.
        static void destroy();
    };
}