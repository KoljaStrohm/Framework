#ifndef DreieckListe_H
#define DreieckListe_H

#include "Punkt.h"
#include "Array.h"

namespace Framework
{
	template< typename T >
    // Eine Ecke eines Dreiecks
	struct DreieckPunkt
	{
		T *punkt;
		Punkt *textur;
        // Konstruktor
        //  punkt: Die Koordinate der Ecke
        //  textur: Die Koordinate in der Textur
        DreieckPunkt( T *punkt, Punkt *textur )
        {
            this->punkt = punkt;
            this->textur = textur;
        }
		// Destruktor
		~DreieckPunkt()
		{
			delete punkt;
			delete textur;
		}
	};

	template< typename T >
    // Eine Liste von Dreiecken, wobei immer die Beiden letzten Punkte des vorheriegen Dreiecks mit dem n�chsten Punkt ein neues Dreieck bilden
	class DreieckListe
	{
	private:
		Array< DreieckPunkt< T >* > *punkte;
		int ref;

	public:
		// Konstruktor
		DreieckListe()
		{
			ref = 1;
			punkte = new Array< DreieckPunkt< T >* >();
		}

		// Destruktor
		~DreieckListe()
		{
			int anz = punkte->getEintragAnzahl();
			for( int i = 0; i < anz; i++ )
				delete punkte->get( i );
			punkte->release();
		}

		// F�gt der Liste einen Punkt hinzu
        //  p: Die Koordinaten des Punktes
        //  textur: Die Koordinaten in der Textur
		void addPunkt( T *p, Punkt *textur )
		{
			punkte->add( new DreieckPunkt< T >( p, textur ) );
		}

        // L�scht den letzten Punkt
		void l�scheLetztenPunkt()
		{
			int i = punkte->getEintragAnzahl() - 1;
			if( !punkte->hat( i ) )
				return;
			delete punkte->get( i );
			punkte->l�sche( i );
		}

        // L�scht alle Ecken
		void lehren()
		{
			int anz = punkte->getEintragAnzahl();
			for( int i = 0; i < anz; i++ )
				delete punkte->get( i );
			punkte->leeren();
		}

		// gibt die Anzahl der Dreiecke zur�ck
		int getDreieckAnzahl() const
		{
			return punkte->getEintragAnzahl() - 2;
		}

        // Gibt zur�ck, ob eine Textur verwendet wird
		bool hatTextur() const
		{
			int anz = punkte->getEintragAnzahl();
			bool ret = 1;
			for( int i = 0; i < anz; i++ )
			{
				if( punkte->hat( i ) )
				    ret &= punkte->get( i )->textur;
			}
			return ret;
		}

        // Gibt die Liste mit Punkten zur�ck
		Array< DreieckPunkt< T >* > *zListe() const
		{
			return punkte;
		}

        // Erh�ht den Reference Counting Z�hler.
        //  return: this.
		DreieckListe *getThis()
		{
			ref++;
			return this;
		}

        // Verringert den Reference Counting Z�hler. Wenn der Z�hler 0 erreicht, wird das Objekt automatisch gel�scht.
        //  return: 0.
		DreieckListe *release()
		{
			ref--;
			if( !ref )
				delete this;
			return 0;
		}
	};
}

#endif