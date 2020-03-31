#ifndef Map_h
#define Map_h

#include "coord.h"
#include "tile.h"
#include "bag.h"
#include <iostream>
#include <curses.h>

using namespace std;
class Map
{
	Coord _size;
	Coord _position;
	Tile*** _tileArray;
	Bag<Coord> _freePos;
	void _createTileArray();

  public:
	Map() : _tileArray( NULL ) {}
	Map( int, int, int = 0, int = 0 );
	~Map();
	Coord getSize() { return _size; }
	Coord getPos() { return _position; }
	Tile*** getTileArray() { return _tileArray; }
	Bag<Coord>& getFreePos();
	bool is_within( Coord );

	void init();
//	chtype stepOn( Coord, chtype );

	Tile** operator[] ( int y ) { return _tileArray[ y ]; }
	friend istream& operator>> ( istream&, Map& );
};

#endif // Map_h
