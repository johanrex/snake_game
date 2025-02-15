#ifndef COMMON_H
#define COMMON_H

#define MAP_SIZE 50
#define MAP_TILE_SIZE 1

typedef enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct Point
{
	int x;
	int y;
} Point;


#endif // !COMMON_H
