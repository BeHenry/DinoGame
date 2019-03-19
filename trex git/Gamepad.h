#ifndef DEF_GAMEPAD
#define DEF_GAMEPAD
#include "aux/Matrix.h"
class Gamepad
{
	public:
	Gamepad();
	~Gamepad();
	virtual int getInput(Matrix info) = 0;
	
	private:
	
	protected:

	int* m_input;
};

#endif
