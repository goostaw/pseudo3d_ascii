#ifndef game_h
#define game_h

#include "screen.h"
#include "map.h"
#include "hero.h"
#include "bag.h"
#include "sprite.h"
#include "figure.h"

class Game
{
	Screen* _scr;
	Map* _map;
	Hero* _hero;
	Bag<Figure*> _monsters;
	
	void _initMap();
	void _initMonsters();

  public:
	Game();
	~Game();
	void loop();
};

#endif // game_h
