#ifndef figure_h
#define figure_h

#include <curses.h>
#include "map.h"
#include "coord.h"

class Figure
{
  protected:
	Coord _pos;
	chtype _memory;
	Map& _map;
  public:
	Figure( Map& m ) : _map( m ) {}
	virtual ~Figure(){}
	Coord getPos(){ return _pos; }
	Coord initRandPos();
	virtual void iconOnMap(){}
	virtual int sprTabIndex(){ return - 1; }
	virtual int color(){ return 0; }
};

#endif // figure_h
