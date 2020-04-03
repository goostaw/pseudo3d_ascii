#ifndef hero_h
#define hero_h

#include "coord.h"
#include "figure.h"
#include "map.h"
#include "array.h"
#include <curses.h>

class Hero : public Figure
{
	enum Direction { NORTH, EAST, SOUTH, WEST } _facing;
	Array<Dcoord> _tempFov;
	Array<Dcoord> _fov;
	Array<Coord> _fovMemory;
	void initFov();
	void initVeil();
	void updateFov();

  public:
	Hero( Map& );

	static Direction dirTab[4];
	static chtype icon[4];
	static Coord movc[4];
	static Array< Array<Coord> > rov [4]; // range of view
	static int dov; // depth of view
	static int wov[ 5 ]; // width of view
	static Array<int> veil[13];
	static void initRov();

	Direction getFacing(){ return _facing; }
	Array<Dcoord>& getFov(){ return _fov; }
	Array<Coord>& getFovMemory(){ return _fovMemory; }
	void iconOnMap();
	void TurnRight();
	void TurnLeft();
	void TurnBack();
	void Move();
	bool isLegal( char );
	void Door();
};

#endif // hero_h
