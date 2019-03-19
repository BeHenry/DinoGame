#ifndef DEF_GAMEOBJECT
#define DEF_GAMEOBJECT

class GameObject
{
	public:
	
	GameObject(int i);
	GameObject(float x, float y, float vx, float vy, float w, float h, int i);
	GameObject();
	~GameObject();
	void jump();
	void upDateVelocity();
	void upDatePosition();
	float getXPos();
	float getYPos();
	void operator=(const GameObject* ob);
	int getId();
	void setAcceleration(float x);
	void setParameters(float x, float y, float vx, float vy,float w, float h, int i);
	int size = 1;
	float getWidth();
	float getSpeed();
	float getHeight();
	
	private:
	
	float delta = 1;
	float height;
	float width;
	float m_xPos;
	float m_yPos;
	float m_yVelocity;
	float m_gravity = 0.1;
	float m_xVelocity;
	float m_xAcceleration = 0;
	int id;
	float m_Impulsion = 5;
	
	friend bool checkCollision(GameObject obj1, GameObject obj2);
};

#endif
