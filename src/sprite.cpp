#include "sprite.h"
#include "cstring"

// s t r i p e
Stripe::Stripe( char* ch )
{
	_lenght = strlen( ch );
	_text = strcpy( new char[ _lenght + 1 ], ch );
}
Stripe::~Stripe()
{
	if ( _text ) delete []_text;
	_text = NULL;
}

// s p r i t e
Sprite::~Sprite()
{
	 if ( _stripePtr ) delete [] _stripePtr;
}

// g l o b a l    o v e r l o a d s
istream& operator>> ( istream& fi, Stripe& sp )
{
	char cudzyslow;
	char a[56]; // tylko do wczytania z pliku
	fi >> cudzyslow; // smiec
	fi.getline( a, 56, '"' ); // wczytuje do znaku "
	sp._lenght = strlen( a ); // ilosc bajtow w c stringu
	sp._text = strcpy( new char[ sp._lenght + 1 ], a ); 
	fi >> sp._crd;
	return fi;
}
// --
istream& operator>> ( istream& fi, Sprite& sp )
{
	fi >> sp._height;

	if( sp._height )
	{
		sp._stripePtr = new Stripe[ sp._height ];
		for ( int i = 0; i < sp._height; i++ )
		{
			fi >> sp._stripePtr[i];
		}
	}
	return fi;
}	
