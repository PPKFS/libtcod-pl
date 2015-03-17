#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

std::map<std::string, std::shared_ptr<TCODConsole>> consoles;

PREDICATE(create_console, 3)
{
	if(consoles.find((char*)A1) == consoles.end())
	{
		consoles[(char*)A1] = std::shared_ptr<TCODConsole>(new TCODConsole((int)A2, (int)A3));
		return TRUE;
	}
	return FALSE;
}

PREDICATE(destroyConsole, 1)
{
	std::map<std::string, std::shared_ptr<TCODConsole>>::iterator it = consoles.find((char*)A1);
	if(it != consoles.end())
		consoles.erase(it);
	return TRUE;
}

PREDICATE(console_flush, 0)
{
	TCODConsole::flush();
	return TRUE;
}

PREDICATE(blit_console, 10)
{
	if(consoles.find((char*)A1) == consoles.end() || consoles.find((char*)A6) == consoles.end())
		return FALSE;
	TCODConsole* src = consoles.find((char*)A1)->second.get();
	TCODConsole* dst = consoles.find((char*)A6)->second.get();

	TCODConsole::blit(src, (int)A2, (int)A3, (int)A4, (int)A5, dst, (int)A7, (int)A8, (double)A9, (double)A10);
	return TRUE;
}

PREDICATE(init_root, 4)
{
	TCODConsole::initRoot((int)A1, (int)A2, (char*)A3, (((char*)A4) == "true"), TCOD_RENDERER_GLSL);
	consoles["root"] = std::shared_ptr<TCODConsole>(TCODConsole::root);
	return TRUE;
}

PREDICATE(console_putChar, 4)
{
	std::map<std::string, std::shared_ptr<TCODConsole>>::iterator it = consoles.find((char*)A1);
	if(it == consoles.end())
		return FALSE;

	it->second->putChar((int)A2, (int)A3, ((char*)A4)[0]);
	return TRUE;
}

PREDICATE(console_clear, 1)
{
	std::map<std::string, std::shared_ptr<TCODConsole>>::iterator it = consoles.find((char*)A1);
	if(it == consoles.end())
		return FALSE;

	it->second->flush();
	return TRUE;
}
