
tcod:
	swipl-ld -Ilib/include -L. -ltcod -ltcodxx -shared -o lib/tcod-pl.so src/main.cpp

clean:
	rm -rf lib/tcod-pl.so