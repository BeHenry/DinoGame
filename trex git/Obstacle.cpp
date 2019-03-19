#include "Obstacle.h"

Obstacle::Obstacle(int i, float x, float y): GameObject(i)
{
	minGap = x;
	minSpeed = y;
	next = false;
	
}
Obstacle::Obstacle(int i, float x, float y, float vx, float vy, float w, float h, float m, float s): GameObject(x,y,vx,vy,w,h,i)
{
	minGap = m;
	minSpeed = s;
	next = false;

}
Obstacle::Obstacle(float currentSpeed, float x): GameObject()
{
	int selectedObstacle;
	float u = (float)rand()/(float)RAND_MAX;
	float coef = 3.5;
	
	//simulation du type (entier entre 1 et 3)
	if(currentSpeed < 4)
	{
		selectedObstacle = (rand() % 2)+1;
	}
	else
	{
		selectedObstacle = (rand() % 3)+1;
	}
	// simulation de la taille (entier entre 1 et 3)
	if(!(selectedObstacle==3))
	{
		gap =  10*currentSpeed+74+u*140*coef;
		if(((selectedObstacle == 1) and (currentSpeed > 2.5)) or ((selectedObstacle == 2) and (currentSpeed > 2.5)))
		{
			size = (rand() % 3)+1;
			
		}
		else 
		{
			size = 1;
		}
	}
	else
	{
		size = 1;
		gap = 20*currentSpeed+100*1+u*180*coef;
	}
	//vérification de la vitesse vias a vis de la taille tirer
		
		
		this->setParameters(x,Height(selectedObstacle), speed(selectedObstacle), (float)0, size*base_width(selectedObstacle), base_height(selectedObstacle), selectedObstacle);
	
	next = false;
	
	
}
Obstacle::~Obstacle()
{
}
float Obstacle::getGap()
{
	return gap;
}
void Obstacle::followingCreated()
{
	next = true;
}
bool Obstacle::isNextCreated()
{
	return next;
}
float base_height(int i)
{
	if(i==1)
	{
		return  40;//hauteur cactus
	}
	else if(i == 2)
	{
		return 30;//hauteur cactus XL
	}
	else if(i ==3)
	{
		return 30;//hauteur ptero
	}
}

float speed(int i)
{
	if(i==1)
	{
		return 0;//speed cactus
	}
	else if(i == 2)
	{
		return 0;//speed cactus XL
	}
	else if(i ==3)
	{
		return 0;//speed ptero
	}
}

float base_width(int i)
{
	if(i==1)
	{
		return 25;//hauteur cactus
	}
	else if(i == 2)
	{
		return 10;//hauteur cactus XL
	}
	else if(i ==3)
	{
		return 12.5;//hauteur ptero
	}
}


float Height(int i)
{
	if(i==1)
	{
		return 0; //hauteur cactus
	}
	else if(i == 2)
	{
		return 0;//hauteur cactus XL
	}
	else if(i ==3)
	{
		int u =(rand() % 3) +1;
		if(u==1)
		{
			return 0;
		}
		else if(u==2)
		{
			return 20;
		}
		else
		{
			return 40;
		}
		//hauteur ptero
	}
}
