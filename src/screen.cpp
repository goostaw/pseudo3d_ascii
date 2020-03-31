#include "screen.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstring>

Screen::Screen( Map* m, Hero* h, Bag< Figure* >& f )
	: _map( m ), _hero( h ), _monsters( f )
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
	_2d = newwin( s.y, s.x, p.y, p.x );
	leaveok( _2d, TRUE );
	keypad( _2d, TRUE );
	// 3d
	_3d = newwin( 19, 57, 1, 20 );
	box( _3d, 0 , 0 );
	leaveok( _3d, TRUE );
	// -------------
	_initSprites( "data/tiles.dat", _tileSprites, tileTabSize );
	_initSprites( "data/figures.dat", _figureSprites, figureTabSize );
}
Screen::~Screen()
{
	delwin( _3d );
	delwin( _2d );
	endwin();
}
void Screen::_initSprites( const char* nm, Bag< Bag< Bag<Sprite> > >&sp, int sz )
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
void Screen::_updatePrevFov()
{
	Bag<Coord>& b = _hero->getFovMemory();
	Coord c;
	
	for ( int i = 0; i < b.size(); i++ )
	{	
		c = b[i];
		Tile *t = (*_map)[c.y][c.x];
		if ( t->is_m ) mvwaddch( _2d, c.y, c.x, t->ch | COLOR_PAIR(3) );
		else mvwaddch( _2d, c.y, c.x, ' ' | COLOR_PAIR(3) );
	}
	b.clear();
}
void Screen::update()
{
	_updatePrevFov();

	Bag<Dcoord>& f = _hero->getFov();
	int b;
	Icoord ic;
	
	werase( _3d );

	for ( int i = 0; i < f.size(); i++ )
	{
		Coord c = f[i].a;
		Tile* &t = (*_map)[c.y][c.x];
		// print 2D
		mvwaddch( _2d, c.y, c.x, t->ch );
		_hero->getFovMemory().push_back( c );
		// print 3D ( map based tiles - walls, doors etc.)
		if ( ( b = t->sprTabIndex() ) >= 0 ) //  polimorfic
		{
			ic.i = b;
			ic.c = f[i].b;
			_printSprite( _tileSprites[ic.i][ic.c.y][ic.c.x] );
		}
		// print 3D ( moveable - monsters, items etc. )
		else
		{
			for ( int m = 0; m < _monsters.capacity(); m++ )
			{
				Coord temp = _monsters.at(m)->getPos();
				if ( c == temp && ( b = _monsters[m]->sprTabIndex() ) >= 0 )
				{
					ic.i = b;
					ic.c = f[i].b;
					Sprite& spr = _figureSprites[ic.i][ic.c.y][ic.c.x];
					_printSprite( spr, _monsters.at(m)->color() );
				}
			}
		}
	}
	wnoutrefresh( _3d );
}
void Screen::_printSprite( Sprite& spr, int color )
{
	char* txt;
	Coord crd;
	wattron( _3d, COLOR_PAIR( color ) );
	for ( int i = 0; i < spr.getHeight(); i++ )
	{
		Stripe& str = spr.getPtr()[i];
		txt = str.getText();
		crd = str.getCrd();
		mvwaddstr( _3d, crd.y, crd.x, txt );
	}
	wattroff( _3d, COLOR_PAIR( color ) );
}
void Screen::help()
{
	fstream fi( "data/help.dat" );
	if ( fi.good() )
	{
		const int width = 50;
		WINDOW* hlp = newwin( 17, width, 4, 15 );
		keypad( hlp, TRUE );
		leaveok( hlp, TRUE );

		box( hlp, 0, 0 );
		char line [ width ];
		int lcount = 2;
		do
		{
			fi.getline( line, width );
			mvwaddstr( hlp, lcount++, 2, line );
		} while ( fi.good() );
		wgetch( hlp );
		delwin( hlp );
		redrawwin( _2d );
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
			WINDOW* w = newwin( 1, l, LINES - 2 , COLS/2 - l/2 );
			waddstr( w, info );
			wrefresh( w );
			delwin( w );
		}
	}
	fi.close();
}
