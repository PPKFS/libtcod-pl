:- module(events,
		[check_for_keypress/1,
		wait_for_keypress/1
		]).

check_for_keypress(Key) :-
	tcod_check_for_keypress(Key).

wait_for_keypress(Key) :-
	tcod_wait_for_keypress(Key).