#ifndef tile_h
#define tile_h

#include <curses.h>

class Tile
{
  public:
	Tile(){}
	Tile( bool isOpen ) : is_open( isOpen ){}
	virtual ~Tile(){}
	chtype ch;
	bool is_m; // is visible in fov memory
	bool is_k; // is known
	bool is_open;
	virtual bool Switch(){ return false; }
	virtual int sprTabIndex(){ return -1; }
};
// ===
class Floor: public Tile
{
  public:
	Floor() { is_m = FALSE; }
};
// ===
class Wall: public Tile
{
  public:
	Wall() { is_m = TRUE; }
	virtual int sprTabIndex(){ return 0; }
};
// ===
class Door: public Tile
{
  public:
	Door() { is_m = FALSE; }
	Door( bool isOpen ) : Tile( isOpen ){}
	virtual bool Switch();
	virtual int sprTabIndex(){ if( is_open ) return 2; else return 1; }
};
#endif // tile_h
