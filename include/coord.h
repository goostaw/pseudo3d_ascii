#ifndef coord_h
#define coord_h

#include <iostream>
#include <fstream>

using namespace std;

class Coord
{
  public:
	Coord(){}
	Coord( int a, int b ) : y( a ), x( b ) {}
	int y;
	int x;
	bool operator== ( Coord & );
	bool operator>= ( int );
	bool operator<= ( int );
	bool operator< ( Coord & );
	Coord & operator+= ( Coord & );
	Coord operator& ( Coord );
	Coord operator+ ( Coord & );
	Coord operator+ ( int );
	Coord TurnR90();
};

extern istream& operator>> ( istream&, Coord& );

class Dcoord
{
	public:
	Coord a;
	Coord b;
};

class Icoord
{
    public:
    	int i;
	Coord c;
};
#endif
