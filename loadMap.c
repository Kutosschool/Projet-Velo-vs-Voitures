#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "loadMap.h"

bool loadMap(int maxX, int maxY){	//Crée un tableau dynamique pour représenter le fichier map.txt

    map = malloc(sizeof(char *) * maxX);
    FILE *mapfile = NULL;
    mapfile = fopen("map.txt", "r");
    if(mapfile == NULL)
    {
        printf("Erreur, fichier vide.\n");
        return false;
    }
    char c;
	int x=0,y=0;
	
    for(y = 0; y < maxY; y++)
    {
        *(map + y) = malloc(sizeof(char *) * maxY);	
		for(x = 0; x < maxX; x++)
		{		
			c = fgetc(mapfile);
			*(*(map+y)+x) = c;
		}
		fgetc(mapfile);
    }
	fclose(mapfile);
		
    printf("\n");
	for(y = 0; y < maxY; y++)
	{
		for(x = 0; x < maxX; x++)
		{
			printf("%c", *(*(map+y)+x));
		}
		printf("\n");
	}
 return true;
 }	