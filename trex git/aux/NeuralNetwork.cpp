#include <math.h>
#include "NeuralNetwork.h"


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

NeuralNetwork::NeuralNetwork(int inputSize, int outputSize, int nLayers, int* layersSizesTab, float (*act)(float))
{
	activation = act;
	
	m_nLayers = nLayers+1;
	weights = new Matrix[m_nLayers];
	
	weights[0].allocate(layersSizesTab[0],inputSize);
	dim= weights[0].getNCol()*weights[0].getNLigne();
	for(int i = 1; i < m_nLayers-1; i++)
	{
		
		weights[i].allocate(layersSizesTab[i],layersSizesTab[i-1]);
		
		dim = dim + weights[i].getNCol()*weights[i].getNLigne();
		
	}
	
	weights[m_nLayers-1].allocate(outputSize,layersSizesTab[m_nLayers-2]);
	dim = dim + weights[m_nLayers-1].getNCol()*weights[m_nLayers-1].getNLigne();
}
NeuralNetwork::NeuralNetwork(std::string s,float (*act)(float))
{
	activation = act;
	int* ligne = new int;
	int* col =  new int ;
	float* poid = new float;
	dim = 0;
	std::ifstream file(s.c_str(),std::ios_base::binary|std::ios_base::in);
	if(file)
	{
		file.read((char*)&m_nLayers, sizeof(int));
		weights = new Matrix[m_nLayers];
		for(int i = 0; i < m_nLayers; i++)
		{
			file.read((char*)ligne, sizeof(int));
			file.read((char*)col, sizeof(int));
			weights[i].allocate(*ligne,*col);
			dim = dim + (*ligne)*(*col);
			
		}
		for(int k = 0; k<m_nLayers; k++)
		{
			for(int i = 1; i<=weights[k].getNLigne(); i++)
			{
				for(int j = 1; j<=weights[k].getNCol(); j++)
				{
					file.read((char*)poid,sizeof(float));
					weights[k].assign(i,j,*poid);
					
				}
			}
		}
		file.close();
	}
	else
	{
		throw std::invalid_argument( "Fichier introuvable" );
	}
	
	delete ligne, col, poid;
	
}
NeuralNetwork::~NeuralNetwork()
{
	delete[] weights;
}
Matrix NeuralNetwork::eval(Matrix M)
{
	
	Matrix result = weights[0]*M;
	result.elementWise(activation);
	for(int i = 1; i < m_nLayers; i++)
	{
		result = weights[i]*result;
		result.elementWise(activation);
	}
return result;
}
void NeuralNetwork::vecToWeights(Matrix v)
{
	
	int counter = 1;
	for(int i=0; i<m_nLayers; i++)
	{
		for(int j=1; j<=weights[i].getNLigne(); j++)
		{
			for(int k=1; k<=weights[i].getNCol(); k++)
			{
				weights[i].assign(j,k,v(counter,1));
				counter  = counter + 1;
			}
		}
	}
	
}
int NeuralNetwork::getDim()
{
	return dim;
}
void NeuralNetwork::save(std::string s)
{
	std::ofstream file(s.c_str(), std::ios::out|std::ios::binary);
	file.write((char*)&m_nLayers,sizeof(int));
	int* ligne = new int;
	int* col = new int;
	float* poid = new float;
	for(int i = 0; i<m_nLayers; i++)
	{
		*ligne = weights[i].getNLigne();
		*col = weights[i].getNCol();
		file.write((char*)ligne,sizeof(int));
		file.write((char*)col,sizeof(int));
	}
	for(int k = 0; k<m_nLayers; k++)
	{
		for(int i = 1; i<=weights[k].getNLigne(); i++)
		{
			for(int j = 1; j<=weights[k].getNCol(); j++)
			{
				*poid = weights[k].operator ()(i,j);
				file.write((char*)poid,sizeof(float));
			}
		}
	}
	file.close();
	delete ligne, col, poid;
}
void NeuralNetwork::weightsToVec(Matrix* ret)
 {
	
	 int counter = 1;
	 for(int k = 0; k<m_nLayers; k++)
	{
		for(int i = 1; i<=weights[k].getNLigne(); i++)
		{
			for(int j = 1; j<=weights[k].getNCol(); j++)
			{
				ret->assign(counter, 1, weights[k].operator ()(i,j));
				counter = counter + 1;
			}
		}
	}

 }
