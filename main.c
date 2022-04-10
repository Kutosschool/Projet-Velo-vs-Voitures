#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "loadMap.h"
#include "drawMap.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "projectiles.h"


int difficulty = 1;
int enemySpeed = 1;


void playerEnemyCollisions(int enemySpeed){             //Appelle la fonction de check des collisions entre joueur et ennemi pour chaque ennemi
    if(!runningGame->paused){
        if (eList->firstEnemy != NULL && eList->lastEnemy != NULL){
            Enemy checkedEnemy = eList->firstEnemy;
            while(checkedEnemy != NULL){
                checkPlayerEnemyCollision(checkedEnemy,p);
                checkedEnemy = checkedEnemy->nextEnemy;
            } 
        }
    }
    glutPostRedisplay();
    glutTimerFunc(200, playerEnemyCollisions, 0);
}

void enemyProjectileCollisions(){                     //Appelle la fonction de check des collisions entre projectile et ennemi pour chaque ennemi
    if(!runningGame->paused){
        if (eList->firstEnemy != NULL && eList->lastEnemy != NULL){
            if (projectileList->firstProjectile != NULL && projectileList->lastProjectile != NULL){
                Enemy checkedEnemy = eList->firstEnemy;
                Projectile checkedProjectile = projectileList->firstProjectile;
                while(checkedEnemy !=NULL){
                    while(checkedProjectile != NULL){
                    checkEnemyCollision(checkedEnemy,checkedProjectile);
                    checkedProjectile = checkedProjectile->nextProjectile;
                    }
                    checkedProjectile = projectileList->firstProjectile;
                    checkedEnemy = checkedEnemy->nextEnemy;
                }    
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(10, enemyProjectileCollisions, 0);
}

void scrollEnemies(int enemySpeed){                             //Cette fonction déplace les enemis d'une case vers le bas, si l'ennemi est arrive en bas de la zone de jeu, il est déplacé en haut
    if(!runningGame->paused){                                   //et peut être déplacé à une position y au hasard ou placé sur la même colonne que le joueur ou simplement replacé en haut de la ligne
        Enemy enemy1 = eList->firstEnemy;
        if (enemy1 != NULL){
            
            enemy1->position.y += 1;
            if(enemy1->position.y >= maxY-2){
                int randomness = rand()%3;
                enemy1->position.y = 1;
                if(randomness == 0){
                    enemy1->position.x = p->pos.x;
                }
                if(randomness == 1){
                    enemy1->position.x = (rand() %(maxX-2)+1);
                }
            }
            while(enemy1->nextEnemy != NULL){
                enemy1 = enemy1->nextEnemy;
                enemy1->position.y += enemySpeed;
                if(enemy1->position.y >= maxY-2){
                    int randomness = rand()%3;
                    enemy1->position.y = 1;
                    if(randomness == 0){
                        enemy1->position.x = p->pos.x;
                    }
                    if(randomness == 1){
                        enemy1->position.x = (rand() %(maxX-2)+1);
                    }
                }
            }
        }
        
    }
    glutPostRedisplay();
    glutTimerFunc(199, scrollEnemies, 1);
}
void scrollProjectiles(){                                           // Déplace les projectiles vers le haut, si ils arrivent tout en haut de la zone de jeu, ils sont marqués pour être supprimés par
    if(!runningGame->paused){                                       // la fonction deleteProjectile()
        Projectile projectile1 = projectileList->firstProjectile;
        if (projectile1 != NULL){
            projectile1->pos.y --;
            if(projectile1->pos.y <= 1){
                projectile1->piercing = 0;
            }
            while(projectile1->nextProjectile != NULL){
                projectile1 = projectile1->nextProjectile;
                projectile1->pos.y --;
                if(projectile1->pos.y <= 1){
                    projectile1->piercing = 0;
                }
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, scrollProjectiles, 1);
}
void deleteProjectiles(){                                       // Appelle la fonction deleteProjectile() pour tous les projectiles
    if(!runningGame->paused){
        if (projectileList->firstProjectile != NULL || projectileList->lastProjectile != NULL){
            deleteProjectile(projectileList);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(10, deleteProjectiles, 4);
}
void spawnNewEnemies(){                                         // Si il y a moins de 10 ennemis sur la zone de jeu, cette fonction appelle la fonction createEnemy() pour en créer de nouveaux
    if(!runningGame->paused){
        Enemy new = createEnemy(maxY, maxX, difficulty);
        if (eList->quantity < 10){
            insertEnemy(eList, new);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000, spawnNewEnemies, 3);
}

void deleteEnemies(){                                       // Appelle la fonction deleteEnemy() pour chaque ennemi
    if(!runningGame->paused){
        if (eList->firstEnemy != NULL || eList->lastEnemy != NULL){
            deleteEnemy(eList);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, deleteEnemies, 4);
}
/*void initRendering()                                        // Fonction GLUT non utilisée
{
	glEnable(GL_DEPTH_TEST);
}*/

void display(){                                                //Fonction GLUT qui permet de update notre jeu
    glClearColor(0.25f,0.25f,0.25f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (p->life <=0){
        runningGame->lost = true;
    }
    game(maxX,maxY,p, eList, projectileList);
    
    //drawMap(maxX,maxY);
	//glutSwapBuffers() ;
	glFlush();
}
void handleResize(int width,int heigth)                     //Fonction GLUT pour prendre en charge le resize de la fenetre
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, heigth, 0);
}

int main(int argc, char*argv[]){
    srand(time(NULL));                  //génère une seed pour les nombres random générés plus tard. Elle est liée au temps de la machine pour ne pas être la même à chaque fois
    maxX = 50;
    maxY = 50;
    
    loadMap(maxX,maxY);
    p = createPlayer(maxX,maxY);
    runningGame = initGame();
    eList = initEnemyList();
    projectileList = initProjectileList();


    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(maxY*Square_size, maxX*Square_size+100);             //Fonction glut qui décide de la taille de la fenètre de jeu
    glutCreateWindow("Voiture vs Velo");
    //initRendering();
    
    glutReshapeFunc(handleResize);
    glutDisplayFunc(display);
    glutTimerFunc(10, enemyProjectileCollisions, 0);
    glutTimerFunc(5, playerEnemyCollisions, 0);
    glutTimerFunc(10, scrollEnemies, 1);
    glutTimerFunc(10, scrollProjectiles, 2);
	glutTimerFunc(30, spawnNewEnemies, 3);
	glutTimerFunc(20, deleteEnemies, 4);
    glutTimerFunc(10, deleteProjectiles, 5);
    
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}