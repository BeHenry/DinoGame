#ifndef DEF_DINO
#define DEF_DINO

class Dino
{
	public:
	
	Dino();
	~Dino();
	void jump();
	void upDateVelocity();
	void upDatePosition();
	float getXPos();
	float getYPos();
	
	private:
	
	
	float m_xPosDino;
	float m_yPosDino;
	float m_yVelocityDino;
	float const m_xVelocityDino = 0;
	float const m_Impulsion = 50;
	float const m_delta = 0.05;
};



#endif
