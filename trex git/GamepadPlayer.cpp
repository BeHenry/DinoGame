#include "GamepadPlayer.h"

GamepadPlayer::GamepadPlayer()
{
}
GamepadPlayer::~GamepadPlayer()
{
}

int GamepadPlayer::getInput(Matrix gameState)
{
	int retour = 0;
	SDL_PollEvent(&evenements);
	if (evenements.type==SDL_KEYDOWN)
	{
		retour = 1;
	}
	else if (evenements.type == SDL_QUIT)
	{
		retour = 2;
	}
	
	
	return retour;
}
