#ifndef hero_h
#define hero_h

#include "coord.h"
#include "figure.h"
#include "map.h"
#include "bag.h"
#include <curses.h>

class Hero : public Figure
{
	int _facing;
	Bag<Dcoord> _tempFov;
	Bag<Dcoord> _fov;
	Bag<Coord> _fovMemory;
	void _initFov();
	void _initVeil();
	void _updateFov();

  public:
	Hero( Map& );

	static chtype icon[4];
	static Coord movc[4];
	static Bag< Bag<Coord> > rov [4]; // range of view
	static int dov; // depth of view
	static int wov[ 5 ]; // width of view
	static Bag<int> veil[13];
	static void initRov();

	int getFacing(){ return _facing; }
	Bag<Dcoord>& getFov(){ return _fov; }
	Bag<Coord>& getFovMemory(){ return _fovMemory; }
	void iconOnMap();
	void TurnRight();
	void TurnLeft();
	void TurnBack();
	void Move();
	bool isLegal( char );
	void Door();
};

#endif // hero_h
