#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "enemies.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>



EnemyList initEnemyList(){  //Initialise la liste d'ennemis
    EnemyList eList = malloc(sizeof(enemyList));
    if(eList == NULL){
       exit(EXIT_FAILURE); 
    }
    eList->firstEnemy = NULL;
    eList->lastEnemy = NULL;
    eList->quantity = 0;
    return eList;
}

Enemy createEnemy(int maxY, int maxX, int difficulty){  //Crée un ennemi
    Enemy new = malloc(sizeof(enemies));
    int y = (rand() %(maxY/8)+1);
    int x = (rand() %(maxX-2)+1);
    
    if (new == NULL){
        exit(EXIT_FAILURE);
    }
    new->position.x = x;
    new->position.y = y;
    new->life = difficulty;
    new->previousEnemy = NULL;
    new->nextEnemy = NULL;
    return new;
}

void insertEnemy(EnemyList eList, Enemy enemy1){    //Insère un ennemi dans la liste
    Enemy new = malloc(sizeof(enemies));
    if (new == NULL){
		exit(EXIT_FAILURE);
	}
    new = enemy1;
    if (eList->firstEnemy == NULL && eList->lastEnemy == NULL){
		eList->firstEnemy = new;
		eList->lastEnemy = new;
	}
    else{
        new->nextEnemy = eList->firstEnemy;
        eList->firstEnemy->previousEnemy = new;
        eList->firstEnemy = new;
    }

    eList->quantity += 1;
}   

void deleteEnemy(EnemyList eList){  //Supprime les ennemis qui n'ont pas de vie
    if (eList->firstEnemy != NULL){
        Enemy base = malloc(sizeof(Enemy));
		if (base == NULL){
			exit(EXIT_FAILURE);
		}
        base = eList->firstEnemy;
        while(base != NULL){
            if(base->life <= 0){
                Enemy deleted = malloc(sizeof(Enemy));
                deleted = base;
                base = base->nextEnemy;
                if(eList->firstEnemy == deleted && eList->lastEnemy == deleted){
                    eList->firstEnemy = NULL;
                    eList->lastEnemy = NULL;
                }
                else if (eList->firstEnemy != deleted && eList->lastEnemy == deleted){
                    eList->lastEnemy = deleted->previousEnemy;
                    eList->lastEnemy->nextEnemy = NULL;
                }
                else if (eList->firstEnemy == deleted && eList->lastEnemy != deleted){
                    eList->firstEnemy = deleted->nextEnemy;
                    eList->firstEnemy->previousEnemy = NULL;
                }
                else{
                    deleted->nextEnemy->previousEnemy = deleted->previousEnemy;
                    deleted->previousEnemy->nextEnemy = deleted->nextEnemy;
                }
                free(deleted);
                eList->quantity--;
            }
            else{
                base = base->nextEnemy;
            }
        }
    }
}

void resetEnemies(){    //Reset la liste d'ennemis et supprime les ennemis
    if (eList->firstEnemy != NULL){
        Enemy base = malloc(sizeof(Enemy));
		if (base == NULL){
			exit(EXIT_FAILURE);
		}
        base = eList->firstEnemy;
        while(base != NULL){
            Enemy deleted = malloc(sizeof(Enemy));
            deleted = base;
            base = base->nextEnemy;
            free(deleted);
        }
        eList->quantity=0;
        eList->firstEnemy=NULL;
        eList->lastEnemy=NULL;
    }
}