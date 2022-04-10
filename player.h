#ifndef _PLAYER_H_
#define _PLAYER_H_

struct position
{
	int x;
	int y;
};
typedef struct position position;
struct play
{
	int life;
	position pos;
	int hit;		//Indice si le joueur à été touché, permet le "clignotement"
};

typedef struct play *player;


player createPlayer(int maxX, int maxY);	//Crée un player
void resetPlayer();							//Reset le player
void moveLeft(player p);					//Déplace le joueur à gauche
void moveRight(player p);					//Déplace le joueur à droite
void moveUp(player p);						//Déplace le joueur en haut
void moveDown(player p);					//Déplace le joueur en bas	


player p;


#endif