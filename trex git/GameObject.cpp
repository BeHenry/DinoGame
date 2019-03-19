#include "GameObject.h"

GameObject::GameObject(int i)
{
	id = i;
	m_xPos = 0;
	m_yPos = 0;
	m_yVelocity = 0;
	m_xVelocity = 0;
	width = 0;
	height = 0;
	
}
GameObject::GameObject()
{
	id = -1;
	m_xPos = 0;
	m_yPos = 0;
	m_yVelocity = 0;
	m_xVelocity = 0;
	width = 0;
	height = 0;
}
GameObject::GameObject(float x, float y, float vx, float vy,float w, float h, int i)
{
	id = i;
	m_xPos = x;
	m_yPos = y;
	m_yVelocity = vy;
	m_xVelocity = vx;
	width = w;
	height = h;
}
void GameObject::setParameters(float x, float y, float vx, float vy,float w, float h, int i)
{
	id = i;
	m_xPos = x;
	m_yPos = y;
	m_yVelocity = vy;
	m_xVelocity = vx;
	width = w;
	height = h;
}
int GameObject::getId()
{
	return id;
}
void GameObject::setAcceleration(float x)
{
	m_xAcceleration = x;
}
void GameObject::jump(){
	if(m_yPos==0){
		m_yVelocity=+delta*m_Impulsion;
	}
}
GameObject::~GameObject(){
}
float GameObject::getSpeed()
{
	return m_xVelocity;
}
void GameObject::upDatePosition()
{
	m_xPos = m_xPos + delta*m_xVelocity;
	int temp = m_yPos + delta*m_yVelocity;
	if (temp>0)
	{
		m_yPos = temp;
	}
	else
	{
		m_yPos = 0;
	}
}
float GameObject::getWidth()
{
	return width;
}
float GameObject::getHeight()
{
	return height;
}
void GameObject::upDateVelocity()
{
	if(m_yPos>0){
		m_yVelocity = m_yVelocity-delta*m_gravity;
	}
	else
	{
		m_yVelocity = 0;
	}
	m_xVelocity += delta*m_xAcceleration;
}

 float GameObject::getXPos()
 {
	 return m_xPos;
 }
 float GameObject::getYPos()
 {
	 return m_yPos;
 }
bool checkCollision(GameObject obj1, GameObject obj2)
{
	
   if((obj2.m_xPos >= obj1.m_xPos + obj1.width)      // trop à droite
    || (obj2.m_xPos + obj2.width <= obj1.m_xPos) // trop à gauche
    || (obj2.m_yPos >= obj1.m_yPos + obj1.height) // trop en bas
    || (obj2.m_yPos + obj2.height <= obj1.m_yPos))
    {  // trop en haut
          return false; 
	}
   else
   {
          return true; 
	}
}

