#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"

PREDICATE(initRoot, 4)
{
	TCODConsole::initRoot((int)A1, (int)A2, (char*)A3, (((char*)A4) == "true"));
	return TRUE;
}

PREDICATE(root_clear, 0)
{
	TCODConsole::root->clear();
	return TRUE;
}

PREDICATE(root_putchar, 3)
{
	TCODConsole::root->putChar((int)A1, (int)A2, ((char*)A3)[0]);
	return TRUE;
}

PREDICATE(flush, 0)
{
	TCODConsole::flush();
	return TRUE;
}

PREDICATE(check_for_keypress, 1)
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY, &key, NULL);
	if(key.vk == TCODK_NONE)
		return FALSE;
	PlCompound comp = PlCompound("key", PlTermv((long)key.pressed, (long)key.vk, (long)key.c));
	return A1 = comp;
}

PREDICATE(wait_for_keypress, 1)
{
	TCOD_key_t key;
	TCODSystem::waitForEvent(TCOD_EVENT_KEY, &key, NULL, true);
	PlCompound comp = PlCompound("key", PlTermv((long)key.pressed, (long)key.vk, (long)key.c));
	return A1 = comp;
}