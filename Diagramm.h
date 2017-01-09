#ifndef Diagramm_H
#define Diagramm_H

#include "Zeichnung.h"
#include "Array.h"

namespace Framework
{
    class LRahmen; // Rahmen.h
    class AlphaFeld; // AlphaFeld.h
    class Text; // Text.h
    class Schrift; // Schrift.h
    class HScrollBar; // Scroll.h
    class VScrollBar; // Scroll.h
    class SLDiag; // aus dieser Datei
    class LDiag; // aus dieser Datei

    // Eine Zeichnung de 2D GUI Frameworks, die ein live Diagramm von werten zeichnet
    class SLDiag : public ZeichnungHintergrund
    {
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 Gitter = 0x01000; // Es wird ein Gitter im Diagramm zur Orientierung gezeichnet
            const static __int64 LinienName = 0x02000; // Es werden die Namen der Graphen angezeigt

            const static __int64 normal = Sichtbar | Hintergrund | Rahmen | Gitter | LinienName; // Vereinigung der Flags Sichtbar, Hintergrund, Rahmen, Gitter, LinienName
        };
    private:
        int gF;
        Array< int > *lFarbe;
        RCArray< Text > *lName;
        RCArray< Array< int > > *ph;
        RCArray< Array< int > > *pb;
        Array< int > *lastValue;
        Schrift *schrift;
        Punkt gitterGr;
        int lines;
        int ref;

