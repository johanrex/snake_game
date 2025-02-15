#ifndef GFX_H
#define GFX_H

#include <SDL3/SDL.h>
#include "snake.h"
#include "fruit.h"

typedef struct Gfx {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Gfx;

Gfx* gfx_setup();
void gfx_cleanup(Gfx* gfx);
void gfx_draw_snake(Gfx* gfx, Snake* snake);
void gfx_draw_fruit(Gfx* gfx, Fruit* fruit);
void gfx_draw_screen(Gfx* gfx, Snake* snake, Fruit* fruit);

#endif // GFX_H
