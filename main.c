#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 600

#define BLACK 0, 0, 0, 255
#define WHITE 255, 255, 255, 255
#define RED 255, 0, 0, 255
#define GREEN 0, 255, 0, 255
#define BLUE 0, 0, 255, 255

#define FRAME_DELAY 1000 / 60
#define NUM_BOIDS 100

// Boid
typedef struct {
		// position
		double x, y;
		
		// velocity
		double vx, vy;

		// acceleration
		double ax, ay;
} boid_t;


// this function is used for drawing the boid
void draw_boid(const boid_t *boid, SDL_Renderer *renderer) {
		// draw velocity
		SDL_SetRenderDrawColor(renderer, RED);
		SDL_RenderDrawLine(renderer, boid->x, boid->y, boid->x + boid->vx, boid->y + boid->vy);

		// draw acceleration
		SDL_SetRenderDrawColor(renderer, BLUE);
		SDL_RenderDrawLine(renderer, boid->x, boid->y, boid->x + boid->ax, boid->y + boid->ay);
		
		// draw the point
		SDL_SetRenderDrawColor(renderer, GREEN);
		SDL_RenderDrawPoint(renderer, boid->x, boid->y);
}


// this function is used for creating the boid
boid_t *create_boid_dynamic(double x, double y, double vx, double vy, double ax, double ay) {
		boid_t *boid = (boid_t *)malloc(sizeof(boid_t));

		if(!boid) {
				fprintf(stderr, "Memory allocation failed\n");
				exit(1);
		}

		boid->x = x;
		boid->y = y;
		boid->vx = vx;
		boid->vy = vy;
		boid->ax = ax;
		boid->ay = ay;

		return boid;
}


// this function is used for updating the boid
void update_boid(boid_t *boid, const double dt) {
		// update the position
		boid->x += boid->vx * dt;
		boid->y += boid->vy * dt;

		// update the velocity
		boid->vx += boid->ax * dt;
		boid->vy += boid->ay * dt;
}


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
		// int x = 400, y = 300;
		
		// create a boid
		boid_t *boid = create_boid_dynamic(400, 300, 40, -20, 10, 20);

		// store initial time
		int start_time = SDL_GetTicks();

		boid_t *boids[NUM_BOIDS];
		
		for(int i=0; i<NUM_BOIDS; i++) {
				boids[i] = create_boid_dynamic(rand() % WIDTH, rand() % HEIGHT, (rand() % 10) -5, (rand() % 10) -5, (rand() % 10) -5, (rand() % 10) -5);
		}

		while(running) {
				while(SDL_PollEvent(&event)) {
						if(event.type == SDL_QUIT) {
								running = 0;
						} else if(event.type == SDL_MOUSEMOTION) {
								// x = event.motion.x;
								// y = event.motion.y;
						}
				}

				// clear screen
				SDL_SetRenderDrawColor(renderer, BLACK);
				SDL_RenderClear(renderer);

				// set draw color
				// SDL_SetRenderDrawColor(renderer, GREEN);
				// SDL_RenderDrawPoint(renderer, x, y);
				
				int current_time = SDL_GetTicks();
				int dt_ms = current_time - start_time;
				start_time = current_time;

				double dt = dt_ms / 1000.0f;

				// draw_boid(boid, renderer);
				// update_boid(boid, dt);
				//
				// draw the boids
				for(int i=0; i<NUM_BOIDS; i++) {
						draw_boid(boids[i], renderer);
						update_boid(boids[i], dt);
				}

				SDL_RenderPresent(renderer);
				SDL_Delay(FRAME_DELAY);

		}

		printf("exiting...\n");

		// free memory if allocated
		free(boid);

		SDL_DestroyWindow(window);
		SDL_Quit();


		return 0;
}
