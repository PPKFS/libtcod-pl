#define PROLOG_MODULE "console"
#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

typedef std::shared_ptr<TCODHeightMap> HeightmapPtr;
typedef std::map<std::string, HeightmapPtr> HeightmapMap;
HeightmapMap heightmaps;

PREDICATE(tcod_create_heightmap, 3)
{
	if(heightmaps.find((char*)A1) == heightmaps.end())
	{
		heightmaps[(char*)A1] = HeightmapPtr(new TCODConsole((int)A2, (int)A3));
		return TRUE;
	}
	return FALSE;
}

PREDICATE(tcod_add_hill, 5)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->addHill((float)A2, (float)A3, (float)A4, (float)A5);
	return TRUE;
}

PREDICATE(tcod_dig_hill, 5)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->digHill((float)A2, (float)A3, (float)A4, (float)A5);
	return TRUE;
}

PREDICATE(tcod_kernel_transform, 7)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	//TODO
	return TRUE;
}

PREDICATE(tcod_normalize, 3)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->normalize((float)A2, (float)A3);
	return TRUE;
}

PREDICATE(tcod_add_heightmaps, 2)
{
	HeightmapMap::iterator it1 = heightmaps.find((char*)A1); 
	HeightmapMap::iterator it2 = heightmaps.find((char*)A2); 
	if(it1 == heightmaps.end() || it2 == heightmaps.end()) 
		return FALSE;
	TCODHeightMap::add(it1->second, it2->second);
	return TRUE;
}

PREDICATE(tcod_multiply_heightmaps, 2)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	HeightmapMap::iterator it1 = heightmaps.find((char*)A1); 
	HeightmapMap::iterator it2 = heightmaps.find((char*)A2); 
	if(it1 == heightmaps.end() || it2 == heightmaps.end()) 
		return FALSE;
	TCODHeightMap::multiply(it1->second, it2->second);
	return TRUE;
}

PREDICATE(tcod_rain_erosion, 4)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->rainErosion((int)A2, (float)A3, (float)A4);
}

PREDICATE(tcod_dig_bezier, 7)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	//TODO
}

PREDICATE(tcod_add_noise, 8)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;

	TCODNoise* noise = new TCODNoise(2);
	it->second->addFbm(noise, (float)A2, (float)A3, (float)A4, (float)A5, (float)A6, (float)A7, (float)A8);
	return TRUE;
}