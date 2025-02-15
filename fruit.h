#ifndef FRUIT_H
#define FRUIT_H

#include "common.h"
#include "snake.h"

typedef Point Fruit;

Fruit fruit_spawn(Snake* snake);
void fruit_remove(Fruit* fruit);

#endif // !FRUIT_H

