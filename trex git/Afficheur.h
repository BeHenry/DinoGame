#ifndef DEF_AFFICHEUR
#define DEF_AFFICHEUR
#include <vector>
#include <SDL2/SDL.h>
#include "Asset.h"
#include "Game.h"
class Afficheur
{
	public:
	void affichage(Game* jeu, int fameid);
	Afficheur(SDL_Renderer* r, int x, int y);
	~Afficheur();
	void addAsset(Asset as, SDL_Rect rendu);
	
	private:
	SDL_Renderer* rend;
	std::vector<Asset> assets;
	std::vector<SDL_Rect> renduAssets;
	int xpos;
	int ypos;
	int currentSpeed = 1;

};

#endif
