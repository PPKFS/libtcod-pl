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
		clear/0]).

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
	tcod_console_putChar(Console, X, Y, Char).

putchar(X, Y, Char) :-
	putchar(root, X, Y, Char).

clear(Name) :-
	tcod_console_clear(Name).

clear :-
	clear(root).

