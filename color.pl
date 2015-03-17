:- module(color,
		[multiply_colors/3]).

:- use_foreign_library('lib/tcod-pl').

multiply_colors(F, Color1, Color2) :-
	float(F),
	tcod_multiply_color_float(Color1, F, Color2), !.

multiply_colors(Color1, F, Color2) :-
	float(F),
	tcod_multiply_color_float(Color1, F, Color2), !.

multiply_colors(Color1, Color2, Color3) :-
	tcod_multiply_colors_together(Color1, Color2, Color3), !.