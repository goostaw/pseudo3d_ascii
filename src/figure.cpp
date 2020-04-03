#include "figure.h"
#include "array.h"
#include <stdlib.h>

Coord Figure::initRandPos()
{
	if ( &_map )
	{
		Array<Coord>& f = _map.getFreePos();
		if ( f.size() )
		{
			_pos = f.at( rand() % f.size() );
			_memory = _map[_pos.y][_pos.x]->ch;
			return _pos;
		}
		else return Coord( 0, 0 );
	}
	else return Coord( 0, 0 );
}
