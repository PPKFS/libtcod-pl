:- module(color,
		[multiply_colors/3,
		add_colors/3,
		subtract_colors/3,
		lerp/4,
		set_hsv/4
		]).

:- use_foreign_library('lib/tcod-pl').

multiply_colors(F, Color1, Color2) :-
	float(F),
	tcod_multiply_color_float(Color1, F, Color2), !.

multiply_colors(Color1, F, Color2) :-
	float(F),
	tcod_multiply_color_float(Color1, F, Color2), !.

multiply_colors(Color1, Color2, Color3) :-
	tcod_multiply_colors_together(Color1, Color2, Color3), !.

add_colors(Color1, Color2, Color3) :-
	tcod_add_colors(Color1, Color2, Color3).

subtract_colors(Color1, Color2, Color3) :-
	tcod_subtract_colors(Color1, Color2, Color3).

lerp(Color1, Color2, Coef, Color3) :-
	tcod_lerp(Color1, Color2, Coef, Color3).

set_hsv(H, S, V, Color) :-
	tcod_set_hsv(H, S, V, Color).