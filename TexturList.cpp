#include "TexturList.h"
#include "Textur.h"
#include "Text.h"

using namespace Framework;

int TexturList::id = 0;
CRITICAL_SECTION TexturList::cs;

// Inhalt der TexturList Klasse
// Konstruktor
TexturList::TexturList()
{
    textures = new RCArray< Textur >();
    names = new RCArray< Text >();
    ref = 1;
}

// Destruktor
TexturList::~TexturList()
{
    textures->release();
    names->release();
}

// F�gt der Liste eine Textur hinzu
//  t: Die Textur
//  name: Der name, unter dem die Textur in der Liste gespeichert wird
bool TexturList::addTextur( Textur *t, const char *name )
{
    EnterCriticalSection( &cs );
    for( auto i = names->getArray(); i.set; i++ )
    {
        if( i.var->istGleich( name ) )
        {
            t->release();
            LeaveCriticalSection( &cs );
            return 0;
        }
    }
    t->id = id++;
    textures->add( t );
    names->add( new Text( name ) );
    LeaveCriticalSection( &cs );
    return 1;
}

// Entfernt eine Textur aus der Liste
//  name: Der Name der Textur
void TexturList::removeTextur( const char *name )
{
    EnterCriticalSection( &cs );
    int index = 0;
    for( auto i = names->getArray(); i.set; i++ )
    {
        if( i.var->istGleich( name ) )
        {
            names->remove( index );
            textures->remove( index );
            LeaveCriticalSection( &cs );
            return;
        }
        index++;
    }
    LeaveCriticalSection( &cs );
}

// �berpr�ft, ob unter einem bestimmten Namen eine Textur abgespeichert wurde
//  name: Der Name
//  return: true, wenn eine Textur mit dem Namen existiert
bool TexturList::hatTextur( const char *name ) const
{
    EnterCriticalSection( &cs );
    for( auto i = names->getArray(); i.set; i++ )
    {
        if( i.var->istGleich( name ) )
        {
            LeaveCriticalSection( &cs );
            return 1;
        }
    }
    LeaveCriticalSection( &cs );
    return 0;
}

// Gibt eine bestimmte Textur zur�ck
//  name: Der Name der Textur
Textur *TexturList::getTextur( const char *name ) const
{
    EnterCriticalSection( &cs );
    int index = 0;
    for( auto i = names->getArray(); i.set; i++ )
    {
        if( i.var->istGleich( name ) )
        {
            LeaveCriticalSection( &cs );
            return textures->get( index );
        }
        index++;
    }
    LeaveCriticalSection( &cs );
    return 0;
}

// Gibt eine bestimmte Textur zur�ck
//  id: Die Id der Textur
Textur *TexturList::getTextur( int id ) const
{
    EnterCriticalSection( &cs );
    for( auto i = textures->getArray(); i.set; i++ )
    {
        if( i.var->getId() == id )
        {
            LeaveCriticalSection( &cs );
            return i.var->getThis();
        }
    }
    LeaveCriticalSection( &cs );
    return 0;
}

// Gibt eine bestimmte Textur ohne erh�hten Reference Counter zur�ck
//  name: Der Name der Textur
Textur *TexturList::zTextur( const char *name ) const
{
    EnterCriticalSection( &cs );
    int index = 0;
    for( auto i = names->getArray(); i.set; i++ )
    {
        if( i.var->istGleich( name ) )
        {
            LeaveCriticalSection( &cs );
            return textures->z( index );
        }
        index++;
    }
    LeaveCriticalSection( &cs );
    return 0;
}

// Gibt eine bestimmte Textur ohne erh�hten Reference Counter zur�ck
//  id: Die Id der Textur
Textur *TexturList::zTextur( int id ) const
{
    EnterCriticalSection( &cs );
    for( auto i = textures->getArray(); i.set; i++ )
    {
        if( i.var->getId() == id )
        {
            LeaveCriticalSection( &cs );
            return i.var;
        }
    }
    LeaveCriticalSection( &cs );
    return 0;
}

// Erh�ht den Reference Counting Z�hler.
//  return: this.
TexturList *TexturList::getThis()
{
    ref++;
    return this;
}

// Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Zeichnung automatisch gel�scht.
//  return: 0.
TexturList *TexturList::release()
{
    ref--;
    if( !ref )
        delete this;
    return 0;
}

// statische Funktionen

// Initialisiert statische private member. Wird vom Framework automatisch aufgerufen.
void TexturList::init()
{
    id = 0;
    InitializeCriticalSection( &cs );
}

// L�scht statische private member. Wird vom Framework automatisch aufgerufen.
void TexturList::destroy()
{
    DeleteCriticalSection( &cs );
}