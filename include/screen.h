#ifndef screen_h
#define screen_h

#include <curses.h>
#include "coord.h"
#include "map.h"
#include "hero.h"
#include "bag.h"
#include "sprite.h"
#include "figure.h"

class Screen
{
	WINDOW* _p2d;
	WINDOW* _p3d;
	Map* _pMap;
	Hero* _pHero;
	Bag< Figure* > &_monsters;
	Bag< Bag< Bag< Sprite > > > _tileSprites;
	Bag< Bag< Bag< Sprite > > > _figureSprites;

	void updatePrevFov();
	void initSprites( const char*, Bag< Bag< Bag< Sprite > > >& , int );
	void printSprite( Sprite&, int = 0 );
	
  public:
	const static int tileTabSize = 3;
	const static int figureTabSize = 1;

	Screen( Map*, Hero*, Bag< Figure* >& );
	~Screen();
	void update();
	void help();
	void firstRunInfo();
	int waitOnKey(){ return wgetch( _p2d ); }
};


#endif // screen_h
