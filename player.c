#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


player createPlayer(int maxX, int maxY)	//Crée un player
{
	player p;

	int xplayer = 0, yplayer = 0;

	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if(*(*(map+y)+x) == 'X')
			{
				xplayer = x;
				yplayer = y;
			}
		}
	}
	p = malloc(sizeof(player));
	p->life = 3;
	p->pos.x = xplayer;
	p->pos.y = yplayer;
	p->hit = 0;
	return p;
}

void resetPlayer(){	//Reset le player
	int xplayer = 0, yplayer = 0;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if(*(*(map+y)+x) == 'X')
			{
				xplayer = x;
				yplayer = y;
			}
		}
	}
	p->life = 3;
	p->pos.x = xplayer;
	p->pos.y = yplayer;
	p->hit = 0;
}

void moveLeft(player p){	//Déplace le joueur à gauche
	int x = 0, y = 0;
	x = p->pos.x-1;
	y = p->pos.y;
	if (*(*(map + x) + y)!='#'){
		p->pos.x = x;
	}

}

void moveRight(player p){	//Déplace le joueur à droite
	int x = 0, y = 0;
	x = p->pos.x+1;
	y = p->pos.y;
	if (*(*(map + x) + y)!='#'){
		p->pos.x = x;
	}
}

void moveUp(player p){	//Déplace le joueur en haut
	int  x = 0, y = 0;    
	x = p->pos.x;
	y = p->pos.y-1;
	if (*(*(map + x) + y)!='#'){
		p->pos.y = y;
	}
}

void moveDown(player p){	//Déplace le joueur en bas
	int  x = 0, y = 0;
	x = p->pos.x;
	y = p->pos.y+1;
	if (*(*(map + x) + y) !='#'){
	p->pos.y = y;
	}
}
