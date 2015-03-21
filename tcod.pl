:- use_module(console).
:- use_module(color).
:- use_module(events).

input:-
	check_for_keypress(X),
	write(X), nl,
	input.

input:-
	input.

hi :-
	init_root(80, 40, 'hi there', true),
	putchar(5, 6, a),
	putchar(6, 7, 4),
	putchar(9, 12, 'f'),
	flush,
	input.
