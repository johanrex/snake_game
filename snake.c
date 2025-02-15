#include <stddef.h>
#include "snake.h"
#include <assert.h>
#include <stdlib.h>


void snake_init(Snake *snake)
{
	snake->head = NULL;
	snake->tail = NULL;
	snake->size = 0;

	//add snake head
	//initialize it in the middle of the map, moving right
	Point position = { MAP_SIZE / 2, MAP_SIZE / 2 };
	Point direction = { 1, 0 };

	for (size_t i = 0; i < SNAKE_DEFAULT_LENGTH; i++)
		snake_extend(snake, position, direction);
}

void snake_extend_default(Snake* snake)
{
	snake_extend(
		snake,
		snake->tail->snake_tile->position,
		snake->tail->snake_tile->direction
	);
}

void snake_extend(Snake *snake, Point position, Point direction)
{
	SnakeTile *new_tile = malloc(sizeof(SnakeTile));
	new_tile->direction = direction;
	new_tile->position = position;

	SnakeNode *new_node = malloc(sizeof(SnakeNode));
	new_node->snake_tile = new_tile;
	
	//first tile?
	if (snake->head == NULL)
	{
		new_node->prev = NULL;
		snake->head = new_node;
		snake->tail = new_node;
	}
	//extend existing snake
	else
	{
		snake->tail->next = new_node;
		new_node->prev = snake->tail;
		snake->tail = new_node;
	}

	new_node->next = NULL;
	snake->size++;
}

void snake_free(Snake *snake)
{
	SnakeNode *curr = snake->head;
	SnakeNode *next;

	while (curr != NULL) {
		next = curr->next;
		free(curr->snake_tile);
		free(curr);
		curr = next;
	}

	snake->head = NULL;
	snake->tail = NULL;
	snake->size = 0;
}

bool snake_move(Snake *snake)
{
	Point prev_tile_pos_before_move;
	prev_tile_pos_before_move.x = -1;
	prev_tile_pos_before_move.y = -1;

	SnakeNode *curr = snake->head;

	//loop over tiles
	while (curr != NULL)
	{
		if (curr != snake->head)
		{
			//if we find tiles that are on top of each other we break
			if (
				prev_tile_pos_before_move.x == curr->snake_tile->position.x &&
				prev_tile_pos_before_move.y == curr->snake_tile->position.y
				)
			{
				break;
			}
		}

		prev_tile_pos_before_move = curr->snake_tile->position;

		Point *curr_dir = &curr->snake_tile->direction;
		Point *curr_pos = &curr->snake_tile->position;

		int new_x = curr_pos->x + curr_dir->x * MAP_TILE_SIZE;
		int new_y = curr_pos->y + curr_dir->y * MAP_TILE_SIZE;

		if (new_x < 0 || new_x >= MAP_SIZE || new_y < 0 || new_y >= MAP_SIZE)
		{
			assert(curr == snake->head);
			return false;
		}

		curr_pos->x = new_x;
		curr_pos->y = new_y;

		curr = curr->next;
	}

	// propagate direction change for all tiles except head
	curr = snake->tail;
	while (curr != snake->head)
	{
		curr->snake_tile->direction = curr->prev->snake_tile->direction;
		curr = curr->prev;
	}

	return true;
}

void snake_update_head_dir(Snake *snake, Direction direction)
{
	switch (direction)
	{
	case UP:
		snake->head->snake_tile->direction.x = 0;
		snake->head->snake_tile->direction.y = -1;
		break;
	case DOWN:
		snake->head->snake_tile->direction.x = 0;
		snake->head->snake_tile->direction.y = 1;
		break;
	case LEFT:
		snake->head->snake_tile->direction.x = -1;
		snake->head->snake_tile->direction.y = 0;
		break;
	case RIGHT:
		snake->head->snake_tile->direction.x = 1;
		snake->head->snake_tile->direction.y = 0;
		break;
	default:
		assert(false);
	}
}

void snake_print(const Snake *snake, void (*print_func)(const char*, ...)) {
	print_func("Snake size: %zu\n", snake->size);
	SnakeNode *curr = snake->head;
	while (curr != NULL) {
		SnakeTile *tile = curr->snake_tile;
		print_func("Tile position: (%d, %d), direction: (%d, %d)\n",
			tile->position.x, tile->position.y,
			tile->direction.x, tile->direction.y);
		curr = curr->next;
	}
}
