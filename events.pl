:- module(events,
		[check_for_keypress/1,
		wait_for_keypress/1,
		key_to_char/2
		]).

key_to_char(key(1, 65, Code), Char) :-
	char_code(Char, Code).
key_to_char(key(1, 64, 32), ' ').
key_to_char(key(1, 2, 8), '\b').
key_to_char(key(1, 4, 13), '\n').

check_for_keypress(Key) :-
	tcod_check_for_keypress(Key).

wait_for_keypress(Key) :-
	tcod_wait_for_keypress(Key).