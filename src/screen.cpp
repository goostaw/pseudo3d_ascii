#include "screen.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstring>

Screen::Screen( Map* m, Hero* h, Array< Figure* >& f )
	: _pMap( m ), _pHero( h ), _monsters( f )
{
	// curses init ----
	initscr();
	resizeterm( 25, 80 );
	cbreak();
	noecho();
	curs_set( 0 );
	leaveok( stdscr, TRUE );
	start_color();
	init_pair( 1, COLOR_GREEN, COLOR_BLUE );
	init_pair( 2, COLOR_RED, COLOR_BLACK );
	init_pair( 3, COLOR_BLUE, COLOR_BLACK );
	// ----------------
	Coord s = m->getSize();
	Coord p = m->getPos();
	// 2d
	_p2d = newwin( s.y, s.x, p.y, p.x );
	leaveok( _p2d, TRUE );
	keypad( _p2d, TRUE );
	// 3d
	_p3d = newwin( 19, 57, 1, 20 );
	box( _p3d, 0 , 0 );
	leaveok( _p3d, TRUE );
	// -------------
	initSprites( "data/tiles.dat", _tileSprites, tileTabSize );
	initSprites( "data/figures.dat", _figureSprites, figureTabSize );
}
Screen::~Screen()
{
	delwin( _p3d );
	delwin( _p2d );
	endwin();
}
void Screen::initSprites( const char* nm, Array< Array< Array<Sprite> > >&sp, int sz )
{
	fstream fi( nm );
	if ( fi.good() )
	{
		sp.resize( sz );
		for( int inx = 0; inx < sz; inx++ )
		{
			sp[inx].resize( Hero::dov );
			for ( int y = 0; y < Hero::dov; y++ )
			{
				sp[inx][y].resize( Hero::wov[y] );
				for ( int x = 0; x < Hero::wov[y]; x++ )
				{
					fi >> sp[inx][y][x];
				}
			} 
		}
	}
	fi.close();
}
void Screen::updatePrevFov()
{
	Array<Coord>& fov = _pHero->getFovMemory();
	Coord crd;
	
	for ( int i = 0; i < fov.size(); i++ )
	{	
		crd = fov[i];
		Tile *t = (*_pMap)[crd.y][crd.x];
		if ( t->is_m ) mvwaddch( _p2d, crd.y, crd.x, t->ch | COLOR_PAIR(3) );
		else mvwaddch( _p2d, crd.y, crd.x, ' ' | COLOR_PAIR(3) );
	}
	fov.roll_down();
}
void Screen::update()
{
	updatePrevFov();

	Array<Dcoord>& fov = _pHero->getFov();
	int index;
	Icoord ic;
	
	werase( _p3d );

	for ( int i = 0; i < fov.size(); i++ )
	{
		Coord crd = fov[i].a;
		Tile* &tile = (*_pMap)[crd.y][crd.x];
		// print 2D
		mvwaddch( _p2d, crd.y, crd.x, tile->ch );
		_pHero->getFovMemory().push_back( crd );
		// print 3D ( map based tiles - walls, doors etc.)
		if ( ( index = tile->sprTabIndex() ) >= 0 ) //  polimorfic
		{
			ic.i = index;
			ic.c = fov[i].b;
			printSprite( _tileSprites[ic.i][ic.c.y][ic.c.x] );
		}
		// print 3D ( movable - monsters, items etc. )
		else
		{
			for ( int m = 0; m < _monsters.capacity(); m++ )
			{
				Coord temp = _monsters.at(m)->getPos();
				if ( crd == temp && ( index = _monsters[m]->sprTabIndex() ) >= 0 )
				{
					ic.i = index;
					ic.c = fov[i].b;
					Sprite& spr = _figureSprites[ic.i][ic.c.y][ic.c.x];
					printSprite( spr, _monsters.at(m)->color() );
				}
			}
		}
	}
	wnoutrefresh( _p3d );
}
void Screen::printSprite( Sprite& spr, int color )
{
	char* txt;
	Coord crd;
	wattron( _p3d, COLOR_PAIR( color ) );
	for ( int i = 0; i < spr.getHeight(); i++ )
	{
		Stripe& str = spr.getPtr()[i];
		txt = str.getText();
		crd = str.getCrd();
		mvwaddstr( _p3d, crd.y, crd.x, txt );
	}
	wattroff( _p3d, COLOR_PAIR( color ) );
}
void Screen::help()
{
	fstream fi( "data/help.dat" );
	if ( fi.good() )
	{
		const int width = 50;
		WINDOW* pHlp = newwin( 17, width, 4, 15 );
		keypad( pHlp, TRUE );
		leaveok( pHlp, TRUE );

		box( pHlp, 0, 0 );
		char line [ width ];
		int lcount = 2;
		do
		{
			fi.getline( line, width );
			mvwaddstr( pHlp, lcount++, 2, line );
		} while ( fi.good() );
		wgetch( pHlp );
		delwin( pHlp );
		redrawwin( _p2d );
		touchwin( stdscr );
		wnoutrefresh( stdscr );
	}
	fi.close();
}
void Screen::firstRunInfo()
{
	// do zrobienia: ma sprawdzic pierwsze uruchomienie i cos wykonac
	fstream fi( "data/nor.dat" );
	if ( fi.good() )
	{
		int n;
		fi >> n;
		if ( !n )
		{
			const char* info = "'h' - Pomoc";
			int l = strlen( info );
			WINDOW* pTemp = newwin( 1, l, LINES - 2 , COLS/2 - l/2 );
			waddstr( pTemp, info );
			wrefresh( pTemp );
			delwin( pTemp );
		}
	}
	fi.close();
}
