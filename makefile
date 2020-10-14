chambers.exe: chambers.obj console_functions.obj graphics_functions.obj game_functions.obj
	link chambers.obj console_functions.obj graphics_functions.obj game_functions.obj

chambers.obj: chambers.c console_functions.h graphics_functions.h game_functions.h
	cl -c chambers.c

console_functions.obj: console_functions.c console_functions.h
	cl -c console_functions.c

graphics_functions.obj: graphics_functions.c graphics_functions.h console_functions.h
	cl -c graphics_functions.c

game_functions.obj: game_functions.c game_functions.h
	cl -c game_functions.c