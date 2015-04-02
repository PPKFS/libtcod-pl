:- module(heightmap,
		[
			create_heightmap/3,
			add_hill/5,
			dig_hill/5,
			normalize/3,
			rain_erosion/4,
			add_noise/8
		]).

create_heightmap(Name, Width, Height) :-
	tcod_create_heightmap(Name, Width, Height).

add_hill(Heightmap, X, Y, Radius, Height) :-
	tcod_add_hill(Heightmap, X, Y, Radius, Height).

dig_hill(Heightmap, X, Y, Radius, Height) :-
	tcod_dig_hill(Heightmap, X, Y, Radius, Height).

normalize(Heightmap, Min, Max) :-
	tcod_normalize(Heightmap, Min, Max).

rain_erosion(Heightmap, Drops, Erosion, Sediment) :-
	tcod_rain_erosion(Heightmap, Drops, Erosion, Sediment).

add_noise(Heightmap, Mulx, Muly, Addx, Addy, Octaves, Delta, Scale) :-
	tcod_add_noise(Heightmap, Mulx, Muly, Addx, Addy, Octaves, Delta, Scale).