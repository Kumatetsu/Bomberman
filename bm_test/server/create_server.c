#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

int				**get_array_map() {
	static int 	map[104][88];
	int 		x;
	int 		y;
	int 		current_x_state;
	int 		current_y_state;

	current_y_state = FREE_SLOT;
	for (y = 0; y < 88; y++) {
		current_x_state = WALL;
		if (x % 8 == 0)
			current_y_state = WALL;
		for (x = 0; x < 104; x++) {
			if (x % 8 == 0 && current_y_state == WALL)
				current_x_state = current_x_state == 1 ? FREE_SLOT : WALL;
			map[x][y] = current_y_state;
		}
	}

	return (int **) map;
}
