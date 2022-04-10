#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include "loadMap.h"
#include "player.h"
#include "enemies.h"
#include "projectiles.h"
#include <math.h>

// Définition de la taille des entités en pixels
#define Player_size 10.0
#define Enemy_size 20.0
#define Projectile_size 5.0

void drawMap(int maxX, int maxY);                       // Affiche la map lue dans le fichier map.txt par loadmap
void drawPlayer();                                      // Affiche le joueur et le fait "clignotter" quand le joueur perd de la vie
void drawEnemy(Enemy enemy);                            // Affiche un ennemi
void drawAllEnemies(EnemyList eList);                   // Appelle la fonction drawEnemy() pour chaque ennemi
void drawProjectile(Projectile projectile);             // Affiche un projectile
void drawAllProjectiles(ProjectileList projectileList); // Appelle la fonction drawProjectile() pour chaque projectile
void drawPauseOrDeath();                                // Affiche le "menu" pause ou perdu
void displayScore();                                    // Affiche le score
void displayLife();                                     // Affiche la vie du joueur


#endif