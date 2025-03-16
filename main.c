#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 600

#define BLACK 0, 0, 0, 255
#define WHITE 255, 255, 255, 255
#define RED 255, 0, 0, 255
#define GREEN 0, 255, 0, 255
#define BLUE 0, 0, 255, 255

#define FRAME_DELAY 1000 / 25

int main(int argc, char **argv) {
		printf("starting...\n");

		if(SDL_Init(SDL_INIT_VIDEO) != 0) {
				printf("SDL Initialization Error: %s\n", SDL_GetError());
				return 1;
		}

		SDL_Window *window = SDL_CreateWindow("BOIDS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		if(!window) {
				printf("Window Creation Error: %s\n", SDL_GetError());
				SDL_Quit();
				return 1;
		}

		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if(!renderer) {
				printf("Renderer Creation Error: %s\n", SDL_GetError());
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 1;
		}

		int running = 1;
		SDL_Event event;
		int x = 400, y = 300;

		while(running) {
				while(SDL_PollEvent(&event)) {
						if(event.type == SDL_QUIT) {
								running = 0;
						} else if(event.type == SDL_MOUSEMOTION) {
								x = event.motion.x;
								y = event.motion.y;
						}
				}

				// clear screen
				SDL_SetRenderDrawColor(renderer, BLACK);
				SDL_RenderClear(renderer);

				// set draw color
				SDL_SetRenderDrawColor(renderer, GREEN);
				SDL_RenderDrawPoint(renderer, x, y);

				SDL_RenderPresent(renderer);
				SDL_Delay(FRAME_DELAY);

		}

		printf("exiting...\n");

		SDL_DestroyWindow(window);
		SDL_Quit();


		return 0;
}
