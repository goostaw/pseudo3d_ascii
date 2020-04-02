#include "hero.h"
#include "bag.h"
#include <stdlib.h>
//#include <time.h>

// static
Hero::Direction Hero::dirTab[4] = { NORTH, EAST, SOUTH, WEST };
int Hero::dov = 5;
chtype Hero::icon[4] = { '^', '>', 'v', '<' };
Coord Hero::movc[4] = { Coord( -1, 0 ),	Coord( 0, 1 ),
			Coord( 1, 0 ),	Coord( 0, -1 ) };
Bag< Bag<Coord> > Hero::rov[4];
int Hero::wov[5] = { 5, 5, 3, 3, 3 };
Bag<int> Hero::veil[13];
// ------
Hero::Hero( Map& m ) : Figure( m )
{
	initRandPos();
	_facing = dirTab[ rand() % 4 ];
	initRov();
	initVeil();
	initFov();
}
void Hero::initRov()
{
	for ( int i = 0; i < 4; i++ )
	{
		rov[i].resize( dov );
		for ( int y = 0; y < dov; y++ )
		{
			rov[i][y].resize( wov[y] );
			for ( int x = 0; x < wov[ y ]; x++ )
			{
				if( !i )
				{
					rov[i].at(y).at(x) = Coord( y - 4, x - wov[y] / 2 );
				}
				else
				{
					Coord temp = rov[i-1][y][x];
					rov[i][y][x] = temp.TurnR90();
				}
			}
		}
	}
}
void Hero::iconOnMap()
{
	_map[_pos.y][_pos.x]->ch = icon[ _facing ];
}
void Hero::TurnRight()
{
	if ( _facing < 3 )	_facing = dirTab[ _facing + 1 ];
	else _facing = NORTH;
	updateFov();
}
void Hero::TurnLeft()
{
	if ( _facing ) _facing = dirTab[ _facing - 1 ];	
	else _facing = WEST;	
	updateFov();
}
void Hero::TurnBack()
{
	if ( _facing < 2 ) _facing = dirTab[ _facing + 2 ];
	else _facing = dirTab[ _facing - 2 ];
	updateFov();
}
void Hero::Move()
{
	Coord t = _pos + movc[_facing];
	chtype &ch = _map[t.y][t.x]->ch;
	if ( isLegal( ch & A_CHARTEXT ) )
	{
		_map[_pos.y][_pos.x]->ch = _memory;
		_memory = ch;
		_pos = t;
		updateFov();
	}
}
bool Hero::isLegal( char ch )
{
	return ch!= '#' &&	ch != '+';
}
void Hero::Door()
{
	Coord c = _pos + movc[_facing];
	Tile* &t = _map[c.y][c.x];
	if ( t->Switch() ) // polimorfic
	{
		t->is_open ? t->ch = '/': t->ch = '+';
		updateFov();
	}
}
void Hero::initFov()
{
	int s = 0;
	for ( int i = 0; i < dov; i++ )
	{
		s += wov[dov];
	}
	_fov.resize( s );
	_fovMemory.resize( s );
	_tempFov.resize( s );
	updateFov();
}
void Hero::updateFov()
{
	iconOnMap();
	_tempFov.roll_down();
	_fov.roll_down();
	int y;
	Coord idx;
	Dcoord dc;
	for ( y = 0; y < dov; y++ )
	{
		idx.y = y;
		for ( int xs = 0, xe = wov[y] - 1; xs <= wov[y] / 2; xs++, xe-- )
		{
			dc.a = _pos + rov[_facing][y][xs];
			idx.x = xs;	
			dc.b = idx;
			_tempFov.push_back( dc );
			if ( xe != xs )
			{
				dc.a = _pos + rov[_facing][y][xe];
				idx.x = xe;	
				dc.b = idx;
				_tempFov.push_back( dc );
			}
		}
	}
	bool vis = true;
	Coord t;
	int s, d;
	for ( y = 0; y < _tempFov.size(); y++ )
	{
		dc = _tempFov[y];
		if ( _map.is_within( dc.a ) )
		{
			if ( y < 13 )
			{
				s = veil[y].size();
				for ( int v = 0; v < s; v++ )
				{
					d = veil[y][v];
					t = _tempFov[d].a;
					char ch = _map[t.y][t.x]->ch & A_CHARTEXT;
					if ( (ch == '#' ) || ( ch == '+' ) )
					{
						vis = false;
						v = s - 1;
					}
				}
				if ( vis )	_fov.push_back( dc );
				else vis = true;
			}
			else _fov.push_back( dc );
		}
	}
}
void Hero::initVeil()
{
	int fovIndex[] =
		{	15, 10, 7,
			15, 11, 8,
			15, 12, 7,
			15, 12, 8,
			15, 9, 12,
			15, 10,
			15, 11,
			15, 12,
			15, 12,
			15, 12,
			15,
			15,
			15 };

	for ( int i = 0, s = 4, f = 0; i < 13; i++ )
	{
		if ( !(i % 5) ) s--;
		veil[i].resize(s);
		for ( int v = 0; v < veil[i].capacity(); v++ )
		{
			veil[i].push_back( fovIndex[ f++ ] );
		}
	}
}
