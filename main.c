#include <stddef.h>
#include <stdio.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <assert.h>

#include "common.h"
#include "snake.h"
#include "gfx.h"
#include "fruit.h"


int main(int argc, char* args[])
{
    //Returns bool in SDL3. 
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return 1;
    }

    Snake snake;
    snake_init(&snake);

    Fruit fruit = fruit_spawn(&snake);

    int exitCode = 0;
    Gfx* gfx = gfx_setup();
    SDL_Log("gfx after setup: %p", (void*)gfx);
    if (!gfx)
    {
        SDL_Log("Unable to initialize program!\n");
        return 1;
    }

    bool quit = false;

    SDL_Event e;
    SDL_zero(e);

    Uint64 last_input_time = SDL_GetTicks();
    Uint64 last_render_time = SDL_GetTicks();
    Uint64 last_fruit_time = 0;
    const Uint64 input_interval = 50; // 20 FPS
    const Uint64 render_interval = 17; // 60 FPS
    const Uint64 fruit_interval = 5000;

    Direction direction = RIGHT;

    while (!quit)
    {
        Uint64 current_time = SDL_GetTicks();

        //update physics
        if (current_time - last_input_time >= input_interval)
        {
            //handle input
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;

                else if (e.type == SDL_EVENT_KEY_DOWN)
                {
                    const char* keyName = SDL_GetKeyName(e.key.key);
                    SDL_Log("Key pressed: %s\n", keyName);

                    if (e.key.key == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                    else
                    {
                        switch (e.key.key)
                        {
                            case SDLK_UP:
								direction = UP;
								break;
							case SDLK_DOWN:
								direction = DOWN;
								break;
							case SDLK_LEFT:
								direction = LEFT;
								break;
							case SDLK_RIGHT:
								direction = RIGHT;
								break;
						}
                        snake_update_head_dir(&snake, direction);
                    }
                }
            }

            // spawn a new fruit?
            if (current_time - last_fruit_time >= fruit_interval)
            {
                fruit = fruit_spawn(&snake);
                last_fruit_time = current_time;
                SDL_Log("Spawned new fruit at: (%d, %d)\n", fruit.x, fruit.y);
            }

            // did we eat fruit?
            if (
                fruit.x == snake.head->snake_tile->position.x &&
                fruit.y == snake.head->snake_tile->position.y
                )
            {
				//grow the snake
				for (int i = 0; i < SNAKE_GROWTH_CONSTANT; i++)
				{
					snake_extend_default(&snake);
				}

                SDL_Log("Snake ate fruit! New size: %zu\n", snake.size);

                //setting this to long ago will force a new fruit to be spawned. 
                last_fruit_time = 0;
                fruit_remove(&fruit);
            }

            snake_move(&snake);

            last_input_time = current_time;
        }

        //update screen
        if (current_time - last_render_time >= render_interval)
        {
            gfx_draw_screen(gfx, &snake, &fruit);
            last_render_time = current_time;
        }

        // sleep to prevent high CPU usage
        SDL_Delay(1);
    }

    gfx_cleanup(gfx);

    return exitCode;
}
