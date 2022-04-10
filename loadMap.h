#ifndef _LOADMAP_H_
#define _LOADMAP_H_

#include <stdbool.h>

#define Square_size 10.0

char **map;

int maxX,maxY;

bool loadMap(int maxX, int maxY); //Crée un tableau dynamique pour représenter le fichier map.txt

#endif