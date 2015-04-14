:-module(tcod,
		[multiply_colors/3,
		add_colors/3,
		subtract_colors/3,
		lerp/4,
		set_hsv/4,
		color/2, 
		check_for_keypress/1,
		wait_for_keypress/1,
		key_to_char/2,
		create_console/3,
		destroy_console/1,
		flush/0,
		init_root/4,
		blit/8,
		blit/10,
		putchar/4,
		putchar/3,
		clear/1,
		clear/0,
		set_default_background/2,
		set_default_background/1,
		set_default_foreground/2,
		set_default_foreground/1,
		set_char_background/4,
		set_char_background/3,
		set_char_foreground/4,
		set_char_foreground/3,
		setchar/4,
		setchar/3,
		is_window_closed/1,
		window_is_closed/0,
		print/4,
		print/3,
		print_rect/6,
		print_rect/5,
		create_heightmap/3,
		add_hill/5,
		dig_hill/5,
		normalize/3,
		rain_erosion/4,
		add_noise/8,
		get_value/4
		]).

:- use_foreign_library('lib/tcod-pl.so').

black(0,0,0).
darkest_grey(31,31,31).
darker_grey(63,63,63).
dark_grey(95,95,95).
grey(127,127,127).
light_grey(159,159,159).
lighter_grey(191,191,191).
lightest_grey(223,223,223).
white(255,255,255).
darkest_sepia(31,24,15).
darker_sepia(63,50,31).
dark_sepia(94,75,47).
sepia(127,101,63).
light_sepia(158,134,100).
lighter_sepia(191,171,143).
lightest_sepia(222,211,195).
desaturated_red(127,63,63).
desaturated_flame(127,79,63).
desaturated_orange(127,95,63).
desaturated_amber(127,111,63).
desaturated_yellow(127,127,63).
desaturated_lime(111,127,63).
desaturated_chartreuse(95,127,63).
desaturated_green(63,127,63).
desaturated_sea(63,127,95).
desaturated_turquoise(63,127,111).
desaturated_cyan(63,127,127).
desaturated_sky(63,111,127).
desaturated_azure(63,95,127).
desaturated_blue(63,63,127).
desaturated_han(79,63,127).
desaturated_violet(95,63,127).
desaturated_purple(111,63,127).
desaturated_fuchsia(127,63,127).
desaturated_magenta(127,63,111).
desaturated_pink(127,63,95).
desaturated_crimson(127,63,79).
lightest_red(255,191,191).
lightest_flame(255,207,191).
lightest_orange(255,223,191).
lightest_amber(255,239,191).
lightest_yellow(255,255,191).
lightest_lime(239,255,191).
lightest_chartreuse(223,255,191).
lightest_green(191,255,191).
lightest_sea(191,255,223).
lightest_turquoise(191,255,239).
lightest_cyan(191,255,255).
lightest_sky(191,239,255).
lightest_azure(191,223,255).
lightest_blue(191,191,255).
lightest_han(207,191,255).
lightest_violet(223,191,255).
lightest_purple(239,191,255).
lightest_fuchsia(255,191,255).
lightest_magenta(255,191,239).
lightest_pink(255,191,223).
lightest_crimson(255,191,207).
lighter_red(255,127,127).
lighter_flame(255,159,127).
lighter_orange(255,191,127).
lighter_amber(255,223,127).
lighter_yellow(255,255,127).
lighter_lime(223,255,127).
lighter_chartreuse(191,255,127).
lighter_green(127,255,127).
lighter_sea(127,255,191).
lighter_turquoise(127,255,223).
lighter_cyan(127,255,255).
lighter_sky(127,223,255).
lighter_azure(127,191,255).
lighter_blue(127,127,255).
lighter_han(159,127,255).
lighter_violet(191,127,255).
lighter_purple(223,127,255).
lighter_fuchsia(255,127,255).
lighter_magenta(255,127,223).
lighter_pink(255,127,191).
lighter_crimson(255,127,159).
light_red(255,63,63).
light_flame(255,111,63).
light_orange(255,159,63).
light_amber(255,207,63).
light_yellow(255,255,63).
light_lime(207,255,63).
light_chartreuse(159,255,63).
light_green(63,255,63).
light_sea(63,255,159).
light_turquoise(63,255,207).
light_cyan(63,255,255).
light_sky(63,207,255).
light_azure(63,159,255).
light_blue(63,63,255).
light_han(111,63,255).
light_violet(159,63,255).
light_purple(207,63,255).
light_fuchsia(255,63,255).
light_magenta(255,63,207).
light_pink(255,63,159).
light_crimson(255,63,111).
red(255,0,0).
flame(255,63,0).
orange(255,127,0).
amber(255,191,0).
yellow(255,255,0).
lime(191,255,0).
chartreuse(127,255,0).
green(0,255,0).
sea(0,255,127).
turquoise(0,255,191).
cyan(0,255,255).
sky(0,191,255).
azure(0,127,255).
blue(0,0,255).
han(63,0,255). 
violet(127,0,255).
purple(191,0,255).
fuchsia(255,0,255).
magenta(255,0,191).
pink(255,0,127).
crimson(255,0,63).
dark_red(191,0,0).
dark_flame(191,47,0).
dark_orange(191,95,0).
dark_amber(191,143,0).
dark_yellow(191,191,0).
dark_lime(143,191,0).
dark_chartreuse(95,191,0).
dark_green(0,191,0).
dark_sea(0,191,95).
dark_turquoise(0,191,143).
dark_cyan(0,191,191). 
dark_sky(0,143,191).
dark_azure(0,95,191).
dark_blue(0,0,191).
dark_han(47,0,191).
dark_violet(95,0,191).
dark_purple(143,0,191).
dark_fuchsia(191,0,191).
dark_magenta(191,0,143).
dark_pink(191,0,95).
dark_crimson(191,0,47).
darker_red(127,0,0).
darker_flame(127,31,0).
darker_orange(127,63,0).
darker_amber(127,95,0).
darker_yellow(127,127,0).
darker_lime(95,127,0).
darker_chartreuse(63,127,0).
darker_green(0,127,0).
darker_sea(0,127,63).
darker_turquoise(0,127,95).
darker_cyan(0,127,127).
darker_sky(0,95,127).
darker_azure(0,63,127).
darker_blue(0,0,127).
darker_han(31,0,127).
darker_violet(63,0,127).
darker_purple(95,0,127).
darker_fuchsia(127,0,127).
darker_magenta(127,0,95).
darker_pink(127,0,63).
darker_crimson(127,0,31).
darkest_red(63,0,0).
darkest_flame(63,15,0).
darkest_orange(63,31,0).
darkest_amber(63,47,0).
darkest_yellow(63,63,0).
darkest_lime(47,63,0).
darkest_chartreuse(31,63,0).
darkest_green(0,63,0).
darkest_sea(0,63,31).
darkest_turquoise(0,63,47).
darkest_cyan(0,63,63).
darkest_sky(0,47,63).
darkest_azure(0,31,63).
darkest_blue(0,0,63).
darkest_han(15,0,63).
darkest_violet(31,0,63).
darkest_purple(47,0,63).
darkest_fuchsia(63,0,63).
darkest_magenta(63,0,47).
darkest_pink(63,0,31).
darkest_crimson(63,0,15).
brass(191,151,96).
copper(197,136,124).
gold(229,191,0).
silver(203,203,203).
celadon(172,255,175).
peach(255,159,127).

