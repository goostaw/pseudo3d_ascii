#ifndef sprite_h
#define sprite_h

#include <iostream>
#include <fstream>
#include "coord.h"

using namespace std;

class Sprite;

class Stripe
{
	char * _text;
	int _lenght;
	Coord _crd;

  public:
	Stripe(){}
	Stripe( char* ch );
	~Stripe();
	char* getText(){ return _text; }
//	int getLenght(){ return _lenght; }
	Coord getCrd(){ return _crd; }

	friend class Sprite;
	friend istream& operator>> ( istream&, Stripe& );
};
class Sprite
{
	Stripe* _stripePtr;
	int _height;

  public:
	Sprite() : _stripePtr( NULL ), _height( 0 ){}
	~Sprite();
	int getHeight(){ return _height; }
	Stripe* getPtr() { return _stripePtr; }
	
	friend istream& operator>> ( istream&, Sprite& );
};

#endif //sprite_h
