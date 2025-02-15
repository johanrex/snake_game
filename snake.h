#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "common.h"

#define SNAKE_DEFAULT_LENGTH 4
#define SNAKE_GROWTH_CONSTANT 2

typedef struct SnakeTile
{
    Point position;
    Point direction;
} SnakeTile;

//TODO remove SnakeNode, use only SnakeTile
typedef struct SnakeNode {
    SnakeTile* snake_tile;
    struct SnakeNode *next;
    struct SnakeNode *prev;
} SnakeNode;

typedef struct Snake 
{
    SnakeNode *head;
    SnakeNode *tail;
    size_t size; // Size of the snake
} Snake;

void snake_init(Snake *snake);
void snake_extend(Snake *snake, Point position, Point direction);
void snake_extend_default(Snake* snake);
void snake_free(Snake *snake);
bool snake_move(Snake *snake);
void snake_update_head_dir(Snake *snake, Direction direction);
void snake_print(const Snake *snake, void (*print_func)(const char *, ...));
#endif // SNAKE_H
