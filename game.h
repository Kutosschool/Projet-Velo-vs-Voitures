#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include "projectiles.h"

struct game{
    int score;
    bool paused;
    int life;
    bool lost;
};
typedef struct game *Game;

Game runningGame;

Game initGame();                                                                        //Initialise une structure partie qui contient des informations importantes sur la partie en cours
void Keyboard(unsigned char key, int x, int y);                                         //Fonction Switch qui gère les inputs qu'elle reçois de la fonction glut glutKeyboardFunc()
void game(int mX, int mY, player p, EnemyList enemies, ProjectileList projectilelist);  //Fonction qui gère toute la logique de la partie, appelle les différentes fonctions d'affichage
void checkEnemyCollision(Enemy enemy1, Projectile projectile1);                         //Vérifie les collisions entre enemis et projectiles, modifie les vies ainsi que le score si il y a une collision
void checkPlayerEnemyCollision(Enemy enemy1,player p);                                  //Vérifie les collisions entre enemis et player, modifie la vie 
void resetGame();                                                                       //Reset la structure Game en cours
void resetAll();                                                                        //Appelle un reset de tous les paramètres de la partie

#endif