#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>


#include "loadMap.h"
#include "drawMap.h"
#include "game.h"

#include "Pause.c"
#include "Lost.c"


void drawMap(int maxX, int maxY){	// Affiche la map lue dans le fichier map.txt par loadmap

	
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{ 
			if(map[y][x] == '#')
			{
                glColor3f(0.0f,0.0f,0.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(x*Square_size,y*Square_size,0.0f);
				
				
				glBegin(GL_QUADS);
				glColor3f(1.0,1.0,1.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
				
			}
			
			
			if (map[y][x]  == '1')
			{
				glColor3f(1.0f,1.0f,1.0f);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(x*Square_size,y*Square_size,0.0f);
				
				glBegin(GL_QUADS);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(Square_size, 0.0f, 0.0f);
					glVertex3f(Square_size,Square_size, 0.0f);
					glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
			}
                 
			if (map[y][x]  == '.' || map[y][x]  == 'X')
			{
				glColor3f(0.5f,0.5f,0.5f);

				glMatrixMode(GL_MODELVIEW);
				
				glLoadIdentity();
				glTranslatef(x*Square_size,y*Square_size,0.0f);
				glBegin(GL_QUADS);

				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
			}	
		}
	}
}



void drawPlayer()	// Affiche le joueur et le fait "clignotter" quand le joueur perd de la vie
{
	int x = p->pos.x;
	int y = p->pos.y;

	if (p->hit >0 && p->life >0){
		p->hit --;
	}
	else{
		if (p->life >0){
			glColor3f(0.0f,1.0f,0.0f);
		}
		else{
			glColor3f(0.0f,0.0f,0.0f);
		}
		
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x*Square_size,y*Square_size,0.0f);

		glBegin(GL_QUADS);
		if (p->life >0){
			
		}
		else{
			
		}
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(Player_size, 0.0f, 0.0f);
		glVertex3f(Player_size,Player_size, 0.0f);
		glVertex3f(0.0f,Player_size, 0.0f);

		glEnd();
	}
	
}

void drawPauseOrDeath()	// Affiche le "menu" pause ou perdu
{
	int x= 25, y = 25;
	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((x*Square_size)-Pause.width/2,(y*Square_size)-Pause.height/2,0.0f);
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	if(runningGame->lost){
		gluBuild2DMipmaps(GL_TEXTURE_2D,Lost.bytes_per_pixel, Lost.width, Lost.height,GL_RGBA,GL_UNSIGNED_BYTE,Lost.pixel_data);
	}
	else{
		gluBuild2DMipmaps(GL_TEXTURE_2D,Pause.bytes_per_pixel, Pause.width, Pause.height,GL_RGBA,GL_UNSIGNED_BYTE,Pause.pixel_data);	
	}
	
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);
	

	glTexCoord2f(0.0,0.0);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0,0.0);  glVertex3f(Pause.width, 0.0f, 0.0f);
	glTexCoord2f(1.0,1.0);  glVertex3f(Pause.width,Pause.height, 0.0f); 
	glTexCoord2f(0.0,1.0);  glVertex3f(0.0f,Pause.height, 0.0f);
	

	
	glEnd();
	
	glDisable(GL_TEXTURE_2D); 
	
}

void drawEnemy(Enemy enemy){	// Affiche un ennemi
	int x = enemy->position.x;
	int y = enemy->position.y;

	glColor3f(1.0f,0.0f,0.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((x-0.5)*Square_size,(y-0.5)*Square_size,0.0f);

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(Enemy_size, 0.0f, 0.0f);
	glVertex3f(Enemy_size,Enemy_size, 0.0f);
	glVertex3f(0.0f,Enemy_size, 0.0f);

	glEnd();
}

void drawAllEnemies(EnemyList eList){	// Appelle la fonction drawEnemy() pour chaque ennemi
	Enemy first = malloc(sizeof(enemies));
	Enemy next = malloc(sizeof(enemies));
	first = eList->firstEnemy;
	next = first->nextEnemy;
	if (first != NULL){
		drawEnemy(first);
		if(next !=NULL){
			drawEnemy(next);
			while(next->nextEnemy != NULL){
				next = next->nextEnemy;
				drawEnemy(next);
			}
		}
	}
}

void drawProjectile(Projectile projectile){	// Affiche un projectile
	int x = projectile->pos.x;
	int y = projectile->pos.y;

	glColor3f(1.0f,1.0f,1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((x*Square_size)+2.5,y*Square_size,0.0f);

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(Projectile_size, 0.0f, 0.0f);
	glVertex3f(Projectile_size,Projectile_size, 0.0f);
	glVertex3f(0.0f,Projectile_size, 0.0f);

	glEnd();
}

void drawAllProjectiles(ProjectileList projectileList){	// Appelle la fonction drawProjectile() pour chaque projectile
	Projectile first = malloc(sizeof(projectile));
	Projectile next = malloc(sizeof(projectile));
	first = projectileList->firstProjectile;
	next = first->nextProjectile;
	if (first != NULL){
		drawProjectile(first);
		if(next !=NULL){
			drawProjectile(next);
			while(next->nextProjectile != NULL){
				next = next->nextProjectile;
				drawProjectile(next);
			}
		}
	}
}

void displayScore(){	// Affiche le score
	glRasterPos2f(0., 0.);
	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(10,550,0.0f);
	glRasterPos2f(0.0, 0.95);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	int score = runningGame->score;
	int i = 0;
	if (score == 0){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
	}
	else{
		while(score != 0){
			score = score/10;
			i++;
		}
		while(i!=0){
			score = runningGame->score;
			if (i==1){
				score = score%10;
				char display = score + '0';
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, display);
				i--;
			}
			else{
				//score = score % (i-1)*10;
				int j= i;
				int power=1;
				while (j>1){
					power = power*10;
					j--;
				}
				score = score%(power*10);
				score = score/power;
				char display = score + '0';
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, display);
				i--;
			}
			
		}
	}
	
	glEnd();

}

void displayLife(){	// Affiche la vie du joueur
	glRasterPos2f(0., 0.);
	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(250,550,0.0f);
	glRasterPos2f(0.0, 0.95);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'f');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	int life = runningGame->life;
	if(life == 3){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	}
	if(life == 2){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	}
	if(life == 1){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	}
	if(life == 0){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	}
	

	
	glEnd();

}

