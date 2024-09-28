#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
	const char *PATH = "test.txt";

	printf("PATH = %s\n", PATH);

	FILE *image = fopen(PATH, "r");

	char path[256];
	int w, h;
	fscanf(image, "%s\n", path);
	fscanf(image, "%d %d\n", &w, &h);

	printf("path = %s\n", path);
	printf("size = %d x %d\n", w,h);

	uint8_t *data = malloc(w*h*3);

	SDL_Window* window = SDL_CreateWindow(
		path,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, SDL_WINDOW_SHOWN
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
	int k = 0;
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			fscanf(image, "%hhu %hhu %hhu\n", &data[k], &data[k+1], &data[k+2]);
			SDL_SetRenderDrawColor(renderer, data[k], data[k+1], data[k+2], 255);
      		SDL_RenderDrawPoint(renderer, j, i);
			k += 3;
		}
	}

    SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	free(data);

	return 0;
}
