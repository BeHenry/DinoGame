#include <math.h>
#include "NN.h"
void NeuralNetwork::initializeWeights(float* w1, int dim1, int dim2)
{
	
	
	for(int i = 0; i<dim1; i++)
	{
		for(int j = 0; j < dim2; j++)
		{
			w1[i*dim2+j]=0;
			
		}
	}
}

NeuralNetwork::NeuralNetwork(int inputSize, int outputSize, int nLayers, int* layersSizesTab)
{
	m_nLayers = nLayers;
	weights = new Matrix[nLayers];
	weights[0].allocate(inputSize,layersSizesTab[0]);
	for(int i = 1; i < nLayers; i++)
	{
		weights[i].allocate(layersSizesTab[i-1],layersSizesTab[i]);
	}
	weights[nLayers-1].allocate(layersSizesTab[nLayers-1],outputSize);
}
NeuralNetwork::~NeuralNetwork()
{
	delete[] weights;
}
Matrix NeuralNetwork::evalNetwork(Matrix M)
{
	Matrix result;
	result = weights[0]*M;
	result.elementWise(activation);
	for(int i = 1; i < m_nLayers; i++)
	{
		result = weights[i]*result;
		result.elementWise(activation);
	}
return result;
}
