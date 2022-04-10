#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h> 

#include "game.h"
#include "loadMap.h"
#include "drawMap.h"
#include "projectiles.h"
//#include "player.h"


bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool RESET = false;


Game initGame(){	//Initialise une structure partie qui contient des informations importantes sur la partie en cours
	Game new = malloc(sizeof(Game));
	new->paused = false;
	new->score = 0;
	new->life = p->life;
	new->lost = false;
	return new;
}

void resetGame(){	//Reset la structure Game en cours
	runningGame->life = 3;
	runningGame->score = 0; 
	runningGame->paused = false;
	runningGame->lost = false;
}
void resetAll(){	//Appelle un reset de tous les paramètres de la partie
	resetEnemies();
	resetPlayer();
	resetProjectiles();
	resetGame();
}




void Keyboard(unsigned char key, int x, int y)  //Fonction Switch qui gère les inputs qu'elle reçois de la fonction glut glutKeyboardFunc()
{
	switch(key)
	{
		case 27:
			exit(0);

		case'z':
			UP = true;
			break;

		case'q':
			LEFT = true;
			break;

		case'd':
			RIGHT = true;
			break;

		case's':
			DOWN = true;
			break;

		case' ':
			SHOOT = true;
			break;

		case'p':
			runningGame->paused = !runningGame->paused ;
			break;

		case'r':
			resetAll();
			break;
		
		case 'y':
			if(runningGame->paused || runningGame->lost){
				exit(0);
			}
			break;
			
			
	}		
}

void game(int mX, int mY, player p, EnemyList enemies, ProjectileList projectilelist)	//Fonction qui gère toute la logique de la partie, appelle les différentes fonctions d'affichage
{
	
	drawMap(maxX, maxY);			
	drawPlayer(p);
	displayScore();
	displayLife();
	
	if(enemies->firstEnemy !=NULL || enemies->lastEnemy !=NULL){
		drawAllEnemies(enemies);
	}
	if(projectilelist->firstProjectile != NULL || projectilelist->lastProjectile != NULL){
		drawAllProjectiles(projectileList);
	}
	if(runningGame->paused){
		drawPauseOrDeath();
	}
	
	
	glutKeyboardFunc(Keyboard);
	if(runningGame->lost){
		runningGame->paused = true;
	}
	if(runningGame->paused){
		UP = false;
		LEFT = false;
		RIGHT = false;
		DOWN = false;
		SHOOT = false;
	}
	if (LEFT == true)
	{
		
		moveLeft(p);		
		LEFT = false;
		
	}
	if (RIGHT == true)
	{
		
		moveRight(p);
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(p);
		UP = false;
	}
	
	if (DOWN == true)
	{
        moveDown(p);
		DOWN = false;
	}
	if (SHOOT == true)
	{
		Projectile new = createProjectilePlayer(p);
        insertProjectile(projectileList,new);
		SHOOT = false;
	}
	glutPostRedisplay();
}

void checkEnemyCollision(Enemy enemy1, Projectile projectile1){		//Vérifie les collisions entre enemis et projectiles, modifie les vies ainsi que le score si il y a une collision
	bool colisionX = false,colisionY = false;
	double projectileXMost = (((projectile1->pos.x)*Square_size)+ 2.5 + (Projectile_size/2));
	double projectileXLeast = (((projectile1->pos.x)*Square_size)- 2.5 - (Projectile_size/2));
	double enemyXMost = (((enemy1->position.x)*Square_size) + 0.5 + (Enemy_size/2));
	double enemyXLeast = (((enemy1->position.x)*Square_size) + 0.5 - (Enemy_size/2));

	if ((enemyXLeast - projectileXMost)< 0.000 && (enemyXMost - projectileXLeast )> 0.000){
		colisionX = true;
	}
	if (projectile1->pos.y == enemy1->position.y){
		colisionY = true;
	}
	if (colisionX && colisionY){
		enemy1->life = enemy1->life-projectile1->damage ;
		projectile1->piercing --;
		runningGame->score ++;
	}
}

void checkPlayerEnemyCollision(Enemy enemy1,player p){	//Vérifie les collisions entre enemis et player, modifie la vie
	bool colisionX = false,colisionY = false;
	double playerXMost = (((p->pos.x)*Square_size)+(Square_size/2));
	double playerXLeast = (((p->pos.x)*Square_size)-(Square_size/2));
	double enemyXMost = (((enemy1->position.x)*Square_size) + 0.5 + (Enemy_size/2));
	double enemyXLeast = (((enemy1->position.x)*Square_size) + 0.5 - (Enemy_size/2));
	if ((enemyXLeast - playerXMost)< 0.000 && (enemyXMost - playerXLeast )> 0.000){
		colisionX = true;
	}
	if (p->pos.y == enemy1->position.y ){
		colisionY = true;
	}
	if (colisionX && colisionY){
		p->life = p->life - 1 ;
		runningGame->life --;
		p->hit = 50;
	}
}