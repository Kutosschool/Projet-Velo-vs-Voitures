#ifndef _PROJECTILES_H_
#define _PROJECTILES_H_

#include <stdbool.h>
#include "player.h"
#include "enemies.h"

struct positionP
{
	int x;
	int y;
};
typedef struct positionP positionP;

struct projectile
{
	int damage;
    int piercing;       // Compte pour la "vie" d'un projectile, sera utilisé si l'on implémente les "power up"
	positionP pos;
    bool damagingPlayer;        //Pas encore utilisé mais permettrait d'avoir des projectiles ennemis
    struct projectile *previousProjectile;
    struct projectile *nextProjectile;
};
typedef struct projectile projectile;
typedef struct projectile *Projectile;


struct projectList{

    int quantity;
    struct projectile *firstProjectile;
    struct projectile *lastProjectile;
};
typedef struct projectList *ProjectileList;


ProjectileList initProjectileList();                                            //Initialise la liste de projectiles
Projectile createProjectilePlayer(player p);                                    //Crée un projectile tiré par le joueur
void insertProjectile(ProjectileList projectileList, Projectile projectile1);   //Ajoute un projectile dans une liste de projectiles
void deleteProjectile(ProjectileList projectileList);                           //Supprime les projectiles qui n'ont plus de "vies"
void resetProjectiles();                                                        //Reset la liste des projectile et supprime les projectiles pour lorsque l'on reset la partie

ProjectileList projectileList;






#endif