#include "Tabelle.h"
#include "Scroll.h"
#include "AlphaFeld.h"
#include "MausEreignis.h"
#include "TastaturEreignis.h"
#include "Bild.h"
#include "Rahmen.h"
#include "Text.h"
#include "ToolTip.h"

using namespace Framework;

// Inhalt der ObjTabelle Klasse aus Tabelle.h
// Konstruktor 
ObjTabelle::ObjTabelle()
    : ZeichnungHintergrund(),
    zZeichnungs( new RCArray< Array< Zeichnung* > >() ),
    spaltenNamen( new RCArray< Text >() ),
    zeilenNamen( new RCArray< Text >() ),
    spaltenBreite( new Array< int >() ),
    zeilenH�he( new Array< int >() ),
    minSpaltenBreite( new Array< int >() ),
    maxSpaltenBreite( new Array< int >() ),
    minZeilenH�he( new Array< int >() ),
    maxZeilenH�he( new Array< int >() ),
    spaltenAnzahl( 0 ),
    zeilenAnzahl( 0 ),
    klickSpalte( -1 ),
    mSpalte( -1 ),
    mZeile( -1 ),
    mx( 0 ),
    my( 0 ),
    selected( -1, -1 ),
    rasterFarbe( 0xFF000000 ),
    rasterBreite( 1 ),
    aRam( 0 ),
    aAf( 0 ),
    msaRam( new RCArray< RCArray< LRahmen > >() ),
    msaAf( new RCArray< RCArray< AlphaFeld > >() ),
    styles( new RCArray< Array< __int64 > >() ),
    ref( 1 )
{
    style = 0;
}

// Destruktor 
ObjTabelle::~ObjTabelle()
{
    if( zZeichnungs )
        zZeichnungs->release();
    if( spaltenNamen )
        spaltenNamen->release();
    if( zeilenNamen )
        zeilenNamen->release();
    if( spaltenBreite )
        spaltenBreite->release();
    if( zeilenH�he )
        zeilenH�he->release();
    if( minSpaltenBreite )
        minSpaltenBreite->release();
    if( maxSpaltenBreite )
        maxSpaltenBreite->release();
    if( minZeilenH�he )
        minZeilenH�he->release();
    if( maxZeilenH�he )
        maxZeilenH�he->release();
    if( aRam )
        aRam->release();
    if( aAf )
        aAf->release();
    if( msaRam )
        msaRam->release();
    if( msaAf )
        msaAf->release();
    if( styles )
        styles->release();
}

