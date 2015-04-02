#define PROLOG_MODULE "console"
#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

typedef std::shared_ptr<TCODConsole> ConsolePtr;
typedef std::map<std::string, std::shared_ptr<TCODConsole>> ConsoleMap;
ConsoleMap consoles;

TCODColor termToColor(PlTerm term)
{
	return TCODColor((int)term[1], (int)term[2], (int)term[3]);
}

PREDICATE(tcod_set_font, 2)
{
	TCODConsole::setCustomFont((char*)A1, (int)A2);
	return TRUE;
}

PREDICATE(tcod_create_console, 3)
{
	if(consoles.find((char*)A1) == consoles.end())
	{
		consoles[(char*)A1] = ConsolePtr(new TCODConsole((int)A2, (int)A3));
		return TRUE;
	}
	return FALSE;
}

PREDICATE(tcod_destroyConsole, 1)
{
	ConsoleMap::iterator it = consoles.find((char*)A1);
	if(it != consoles.end())
		consoles.erase(it);
	return TRUE;
}

PREDICATE(tcod_flush, 0)
{
	TCODConsole::flush();
	return TRUE;
}

PREDICATE(tcod_blit, 10)
{
	if(consoles.find((char*)A1) == consoles.end() || consoles.find((char*)A6) == consoles.end())
		return FALSE;
	TCODConsole* src = consoles.find((char*)A1)->second.get();
	TCODConsole* dst = consoles.find((char*)A6)->second.get();

	TCODConsole::blit(src, (int)A2, (int)A3, (int)A4, (int)A5, dst, (int)A7, (int)A8, (double)A9, (double)A10);
	return TRUE;
}

PREDICATE(tcod_init_root, 4)
{
	TCODConsole::initRoot((int)A1, (int)A2, (char*)A3, (((char*)A4) == "true"), TCOD_RENDERER_GLSL);
	consoles["root"] = ConsolePtr(TCODConsole::root);
	return TRUE;
}

PREDICATE(tcod_console_putChar, 4)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->putChar((int)A2, (int)A3, (int)A4);
	return TRUE;
}

PREDICATE(tcod_console_clear, 1)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->clear();
	return TRUE;
}

PREDICATE(tcod_set_default_bg, 2)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->setDefaultBackground(termToColor(A2));
	return TRUE;
}

PREDICATE(tcod_set_default_fg, 2)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->setDefaultForeground(termToColor(A2));
	return TRUE;
}

PREDICATE(tcod_set_char_fg, 4)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->setCharForeground((int)A2, (int)A3, termToColor(A4));
	return TRUE;
}

PREDICATE(tcod_set_char_bg, 4)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->setCharBackground((int)A2, (int)A3, termToColor(A4));
	return TRUE;
}

PREDICATE(tcod_set_ascii, 4)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->setChar((int)A2, (int)A3, (int)A4);
	return TRUE;
}

PREDICATE(tcod_is_window_closed, 1)
{
	return (A1 = (TCODConsole::isWindowClosed() ? PlTerm("yes") : PlTerm("no")));
}

PREDICATE(tcod_print, 4)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->print((int)A2, (int)A3, (char*)A4);
	return TRUE;
}

PREDICATE(tcod_print_rect, 6)
{
	ConsoleMap::iterator it = consoles.find((char*)A1); 
	if(it == consoles.end()) 
		return FALSE;
	it->second->printRect((int)A2, (int)A3, (int)A4, (int)A5, (char*)A6);
	return TRUE;
}