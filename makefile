chambers.exe: chambers.obj console_functions.obj notris_graphics_functions.obj notris_game_functions.obj
	link chambers.obj console_functions.obj notris_graphics_functions.obj notris_game_functions.obj

chambers.obj: chambers.c console_functions.h notris/notris_graphics_functions.h notris/notris_game_functions.h notris/notris_structures.h
	cl -c chambers.c

console_functions.obj: console_functions.c console_functions.h
	cl -c console_functions.c

notris_graphics_functions.obj: console_functions.h notris/notris_graphics_functions.c notris/notris_graphics_functions.h notris/notris_structures.h 
	cl -c notris/notris_graphics_functions.c

notris_game_functions.obj: notris/notris_game_functions.c notris/notris_game_functions.h notris/notris_structures.h
	cl -c notris/notris_game_functions.c