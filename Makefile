
tcod:
	swipl-ld -Ilib/include -L. -ltcod -ltcodxx -shared -cc-options,-std=c++11 -o lib/tcod-pl.so src/events.cpp src/console.cpp src/color.cpp src/heightmap.cpp

clean:
	rm -rf lib/tcod-pl.so
