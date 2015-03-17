#define PROLOG_MODULE "color"
#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

/*
TODO:
set hue/sat/val
get hue/sat/val
shift hue
scale HSV
generate color map
*/
TCODColor createColor(PlTerm term)
{
	return TCODColor((int)term[1], (int)term[2], (int)term[3]);
}

PlTerm colorToTerm(TCODColor color)
{
	return PlCompound("color", PlTermv((long)color.r, (long)color.g, (long)color.b));
}

PREDICATE(tcod_multiply_colors_together, 3)
{
	TCODColor a = createColor(A1), b = createColor(A2);
	return A3 = colorToTerm(a * b);
}

PREDICATE(tcod_multiply_color_float, 3)
{
	TCODColor a = createColor(A1);
	return A3 = colorToTerm(a * (double)A2);
}

PREDICATE(tcod_add_colors, 3)
{
	TCODColor a = createColor(A1), b = createColor(A2);
	return A3 = colorToTerm(a + b);
}

PREDICATE(tcod_sub_colors, 3)
{
	TCODColor a = createColor(A1), b = createColor(A2);
	return A3 = colorToTerm(a - b);
}

PREDICATE(tcod_lerp, 4)
{
	TCODColor a = createColor(A1), b = createColor(A2);
	return A4 = colorToTerm(TCODColor::lerp(a, b, (double)A3));
}

PREDICATE(tcod_set_hsv, 4)
{
	TCODColor a;
	a.setHSV((double)A1, (double)A2, (double)A3);
	return A4 = colorToTerm(a);
}