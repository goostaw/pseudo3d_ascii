#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "bat.h"

using namespace std;
Game::Game()
{
	srand( time( NULL ) );

	_pMap = new Map;
	_pMap->init();
	_pHero = new Hero( *_pMap );
	initMonsters();
	_pScr = new Screen( _pMap, _pHero, _monsters );
}
Game::~Game()
{
	delete _pScr;
	delete _pHero;
	delete _pMap;
	for ( int i = 0; i < _monsters.size(); i++ ) delete _monsters[i];
}
void Game::initMonsters()
{
	int size = rand() % 7 + 1;
	 _monsters.resize( size );

	for ( int i = 0; i < size; i++ )
	{
		_monsters[i] = new Bat( *_pMap );
		_monsters[i]->initRandPos();
		_monsters[i]->iconOnMap();
	}
}
void Game::loop()
{	
	_pScr->update();
	_pScr->firstRunInfo();
	
	int w = 0;
	while ( w != 'q' )
	{
		w = _pScr->waitOnKey();
		switch ( w )
		{
			case KEY_LEFT:	_pHero->TurnLeft(); break;
			case KEY_RIGHT:	_pHero->TurnRight(); break;
			case KEY_UP:	_pHero->Move(); break;
			case KEY_DOWN:	_pHero->TurnBack(); break;
			case 'd':		_pHero->Door(); break;
			case 'h':	_pScr->help(); break;
		}
		_pScr->update();
	}
}