// nicht constant 
void ObjTabelle::addSpalte( const char *name ) // Spalte hinzuf�gen
{
    lockZeichnung();
    zZeichnungs->add( new Array< Zeichnung* >(), spaltenAnzahl );
    spaltenNamen->add( new Text( name ), spaltenAnzahl );
    spaltenBreite->add( 100 );
    msaRam->add( new RCArray< LRahmen >(), spaltenAnzahl );
    msaAf->add( new RCArray< AlphaFeld >(), spaltenAnzahl );
    ++spaltenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addSpalte( Text *name )
{
    lockZeichnung();
    zZeichnungs->add( new Array< Zeichnung* >(), spaltenAnzahl );
    spaltenNamen->add( name, spaltenAnzahl );
    spaltenBreite->add( 100 );
    msaRam->add( new RCArray< LRahmen >(), spaltenAnzahl );
    msaAf->add( new RCArray< AlphaFeld >(), spaltenAnzahl );
    ++spaltenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addSpalte( int sNum, const char *name ) // Spalte bei sNum einf�gen
{
    if( sNum > spaltenAnzahl )
        return;
    lockZeichnung();
    zZeichnungs->add( new Array< Zeichnung* >(), sNum );
    spaltenNamen->add( new Text( name ), sNum );
    spaltenBreite->add( 100, sNum );
    minSpaltenBreite->add( 0, sNum );
    maxSpaltenBreite->add( 300, sNum );
    msaRam->add( new RCArray< LRahmen >(), sNum );
    msaAf->add( new RCArray< AlphaFeld >(), sNum );
    styles->add( new Array< __int64 >(), sNum );
    ++spaltenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addSpalte( int sNum, Text *name )
{
    if( sNum > spaltenAnzahl )
        return;
    lockZeichnung();
    zZeichnungs->add( new Array< Zeichnung* >(), sNum );
    spaltenNamen->add( name, sNum );
    spaltenBreite->add( 100, sNum );
    minSpaltenBreite->add( 0, sNum );
    maxSpaltenBreite->add( 300, sNum );
    msaRam->add( new RCArray< LRahmen >(), sNum );
    msaAf->add( new RCArray< AlphaFeld >(), sNum );
    styles->add( new Array< __int64 >(), sNum );
    ++spaltenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addZeile( const char *name ) // Zeile Hinzuf�gen
{
    lockZeichnung();
    zeilenNamen->add( new Text( name ), zeilenAnzahl );
    zeilenH�he->add( 20 );
    ++zeilenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addZeile( Text *name )
{
    lockZeichnung();
    zeilenNamen->add( name, zeilenAnzahl );
    zeilenH�he->add( 20 );
    ++zeilenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addZeile( int zNum, const char *name ) // Zeile bei zNum einf�gen
{
    if( zNum > zeilenAnzahl )
        return;
    lockZeichnung();
    zeilenNamen->add( new Text( name ), zNum );
    zeilenH�he->add( 20, zNum );
    minZeilenH�he->add( 0, zNum );
    maxZeilenH�he->add( 100, zNum );
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        if( zZeichnungs->z( i ) )
            zZeichnungs->z( i )->add( 0, zNum );
        if( msaRam->z( i ) )
            msaRam->z( i )->add( 0, zNum );
        if( msaAf->z( i ) )
            msaAf->z( i )->add( 0, zNum );
        if( styles->z( i ) )
            styles->z( i )->add( 0, zNum );
    }
    ++zeilenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::addZeile( int zNum, Text *name )
{
    if( zNum > zeilenAnzahl )
        return;
    lockZeichnung();
    zeilenNamen->add( name, zNum );
    zeilenH�he->add( 20, zNum );
    minZeilenH�he->add( 0, zNum );
    maxZeilenH�he->add( 100, zNum );
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        if( zZeichnungs->z( i ) )
            zZeichnungs->z( i )->add( 0, zNum );
        if( msaRam->z( i ) )
            msaRam->z( i )->add( 0, zNum );
        if( msaAf->z( i ) )
            msaAf->z( i )->add( 0, zNum );
        if( styles->z( i ) )
            styles->z( i )->add( 0, zNum );
    }
    ++zeilenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::removeSpalte( int sNum ) // Spalte l�schen
{
    if( sNum >= spaltenAnzahl )
        return;
    lockZeichnung();
    zZeichnungs->l�sche( sNum );
    spaltenNamen->l�sche( sNum );
    spaltenBreite->l�sche( sNum );
    minSpaltenBreite->l�sche( sNum );
    maxSpaltenBreite->l�sche( sNum );
    if( msaRam->z( sNum ) )
        msaRam->z( sNum )->release();
    msaRam->l�sche( sNum );
    if( msaAf->z( sNum ) )
        msaAf->z( sNum )->release();
    msaAf->l�sche( sNum );
    styles->l�sche( sNum );
    --spaltenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::removeSpalte( const char *name )
{
    removeSpalte( getSpaltenNummer( name ) );
}

void ObjTabelle::removeSpalte( Text *name )
{
    removeSpalte( getSpaltenNummer( name ) );
}

void ObjTabelle::removeZeile( int zNum ) // Zeile l�schen
{
    if( zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    zeilenNamen->l�sche( zNum );
    zeilenH�he->l�sche( zNum );
    minZeilenH�he->l�sche( zNum );
    maxZeilenH�he->l�sche( zNum );
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        if( zZeichnungs->z( i ) )
            zZeichnungs->z( i )->l�sche( zNum );
        if( msaRam->z( i ) )
            msaRam->z( i )->l�sche( zNum );
        if( msaAf->z( i ) )
            msaAf->z( i )->l�sche( zNum );
        if( styles->z( i ) )
            styles->z( i )->l�sche( zNum );
    }
    --zeilenAnzahl;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::removeZeile( const char *name )
{
    removeZeile( getZeilenNummer( name ) );
}

void ObjTabelle::removeZeile( Text *name )
{
    removeZeile( getZeilenNummer( name ) );
}

void ObjTabelle::setSpaltePosition( const char *name, int pos ) // setzt die Position einer Spalte
{
    setSpaltePosition( getSpaltenNummer( name ), pos );
}

void ObjTabelle::setSpaltePosition( Text *name, int pos )
{
    setSpaltePosition( getSpaltenNummer( name ), pos );
}

void ObjTabelle::setSpaltePosition( int sNum, int pos )
{
    if( sNum >= spaltenAnzahl || pos >= spaltenAnzahl || sNum == pos )
        return;
    int l�schPos = sNum;
    int insertPos = pos;
    if( pos < sNum )
        ++l�schPos;
    else
        ++insertPos;
    lockZeichnung();
    zZeichnungs->add( zZeichnungs->get( sNum ), insertPos );
    zZeichnungs->l�sche( l�schPos );
    spaltenNamen->add( spaltenNamen->get( sNum ), insertPos );
    spaltenNamen->l�sche( l�schPos );
    spaltenBreite->add( spaltenBreite->hat( sNum ) ? spaltenBreite->get( sNum ) : 0, insertPos );
    spaltenBreite->l�sche( l�schPos );
    minSpaltenBreite->add( minSpaltenBreite->hat( sNum ) ? minSpaltenBreite->get( sNum ) : 0, insertPos );
    minSpaltenBreite->l�sche( l�schPos );
    msaRam->add( msaRam->z( sNum ), insertPos );
    msaRam->l�sche( l�schPos );
    msaAf->add( msaAf->z( sNum ), insertPos );
    msaAf->l�sche( l�schPos );
    styles->add( styles->get( sNum ), insertPos );
    styles->l�sche( l�schPos );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setZeilePosition( const char *name, int pos ) // setzt die Zeilen Position
{
    setZeilePosition( getZeilenNummer( name ), pos );
}

void ObjTabelle::setZeilePosition( Text *name, int pos )
{
    setZeilePosition( getZeilenNummer( name ), pos );
}

void ObjTabelle::setZeilePosition( int zNum, int pos )
{
    if( zNum >= zeilenAnzahl || pos >= zeilenAnzahl || pos == zNum )
        return;
    int l�schPos = zNum;
    int insertPos = pos;
    if( pos < zNum )
        ++l�schPos;
    else
        ++insertPos;
    lockZeichnung();
    zeilenNamen->add( zeilenNamen->get( zNum ), insertPos );
    zeilenNamen->l�sche( l�schPos );
    zeilenH�he->add( zeilenH�he->hat( zNum ) ? zeilenH�he->get( zNum ) : 0, insertPos );
    zeilenH�he->l�sche( l�schPos );
    minZeilenH�he->add( minZeilenH�he->hat( zNum ) ? minZeilenH�he->get( zNum ) : 0, insertPos );
    minZeilenH�he->l�sche( l�schPos );
    maxZeilenH�he->add( maxZeilenH�he->hat( zNum ) ? maxZeilenH�he->get( zNum ) : 0, insertPos );
    maxZeilenH�he->l�sche( l�schPos );
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        if( zZeichnungs->z( i ) )
        {
            zZeichnungs->z( i )->add( zZeichnungs->z( i )->hat( zNum ) ? zZeichnungs->z( i )->get( zNum ) : 0, insertPos );
            zZeichnungs->z( i )->l�sche( l�schPos );
        }
        if( msaRam->z( i ) )
        {
            msaRam->z( i )->add( msaRam->z( i )->z( zNum ) ? msaRam->z( i )->get( zNum ) : 0, insertPos );
            msaRam->z( i )->l�sche( l�schPos );
        }
        if( msaAf->z( i ) )
        {
            msaAf->z( i )->add( msaAf->z( i )->z( zNum ) ? msaAf->z( i )->get( zNum ) : 0, insertPos );
            msaAf->z( i )->l�sche( l�schPos );
        }
        if( styles->z( i ) )
        {
            styles->z( i )->add( styles->z( i )->hat( zNum ) ? styles->z( i )->get( zNum ) : 0, insertPos );
            styles->z( i )->l�sche( l�schPos );
        }
    }
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setZeichnungZ( int sNum, int zNum, Zeichnung *zObj ) // setzt ein Zeichnung
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    if( !zZeichnungs->z( sNum ) )
        zZeichnungs->set( new Array< Zeichnung* >(), sNum );
    zZeichnungs->z( sNum )->set( zObj, zNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setZeichnungZ( const char *spaltenName, const char *zeilenName, Zeichnung *zZeichnung )
{
    setZeichnungZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), zZeichnung );
}

void ObjTabelle::setZeichnungZ( Text *spaltenName, Text *zeilenName, Zeichnung *zZeichnung )
{
    setZeichnungZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), zZeichnung );
}

void ObjTabelle::setSpaltenBreite( int sNum, int br ) // setzt die Spaltenbreite
{
    if( sNum >= spaltenAnzahl )
        return;
    lockZeichnung();
    spaltenBreite->set( br, sNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setSpaltenBreite( const char *name, int br )
{
    setSpaltenBreite( getSpaltenNummer( name ), br );
}

void ObjTabelle::setSpaltenBreite( Text *name, int br )
{
    setSpaltenBreite( getSpaltenNummer( name ), br );
}

void ObjTabelle::setZeilenH�he( int zNum, int h� ) // setzt die Zeilenh�he
{
    if( zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    zeilenH�he->set( h�, zNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setZeilenH�he( const char *name, int h� )
{
    setZeilenH�he( getZeilenNummer( name ), h� );
}

void ObjTabelle::setZeilenH�he( Text *name, int h� )
{
    setZeilenH�he( getZeilenNummer( name ), h� );
}

void ObjTabelle::setMinSpaltenBreite( int sNum, int minBr ) // setzt die mindest Spaltenbreite
{
    if( sNum >= spaltenAnzahl )
        return;
    lockZeichnung();
    minSpaltenBreite->set( minBr, sNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setMinSpaltenBreite( const char *name, int minBr )
{
    setMinSpaltenBreite( getSpaltenNummer( name ), minBr );
}

void ObjTabelle::setMinSpaltenBreite( Text *name, int minBr )
{
    setMinSpaltenBreite( getSpaltenNummer( name ), minBr );
}

void ObjTabelle::setMaxSpaltenBreite( int sNum, int maxBr ) // setzt die maximale Spaltenbreite
{
    if( sNum >= spaltenAnzahl )
        return;
    lockZeichnung();
    maxSpaltenBreite->set( maxBr, sNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setMaxSpaltenBreite( const char *name, int maxBr )
{
    setMaxSpaltenBreite( getSpaltenNummer( name ), maxBr );
}

void ObjTabelle::setMaxSpaltenBreite( Text *name, int maxBr )
{
    setMaxSpaltenBreite( getSpaltenNummer( name ), maxBr );
}

void ObjTabelle::setMinZeilenH�he( int zNum, int minH� ) // setzt die mindest Zeilenh�he
{
    if( zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    minZeilenH�he->set( minH�, zNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setMinZeilenH�he( const char *name, int minH� )
{
    setMinZeilenH�he( getZeilenNummer( name ), minH� );
}

void ObjTabelle::setMinZeilenH�he( Text *name, int minH� )
{
    setMinZeilenH�he( getZeilenNummer( name ), minH� );
}

void ObjTabelle::setMaxZeilenH�he( int zNum, int maxH� ) // setzt die maximale Zeilenh�he
{
    if( zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    maxZeilenH�he->set( maxH�, zNum );
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setMaxZeilenH�he( const char *name, int maxH� )
{
    setMaxZeilenH�he( getZeilenH�he( name ), maxH� );
}

void ObjTabelle::setMaxZeilenH�he( Text *name, int maxH� )
{
    setMaxZeilenH�he( getZeilenH�he( name ), maxH� );
}

void ObjTabelle::setAuswahl( int sNum, int zNum ) // w�hlt das entsprechnde Feld aus
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    lockZeichnung();
    selected.x = sNum;
    selected.y = zNum;
    rend = 1;
    unlockZeichnung();
}

void ObjTabelle::setAuswahl( const char *spaltenName, const char *zeilenName )
{
    setAuswahl( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

void ObjTabelle::setAuswahl( Text *spaltenName, Text *zeilenName )
{
    setAuswahl( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

void ObjTabelle::setRasterFarbe( int f ) // settzt die Farbe des Rasters
{
    rasterFarbe = f;
    rend = 1;
}

void ObjTabelle::setRasterBreite( int br ) // setzt die Breite des Rasters
{
    rasterBreite = br;
    rend = 1;
}

void ObjTabelle::setARahmenZ( LRahmen *ram ) // setzt den auswahl Rahmen
{
    if( aRam )
        aRam->release();
    aRam = ram;
    rend = 1;
}

void ObjTabelle::setARFarbe( int f ) // setzt die auswahl Rahmen Farbe
{
    if( !aRam )
        aRam = new LRahmen();
    aRam->setFarbe( f );
    rend = 1;
}

void ObjTabelle::setARBreite( int br ) // setzt die auswahl Rahmen Breite
{
    if( !aRam )
        aRam = new LRahmen();
    aRam->setRamenBreite( br );
    rend = 1;
}

void ObjTabelle::setAAlphaFeldZ( AlphaFeld *af ) // setzt das auswahl AlphaFeld
{
    if( aAf )
        aAf->release();
    aAf = af;
    rend = 1;
}

void ObjTabelle::setAAfFarbe( int f ) // setzt die Farbe des auswahl AlphaFeldes
{
    if( !aAf )
        aAf = new AlphaFeld();
    aAf->setFarbe( f );
    rend = 1;
}

void ObjTabelle::setAAfSt�rke( int st ) // setzt die St�rke des auswahl AlphaFeldes
{
    if( !aAf )
        aAf = new AlphaFeld();
    aAf->setSt�rke( st );
    rend = 1;
}

void ObjTabelle::setARahmenZ( int sNum, int zNum, LRahmen *ram ) // setzt den auswahl Rahmen
{
    if( msaRam->z( sNum ) )
        msaRam->z( sNum )->set( ram, zNum );
    rend = 1;
}

void ObjTabelle::setARahmenZ( const char *spaltenName, const char *zeilenName, LRahmen *ram )
{
    setARahmenZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), ram );
}

void ObjTabelle::setARahmenZ( Text *spaltenName, Text *zeilenName, LRahmen *ram )
{
    setARahmenZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), ram );
}

void ObjTabelle::setARFarbe( int sNum, int zNum, int f ) // setzt die auswahl Rahmen Farbe
{
    if( msaRam->z( sNum ) )
    {
        LRahmen *tmp = msaRam->z( sNum )->z( zNum );
        if( !tmp )
        {
            tmp = new LRahmen();
            msaRam->z( sNum )->set( tmp, zNum );
        }
        tmp->setFarbe( f );
        rend = 1;
    }
}

void ObjTabelle::setARFarbe( const char *spaltenName, const char *zeilenName, int f )
{
    setARFarbe( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), f );
}

void ObjTabelle::setARFarbe( Text *spaltenName, Text *zeilenName, int f )
{
    setARFarbe( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), f );
}

void ObjTabelle::setARBreite( int sNum, int zNum, int br ) // setzt die auswahl Rahmen Breite
{
    if( msaRam->z( sNum ) )
    {
        LRahmen *tmp = msaRam->z( sNum )->z( zNum );
        if( !tmp )
        {
            tmp = new LRahmen();
            msaRam->z( sNum )->set( tmp, zNum );
        }
        tmp->setRamenBreite( br );
        rend = 1;
    }
}

void ObjTabelle::setARBreite( const char *spaltenName, const char *zeilenName, int br )
{
    setARBreite( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), br );
}

void ObjTabelle::setARBreite( Text *spaltenName, Text *zeilenName, int br )
{
    setARBreite( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), br );
}

void ObjTabelle::setAAlphaFeldZ( int sNum, int zNum, AlphaFeld *af ) // setzt das auswahl AlphaFeld
{
    if( msaAf->z( sNum ) )
        msaAf->z( sNum )->set( af, zNum );
    rend = 1;
}

void ObjTabelle::setAAlphaFeldZ( const char *spaltenName, const char *zeilenName, AlphaFeld *af )
{
    setAAlphaFeldZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), af );
}

void ObjTabelle::setAAlphaFeldZ( Text *spaltenName, Text *zeilenName, AlphaFeld *af )
{
    setAAlphaFeldZ( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), af );
}

void ObjTabelle::setAAfFarbe( int sNum, int zNum, int f ) // setzt die Farbe des auswahl AlphaFeldes
{
    if( msaAf->z( sNum ) )
    {
        AlphaFeld *tmp = msaAf->z( sNum )->z( zNum );
        if( !tmp )
        {
            tmp = new AlphaFeld();
            msaAf->z( sNum )->set( tmp, zNum );
        }
        tmp->setFarbe( f );
        rend = 1;
    }
}

void ObjTabelle::setAAfFarbe( const char *spaltenName, const char *zeilenName, int f )
{
    setAAfFarbe( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), f );
}

void ObjTabelle::setAAfFarbe( Text *spaltenName, Text *zeilenName, int f )
{
    setAAfFarbe( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), f );
}

void ObjTabelle::setAAfSt�rke( int sNum, int zNum, int st ) // setzt die St�rke des auswahl AlphaFeldes
{
    if( msaAf->z( sNum ) )
    {
        AlphaFeld *tmp = msaAf->z( sNum )->z( zNum );
        if( !tmp )
        {
            tmp = new AlphaFeld();
            msaAf->z( sNum )->set( tmp, zNum );
        }
        tmp->setSt�rke( st );
        rend = 1;
    }
}

void ObjTabelle::setAAfSt�rke( const char *spaltenName, const char *zeilenName, int st )
{
    setAAfSt�rke( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), st );
}

void ObjTabelle::setAAfSt�rke( Text *spaltenName, Text *zeilenName, int st )
{
    setAAfSt�rke( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), st );
}

void ObjTabelle::addMsStyle( int sNum, int zNum, __int64 style ) // setzt den Style wenn Multistyled
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    if( styles->z( sNum ) )
        styles->z( sNum )->set( ( styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0 ) | style, zNum );
    rend = 1;
}

void ObjTabelle::addMsStyle( const char *spaltenName, const char *zeilenName, __int64 style )
{
    addMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

void ObjTabelle::addMsStyle( Text *spaltenName, Text *zeilenName, __int64 style )
{
    addMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

void ObjTabelle::setMsStyle( int sNum, int zNum, __int64 style )
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    if( styles->z( sNum ) )
        styles->z( sNum )->set( style, zNum );
    rend = 1;
}

void ObjTabelle::setMsStyle( const char *spaltenName, const char *zeilenName, __int64 style )
{
    setMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

void ObjTabelle::setMsStyle( Text *spaltenName, Text *zeilenName, __int64 style )
{
    setMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

void ObjTabelle::setMsStyle( int sNum, int zNum, __int64 style, bool add_remove )
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    if( styles->z( sNum ) )
    {
        if( add_remove )
            styles->z( sNum )->set( ( styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0 ) | style, zNum );
        else
            styles->z( sNum )->set( ( styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0 ) & ( ~style ), zNum );
        rend = 1;
    }
}

void ObjTabelle::setMsStyle( const char *spaltenName, const char *zeilenName, __int64 style, bool add_remove )
{
    setMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style, add_remove );
}

void ObjTabelle::setMsStyle( Text *spaltenName, Text *zeilenName, __int64 style, bool add_remove )
{
    setMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style, add_remove );
}

void ObjTabelle::l�scheMsStyle( int sNum, int zNum, __int64 style )
{
    if( sNum >= spaltenAnzahl || zNum >= zeilenAnzahl )
        return;
    if( styles->z( sNum ) )
        styles->z( sNum )->set( ( styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0 ) & ( ~style ), zNum );
    rend = 1;
}

void ObjTabelle::l�scheMsStyle( const char *spaltenName, const char *zeilenName, __int64 style )
{
    l�scheMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

void ObjTabelle::l�scheMsStyle( Text *spaltenName, Text *zeilenName, __int64 style )
{
    l�scheMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

bool ObjTabelle::tick( double tickVal ) // tick Message
{
    lockZeichnung();
    for( int i = 0; i < zeilenAnzahl; ++i )
    {
        for( int j = 0; j < spaltenAnzahl; ++j )
        {
            Zeichnung *obj = zZeichnung( j, i );
            if( obj )
                rend |= obj->tick( tickVal );
        }
    }
    unlockZeichnung();
    return __super::tick( tickVal );
}

void ObjTabelle::doMausEreignis( MausEreignis &me ) // verarbeitet Nachrichten
{
    bool nmakc = !me.verarbeitet;
    if( hatStyleNicht( Style::Sichtbar ) || hatStyleNicht( Style::Erlaubt ) )
        return;
    bool removeFokus = 0;
    if( me.verarbeitet || !( me.mx >= pos.x && me.mx <= pos.x + gr.x && me.my >= pos.y && me.my <= pos.y + gr.y ) )
    {
        if( mausIn )
        {
            mausIn = 0;
            MausEreignis me2;
            me2.id = ME_Verl�sst;
            me2.mx = me.mx;
            me2.my = me.my;
            me2.verarbeitet = 0;
            doMausEreignis( me2 );
            return;
        }
        removeFokus = 1;
    }
    bool au�erhalb = !( me.mx >= pos.x && me.mx <= pos.x + gr.x && me.my >= pos.y && me.my <= pos.y + gr.y ) && me.id != ME_Verl�sst;
    bool MakB = Mak && ( me.verarbeitet || au�erhalb || Mak( makParam, this, me ) );
    if( !( me.mx >= pos.x && me.mx <= pos.x + gr.x && me.my >= pos.y && me.my <= pos.y + gr.y ) && me.id != ME_Verl�sst )
    {
        if( removeFokus && me.id == ME_RLinks )
        {
            if( MakB )
                l�scheStyle( Style::Fokus );
        }
    }
    else if( !mausIn && me.id != ME_Verl�sst )
    {
        mausIn = 1;
        MausEreignis me2;
        me2.id = ME_Betritt;
        me2.mx = me.mx;
        me2.my = me.my;
        me2.verarbeitet = 0;
        doMausEreignis( me2 );
    }
    int tmx = me.mx;
    int tmy = me.my;
    bool aufScroll = 0;
    if( !au�erhalb && vertikalScrollBar && hatStyle( Style::VScroll ) && me.mx > pos.x + gr.x - 15 )
        aufScroll = 1;
    if( !au�erhalb && horizontalScrollBar && hatStyle( Style::HScroll ) && me.my > pos.y + gr.y - 15 )
        aufScroll = 1;
    me.mx -= pos.x + ( ( horizontalScrollBar && hatStyle( Style::HScroll ) ) ? horizontalScrollBar->getScroll() : 0 );
    me.my -= pos.y + ( ( vertikalScrollBar && hatStyle( Style::VScroll ) ) ? vertikalScrollBar->getScroll() : 0 );
    if( MakB )
    {
        lockZeichnung();
        if( removeFokus && me.id == ME_RLinks )
        {
            l�scheStyle( Style::Fokus );
            klickSpalte = -1;
        }
        if( !me.verarbeitet && !au�erhalb && !aufScroll )
        {
            double ox = getMausSpalte( me.mx + ( ( horizontalScrollBar && hatStyle( Style::HScroll ) ) ? horizontalScrollBar->getScroll() : 0 ) );
            double oy = getMausZeile( me.my + ( ( vertikalScrollBar && hatStyle( Style::VScroll ) ) ? vertikalScrollBar->getScroll() : 0 ) );
            if( me.id == ME_RLinks )
            {
                addStyle( Style::Fokus );
                klickSpalte = -1;
                mSpalte = -1, mZeile = -1;
            }
            if( ( hatStyle( Style::SpaltenBreite�nderbar ) || hatStyle( Style::ZeilenH�he�nderbar ) ) && klickSpalte < 0 )
            {
                if( hatStyle( Style::SpaltenBreite�nderbar ) )
                {
                    if( me.id == ME_PLinks && ox != (int)ox )
                    {
                        mSpalte = ox;
                        mx = me.mx;
                        rend = 1;
                    }
                    if( mSpalte > -1 )
                    {
                        int br = getSpaltenBreite( (int)mSpalte ) + ( me.mx - mx );
                        if( hatStyle( Style::SpaltenBreiteMax ) && br > getMaxSpaltenBreite( (int)mSpalte ) )
                            br = getMaxSpaltenBreite( (int)mSpalte );
                        if( hatStyle( Style::SpaltenBreiteMin ) && br < getMinSpaltenBreite( (int)mSpalte ) )
                            br = getMinSpaltenBreite( (int)mSpalte );
                        setSpaltenBreite( (int)mSpalte, br );
                        mx = me.mx;
                        rend = 1;
                    }
                }
                if( hatStyle( Style::ZeilenH�he�nderbar ) )
                {
                    if( me.id == ME_PLinks && oy != (int)oy )
                    {
                        mZeile = oy;
                        my = me.my;
                        rend = 1;
                    }
                    if( mZeile > -1 )
                    {
                        int h� = getZeilenH�he( (int)mZeile ) + ( me.my - my );
                        if( hatStyle( Style::ZeilenH�heMax ) && h� > getMaxZeilenH�he( (int)mZeile ) )
                            h� = getMaxZeilenH�he( (int)mZeile );
                        if( hatStyle( Style::ZeilenH�heMin ) && h� < getMinZeilenH�he( (int)mZeile ) )
                            h� = getMinZeilenH�he( (int)mZeile );
                        setZeilenH�he( (int)mZeile, h� );
                        my = me.my;
                        rend = 1;
                    }
                }
            }
            if( hatStyle( Style::SpaltenBeweglich ) && ox == (int)ox && mSpalte == -1 && mZeile == -1 )
            {
                if( klickSpalte >= 0 && klickSpalte < spaltenAnzahl && klickSpalte != ox && !oy && ox >= 0 )
                {
                    setSpaltePosition( klickSpalte, (int)ox );
                    klickSpalte = (int)ox;
                    rend = 1;
                }
                if( me.id == ME_PLinks )
                {
                    if( !oy && klickSpalte < 0 )
                    {
                        klickSpalte = (int)ox;
                        rend = 1;
                    }
                }
            }
        }
        me.mx += ( horizontalScrollBar && hatStyle( Style::HScroll ) ) ? horizontalScrollBar->getScroll() : 0;
        me.my += ( vertikalScrollBar && hatStyle( Style::VScroll ) ) ? vertikalScrollBar->getScroll() : 0;
        if( me.id != ME_Betritt && me.id != ME_Verl�sst )
        {
            if( !au�erhalb )
            {
                bool vs = hatStyle( Style::VScroll ) && vertikalScrollBar;
                bool hs = hatStyle( Style::HScroll ) && horizontalScrollBar;
                int rbr = rahmen ? rahmen->getRBreite() : 0;
                if( vs )
                {
                    if( hs )
                        horizontalScrollBar->doMausMessage( rbr, gr.y - 15 - rbr, gr.x - 15 - rbr * 2, 15, me );
                    vertikalScrollBar->doMausMessage( gr.x - 15 - rbr, rbr, 15, gr.y - rbr * 2, me );
                }
                else if( hs )
                    horizontalScrollBar->doMausMessage( rbr, gr.y - 15 - rbr, gr.x - rbr * 2, 15, me );
            }
            unlockZeichnung();
            if( aufScroll )
                me.verarbeitet = 1;
            for( int i = 0; i < zeilenAnzahl; ++i )
            {
                for( int j = 0; j < spaltenAnzahl; ++j )
                {
                    bool b = me.verarbeitet;
                    Zeichnung *obj = zZeichnung( j, i );
                    if( obj )
                        obj->doMausEreignis( me );
                    if( !b && me.verarbeitet && me.id == ME_PLinks )
                        selected = Punkt( j, i );
                }
            }
        }
        else
            unlockZeichnung();
        if( me.mx >= 0 && me.mx <= gr.x && me.my >= 0 && me.my <= gr.y )
            me.verarbeitet = 1;
    }
    if( nmakc && me.verarbeitet && nMak )
        me.verarbeitet = nMak( nmakParam, this, me );
    me.mx = tmx;
    me.my = tmy;
}

void ObjTabelle::doTastaturEreignis( TastaturEreignis &te )
{
    bool ntakc = !te.verarbeitet;
    if( hatStyleNicht( Style::Fokus ) || hatStyleNicht( Style::Erlaubt ) || hatStyleNicht( Style::Sichtbar ) )
        return;
    if( Tak && ( te.verarbeitet || Tak( takParam, this, te ) ) )
    {
        lockZeichnung();
        if( zZeichnung( selected.x, selected.y ) )
        {
            zZeichnung( selected.x, selected.y )->doTastaturEreignis( te );
            if( !te.verarbeitet && te.id == TE_Press )
            {
                if( te.taste == T_Oben )
                {
                    --( selected.y );
                    rend = 1;
                }
                if( te.taste == T_Unten )
                {
                    ++( selected.y );
                    rend = 1;
                }
                if( te.taste == T_Links )
                {
                    --( selected.x );
                    rend = 1;
                }
                if( te.taste == T_Rechts )
                {
                    ++( selected.x );
                    rend = 1;
                }
            }
        }
        unlockZeichnung();
    }
    te.verarbeitet = 1;
    if( ntakc && te.verarbeitet && nTak )
        te.verarbeitet = nTak( ntakParam, this, te );
}

void ObjTabelle::render( Bild &zRObj ) // zeichnet nach zRObj
{
    if( hatStyleNicht( Style::Sichtbar ) )
        return;
    __super::render( zRObj );
    lockZeichnung();
    if( !zRObj.setDrawOptions( innenPosition, innenGr��e ) )
    {
        unlockZeichnung();
        return;
    }
    int xPos = 0;
    if( horizontalScrollBar && hatStyle( Style::HScroll ) )
        xPos -= horizontalScrollBar->getScroll();
    for( int s = 0; s < spaltenAnzahl; ++s )
    {
        int sBr = spaltenBreite->hat( s ) ? spaltenBreite->get( s ) : 0;
        int yPos = 0;
        if( vertikalScrollBar && hatStyle( Style::VScroll ) )
            yPos -= vertikalScrollBar->getScroll();
        Array< Zeichnung* > *tmp_zZeichnungs = zZeichnungs->z( s );
        if( !tmp_zZeichnungs )
            continue;
        for( int z = 0; z < zeilenAnzahl && tmp_zZeichnungs; ++z )
        {
            int zH� = zeilenH�he->hat( z ) ? zeilenH�he->get( z ) : 0;
            Zeichnung *obj = tmp_zZeichnungs->hat( z ) ? tmp_zZeichnungs->get( z ) : 0;
            if( obj )
            {
                obj->setPosition( xPos, yPos );
                obj->setGr��e( sBr, zH� );
                obj->render( zRObj );
                if( selected.x == s && selected.y == z )
                {
                    LRahmen *tmp_aRam = aRam;
                    AlphaFeld *tmp_aAf = aAf;
                    bool aRamB = hatStyle( Style::AuswahlRahmen ) && tmp_aRam;
                    bool aAfB = hatStyle( Style::AuswahlBuffer ) && tmp_aAf;
                    if( hatStyle( Style::AuswahlMultistyled ) )
                    {
                        tmp_aRam = getARahmen( s, z );
                        tmp_aAf = getAAlphaFeld( s, z );
                        aRamB = hatMsStyle( s, z, Style::AuswahlRahmen ) && tmp_aRam;
                        aAfB = hatMsStyle( s, z, Style::AuswahlBuffer ) && tmp_aAf;
                    }
                    int aRbr = 0;
                    if( aRamB )
                    {
                        tmp_aRam->setPosition( xPos, yPos );
                        tmp_aRam->setGr��e( sBr, zH� );
                        tmp_aRam->render( zRObj );
                        aRbr = tmp_aRam->getRBreite();
                    }
                    if( aAfB )
                    {
                        tmp_aAf->setPosition( aRbr + xPos, aRbr + yPos );
                        tmp_aAf->setGr��e( sBr - aRbr * 2, zH� - aRbr * 2 );
                        tmp_aAf->render( zRObj );
                    }
                }
            }
            if( hatStyle( Style::Raster ) )
            {
                zRObj.drawLinieH( xPos, yPos + zH�, sBr, rasterFarbe );
                yPos += rasterBreite;
            }
            yPos += zH�;
            if( z == zeilenAnzahl - 1 && vertikalScrollBar && hatStyle( Style::VScroll ) )
                vertikalScrollBar->getScrollData()->max = yPos + vertikalScrollBar->getScroll();
        }
        if( hatStyle( Style::Raster ) )
        {
            zRObj.drawLinieV( xPos + sBr, 0, innenGr��e.y, rasterFarbe );
            xPos += rasterBreite;
        }
        xPos += sBr;
    }
    if( horizontalScrollBar && hatStyle( Style::HScroll ) )
        horizontalScrollBar->getScrollData()->max = xPos + horizontalScrollBar->getScroll();
    zRObj.releaseDrawOptions();
    unlockZeichnung();
}

// constant 
int ObjTabelle::getSpaltenAnzahl() const // gibt die Anzahl der Spalten zur�ck
{
    return spaltenAnzahl;
}

int ObjTabelle::getZeilenAnzahl() const // gibt die Anzahl der Zeilen zur�ck
{
    return zeilenAnzahl;
}

int ObjTabelle::getSpaltenNummer( const char *name ) const // gibt die Nummer der Spalte mit dem Namen name zur�ck
{
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        if( spaltenNamen->z( i )->istGleich( name ) )
            return i;
    }
    return -1;
}

int ObjTabelle::getSpaltenNummer( Text *name ) const
{
    int ret = getSpaltenNummer( name->getText() );
    name->release();
    return ret;
}

Text *ObjTabelle::getSpaltenName( int num ) const // gibt den Namen der Spalte mit Nummer num zur�ck
{
    return spaltenNamen->get( num );
}

Text *ObjTabelle::zSpaltenName( int num ) const
{
    return spaltenNamen->z( num );
}

int ObjTabelle::getZeilenNummer( const char *name ) const // gibt die Nummer der Zeile mit dem Namen name zur�ck
{
    for( int i = 0; i < zeilenAnzahl; ++i )
    {
        if( zeilenNamen->z( i )->istGleich( name ) )
            return i;
    }
    return -1;
}

int ObjTabelle::getZeilenNummer( Text *name ) const
{
    int ret = getZeilenNummer( name->getText() );
    name->release();
    return ret;
}

Text *ObjTabelle::getZeilenName( int num ) const // gibt den Namen der Zeile mit Nummer num zur�ck
{
    return zeilenNamen->get( num );
}

Text *ObjTabelle::zZeilenName( int num ) const
{
    return zeilenNamen->z( num );
}

Punkt ObjTabelle::getZeichnungPosition( Zeichnung *zObj ) const // gibt die Position eines Zeichnungs zur�ck
{
    for( int x = 0; x < spaltenAnzahl; ++x )
    {
        for( int y = 0; y < zeilenAnzahl; ++y )
        {
            if( zZeichnung( x, y ) == zObj )
                return Punkt( x, y );
        }
    }
    return Punkt( -1, -1 );
}

Zeichnung *ObjTabelle::zZeichnung( int sNum, int zNum ) const // gibt das Zeichnung auf der Position zur�ck
{
    if( !zZeichnungs->z( sNum ) )
        return 0;
    Array< Zeichnung* > *tmp = zZeichnungs->z( sNum );
    if( !tmp->hat( zNum ) )
        return 0;
    return tmp ? tmp->get( zNum ) : 0;
}

Zeichnung *ObjTabelle::zZeichnung( const char *spaltenName, const char *zeilenName ) const
{
    return zZeichnung( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

Zeichnung *ObjTabelle::zZeichnung( Text *spaltenName, Text *zeilenName ) const
{
    return zZeichnung( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

int ObjTabelle::getSpaltenBreite( int num ) const // gibt die Breite der Spalte zur�ck
{
    return spaltenBreite->get( num );
}

int ObjTabelle::getSpaltenBreite( const char *name ) const
{
    return getSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getSpaltenBreite( Text *name ) const
{
    return getSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getZeilenH�he( int num ) const // gibt die H�he der Zeile zur�ck
{
    return zeilenH�he->get( num );
}

int ObjTabelle::getZeilenH�he( const char *name ) const
{
    return getZeilenH�he( getZeilenNummer( name ) );
}

int ObjTabelle::getZeilenH�he( Text *name ) const
{
    return getZeilenH�he( getZeilenNummer( name ) );
}

int ObjTabelle::getMinSpaltenBreite( int num ) const // gibt die minimale Spaltengr��e zur�ck
{
    return minSpaltenBreite->get( num );
}

int ObjTabelle::getMinSpaltenBreite( const char *name ) const
{
    return getMinSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getMinSpaltenBreite( Text *name ) const
{
    return getMinSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getMaxSpaltenBreite( int num ) const // gibt die maximale Spaltengr��e zur�ck
{
    return maxSpaltenBreite->get( num );
}

int ObjTabelle::getMaxSpaltenBreite( const char *name ) const
{
    return getMaxSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getMaxSpaltenBreite( Text *name ) const
{
    return getMaxSpaltenBreite( getSpaltenNummer( name ) );
}

int ObjTabelle::getMinZeilenH�he( int num ) const // gibt die minimale Zeilenh�he zur�ck
{
    return minZeilenH�he->get( num );
}

int ObjTabelle::getMinZeilenH�he( const char *name ) const
{
    return getMinZeilenH�he( getZeilenNummer( name ) );
}

int ObjTabelle::getMinZeilenH�he( Text *name ) const
{
    return getMinZeilenH�he( getZeilenNummer( name ) );
}

int ObjTabelle::getMaxZeilenH�he( int num ) const // gibt die maximale Zeilenh�he zur�ck
{
    return maxZeilenH�he->get( num );
}

int ObjTabelle::getMaxZeilenH�he( const char *name ) const
{
    return getMaxZeilenH�he( getZeilenNummer( name ) );
}

int ObjTabelle::getMaxZeilenH�he( Text *name ) const
{
    return getMaxZeilenH�he( getZeilenNummer( name ) );
}

double ObjTabelle::getMausSpalte( int mx ) const // ermittelt die Spalte unter der Maus
{
    if( mx >= gr.x )
        return -1;
    int hsBeg = ( horizontalScrollBar && hatStyle( Style::HScroll ) ) ? horizontalScrollBar->getScroll() : 0;
    mx += hsBeg;
    if( mx < 0 )
        return -1;
    int xx = rahmen ? rahmen->getRBreite() : 0;
    for( int i = 0; i < spaltenAnzahl; ++i )
    {
        xx += spaltenBreite->get( i );
        if( mx < xx - 5 )
            return i;
        if( mx < xx + 5 )
            return i + 0.5;
        xx += rasterBreite;
    }
    return -1;
}

Text *ObjTabelle::getMausSpaltenName( int mx ) const
{
    double tmp = getMausSpalte( mx );
    if( tmp != (int)tmp )
        return 0;
    return getSpaltenName( (int)tmp );
}

Text *ObjTabelle::zMausSpaltenName( int mx ) const
{
    double tmp = getMausSpalte( mx );
    if( tmp != (int)tmp )
        return 0;
    return zSpaltenName( (int)tmp );
}

double ObjTabelle::getMausZeile( int my ) const // ermittelt die Zeile unter der Maus
{
    if( my >= gr.y )
        return -1;
    if( my < 0 )
        return -1;
    int vsBeg = vertikalScrollBar && hatStyle( Style::VScroll ) ? vertikalScrollBar->getScroll() : 0;
    my += vsBeg;
    int yy = rahmen ? rahmen->getRBreite() : 0;
    for( int i = 0; i < zeilenAnzahl; ++i )
    {
        yy += zeilenH�he->get( i );
        if( my < yy - 5 )
            return i;
        if( my < yy + 5 )
            return i + 0.5;
        yy += rasterBreite;
    }
    return -1;
}

Text *ObjTabelle::getMausZeilenName( int my ) const
{
    double tmp = getMausZeile( my );
    if( tmp != (int)tmp )
        return 0;
    return getZeilenName( (int)tmp );
}

Text *ObjTabelle::zMausZeilenName( int my ) const
{
    double tmp = getMausZeile( my );
    if( tmp != (int)tmp )
        return 0;
    return zZeilenName( (int)tmp );
}

const Punkt &ObjTabelle::getAuswahlPosition() const // gibt die Auswahl Position zur�ck
{
    return selected;
}

int ObjTabelle::getRasterFarbe() const // gibt die Farbe des Rasters zur�ck
{
    return rasterFarbe;
}

int ObjTabelle::getRasterBreite() const // gibt die Breite des Rasters zur�ck
{
    return rasterBreite;
}

LRahmen *ObjTabelle::getARahmen() const // gibt den auswahl Rahmen zur�ck
{
    return aRam ? aRam->getThis() : 0;
}

LRahmen *ObjTabelle::zARahmen() const
{
    return aRam;
}

AlphaFeld *ObjTabelle::getAAlphaFeld() const // gibt das auswahl AlphaFeld zur�ck
{
    return aAf ? aAf->getThis() : 0;
}

AlphaFeld *ObjTabelle::zAAlphaFeld() const
{
    return aAf;
}

LRahmen *ObjTabelle::getARahmen( int sNum, int zNum ) const // gibt den auswahl Rahmen zur�ck
{
    RCArray< LRahmen > *tmp = msaRam->z( sNum );
    return tmp ? tmp->get( zNum ) : 0;
}

LRahmen *ObjTabelle::zARahmen( int sNum, int zNum ) const
{
    RCArray< LRahmen > *tmp = msaRam->z( sNum );
    return tmp ? tmp->z( zNum ) : 0;
}

AlphaFeld *ObjTabelle::getAAlphaFeld( int sNum, int zNum ) const // gibt das auswahl AlphaFeld zur�ck
{
    RCArray< AlphaFeld > *tmp = msaAf->z( sNum );
    return tmp ? tmp->get( zNum ) : 0;
}

AlphaFeld *ObjTabelle::zAAlphaFeld( int sNum, int zNum ) const
{
    return msaAf->z( sNum ) ? msaAf->z( sNum )->z( zNum ) : 0;
}

LRahmen *ObjTabelle::getARahmen( const char *spaltenName, const char *zeilenName ) const // gibt den auswahl Rahmen zur�ck
{
    return getARahmen( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

LRahmen *ObjTabelle::zARahmen( const char *spaltenName, const char *zeilenName ) const
{
    return zARahmen( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

AlphaFeld *ObjTabelle::getAAlphaFeld( const char *spaltenName, const char *zeilenName ) const // gibt das auswahl AlphaFeld zur�ck
{
    return getAAlphaFeld( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

AlphaFeld *ObjTabelle::zAAlphaFeld( const char *spaltenName, const char *zeilenName ) const
{
    return zAAlphaFeld( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

LRahmen *ObjTabelle::getARahmen( Text *spaltenName, Text *zeilenName ) const // gibt den auswahl Rahmen zur�ck
{
    return getARahmen( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

LRahmen *ObjTabelle::zARahmen( Text *spaltenName, Text *zeilenName ) const
{
    return zARahmen( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

AlphaFeld *ObjTabelle::getAAlphaFeld( Text *spaltenName, Text *zeilenName ) const // gibt das auswahl AlphaFeld zur�ck
{
    return getAAlphaFeld( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

AlphaFeld *ObjTabelle::zAAlphaFeld( Text *spaltenName, Text *zeilenName ) const
{
    return zAAlphaFeld( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ) );
}

bool ObjTabelle::hatMsStyle( int sNum, int zNum, __int64 style ) const // pr�ft, ob style vorhanden ist
{
    __int64 s = styles->z( sNum ) && styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0;
    return ( s | style ) == s;
}

bool ObjTabelle::hatMsStyleNicht( int sNum, int zNum, __int64 style ) const // pr�ft, ob style nicht vorhanden ist
{
    __int64 s = styles->z( sNum ) && styles->z( sNum )->hat( zNum ) ? styles->z( sNum )->get( zNum ) : 0;
    return ( s | style ) != s;
}

bool ObjTabelle::hatMsStyle( const char *spaltenName, const char *zeilenName, __int64 style ) const // pr�ft, ob style vorhanden ist
{
    return hatMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

bool ObjTabelle::hatMsStyleNicht( const char *spaltenName, const char *zeilenName, __int64 style ) const // pr�ft, ob style nicht vorhanden ist
{
    return hatMsStyleNicht( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

bool ObjTabelle::hatMsStyle( Text *spaltenName, Text *zeilenName, __int64 style ) const // pr�ft, ob style vorhanden ist
{
    return hatMsStyle( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

bool ObjTabelle::hatMsStyleNicht( Text *spaltenName, Text *zeilenName, __int64 style ) const // pr�ft, ob style nicht vorhanden ist
{
    return hatMsStyleNicht( getSpaltenNummer( spaltenName ), getZeilenNummer( zeilenName ), style );
}

Zeichnung *ObjTabelle::dublizieren() const // Erzeugt eine Kopie des Zeichnungs
{
    ObjTabelle *obj = new ObjTabelle();
    obj->setPosition( pos );
    obj->setGr��e( gr );
    obj->setMausEreignisParameter( makParam );
    obj->setTastaturEreignisParameter( takParam );
    obj->setMausEreignis( Mak );
    obj->setTastaturEreignis( Tak );
    if( toolTip )
        obj->setToolTipText( toolTip->zText()->getText(), toolTip->zBildschirm() );
    obj->setStyle( style );
    if( rahmen )
        obj->setLinienRahmenZ( (LRahmen*)rahmen->dublizieren() );
    obj->setHintergrundFarbe( hintergrundFarbe );
    if( hintergrundBild )
        obj->setHintergrundBild( hintergrundBild->getThis() );
    if( hintergrundFeld )
        obj->setAlphaFeldZ( (AlphaFeld*)hintergrundFeld->dublizieren() );
    obj->setRasterFarbe( rasterFarbe );
    obj->setRasterBreite( rasterBreite );
    if( aRam )
        obj->setARahmenZ( (LRahmen*)aRam->dublizieren() );
    if( aAf )
        obj->setAAlphaFeldZ( (AlphaFeld*)aAf->dublizieren() );
    for( int s = 0; s < spaltenAnzahl; ++s )
    {
        obj->addSpalte( spaltenNamen->get( s ) );
        if( spaltenBreite->hat( s ) )
            obj->setSpaltenBreite( s, spaltenBreite->get( s ) );
        if( minSpaltenBreite->hat( s ) )
            obj->setMinSpaltenBreite( s, minSpaltenBreite->get( s ) );
        if( maxSpaltenBreite->hat( s ) )
            obj->setMaxSpaltenBreite( s, maxSpaltenBreite->get( s ) );
        for( int z = 0; z < zeilenAnzahl; ++z )
        {
            if( !s )
            {
                obj->addZeile( zeilenNamen->get( z ) );
                if( zeilenH�he->hat( z ) )
                    obj->setZeilenH�he( z, zeilenH�he->get( z ) );
                if( minZeilenH�he->hat( z ) )
                    obj->setMinZeilenH�he( z, minZeilenH�he->get( z ) );
                if( maxZeilenH�he->hat( z ) )
                    obj->setMaxZeilenH�he( z, maxZeilenH�he->get( z ) );
            }
            if( zZeichnungs->z( s ) && zZeichnungs->z( s )->hat( z ) )
                obj->setZeichnungZ( s, z, zZeichnungs->z( s )->get( z ) );
            if( styles->z( s ) && styles->z( s )->hat( z ) )
                obj->setMsStyle( s, z, styles->z( s )->get( z ) );
            if( msaRam->z( s ) && msaRam->z( s )->z( z ) )
                obj->setARahmenZ( s, z, (LRahmen*)msaRam->z( s )->z( z )->dublizieren() );
            if( msaAf->z( s ) && msaAf->z( s )->z( z ) )
                obj->setAAlphaFeldZ( s, z, (AlphaFeld*)msaAf->z( s )->z( z )->dublizieren() );
        }
    }
    obj->setAuswahl( selected.x, selected.y );
    return obj;
}

// Reference Counting
ObjTabelle *ObjTabelle::getThis()
{
    ++ref;
    return this;
}

ObjTabelle *ObjTabelle::release()
{
    --ref;
    if( !ref )
        delete this;
    return 0;
}