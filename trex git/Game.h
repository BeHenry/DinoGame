#ifndef DEF_GAME
#define DEF_GAME
#include "GameObject.h"
#include "Obstacle.h"
#include "Gamepad.h"
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <vector>
#include "aux/Matrix.h"
class Game
{
	private:
	
	Gamepad* m_padPlayer1;
	bool m_gameState;
	std::vector<GameObject*> objects;
	void addObstacle();
	void generateObstacle();
	
	
	
	public:
	Game(Gamepad* pad1);
	~Game();
	bool frameUpdate();
	void reinit();
	void setPads(Gamepad* pad);
	void newObstacle();
	Matrix GameState();
	int nObjects();
	int getObjId(int i);
	int getXObj(int i);
	int getYObj(int i);
	int getSizeObj(int i);
	
};

#endif
