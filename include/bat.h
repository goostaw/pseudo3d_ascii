#ifndef bat_h
#define bat_h

#include "figure.h"
#include <curses.h>

class Bat : public Figure
{
	public:
	Bat( Map& m );
	virtual void iconOnMap();
	virtual int sprTabIndex(){ return 0; }
	virtual int color(){ return 2; }
};

#endif // bat_h
