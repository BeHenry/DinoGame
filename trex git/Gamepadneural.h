#ifndef DEF_GAMEPADNEURAL
#define DEF_GAMEPADNEURAL
#include "Gamepad.h"
#include "aux/NeuralNetwork.h"
#include "aux/simu.h"
#include <iostream>
#include <math.h>
#include "string.h"
class Gamepadneural : public Gamepad
{
	public:
	
	Gamepadneural();
	Gamepadneural(std::string s, float (*act)(float));
	~Gamepadneural();
	int getInput(Matrix info);
	void setWeight(Matrix* M, Matrix* m);
	Matrix getWVec();
	void changeWeight(Matrix M);
	void Mutation();
	void vecToWeight();
	void sampleWeights(Matrix* M,Matrix* m);
	void updateWeight();
	int getDim();
	void save(std::string s);
	
	private:
	NeuralNetwork* Net;
	Matrix vec;
	
	
	
};

#endif
