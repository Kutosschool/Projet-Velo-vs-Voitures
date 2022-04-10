#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct positionE
{
    int x;
    int y;
};
typedef struct positionE positionE;

typedef struct enemies enemies;
struct enemies{

    positionE position;
    int life;
    struct enemies *previousEnemy;
    struct enemies *nextEnemy;
};

typedef struct enemyList enemyList;
struct enemyList{

    int quantity;
    struct enemies *firstEnemy;
    struct enemies *lastEnemy;
};



typedef struct enemies *Enemy; 
typedef struct enemyList *EnemyList;
Enemy createEnemy(int maxY, int maxX, int difficulty);      //Crée un ennemi
EnemyList initEnemyList();                                  //Initialise la liste d'ennemis
void insertEnemy(EnemyList eList, Enemy enemy);             //Insère un ennemi dans la liste
void deleteEnemy(EnemyList eList);                          //Supprime les ennemis qui n'ont pas de vie
void resetEnemies();                                        //Reset la liste d'ennemis et supprime les ennemis
Enemy enemy1;
EnemyList eList;








#endif
