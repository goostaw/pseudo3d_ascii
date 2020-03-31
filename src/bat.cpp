#include "bat.h"

void Bat::iconOnMap()
{
	_map[_pos.y][_pos.x]->ch = 'B' | COLOR_PAIR( 2 );
}
Bat::Bat( Map& m ) : Figure( m )
{
}
