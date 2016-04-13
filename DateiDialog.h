#ifndef DateiDialog_H
#define DateiDialog_H

#include "Array.h"
#include "Thread.h"

namespace Framework
{
    class Text; // Text.h

    void InitDialog();

    // Erstellt einen Datei �ffnen/speichern Dialog
    class DateiDialog
    {
    private:
        RCArray< Text > *typeName;
        RCArray< Text > *type;
        int fileIndex;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) DateiDialog();
        // Destruktor
        __declspec( dllexport ) ~DateiDialog();
        // L�scht die Liste mit zugelassenen Dateitypen
        __declspec( dllexport ) void l�scheDateiTypen();
        // F�gt einen zugelassenen Dateityp hinzu
        //  name: Der Name des Dateitypes. Ist f�r den Nutzer in der Select Box sichtbar
        //  typ: Der Dateityp, der ausgew�hlt werden darf
        __declspec( dllexport ) void addDateiTyp( char *name, char *typ );
        // F�gt einen zugelassenen Dateityp hinzu
        //  name: Der Name des Dateitypes. Ist f�r den Nutzer in der Select Box sichtbar
        //  typ: Der Dateityp, der ausgew�hlt werden darf
        __declspec( dllexport ) void addDateiTyp( Text *name, Text *typ );
        // Setzt den zu Beginn ausgew�hlten Dateityp
        //  i: Der Index des Dateityps. Der, der als erstes hinzugef�gt wurde, hat den Index 0.
        __declspec( dllexport ) void setDateiTypAuswahl( int i );
        // Zeigt den Dateidialog an
        //  open: true, wenn der Dialog zum �ffnen dienen soll. false zum Speichern
        //  return: Den Pfad zur ausgew�hlten Datei
        __declspec( dllexport ) Text *anzeigen( bool open ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) DateiDialog *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) DateiDialog *release();
    };

    // Verwaltet einen Datei �ffnen/speichern Dialog ohne zu warten
    class DateiDialogTh : public Thread
    {
    private:
        DateiDialog *dialog;
        Text *ret;
        bool �ffnen;
        int ref;

    public:
        // Konstruktor
        __declspec( dllexport ) DateiDialogTh();
        // Destruktor
        __declspec( dllexport ) ~DateiDialogTh();
        // Legt fest, ob der Dialog zum �ffnen oder speichern ist
        //  b: 1, wenn er zum �fnen ist. 0, wenn er zum speichern ist
        __declspec( dllexport ) void set�ffnen( bool b );
        // L�scht die liste mit erlaubten Dateitypen
        __declspec( dllexport ) void l�scheDateiTypen();
        // F�gt einen zugelassenen Dateityp hinzu
        //  name: Der Name des Dateitypes. Ist f�r den Nutzer in der Select Box sichtbar
        //  typ: Der Dateityp, der ausgew�hlt werden darf
        __declspec( dllexport ) void addDateiTyp( char *name, char *typ );
        // F�gt einen zugelassenen Dateityp hinzu
        //  name: Der Name des Dateitypes. Ist f�r den Nutzer in der Select Box sichtbar
        //  typ: Der Dateityp, der ausgew�hlt werden darf
        __declspec( dllexport ) void addDateiTyp( Text *name, Text *typ );
        // Setzt den zu Beginn ausgew�hlten Dateityp
        //  i: Der Index des Dateityps. Der, der als erstes hinzugef�gt wurde, hat den Index 0.
        __declspec( dllexport ) void setDateiTypAuswahl( int i );
        // Diese Funktion wird von der Klasse selbst aufgerufen.
        // Benutze die start Funktion um den Dialog anzuzeigen
        __declspec( dllexport ) void thread() override;
        // Gibt den Pfad zur Datei zur�ck.
        // Funktioniert erst, nachdem der Thread beendet wurde
        __declspec( dllexport ) Text *getPfad() const;
        // Gibt den Pfad zur Datei ohne erh�hten Reference Counter zur�ck.
        // Funktioniert erst, nachdem der Thread beendet wurde
        __declspec( dllexport ) Text *zPfad() const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) DateiDialogTh *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) DateiDialogTh *release();
    };
};

#endif