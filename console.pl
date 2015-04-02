:- module(console,
		[create_console/3,
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
		print_rect/5
		]).

:- use_module(color).

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

