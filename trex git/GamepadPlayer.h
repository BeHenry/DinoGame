#ifndef DEF_GAMEPADPLAYER
#define DEF_GAMEPADPLAYER
#include "Gamepad.h"
#include "aux/Matrix.h"
#include "SDL2/SDL.h"
class GamepadPlayer : public Gamepad
{
	private:
	SDL_Event evenements;
	
	public:
	GamepadPlayer();
	~GamepadPlayer();
	int getInput(Matrix GameState);
};

#endif
