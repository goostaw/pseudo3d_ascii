#ifndef Map_h
#define Map_h

#include "coord.h"
#include "tile.h"
#include "array.h"
#include <iostream>
#include <curses.h>

using namespace std;
class Map
{
	Coord _size;
	Coord _position;
	Tile*** _pTileArray;
	Array<Coord> _freePos;
	void createTileArray();

  public:
	Map() : _pTileArray( NULL ) {}
	Map( int, int, int = 0, int = 0 );
	~Map();
	Coord getSize() { return _size; }
	Coord getPos() { return _position; }
	Tile*** getTileArray() { return _pTileArray; }
	Array<Coord>& getFreePos();
	bool is_within( Coord );

	void init();
//	chtype stepOn( Coord, chtype );

	Tile** operator[] ( int y ) { return _pTileArray[ y ]; }
	friend istream& operator>> ( istream&, Map& );
};

#endif // Map_h
