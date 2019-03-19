#ifndef DEF_OBSTACLE
#define DEF_OBSTACLE
#include "GameObject.h"
#include "stdlib.h"
	float Height(int i);
	float speed(int i);
	float base_width(int i);
	float base_height(int i);
	
class Obstacle : public GameObject
{
	public:
	Obstacle(int i, float x, float y);
	Obstacle(int i, float x, float y, float vx, float vy, float w, float h, float m, float s);
	~Obstacle();
	Obstacle(float currentSpeed, float x);
	float getGap();
	void followingCreated();
	bool isNextCreated();
	
	 
	private:
	
	
	int minGap;
	float minSpeed;
	float gap;
	bool next;
};
#endif
