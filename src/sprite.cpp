#include "sprite.h"
#include "cstring"

// s t r i p e
Stripe::Stripe( char* ch )
{
	_lenght = strlen( ch );
	_pText = strcpy( new char[ _lenght + 1 ], ch );
}
Stripe::~Stripe()
{
	if ( _pText ) delete []_pText;
	_pText = NULL;
}

// s p r i t e
Sprite::~Sprite()
{
	 if ( _pStripe ) delete [] _pStripe;
}

// g l o b a l    o v e r l o a d s
istream& operator>> ( istream& fi, Stripe& sp )
{
	char cudzyslow;
	char a[56]; // tylko do wczytania z pliku
	fi >> cudzyslow; // smiec
	fi.getline( a, 56, '"' ); // wczytuje do znaku "
	sp._lenght = strlen( a ); // ilosc bajtow w c stringu
	sp._pText = strcpy( new char[ sp._lenght + 1 ], a ); 
	fi >> sp._crd;
	return fi;
}
// --
istream& operator>> ( istream& fi, Sprite& sp )
{
	fi >> sp._height;

	if( sp._height )
	{
		sp._pStripe = new Stripe[ sp._height ];
		for ( int i = 0; i < sp._height; i++ )
		{
			fi >> sp._pStripe[i];
		}
	}
	return fi;
}	