color(Name, Color) :-
	atom(Name),
	call(Name, R, G, B),
	Color = color(R, G, B).

color(Color, Color) :-
	functor(Color, Name, 3),
	Name = color.

multiply_colors(F,Color1,Color2):-
	float(F),
	color(Color1, C1),
	tcod_multiply_color_float(C1,F,Color2),!.

multiply_colors(Color1,F,Color2):-
	float(F),
	color(Color1, C1),
	tcod_multiply_color_float(C1,F,Color2),!.

multiply_colors(Color1,Color2,Color3):-
	color(Color1, C1),
	color(Color2, C2),
	tcod_multiply_colors_together(C1,C2,Color3),!.

add_colors(Color1,Color2,Color3):-
	color(Color1, C1),
	color(Color2, C2),
	tcod_add_colors(C1,C2,Color3).

subtract_colors(Color1,Color2,Color3):-
	color(Color1, C1),
	color(Color2, C2),
	tcod_subtract_colors(C1,C2,Color3).

lerp(Color1,Color2,Coef,Color3):-
	color(Color1, C1),
	color(Color2, C2),
	tcod_lerp(C1,C2,Coef,Color3).

set_hsv(H,S,V,Color):-
	tcod_set_hsv(H,S,V,Color).

gen_map(Count, Cols, Indices, Map) :-
	tcod_gen_map(Count, Cols, Indices, Map).

