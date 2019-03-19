#include "Dino.h"

Dino::Dino()
{
	m_xPosDino = 0;
	m_yPosDino = 0;
	m_yVelocityDino = 0;
}


void Dino::jump(){
	if(m_yPosDino==0){
		m_yVelocityDino=+m_Impulsion;
	}
}
Dino::~Dino(){
}
void Dino::upDatePosition()
{
	m_xPosDino = m_xPosDino + m_xVelocityDino*m_delta;
	int temp = m_yPosDino + m_yVelocityDino*m_delta;
	if (temp>0)
	{
		m_yPosDino = temp;
	}
	else
	{
		m_yPosDino = 0;
	}
}

void Dino:: upDateVelocity()
{
	if(m_yPosDino>0){
		m_yVelocityDino = m_yVelocityDino-9.8*m_delta;
	}
	else
	{
		m_yVelocityDino = 0;
	}
}
 float Dino::getXPos()
 {
	 return m_xPosDino;
 }
 float Dino::getYPos()
 {
	 return m_yPosDino;
 }
