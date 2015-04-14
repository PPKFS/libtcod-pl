#define PROLOG_MODULE "tcod"
#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

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

PlTerm colorsToList(const std::vector<TCODColor>& cols)
{
	PlTerm term;
	PlTail tail(term);

	for(int i = 0; i < cols.size(); ++i)
	{
		tail.append(colorToTerm(cols[i]));
	}
	tail.close();
	return term;
}

std::vector<TCODColor> listOfColors(PlTerm t)
{
	std::vector<TCODColor> colors;

	PlTail tail(t);
	PlTerm e;

	while(tail.next(e))
		colors.push_back(createColor(e));

	return colors;
}

std::vector<int> listOfInts(const PlTerm& t)
{
	std::vector<int> ints;

	PlTail tail(t);
	PlTerm e;

	while(tail.next(e))
	{
		int i = (int)e;
		ints.push_back(i);
	}

	return ints;
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

PREDICATE(tcod_gen_map, 4)
{
	std::vector<int> indices = listOfInts(A3);
	std::vector<TCODColor> keys = listOfColors(A2);	
	int count = (int)A1;
	TCODColor map[indices[count-1]+1];
	TCODColor::genMap(map, count, keys.data(), indices.data());
	std::vector<TCODColor> colors = std::vector<TCODColor>(map, map + indices[count-1]+1);
	PlTerm term = colorsToList(colors);
	return A4 = term;
}