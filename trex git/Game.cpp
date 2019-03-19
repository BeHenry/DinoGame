#include "Game.h"

Game::Game(Gamepad* pad1)
{
	m_padPlayer1 = pad1;
	GameObject* dino = new GameObject(0,0,2,0,30,35,0);
	dino->setAcceleration(0.0005);
	objects.push_back(dino);

}

Game::~Game()
{
	for(int i = 0; i<objects.size(); i++)
	{
		delete objects[i];
	}
}
void Game::setPads(Gamepad* pad)
{
	m_padPlayer1 = pad;
}

void Game::reinit()
{
	for(int i = 0; i<objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
	GameObject* dino = new GameObject(0,0,2,0,45,35,0);
	dino->setAcceleration(0.0005);
	objects.push_back(dino);
}

void Game::addObstacle()
{
	
	float next;
	if(objects.size()>1)
	{
		
		
			
			
		next = objects[1]->getXPos()+objects[1]->getWidth()+((Obstacle *)objects[1])->getGap();
		
	
		if((((next-objects[0]->getXPos())>600)) and !(((Obstacle *)objects[1])->isNextCreated()))
		{
			
			objects.push_back(new Obstacle(objects[0]->getSpeed(),next));
			((Obstacle *)objects[1])->followingCreated();
		}	
		
	}
	else
	{
		objects.push_back(new Obstacle(objects[0]->getSpeed(),  objects[0]->getXPos()+600));
		
		
	}
}

void Game::generateObstacle()
{
	int max = 50;
	float time = 700;
	float u;
	for (int i = 1; i<max; i++)
	{
		u=(float)rand()/(float)RAND_MAX;
		time=150+time-100*log(u);
		
	}
	
}
Matrix Game::GameState()
{
	Matrix M = Matrix(9,1);
	M.assign(1,1,objects[0]->getYPos());
	int n = objects.size();
	for(int i = 1; i<3; i++)
	{
		if(i<n)
		{
			M.assign(4*i-2,1,objects[i]->getXPos()-objects[0]->getXPos());
			M.assign(4*i-1,1,objects[i]->getYPos());
			M.assign(4*i,1,objects[i]->getWidth());
			M.assign(4*i+1,1,objects[i]->getHeight());
		}
		else
		{
			M.assign(4*i-2,1,-1);
			M.assign(4*i-1,1,-1);
			M.assign(4*i,1,-1);
			M.assign(4*i+1,1,-1);
		}
	}
	return M;
}
bool Game::frameUpdate()
{
	
	
	bool terminer = false;
	this->addObstacle();
	
	int retour = m_padPlayer1->getInput(this->GameState());
	if (retour==1)
	{
		objects[0]->jump();
	}
	
	objects[0]->upDatePosition();
	objects[0]->upDateVelocity();
	for (int i=1; i<objects.size(); i++)
	{
		terminer = terminer || (checkCollision(*objects[0], *objects[i]));
		if(objects[i]->getXPos()-objects[0]->getXPos()<-70)
		{
			delete objects[i];
			objects.erase(objects.begin()+i);
		}
	}
	
	return terminer;
}
int Game::nObjects()
{
	return objects.size();
}
int Game::getObjId(int i)
{
	return objects[i]->getId();
}
int Game::getXObj(int i)
{
	return floor(objects[i]->getXPos());
}
int Game::getYObj(int i)
{
	return floor(objects[i]->getYPos());
}
int Game::getSizeObj(int i)
{
	return floor( objects[i]->size);
}
/*
void Game::reinit()
{
	m_scorep1 = 0;
	m_scorep2 = 0;
}
*/


