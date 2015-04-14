#define PROLOG_MODULE "tcod"
#include <SWI-cpp.h>
#include <SWI-Prolog.h>
#include "libtcod.hpp"
#include <map>
#include <string>
#include <memory>

typedef std::shared_ptr<TCODHeightMap> HeightmapPtr;
typedef std::map<std::string, HeightmapPtr> HeightmapMap;
HeightmapMap heightmaps;

bool createHeightmap(std::string name, int width, int height)
{
	if(heightmaps.find(name) == heightmaps.end())
	{
		heightmaps[name] = HeightmapPtr(new TCODHeightMap(width, height));
		return true;
	}
	return false;
}

PREDICATE(tcod_create_heightmap, 3)
{
	return createHeightmap((char*)A1, (int)A2, (int)A3) ? TRUE : FALSE;
}

PREDICATE(tcod_add_hill, 5)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->addHill((double)A2, (double)A3, (double)A4, (double)A5);
	return TRUE;
}

PREDICATE(tcod_dig_hill, 5)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->digHill((double)A2, (double)A3, (double)A4, (double)A5);
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
	it->second->normalize((double)A2, (double)A3);
	return TRUE;
}

/*PREDICATE(tcod_add_heightmaps, 3)
{
	if(createHeightmap())
	HeightmapMap::iterator it1 = heightmaps.find((char*)A1); 
	HeightmapMap::iterator it2 = heightmaps.find((char*)A2); 
	if(it1 == heightmaps.end() || it2 == heightmaps.end()) 
		return FALSE;
	TCODHeightMap::add(it1->second.get(), it2->second.get());
	return TRUE;
}*/

/*PREDICATE(tcod_multiply_heightmaps, 3)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	HeightmapMap::iterator it1 = heightmaps.find((char*)A1); 
	HeightmapMap::iterator it2 = heightmaps.find((char*)A2); 
	if(it1 == heightmaps.end() || it2 == heightmaps.end()) 
		return FALSE;
	TCODHeightMap::multiply(it1->second.get(), it2->second.get());
	return TRUE;
}*/

PREDICATE(tcod_rain_erosion, 4)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	it->second->rainErosion((int)A2, (double)A3, (double)A4, NULL);
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
	it->second->addFbm(noise, (double)A2, (double)A3, (double)A4, (double)A5, (double)A6, (double)A7, (double)A8);
	return TRUE;
}

PREDICATE(tcod_get_value, 4)
{
	HeightmapMap::iterator it = heightmaps.find((char*)A1); 
	if(it == heightmaps.end()) 
		return FALSE;
	return A4 = it->second->getValue((int)A2, (int)A3);
}