#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

std::map<std::string, std::shared_ptr<TCODConsole>> consoles;

PREDICATE(console_createConsole, 3)
{
	if(consoles.find((char*)A1) == consoles.end())
	{
		consoles[(char*)A1] = new TCODConsole((int)A2, (int)A3, TCOD_RENDERER_GLSL);
		return TRUE;
	}
	return FALSE;
}

PREDICATE(console_destroyConsole, 1)
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
	TCODConsole* src = consoles.find((char*)A1)->second;
	TCODConsole* dst = consoles.find((char*)A6)->second;

	TCODConsole::blit(src, (int)A2, (int)A3, (int)A4, (int)A5, dst, (int)A7, (int)A8, (float)A9, (float)A10);
	return TRUE;
}

PREDICATE(init_root, 4)
{
	TCODConsole::initRoot((int)A1, (int)A2, (char*)A3, (((char*)A4) == "true"));
	consoles["root"] = TCODConsole::root;
	return TRUE;
}

PREDICATE(root_putchar, 3)
{
	TCODConsole::root->putChar((int)A1, (int)A2, ((char*)A3)[0]);
	return TRUE;
}

PREDICATE(console_putchar, 4)
{
	std::map<std::string, std::shared_ptr<TCODConsole>>::iterator it = consoles.find((char*)A1);
	if(it == consoles.end())
		return FALSE;

	it->second->putchar((int)A2, (int)A3, ((char*)A4)[0]);
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

PREDICATE(root_clear, 0)
{
	TCODConsole::root->clear();
	return TRUE;
}
