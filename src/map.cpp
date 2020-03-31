#include "map.h"

Map::Map( int sy, int sx, int py, int px )
		: _size( sy, sx ), _position( py, px )
{
	_createTileArray();
}
Map::~Map()
{
	for ( int y = 0; y < _size.y; y++ )
	{
		for ( int x = 0; x < _size.x; x++ )
		{
			delete _tileArray[y][x];
		}
		delete [] _tileArray[y];
	}
	delete [] _tileArray;
}
void Map::_createTileArray()
{
	_tileArray = new Tile** [ _size.y ];
	for ( int y = 0; y < _size.y; y++ )
	{
		_tileArray[ y ] = new Tile*[ _size.x ];
	}
}
Bag<Coord>& Map::getFreePos()
{
	_freePos.clear();

	for ( int y = 0; y < _size.y; y++ )
	{
		for ( int x = 0; x < _size.x; x++ )
		{
			if ( ( _tileArray[y][x]->ch & A_CHARTEXT  ) == '.' )
			{
				_freePos.push_back( Coord( y, x ) );
			}
		}
	}
	return _freePos;
}
void Map::init()
{
	ifstream fi("data/m1.dat");
	if ( fi.good() )
	{
		fi >> *this;
	}
	fi.close();
}
bool Map::is_within( Coord c )
{
	return c >= 0 && c < _size;
}
/*
chtype Map::stepOn( Coord c, chtype ch )
{
	chtype previous = _tileArray[c.y][c.x]->ch;
	_tileArray[c.y][c.x]->ch = ch;
	return previous;
	
}
*/
// global operator overloads
istream& operator>> ( istream& i, Map& m )
{
	i >> m._size.y >> m._size.x >> m._position.y >> m._position.x;
//	char linefeed;
//	i.get( linefeed );
	if ( !m._tileArray ) m._createTileArray();
	
	char* temp = new char[m._size.x + 1]; // + 1  miejsce na 0
	
	i.getline( temp, m._size.x + 2 );// znaki do konca lini do kosza
	for ( int y = 0; y < m._size.y; y++ )
	{
		i.getline( temp, m._size.x + 2 ); //  + 1 coby linefeed zadzialal
		for ( int x = 0; x < m._size.x; x++ )
		{
			Tile* &t = m._tileArray[y][x];
			switch ( temp[x] )
			{
				case '.': t = new Floor; break;
				case '#': t = new Wall; break;
				case '+': t = new Door;	t->is_open = false; break;
				case '/': t = new Door; t->is_open = true; break;
				default: t = new Floor;
			}
			t->ch = temp[x];
		}
	}
	delete []temp;
	return i;
}