%% events
key_to_char(key(1, 65, Code), Char) :-
	char_code(Char, Code).
key_to_char(key(1, 64, 32), ' ').
key_to_char(key(1, 2, 8), '\b').
key_to_char(key(1, 4, 13), '\n').

check_for_keypress(Key) :-
	tcod_check_for_keypress(Key).

wait_for_keypress(Key) :-
	tcod_wait_for_keypress(Key).

%% console
create_console(Name, W, H) :-
	Name \= root,
	tcod_create_console(Name, W, H).

destroy_console(Name) :-
	Name \= root,
	tcod_destroy_console(Name).

flush:-
	tcod_flush.

init_root(W, H, Title, Fullscreen) :-
	tcod_init_root(W, H, Title, Fullscreen).

blit(Src, XSrc, YSrc, WSrc, HSrc, Dst, XDst, YDst) :-
	tcod_blit(Src, XSrc, YSrc, WSrc, HSrc, Dst, XDst, YDst, 1.0, 1.0).

blit(Src, XSrc, YSrc, WSrc, HSrc, Dst, XDst, YDst, FAlpha, BAlpha) :-
	tcod_blit(Src, XSrc, YSrc, WSrc, HSrc, Dst, XDst, YDst, FAlpha, BAlpha).

putchar(Console, X, Y, Char) :-
	integer(Char),
	tcod_console_putChar(Console, X, Y, Char)
	;
	char_code(Char, Code),
	tcod_console_putChar(Console, X, Y, Code).

putchar(X, Y, Char) :-
	putchar(root, X, Y, Char).

clear(Name) :-
	tcod_console_clear(Name).

clear :-
	clear(root).

set_default_background(Name, Color) :-
	color(Color, Color2),
	tcod_set_default_bg(Name, Color2).

set_default_background(Color) :-
	set_default_background(root, Color).

set_default_foreground(Name, Color) :-
	color(Color, Color2),
	tcod_set_default_fg(Name, Color2).

set_default_foreground(Color) :-
	set_default_foreground(root, Color).

set_char_background(Name, X, Y, Color) :-
	color(Color, Color2),
	tcod_set_char_bg(Name, X, Y, Color2).

set_char_background(X, Y, Color) :-
	set_char_background(root, X, Y, Color).

set_char_foreground(Name, X, Y, Color) :-
	color(Color, Color2),
	tcod_set_char_fg(Name, Color2).

set_char_foreground(X, Y, Color) :-
	set_char_foreground(root, X, Y, Color).

setchar(Console, X, Y, Char):-
	integer(Char),
	tcod_set_ascii(Console, X, Y, Char)
	;
	char_code(Char, Code),
	tcod_set_ascii(Console, X, Y, Code).

setchar(X, Y, Char) :-
	setchar(root, X, Y, Char).

is_window_closed(X):-
	tcod_is_window_closed(X).

window_is_closed:-
	is_window_closed(yes).

print(Console, X, Y, Str):-
	tcod_print(Console, X, Y, Str).

print(X, Y, Str):-
	print(root, X, Y, Str).

print_rect(Console, X, Y, W, H, Str):-
	tcod_print(Console, X, Y, W, H, Str).

print_rect(X, Y,W, H, Str):-
	print(root, X, Y, W, H, Str).

%% Heightmap

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

get_value(Heightmap, X, Y, Val) :-
	tcod_get_value(Heightmap, X, Y, Val).