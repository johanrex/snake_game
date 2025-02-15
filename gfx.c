#include <assert.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include "common.h"
#include "gfx.h"
#include "snake.h"
#include "fruit.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

static inline int map_to_screen(int val) {
    return val * SCREEN_WIDTH / MAP_SIZE;
}

static inline int screen_tile_size() {
    return map_to_screen(MAP_TILE_SIZE);
}

#define SCREEN_TILE_SIZE (float)screen_tile_size(MAP_TILE_SIZE)

Gfx* gfx_setup()
{
    //Returns bool in SDL3. 
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return NULL;
    }

    Gfx* gfx = (Gfx*)malloc(sizeof(Gfx));
    if (gfx == NULL)
    {
        SDL_Log("Memory allocation for Gfx failed!\n");
        SDL_Quit();
        return NULL;
    }

    gfx->window = SDL_CreateWindow("Snake", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (gfx->window == NULL)
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        free(gfx);
        SDL_Quit();
        return NULL;
    }

    gfx->renderer = SDL_CreateRenderer(gfx->window, NULL);
    if (gfx->renderer == NULL)
    {
        SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
        SDL_DestroyWindow(gfx->window);
        free(gfx);
        SDL_Quit();
        return NULL;
    }

    SDL_Log("Graphics setup successfully.");
    SDL_Log("gfx: %p", (void*)gfx);
    return gfx;
}

void gfx_cleanup(Gfx *gfx)
{
    if (gfx != NULL)
    {
        if (gfx->renderer != NULL)
        {
            SDL_DestroyRenderer(gfx->renderer);
        }
        if (gfx->window != NULL)
        {
            SDL_DestroyWindow(gfx->window);
        }
        free(gfx);
        gfx = NULL;
    }
    SDL_Quit();
}


void gfx_draw_snake(Gfx *gfx, Snake* snake)
{
    //by looping from the tail, we make sure that the head is drawn last, thus always on top and visible.
    SnakeNode* curr = snake->tail;
    while (curr != NULL)
    {
        Point* curr_pos = &curr->snake_tile->position;

        float screenPosX = (float)map_to_screen(curr_pos->x);
        float screenPosY = (float)map_to_screen(curr_pos->y);

        SDL_FRect rect = {
            screenPosX,
            screenPosY,
            SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE
        };

        if (curr == snake->head)
            SDL_SetRenderDrawColor(gfx->renderer, 200, 100, 100, 255);
        else
            SDL_SetRenderDrawColor(gfx->renderer, 100, 100, 180, 255);

        SDL_RenderFillRect(gfx->renderer, &rect);

        curr = curr->prev;
    }
}

void gfx_draw_fruit(Gfx* gfx, Fruit* fruit)
{
    if (fruit->x != -1 && fruit->y != -1)
    {
        SDL_SetRenderDrawColor(gfx->renderer, 100, 200, 100, 255);
        SDL_FRect rect = {
            (float)map_to_screen(fruit->x),
            (float)map_to_screen(fruit->y),
            SCREEN_TILE_SIZE,
            SCREEN_TILE_SIZE
        };
        SDL_RenderFillRect(gfx->renderer, &rect);
    }
}

void gfx_draw_screen(Gfx* gfx, Snake* snake, Fruit* fruit)
{
    SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gfx->renderer);
    gfx_draw_snake(gfx, snake);
    gfx_draw_fruit(gfx, fruit);
    SDL_RenderPresent(gfx->renderer);
}