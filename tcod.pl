:- use_foreign_library('lib/tcod-pl').

input:-
	check_for_keypress(X),
	write(X), nl,
	input.

input:-
	input.

hi :-
	initRoot(80, 40, 'hi there', true),
	create_console("bar", 20, 20),
	putchar("bar", 5, 5, '@'),
	blit_console("bar", 0, 0, 20, 20, "root", 0, 0, 1.0, 1.0),
	flush,
	input.
