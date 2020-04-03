#ifndef game_h
#define game_h

#include "screen.h"
#include "map.h"
#include "hero.h"
#include "array.h"
#include "sprite.h"
#include "figure.h"

class Game
{
	Screen* _pScr;
	Map* _pMap;
	Hero* _pHero;
	Array<Figure*> _monsters;
	
	void initMonsters();

  public:
	Game();
	~Game();
	void loop();
};

#endif // game_h
