#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "bat.h"

using namespace std;
Game::Game()
{
	srand( time( NULL ) );

	_map = new Map;
	_map->init();
	_hero = new Hero( *_map );
	_initMonsters();
	_scr = new Screen( _map, _hero, _monsters );
}
Game::~Game()
{
	delete _scr;
	delete _hero;
	delete _map;
	for ( int i = 0; i < _monsters.size(); i++ ) delete _monsters[i];
}
void Game::_initMonsters()
{
	int size = rand() % 7 + 1;
	 _monsters.resize( size );

	for ( int i = 0; i < size; i++ )
	{
		_monsters[i] = new Bat( *_map );
		_monsters[i]->initRandPos();
		_monsters[i]->iconOnMap();
	}
}
void Game::loop()
{	
	_scr->update();
	_scr->firstRunInfo();
	
	int w = 0;
	while ( w != 'q' )
	{
		w = _scr->waitOnKey();
		switch ( w )
		{
			case KEY_LEFT:	_hero->TurnLeft(); break;
			case KEY_RIGHT:	_hero->TurnRight(); break;
			case KEY_UP:	_hero->Move(); break;
			case KEY_DOWN:	_hero->TurnBack(); break;
			case 'd':		_hero->Door(); break;
			case 'h':	_scr->help(); break;
		}
		_scr->update();
	}
}
