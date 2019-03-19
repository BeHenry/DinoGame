#include "Gamepadneural.h"


Gamepadneural::Gamepadneural()
{
	int lay[3] {8,5,5};
	Net = new NeuralNetwork(9, 1, 2, lay, &atan);
	vec.allocate(Net->getDim(),1);
}
Gamepadneural::~Gamepadneural()
{
	delete Net;
}

Gamepadneural::Gamepadneural(std::string s, float (*act)(float))
{
	Net = new NeuralNetwork(s,act);
	vec.allocate(Net->getDim(),1);
	Net->weightsToVec(&vec);
}

int Gamepadneural::getInput(Matrix info)
{
	

	
	Matrix output_2=Net->eval(info);
	
	if (output_2(1,1)<0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
	
}
Matrix Gamepadneural::getWVec()
{
	return vec;
}


void Gamepadneural::sampleWeights(Matrix* M,Matrix* m)
{
	
	vec=GaussianVector(M,m);
	Net->vecToWeights(vec);
}
void Gamepadneural::changeWeight(Matrix M)
{
	
	vec=M;
	Net->vecToWeights(vec);
}
void Gamepadneural::updateWeight()
{
	Net->vecToWeights(vec);
}
void Gamepadneural::vecToWeight()
{
	this->changeWeight(vec);
}
void Gamepadneural::Mutation()
{
	float U;
	float p = 0.5;
	for (int i=1; i<=Net->getDim(); i++)
	{
		U=(float)rand()/(float)RAND_MAX;
		if(U<p)
		{
			vec.assign(i,1,vec(i,1)+5*normal());
		}
		
	}
	this->updateWeight();
}
int Gamepadneural::getDim()
{
	return Net->getDim();
}
void Gamepadneural::save(std::string s)
{
	Net->save(s);
}
