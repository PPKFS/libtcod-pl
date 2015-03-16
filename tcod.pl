:- use_foreign_library('lib/tcod-pl').

input:-
	check_for_keypress(X),
	write(X), nl,
	input.

input:-
	input.

hi :-
	initRoot(80, 40, 'hi there', true),
	input.
