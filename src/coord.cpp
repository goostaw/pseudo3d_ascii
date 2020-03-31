#include "coord.h"

bool Coord::operator== ( Coord &c )
{
	return y == c.y && x == c.x;
}
bool Coord::operator>= ( int a )
{
	return y >= a && x >= a ;
}
bool Coord::operator<= ( int a )
{
	return y <= a && x <= a;
}
bool Coord::operator< ( Coord & c )
{
	return y < c.y && x < c.x;
}
Coord & Coord::operator+= ( Coord & ob )
{
	this->y += ob.y;
	this->x += ob.x;
	return * this;
}
Coord Coord::operator& ( Coord  ob )
{
	Coord suma;
	suma.y = this->y + ob.y;
	suma.x = this->x + ob.x;
	return suma;
}

Coord Coord::operator+ ( Coord & ob )
{
	Coord suma;
	suma.y = this->y + ob.y;
	suma.x = this->x + ob.x;
	return suma;
}
Coord Coord::operator+ ( int i )
{
	Coord suma;
	suma.y = this->y + i;
	suma.x = this->x + i;
	return suma;
}

Coord Coord::TurnR90()
{
	Coord t;
	t.y = this->x;
	t.x = this->y * ( -1 );
	return t;
}
// global overloads
istream& operator>> ( istream& fi, Coord& cr )
{
	fi >> cr.y >> cr.x;
	return fi;
}
