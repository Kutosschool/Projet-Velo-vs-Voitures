#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "projectiles.h"

ProjectileList initProjectileList(){    //Initialise la liste de projectiles
    ProjectileList newList = malloc(sizeof(ProjectileList));
    if(newList == NULL){
       exit(EXIT_FAILURE); 
    }
    newList->firstProjectile= NULL;
    newList->lastProjectile = NULL;
    newList->quantity = 0;
    return newList;
}


Projectile createProjectilePlayer(player p){    //Crée un projectile tiré par le joueur
    Projectile new = malloc(sizeof(projectile));
    int y = (p->pos.y)-1;
    int x = p->pos.x;
    new->pos.x = x;
    new->pos.y = y;
    new->damage = 1;
    new->piercing = 1;
    new->damagingPlayer = false;
    new->previousProjectile = NULL;
    new->nextProjectile = NULL;
    return new;
}

void insertProjectile(ProjectileList projectileList, Projectile projectile1){   //Ajoute un projectile dans une liste de projectiles
    Projectile new = malloc(sizeof(Projectile));
    if (new == NULL){
		exit(EXIT_FAILURE);
	}
    new = projectile1;
    if (projectileList->firstProjectile == NULL || projectileList->lastProjectile == NULL){
		projectileList->firstProjectile = new;
		projectileList->lastProjectile = new;
	}
    else{
        new->nextProjectile = projectileList->firstProjectile;
        projectileList->firstProjectile->previousProjectile = new;
        projectileList->firstProjectile = new;
    }

    projectileList->quantity += 1;
} 

void deleteProjectile(ProjectileList projectileList){   //Supprime les projectiles qui n'ont plus de "vies"
    if (projectileList->firstProjectile != NULL){
        Projectile base = malloc(sizeof(Projectile));
		if (base == NULL){
			exit(EXIT_FAILURE);
		}
        base = projectileList->firstProjectile;
        while(base != NULL){
            if(base->piercing <= 0){
                Projectile deleted = malloc(sizeof(Projectile));
                deleted = base;
                base = base->nextProjectile;
                if(projectileList->firstProjectile == deleted && projectileList->lastProjectile == deleted){
                    projectileList->firstProjectile = NULL;
                    projectileList->lastProjectile = NULL;
                }
                else if (projectileList->firstProjectile != deleted && projectileList->lastProjectile == deleted){
                    projectileList->lastProjectile = deleted->previousProjectile;
                    projectileList->lastProjectile->nextProjectile = NULL;
                }
                else if (projectileList->firstProjectile == deleted && projectileList->lastProjectile != deleted){
                    projectileList->firstProjectile = deleted->nextProjectile;
                    projectileList->firstProjectile->previousProjectile = NULL;
                }
                else{
                    deleted->nextProjectile->previousProjectile = deleted->previousProjectile;
                    deleted->previousProjectile->nextProjectile = deleted->nextProjectile;
                }
                free(deleted);
                projectileList->quantity--;
            }
            else{
                base = base->nextProjectile;
            }
        }
    }
}

void resetProjectiles(){    //Reset la liste des projectile et supprime les projectiles pour lorsque l'on reset la partie
    if (projectileList->firstProjectile != NULL){
        Projectile base = malloc(sizeof(Projectile));
		if (base == NULL){
			exit(EXIT_FAILURE);
		}
        base = projectileList->firstProjectile;
        while(base != NULL){
            Projectile deleted = malloc(sizeof(Projectile));
            deleted = base;
            base = base->nextProjectile;
            free(deleted);            
        }
        projectileList->quantity = 0;
        projectileList->firstProjectile = NULL;
        projectileList->lastProjectile = NULL;
    }
}