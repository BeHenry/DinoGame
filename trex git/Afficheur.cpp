#include "Afficheur.h"

Afficheur::Afficheur(SDL_Renderer* r, int x, int y)
{
	rend = r;
	xpos = x;
	ypos = y;
}

Afficheur::~Afficheur(){
}

void Afficheur::affichage(Game* jeu, int fameid)
{
	
	SDL_Rect temp;
	SDL_Rect temp2;
	//Affichage du décors
	int id = 4;
	int dinoXpos = jeu->getXObj(0);
	temp = renduAssets[id];
	temp.y = 130+ypos;
	int r = dinoXpos % temp.w;
	temp.x=-r;
	
	SDL_RenderCopy(rend,assets[id].getTexture(),assets[id].getRect(fameid),&temp);
	// Affichage de objet de jeu
	if(temp.x+temp.w<600)
	{
		temp.x=temp.x+temp.w;
		SDL_RenderCopy(rend,assets[id].getTexture(),assets[id].getRect(fameid),&temp);
	}
	int n = jeu->nObjects(); 
	
	for(int i = 0; i < n; i++)
	{
		id = jeu->getObjId(i);
		temp = renduAssets[id];
		temp.x = xpos + jeu->getXObj(i)-dinoXpos+30;
		
		temp.y = ypos+105 - jeu->getYObj(i);
		
		temp2 = *assets[id].getRect(fameid);
		temp2.w = temp2.w*jeu->getSizeObj(i);
		temp.w = temp.w*jeu->getSizeObj(i);
		SDL_RenderCopy(rend,assets[id].getTexture(),&temp2,&temp);
	}
	
	
	
	
	
	
}

void Afficheur::addAsset(Asset as, SDL_Rect rendu)
{
	assets.push_back(as);
	renduAssets.push_back(rendu);
}
