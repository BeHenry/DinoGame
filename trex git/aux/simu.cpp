#include <math.h>
#include "Matrix.h"
float normal()
{
	float u = (float)rand()/(float)RAND_MAX;
	float v = (float)rand()/(float)RAND_MAX;
	return sqrt(-2*log(u))*cos(2*M_PI*v);
}
Matrix iidGaussian(int dim)
{
	Matrix m = Matrix(dim, 1);
	for(int i = 1; i <= dim; i++)
	{
		m.assign(i,1,normal());
	}
	return m;
}

Matrix GaussianVector(Matrix* M, Matrix* mean)
{
	return (*M)*iidGaussian(M->getDim())+*mean;
}
Matrix mixing(Matrix M, Matrix N, int scoreM, int scoreN)
{
	float p=float(scoreM)/(scoreM+scoreN);
	int n = M.getNLigne();
	Matrix ret = Matrix(n,1);
	float u; 
	for(int i = 1; i<=n; i++)
	{
		u = (float)rand()/(float)RAND_MAX;
		if(u<p)
		{
			ret.assign(i,1,M(i,1));
		}
		else
		{
			ret.assign(i,1,N(i,1));
		}
		
	}
	return ret;
}
