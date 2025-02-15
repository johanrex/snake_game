#include "fruit.h"
#include <stdbool.h>
#include <stdlib.h> // Include this header for NULL and rand()

Fruit fruit_spawn(Snake * snake)
{
	bool fruit_spawned = false;

	int x = -1; // Initialize x
	int y = -1; // Initialize y

	// Check if snake fills the whole map. If it does, don't spawn any more fruit. 
	// TODO: Should probably stop the game at this point. 
	if (snake->size < MAP_SIZE * MAP_SIZE)
	{
		while (!fruit_spawned)
		{
			x = rand() % MAP_SIZE;
			y = rand() % MAP_SIZE;

			//check if the fruit is on the snake
			SnakeNode* curr = snake->head;
			while (curr != NULL)
			{
				if (curr->snake_tile->position.x == x && curr->snake_tile->position.y == y)
					break;
				curr = curr->next;
			}

			fruit_spawned = true;
		}
	}

	Fruit fruit;
	fruit.x = x;
	fruit.y = y;

	return fruit;
}

void fruit_remove(Fruit* fruit)
{
	fruit->x = -1;
	fruit->y = -1;
}
