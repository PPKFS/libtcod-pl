:- use_module(console).
:- use_module(color).

input:-
	check_for_keypress(X),
	write(X), nl,
	input.

input:-
	input.

hi :-
	init_root(80, 40, 'hi there', true),
	create_console(bar, 20, 20),
	flush,
	input.
