#ifndef NeuralNetwork
#define NeuralNetwork
#include "Matrix.h"

class NeuralNetwork
{
	public:
	NeuralNetwork(int inputSize, int outputSize, int nLayers, int* layersSizesTab);
	~NeuralNetwork();
	void initializeWeights(float* w1, int dim1, int dim2);
	void computeLayer(float* neuralIn, float* neuralOut, float* weights, int nn1, int nn2);
	
	private:
	
	int m_nLayers;
	Matrix* weights;

}

#endif
