#ifndef DEF_NEURALNETWORK
#define DEF_NEURALNETWORK
#include "Matrix.h"
#include "string.h"
#include <fstream>
class NeuralNetwork
{
	public:
	NeuralNetwork(int inputSize, int outputSize, int nLayers, int* layersSizesTab,float (*act)(float));
	NeuralNetwork(std::string s, float (*act)(float));
	~NeuralNetwork();
	void initializeWeights(float* w1, int dim1, int dim2);
	Matrix eval(Matrix M);
	void vecToWeights(Matrix v);
	void weightsToVec(Matrix* vec);
	int getDim();
	void save(std::string s);
	
	private:
	int dim;
	int m_nLayers;
	Matrix* weights;
	float (*activation)(float);

};

#endif