    public:
        // Konstruktor 
        __declspec( dllexport ) SLDiag();
        // Destruktor 
        __declspec( dllexport ) virtual ~SLDiag();
        // Setzt einen Zeiger zur verwendeten Schrift
        //  schrift: Die Schrift
        __declspec( dllexport ) void setSchriftZ( Schrift *schrift );
        // Setzt die Abst�nde zwischen den Linien des Gitters
        //  gr: F�r x den Abstand zwischen jeder vertikalen Linie in Pixeln und f�r y den Abstand zwischen jeder Horizontalen Linie in den dargestellen y Werten
        __declspec( dllexport ) void setGSize( Punkt &gr );
        // Setzt die Farbe der Raster Linien
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setGFarbe( int f );
        // F�gt dem Diagramm einen neuen Graphen hinzu
        //  name: Der Name des Graphen. Er wird bei dem Flag LinienName im Diagramm angezeigt
        __declspec( dllexport ) void addLinie( const char *name );
        // F�gt dem Diagramm einen neuen Graphen hinzu
        //  name: Der Name des Graphen. Er wird bei dem Flag LinienName im Diagramm angezeigt
        __declspec( dllexport ) void addLinie( Text *txt );
        // Setzt die Farbe eines Graphen
        //  lNum: Der Index des Graphen
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setLFarbe( int lNum, int f );
        // F�gt einem Graphen einen Punkt hinzu. Hierdurch verschieben sich alle Punkte des Graphen so weit nach Links, dass der neue Punkt rechts auftaucht. Geht ein Punkt links aus dem Diagramm raus, wird er gel�scht.
        // Auf diese Weise erscheint das Diagramm wie eine Abbildung einer Live Messung
        //  x: Der Abstand zum Letzten Punkt in Pixeln
        //  y: Den Wert der abgebildeten Funktion in dem Punkt
        __declspec( dllexport ) void addPunkt( int lNum, int x, int h );
        // Entfernt einen Graphen
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) void removeLinie( int lNum );
        // Zeichnet das Diagramm
        //  zRObj: Das Bild, in das gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt die verwendete Schrift zur�ck
        __declspec( dllexport ) Schrift *getSchrift() const;
        // Gibt die verwendete Schrift ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Schrift *zSchrift() const;
        // Gibt die Gr��e eines Quadrats des Gitters zur�ck, wobei die Braite in Pixeln und die H�he in Werten der y Achse ist
        __declspec( dllexport ) const Punkt &getGSize() const;
        // Gibt die Farbe des Gitters in A8R8G8B8 Format zur�ck
        __declspec( dllexport ) int getGFarbe() const;
        // Gibt den Index eines Graphen zur�ck
        //  name: Der Name des Graphen
        __declspec( dllexport ) int getLinienNummer( const char *name ) const;
        // Gibt den Index eines Graphen zur�ck
        //  name: Der Name des Graphen
        __declspec( dllexport ) int getLinienNummer( Text *name ) const;
        // Gibt den Namen eines Graphen zur�ck
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) Text *getLinienName( int lNum ) const;
        // Gibt den Namen eines Graphen ohne erh�hten Reference Counter zur�ck
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) Text *zLinienNamen( int lNum ) const;
        // Gibt den H�chsten y Wert von allen Graphen zur�ck
        __declspec( dllexport ) int getHighestValue() const;
        // Gibt den H�chsten y Wert von einem Bestimmten Graphen zur�ck
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) int getHighestValue( int lNum ) const;
        // Gibt den Durchschnittswert aller im Diagramm gespeicherten Punkten eines Graphen zur�ck
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) int getMedian( int lNum ) const;
        // Gibt die Anzahl an Graphen zur�ck
        __declspec( dllexport ) int getLAnzahl() const;
        // Gibt den y Wert des letzten Punktes eines Graphen zur�ck
        //  lNum: Der Index des Graphen
        __declspec( dllexport ) int getLastValue( int lNum ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) SLDiag *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) SLDiag *release();
    };

    // Punkt eines Wertes eines Diagramms
    struct DiagPunkt
    {
        // Position des Punktes auf dem Horizontalen Intervall des Diagramms
        double hIntervall;
        // Position des punktes auf dem Vertikalen Intervall des Diagramms
        double vIntervall;
    };

    // Wert der in einem Diagramm visualisiert wird
    struct DiagWert
    {
        // Style eines Diagramm Wertes
        class Style
        {
        public:
            const static int Sichtbar = 0x01; // Legt fest, ob der Wert angezeigt werden soll
            const static int Alpha = 0x02; // Legt fest, ob beim zeichnen des Wertes Alphablending verwendet werden soll
            const static int Hintergrund = 0x04; // Legt fest, ob der Wert einen Hintergrund hat
            const static int HAlpha = 0x08; // Legt fest, ob beim zeichnen des Hintergrundes Alphablending verwendet werden soll
            const static int Name = 0x10; // Legt fest, ob der Name des Wertes gezeichnet werden soll
        };
        // Style des Wertes
        int style;
        // Farbe des Wertes
        int farbe;
        // Hintergrundfarbe des Wertes
        int hintergrund;
        // Name des Wertes
        Text *name;
        // Punkte des Wertes
        Array< DiagPunkt* > *punkte;

        // Konstruktor
        __declspec( dllexport ) DiagWert();
        // Destruktor
        __declspec( dllexport ) ~DiagWert();
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) DiagWert *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) DiagWert *release();

    private:
        // Reference Counting
        int ref;
    };

    // Daten f�r ein Diagramm
    struct DiagDaten
    {
        class Style
        {
        public:
            const static int Sichtbar = 0x0001; // Legt Fest, ob die Daten sichtbar sein sollen
            const static int Raster = 0x0002; // Legt fest, ob ein Raster zur Orientierung angezeigt werden soll
            const static int RasterAlpha = 0x0004; // Legt fest, ob zum Zeichnen des Rasters Alphablending verwendet werden soll
            const static int AutoIntervallHeight = 0x0008; // Legt fest, dass alle Werte automatisch so auf der y Achse Skalliert werden, dass immer die komplette H�he des Diagramms genutzt wird
            const static int AutoIntervallBreite = 0x0010; // Legt fest, dass alle Wert automatisch so auf der x Achse Skalliert werden, dass immer die komplette Breite des Diagramms genutzt wird
            const static int HIntervall = 0x0020; // Legt fest, ob die X Achse gezeichnet werden soll
            const static int VIntervall = 0x0040; // Legt fest, ob die Y Achse gezeichnet werden soll
            const static int HIntervallTexte = 0x0200; // Legt fest, ob spezielle Texte f�r die Werte der X Achse gezeichnet werden sollen
            const static int VIntervallTexte = 0x0400; // Left fest, ob spezielle Texte f�r die Werte der Y Achse gezeichnet werden sollen
            const static int AutoRasterBreite = 0x0800; // Legt fest, ob der Abstand zwischen den Vertikalen Linien des Rasters automatisch gew�hlt werden soll
            const static int AutoRasterHeight = 0x1000; // Legt fest, ob der Abstand zwischen den Horizontalen Rasterlinien automatisch gew�hlt werden soll

            const static int intervalle = HIntervall | VIntervall; // Vereiniegt die Flags HIntervall, VIntervall
            const static int intervallTexte = HIntervallTexte | VIntervallTexte; // Vereint die Flags HIntervallTexte, VIntervallTexte
            const static int autoRaster = AutoRasterHeight | AutoRasterBreite | Raster; // Vereint die Flags AutoRasterH�he, AutoRasterBreite, Raster
            const static int autoIntervall = AutoIntervallHeight | AutoIntervallBreite; // Vereint die Flags AutoIntervallH�he, AutoIntervallBreite
        };
        // Style eines Diagramms
        int style;
        // Breite einer Rasterlinie
        int rasterDicke;
        // Breite eines Rasterk�stchens
        double rasterBreite;
        // H�he eines Rasterk�stchens
        double rasterHeight;
        // Farbe des Rasters
        int rasterFarbe;
        // Schriftfarbe des Horizontalen Intervalls
        int hIntervallFarbe;
        // Schriftfarbe des Vertikalen Intervalls
        int vIntervallFarbe;
        // Name des Horizontalen Intervalls
        Text *hIntervallName;
        // Name des Vertikalen Intervalls
        Text *vIntervallName;
        // Anzeigen des Horizontalen Intervalls
        RCArray< Text > *hIntervallTexte;
        // Anzeigen des Vertikalen Intervalls
        RCArray< Text > *vIntervallTexte;
        // einzelne Horizontale Intervalle
        Array< double > *hIntervallWerte;
        // einzelne Vertikale Intervalle
        Array< double > *vIntervallWerte;
        // Breite des Wertes 1 in Pixeln bei dem horizontalen Intervall ( wird durch das setzen von AutoIntervallBreite �berschrieben )
        double hIntervallBreite;
        // H�he des Wertes 1 in Pixeln bei dem vertikalen Intervall ( wird durch das setzen von AutoIntervallH�he �berschrieben )
        double vIntervallHeight;
        // Werte, die in dem Diagramm visualisiert werden
        RCArray< DiagWert > *werte;

        // Konstruktor
        __declspec( dllexport ) DiagDaten();
        // Destruktor
        __declspec( dllexport ) ~DiagDaten();
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) DiagDaten *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) DiagDaten *release();

    private:
        // Reference Counting
        int ref;
    };

    // Basisklasse der verschiedenen Diagramm Arten
    class BaseDiag
    {
    protected:
        DiagDaten *daten;
        bool changed;
        CRITICAL_SECTION *lock;
        int ref;

    public:
        // Konstruktor
        //  lock: Ein Zeiger zur CRITICAL_SECTION, mit der die Diagramm Klasse, die von dieser Klasse erbt Multithread sicher gemacht wird
        __declspec( dllexport ) BaseDiag( CRITICAL_SECTION *lock );
        // Destruktor
        __declspec( dllexport ) virtual ~BaseDiag();
        // Setzt einen Zeiger auf die Daten des Diagramms
        //  dd: Die Daten
        __declspec( dllexport ) void setDiagDatenZ( DiagDaten *dd );
        // Kopiert die Daten eines Diagramms
        //  dd: Die Daten
        __declspec( dllexport ) void setDiagDaten( DiagDaten *dd );
        // Rasterdicke setzen
        //  d: Die Breite einer Rasterlinie in Pixeln
        __declspec( dllexport ) void setRasterDicke( int d );
        // Rasterbreite setzen
        //  br: Der Abstand zwischen zwei Vertikalen Rasterlinien in Pixeln
        __declspec( dllexport ) void setRasterBreite( int br );
        // Rasterh�he setzen
        //  hi: Der Abstand zwischen zwei Horizontalen Rasterlinien in Pixeln
        __declspec( dllexport ) void setRasterHeight( int hi );
        // Rasterfarbe setzen
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setRasterFarbe( int f );
        // Setzt die Intervall Breite
        //  br: Der Abstand zwischen den Werten 0 und 1 auf der X Achse in Pixeln
        __declspec( dllexport ) void setHIntervallBreite( double br );
        // Setzt die Intervall H�he
        //  hi: Der Abstand zwischen den Werten 0 und 1 auf der Y Achse in Pixeln
        __declspec( dllexport ) void setVIntervallHeight( double hi );
        // Setzt die Farbe der X Achse
        //  f: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setHIntervallFarbe( int f );
        // Setzt die Farbe der Y Achse
        //  f: Die Farbe im A8R8G8B8 Formats
        __declspec( dllexport ) void setVIntervallFarbe( int f );
        // Setzt den Namen der X Achse
        //  name: Der Name
        __declspec( dllexport ) void setHIntervallName( char *name );
        // Setzt den Namen der X Achse
        //  name: Der Name
        __declspec( dllexport ) void setHIntervallName( Text *name );
        // Setzt den Namen der Y Achse
        //  name: Der Name
        __declspec( dllexport ) void setVIntervallName( char *name );
        // Setzt den Namen der Y Achse
        //  name: Der Name
        __declspec( dllexport ) void setVIntervallName( Text *name );
        // Beschriftet einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void addHIntervallText( double hIntervall, char *text );
        // Beschriftet einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void addHIntervallText( double hIntervall, Text *text );
        // setzt den Zeiger auf eine Beschriftung in einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setHIntervallTextZ( double hIntervall, Text *text );
        // �ndert eine Beschriftung in einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setHIntervallText( double hIntervall, Text *text );
        // �ndert eine Beschriftung in einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setHIntervallText( double hIntervall, char *text );
        // Entfernt eine Beschriftung in einen Betimmten Wert der X Achse, falls der Flag HIntervallTexte in den DiagDaten gesetzt wurde
        //  hIntervall: Der Wert, der nicht mehr beschriftet sein soll
        __declspec( dllexport ) void removeHIntervallText( double hIntervall );
        // Beschriftet einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void addVIntervallText( double vIntervall, char *text );
        // Beschriftet einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void addVIntervallText( double vIntervall, Text *text );
        // setzt den Zeiger auf eine Beschriftung in einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setVIntervallTextZ( double vIntervall, Text *text );
        // �ndert eine Beschriftung in einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setVIntervallText( double vIntervall, Text *text );
        // �ndert eine Beschriftung in einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der beschriftet werden soll
        //  text: Die Beschriftung
        __declspec( dllexport ) void setVIntervallText( double vIntervall, char *text );
        // Entfernt eine Beschriftung in einen Betimmten Wert der Y Achse, falls der Flag VIntervallTexte in den DiagDaten gesetzt wurde
        //  vIntervall: Der Wert, der nicht mehr beschriftet sein soll
        __declspec( dllexport ) void removeVIntervallText( double vIntervall );
        // F�gt einen im Diagramm dargestellten Wert (Graph) hinzu
        //  w: Der neue Wert
        __declspec( dllexport ) void addWertZ( DiagWert *w );
        // F�gt einen im Diagramm dargestellten Wert (Graph) hinzu, indem ein anderer Kopiert wird
        //  w: Der Wert, der Kopiert werden soll
        __declspec( dllexport ) void addWert( DiagWert *w );
        // F�gt einen im Diagramm dargestellten Wert (Graph) hinzu
        //  name: Der Name des Wertes
        __declspec( dllexport ) void addWert( const char *name );
        // F�gt einen im Diagramm dargestellten Wert (Graph) hinzu
        //  name: Der Name des Wertes
        __declspec( dllexport ) void addWert( Text *txt );
        // setzt die Farbe eines Wertes
        //  wNum: Der Index des Wertes
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setWertFarbe( int wNum, int fc );
        // f�gt einem Wert einen Punkt hinzu
        //  wNum: Der Index des Wertes
        //  p: Der neue Punkt
        __declspec( dllexport ) void addPunktZ( int wNum, DiagPunkt *p );
        // f�gt einem Wert einen Punkt hinzu, indem ein Punkt kopiert wird
        //  wNum: Der Index des Wertes
        //  p: Der Punkt, der kopiert werden soll
        __declspec( dllexport ) void addPunkt( int wNum, DiagPunkt *p );
        // F�gt einem Wert einen Punkt hinzu
        //  wNum: Der Index des Wertes
        //  hI: Der Wert des Punktes auf der X Achse
        //  vI: Der Wert des Punktes auf der Y Achse
        __declspec( dllexport ) void addPunkt( int wNum, double hI, double vI );
        // Setzt einen Zeiger auf einen vorhandenen Punkt eines Wertes
        //  wNum: Der Index des Wertes
        //  hI: Der Wert des Punktes auf der X Achse, der ersetzt werden soll
        //  p: Der neue Punkt
        __declspec( dllexport ) void setPunktZ( int wNum, double hI, DiagPunkt *p );
        // Setzt einen vorhandenen Punkt eines Wertes, indem ein Punkt kopiert wird
        //  wNum: Der Index des Wertes
        //  hI: Der Wert des Punktes auf der X Achse, der ersetzt werden soll
        //  p: Der neue Punkt
        __declspec( dllexport ) void setPunkt( int wNum, double hI, DiagPunkt *p );
        // Setzt einen vorhandenen Punkt eines Wertes
        //  wNum: Der Index des Wertes
        //  hI: Der Wert des Punktes auf der X Achse, der ersetzt werden soll
        //  h: Der Wert auf der X Achse des neuen Punktes
        //  v: Der Wert auf der Y Achse des neuen Punktes
        __declspec( dllexport ) void setPunkt( int wNum, double hI, double h, double v );
        // Setzt einen Zeiger auf einen vorhandenen Punkt eines Wertes
        //  wNum: Der Index des Wertes
        //  pNum: Der Index des Punktes im Wert
        //  p: Der neue Punkt
        __declspec( dllexport ) void setPunktZ( int wNum, int pNum, DiagPunkt *p );
        // Setzt einen vorhandenen Punkt eines Wertes, indem ein Punkt kopiert wird
        //  wNum: Der Index des Wertes
        //  pNum: Der Index des Punktes im Wert
        //  p: Der neue Punkt
        __declspec( dllexport ) void setPunkt( int wNum, int pNum, DiagPunkt *p );
        // Setzt einen vorhandenen Punkt eines Wertes
        //  wNum: Der Index des Wertes
        //  pNum: Der Index des Punktes im Wert
        //  h: Der Wert auf der X Achse des neuen Punktes
        //  v: Der Wert auf der Y Achse des neuen Punktes
        __declspec( dllexport ) void setPunkt( int wNum, int pNum, double h, double v );
        // L�scht einen vorhandenen Punkt
        //  wNum: Der Index des Wertes
        //  hI: Der Wert auf der X Achse des Punktes, der gel�scht werden soll
        __declspec( dllexport ) void removePunkt( int wNum, double hI );
        // L�scht einen vorhandenen Punkt
        //  wNum: Der Index des Wertes
        //  pNum: Der Index des Punktes im Wert
        __declspec( dllexport ) void removePunkt( int wNum, int pNum );
        // entfernt einen Wert
        //  wNum: Der Index des Wertes
        __declspec( dllexport ) void removeWert( int wNum );
        // entfernt einen Wert
        //  name: Der Name des Wertes
        __declspec( dllexport ) void removeWert( char *name );
        // entfernt einen Wert
        //  name: Der Name des Wertes
        __declspec( dllexport ) void removeWert( Text *name );
        // F�gt den DiagDaten bestimmte Styles hinzu
        //  style: Die neuen Styles
        __declspec( dllexport ) void addDatenStyle( int style );
        // Setzt die Styles der DiagDaten
        //  style: Die neuen Styles
        __declspec( dllexport ) void setDatenStyle( int style );
        // Setzt die Styles der DiagDaten
        //  style: Die Styles
        //  addRemove: 1, falls die Styles hinzugef�gt werden sollem. 0, falls die Styles entfernt werden sollen
        __declspec( dllexport ) void setDatenStyle( int style, bool addRemove );
        // Entfernt Styles der DiagDaten
        //  style: Die Styles, die entfernt werden sollen
        __declspec( dllexport ) void removeDatenStyle( int style );
        // F�gt einem bestimmten Wert bestimmte Styles hinzu
        //  wNum: Der Index des Wertes
        //  style: Die neuen Styles
        __declspec( dllexport ) void addWertStyle( int wNum, int style );
        // Setzt die Styles eines Bestimmten Wertes
        //  wNum: Der Index des Wertes
        //  style: Die neuen Styles
        __declspec( dllexport ) void setWertStyle( int wNum, int style );
        // Setzt die Styles eines Bestimmten Wertes
        //  wNum: Der Index des Wertes
        //  style: Die Styles
        //  addRemove: 1, falls die Styles hinzugef�gt werden sollem. 0, falls die Styles entfernt werden sollen
        __declspec( dllexport ) void setWertStyle( int wNum, int style, bool addRemove );
        // Entfernt Styles eines Bestimmten Wertes
        //  wNum: Der Index des Wertes
        //  style: Die Styles, die entfernt werden sollen
        __declspec( dllexport ) void removeWertStyle( int wNum, int style );
        // Gibt die Daten des Diagramms zur�ck
        __declspec( dllexport ) DiagDaten *getDiagDaten() const;
        // Gibt die Daten des Diagramms ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) DiagDaten *zDiagDaten() const;
        // Gibt die Daten eines Wertes zur�ck
        //  wNum: Der Index des Wertes
        __declspec( dllexport ) DiagWert *getDiagWert( int wNum ) const;
        // Gibt die Daten eines Wertes ohne erh�hten Reference Counter zur�ck
        //  wNum: Der Index des Wertes
        __declspec( dllexport ) DiagWert *zDiagWert( int wNum ) const;
        // Gibt die Daten eines Wertes zur�ck
        //  name: Der Name des Wertes
        __declspec( dllexport ) DiagWert *getDiagWert( char *name ) const;
        // Gibt die Daten eines Wertes ohne erh�hten Reference Counter zur�ck
        //  name: Der Name des Wertes
        __declspec( dllexport ) DiagWert *zDiagWert( char *name ) const;
        // Gibt den Index eines Wertes zur�ck
        //  name: Der Name des Wertes
        __declspec( dllexport ) int getDiagWertPos( char *name ) const;
        // Gibt den Index eines Punktes von einem Wert zur�ck
        //  wNum: Der Index des Wertes
        //  hI: Der Wert auf der X Achse des Punktes
        __declspec( dllexport ) int getDiagPunktPos( int wNum, double hI ) const;
        // Gibt den Index eines Punktes von einem Wert zur�ck
        //  wName: Der Name des Wertes
        //  hI: Der Wert auf der X Achse des Punktes
        __declspec( dllexport ) int getDiagPunktPos( char *wName, double hI ) const;
        // Pr�ft, ob bestimmte Styles in den DiagDaten gesetzt wurden
        //  style: Die Styles
        __declspec( dllexport ) inline bool hatDatenStyle( int style ) const;
        // Pr�ft, ob bestimmte Styles in den DiagDaten nicht gesetzt wurden
        //  style: Die Styles
        __declspec( dllexport ) inline bool hatDatenStyleNicht( int style ) const;
        // Pr�ft, ob bestimmte Styles f�r einen bestimmten Wert gesetzt wurden
        //  wNum: Der Index des Wertes
        //  style: Die Styles
        __declspec( dllexport ) inline bool hatWertStyle( int wNum, int style ) const;
        // Pr�ft, ob bestimmte Styles f�r einen bestimmten Wert nicht gesetzt wurden
        //  wNum: Der Index des Wertes
        //  style: Die Styles
        __declspec( dllexport ) inline bool hatWertStyleNicht( int wNum, int style ) const;
        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
        __declspec( dllexport ) BaseDiag *getThis();
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) virtual BaseDiag *release();
    };

    // Eine Zeichnung des 2D GUI Frameworks, die die Diagrammdaten als Liniengraphen darstellt
    class LDiag : public ZeichnungHintergrund, public BaseDiag
    {
    public:
        class Style : public ZeichnungHintergrund::Style
        {
        public:
            const static __int64 DatenRahmen = 0x0001000; // Legt fest, ob um die daten ein Rahmen gezeichnet wird
            const static __int64 DatenHintergrund = 0x02000; // legt fest, ob die Daten einen Hintergrund haben
            const static __int64 DatenHAlpha = 0x04000; // legt fest, ob beim zeichnen des Hintergrunds der Daten alpha blending benutzt wird
            const static __int64 DatenHBild = 0x008000; // Legt fest, ob f�r den Hintergrund der Daten ein Bild verwendet werden soll
            const static __int64 DatenBuffered = 0x010000; // Legt fest, ob die Daten einen Farb�bergang haben

            const static __int64 scroll = VScroll | HScroll; // Vereint die Flags VScroll und HScroll
            const static __int64 normal = Hintergrund | scroll | DatenRahmen; // Vereint die Flags Hintergrund, scroll, DatenRahmen
        };
    private:
        Schrift *schrift;
        LRahmen *dRam;
        int dBgF;
        Bild *dBgB;
        AlphaFeld *dAf;
        Bild *vIntervallRB;
        Bild *hIntervallRB;
        int schriftGr;

    public:
        // Konstruktor
        __declspec( dllexport ) LDiag();
        // Destruktor
        __declspec( dllexport ) virtual ~LDiag();
        // Setzt die Schrift
        //  schrift: Die Schrift
        __declspec( dllexport ) void setSchriftZ( Schrift *schrift );
        // Setzt die gr��e der Schrift
        //  gr: Die H�he einer Zeile in Pixeln
        __declspec( dllexport ) void setSchriftSize( int gr );
        // Setzt den inneren Rahmen um das eigentliche Diagramm (Rahmen um die Daten)
        //  ram: Der Rahmen
        __declspec( dllexport ) void setDatenRahmenZ( LRahmen *ram );
        // Setzt den inneren Rahmen um das eigentliche Diagramm (Rahmen um die Daten), indem ein Rahmen kopiert wird
        //  ram: Der Rahmen, der kopiert werden soll
        __declspec( dllexport ) void setDatenRahmen( LRahmen *ram );
        // Setzt die Breite des inneren Rahmen um das eigentliche Diagramm (Rahmen um die Daten)
        //  br: Die Breite in Pixeln
        __declspec( dllexport ) void setDatenRahmenBreite( int br );
        // Setzt die Farbe des inneren Rahmen um das eigentliche Diagramm (Rahmen um die Daten)
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setDatenRahmenFarbe( int fc );
        // Setzt den Hintergrund des eigentlichen Diagramms
        __declspec( dllexport ) void setDatenHintergrundFarbe( int fc );
        __declspec( dllexport ) void setDatenHintergrundBildZ( Bild *b );
        __declspec( dllexport ) void setDatenHintergrundBild( Bild *b );
        // Setzt den Farb�bergang des eigentlichen Diagramms (Farb�bergang der Daten)
        //  af: Der Farb�bergang
        __declspec( dllexport ) void setDatenAlphaFeldZ( AlphaFeld *af );
        // Setzt den Farb�bergang des eigentlichen Diagramms (Farb�bergang der Daten), indem ein Farb�bergang kopiert wird
        //  af: Der Farb�bergang, der Kopiert werden soll
        __declspec( dllexport ) void setDatenAlphaFeld( AlphaFeld *af );
        // Setzt die Farbe des Farb�bergangs des eigentlichen Diagramms (Farb�bergang der Daten)
        //  fc: Die Farbe im A8R8G8B8 Format
        __declspec( dllexport ) void setDatenAlphaFeldFarbe( int fc );
        // Setzt die FaSt�rkerbe des Farb�bergangs des eigentlichen Diagramms (Farb�bergang der Daten)
        //  st: Die St�rke
        __declspec( dllexport ) void setDatenAlphaFeldStrength( int st );
        // Verarbeitet Maus Nachrichten
        //  me: Das Ereignis, was durch die Mauseingabe ausgel��t wurde
        __declspec( dllexport ) void doMausEreignis( MausEreignis &me ) override;
        // Zeichnet das Objekt nach zRObj, falls es sichtbar ist
        //  zRObj: Das Bild, in welches gezeichnet werden soll
        __declspec( dllexport ) void render( Bild &zRObj ) override;
        // Gibt die Schrift zur�ck
        __declspec( dllexport ) Schrift *getSchrift() const;
        // Gibt die Schrift ohne erh�hten Reference Counter zur�ck
        __declspec( dllexport ) Schrift *zSchrift() const;
        // Gibt den inneren Rahmen um das eigentliche Diagramm zur�ck (Rahmen um die Daten)
        __declspec( dllexport ) LRahmen *getDatenRahmen() const;
        // Gibt den inneren Rahmen um das eigentliche Diagramm ohne erh�hten Reference Counter zur�ck (Rahmen um die Daten)
        __declspec( dllexport ) LRahmen *zDatenRahmen() const;
        // Gibt die Farbe des inneren Rahmens um das eigentliche Diagramm im A8R8G8B8 Format zur�ck (Rahmen um die Daten)
        __declspec( dllexport ) int getDatenRahmenFarbe() const;
        // Gibt die Breite des inneren Rahmens um das eigentliche Diagramm in Pixeln zur�ck (Rahmen um die Daten)
        __declspec( dllexport ) int getDatenRahmenBreite() const;
        // Gibt die Farbe des Hintergrunds des eigentlichen Diagramms im A8R8G8B8 Format zur�ck (Hintergrund der Daten)
        __declspec( dllexport ) int getDatenHintergrundFarbe() const;
        // Gibt das Hintergrund Bild des eigentlichen Diagramms zur�ck (Hintergrund Bild der Daten)
        __declspec( dllexport ) Bild *getDatenHintergrundBild() const;
        // Gibt das Hintergrund Bild des eigentlichen Diagramms ohne erh�hten Reference Counter zur�ck (Hintergrund Bild der Daten)
        __declspec( dllexport ) Bild *zDatenHintergrundBild() const;
        // Gibt den Farb�bergang des eigentlichen Diagramms zur�ck (Farb�bergang der Daten)
        __declspec( dllexport ) AlphaFeld *getDatenAlphaFeld() const;
        // Gibt den Farb�bergang des eigentlichen Diagramms ohne erh�hten Reference Counter zur�ck (Farb�bergang der Daten)
        __declspec( dllexport ) AlphaFeld *zDatenAlphaFeld() const;
        // Gibt die Farbe des Farb�bergangs des eigentlichen Diagramms im A8R8G8B8 Format zur�ck (Farb�bergang der Daten)
        __declspec( dllexport ) int getDatenAlphaFeldFarbe() const;
        // Gibt die St�rke des Farb�bergangs des eigentlichen Diagramms zur�ck (Farb�bergang der Daten)
        __declspec( dllexport ) int getDatenAlphaFeldStrength() const;
        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
        __declspec( dllexport ) BaseDiag *release() override;
    };
}

#endif