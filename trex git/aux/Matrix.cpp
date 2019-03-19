#include "Matrix.h"

Matrix::Matrix(int dim1, int dim2)
{
	m_dimLigne = dim1;
	m_dimCol = dim2;
	
	m_tab = new float[m_dimLigne*m_dimCol];
	for(int i = 0; i < m_dimLigne; i++)
	{
		for(int j = 0; j < m_dimCol; j++)
		{
			m_tab[i*m_dimCol+j] = 0;
		}
	}
	
}

Matrix::Matrix()
{
	m_tab = NULL;
}
int Matrix::getNLigne()
{
	return m_dimLigne;
}
int Matrix::getNCol()
{
	return m_dimCol;
}
void Matrix::allocate(int ligne, int colonnes)
{
	if(m_tab==NULL)
	{
		m_dimLigne=ligne;
		m_dimCol=colonnes;
		m_tab = new float[m_dimLigne*m_dimCol];
		for(int i = 0; i < m_dimLigne; i++)
		{
			for(int j = 0; j < m_dimCol; j++)
			{
				m_tab[i*m_dimCol+j] = 0;
			}
		}
	}
	else
	{
		throw std::invalid_argument( "Matrix already defined" );
	}
}
void Matrix::seeDim()
{
	std::cout << "Matrice à " << m_dimLigne << " lignes et " << m_dimCol << " colonnes" << std::endl;
}
Matrix::Matrix(float* tab, int dim1)
{
	m_dimLigne = dim1;
	m_dimCol = dim1;
	
	m_tab = new float[m_dimLigne*m_dimCol];
	for(int i = 0; i < m_dimLigne; i++)
	{
		for(int j = 0; j < m_dimCol; j++)
		{
			m_tab[i*m_dimCol+j] = tab[i*m_dimCol+j];
		}
	}
	
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	m_dimLigne = mat.m_dimLigne;
	m_dimCol = mat.m_dimCol;
	
	for(int i = 0; i < m_dimLigne; i++)
	{
		for(int j = 0; j < m_dimCol; j++)
		{
			m_tab[i*m_dimCol+j] = mat(i+1,j+1);
		}
	}
	return *this;
} 
Matrix::Matrix(const Matrix& m)
{
	m_dimLigne = m.m_dimLigne;
	m_dimCol = m.m_dimCol;
	
	m_tab = new float[m_dimLigne*m_dimCol];
	for(int i = 0; i < m_dimLigne; i++)
	{
		for(int j = 0; j < m_dimCol; j++)
		{
			m_tab[i*m_dimCol+j] = m(i+1,j+1);
		}
	}
		
}
Matrix::~Matrix()
{
	if(!(m_tab==NULL))
	{
		delete[] m_tab;
	}
}
float Matrix::operator()(int el1,int el2) const
{
	if ((el1>m_dimLigne) || (el2>m_dimCol))
	{
		throw std::invalid_argument( "indices inadaptés" );
	}
	return m_tab[(el1-1)*m_dimCol+(el2-1)];
}


int Matrix::getDim()
{
	return this->m_dimCol;
}
void Matrix::assign(int i, int j, float val)
{
	if ((i>m_dimLigne) || (j>m_dimCol))
	{
		throw std::invalid_argument( "indices inadaptés" );
	}
	m_tab[(i-1)*m_dimCol+(j-1)] = val;
}
/*std::ostream& Matrix::operator<<(std::ostream &flux)
{
	for(int i = 0; i < m_dimLigne; i++)
	{
		for(int j = 0; j < m_dimCol; j++)
		{
			flux << mat.m_tab[i*m_dimCol+j] << " ";
		}
		flux << std::endl;
	}	
}*/
Matrix Matrix::operator+(const Matrix& mat2)
{
	Matrix m = Matrix(this->m_dimLigne, this->m_dimCol);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			m.assign(i,j,mat2(i,j)+this->operator()(i,j));
		}
	}
	return m;
}
float Matrix::sum()
{
	float ret;
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			ret=ret+this->operator ()(i,j);
		}
	}
	return ret;
}
Matrix Matrix::operator-(const Matrix& mat2)
{
	Matrix m = Matrix(this->m_dimLigne, this->m_dimCol);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		float test;
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			m.assign(i,j,this->operator()(i,j)-mat2(i,j));
		}
	}
	return m;
}
void Matrix::elementWise(float (*func)(float))
{
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			this->assign(i,j,func(this->operator()(i,j)));
		}
	}
}
void Matrix::zeros()
{
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			this->assign(i,j,0);
		}
	}
}
Matrix Matrix::operator/(float a)
{
	Matrix ret = Matrix(this->m_dimLigne, this->m_dimCol);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			ret.assign(i,j,this->operator()(i,j)/a);
		}
	}
	return ret;
}

Matrix Matrix::operator*(const Matrix &mat2)
{
	if (!(m_dimCol==mat2.m_dimLigne))
	{
		throw std::invalid_argument( "multiplication impossible" );
	}
	float value = 0;
	
	Matrix result = Matrix(this->m_dimLigne,mat2.m_dimCol);

	for(int i = 1; i <= result.m_dimLigne; i++)
	{
		for(int j = 1; j <= result.m_dimCol; j++)
		{
			value = 0;
			for(int k = 1; k <= this->m_dimCol; k++)
			{
				value = value + this->operator()(i,k)*mat2(k,j);
			}
			result.assign(i,j,value);
		}
	}

	return result;
}
bool Matrix::hasNan()
{
	bool ret = false;
	float curVal;
	for (int i = 1; i<=this->m_dimLigne; i++)
	{
		for (int j = 1; j<= this->m_dimCol; j++)
		{
			curVal=this->operator()(i,j);
			if(curVal!=curVal)
			{
				ret = true;
			}
		}
	}
return ret;
}
/*Matrix Matrix::LDL(bool* flag)
{
	float sum;
	float temp;
	Matrix L = Matrix(this->m_dimLigne, this->m_dimCol);
	Matrix D = Matrix(this->m_dimLigne, this->m_dimCol);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		
		for(int j = 1; j <= i; j++)
		{
			sum = 0;
			if(i==j)
			{				
				for(int k = 1; k < j; k++)
				{
					sum = sum + pow(result(j,k),2.0)*D(k,k);					
					
				}
				temp = (this->operator()(i,j)-sum);
				D.assign(i,j,temp);
				
				
			}
			else
			{
				for(int k = 1; k < j; k++)
				{
					sum = sum+ result(j,k)*result(i,k);
				}
				temp = (this->operator()(i,j)-sum)/result(j,j);
				if(temp!=temp)
				{
					*flag = false;
				}
				result.assign(i,j,temp);
				
			}
		}
	}
	return result;
}*/
Matrix Matrix::cholesky(bool* flag)
{
	float sum;
	float temp;
	Matrix result = Matrix(this->m_dimLigne,this->m_dimLigne);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		
		for(int j = 1; j <= i; j++)
		{
			sum = 0;
			if(i==j)
			{				
				for(int k = 1; k < j; k++)
				{
					sum = sum + pow(result(j,k),2.0);					
					
				}
				temp = sqrt((this->operator()(i,j)-sum));
				if (temp<=0)
				{
					*flag = false;
				}
				
				result.assign(i,j, temp);
				
			}
			else
			{
				for(int k = 1; k < j; k++)
				{
					sum = sum+ result(j,k)*result(i,k);
				}
				temp = (this->operator()(i,j)-sum)/result(j,j);
				if(temp!=temp)
				{
					*flag = false;
				}
				result.assign(i,j,temp);
				
			}
		}
	}
	return result;
}


Matrix outterProduct(Matrix v1, Matrix v2)
{
	Matrix mat = Matrix(v1.m_dimLigne,v2.m_dimLigne);
	float temp;
	for(int i = 1; i <= v1.m_dimLigne; i++)
	{
		for(int j = 1; j <= v2.m_dimLigne; j++)
		{
			temp = v1(i,1)*v2(j,1);
			mat.assign(i,j,v1(i,1)*v2(j,1));
		}
	}
	return mat;
}

Matrix indentity(int dim)
{
	Matrix mat = Matrix(dim,dim);
	for(int i =1; i<=dim; i++)
	{
		mat.assign(i,i,10);
	}
	return mat;
}

Matrix vector(int dim, float values[])
{
	Matrix vec = Matrix(dim,1);
	for(int i = 1; i <= dim; i++)
	{
		vec.assign(i,1,values[i-1]);
	}
	return vec;
}
Matrix Matrix::scalarmult(float a)
{
	if (a!=a)
	{
		
		throw std::invalid_argument( "Problem in scalar mult" );
	}
	Matrix mat = Matrix(m_dimLigne, m_dimCol);
	for(int i = 1; i <= this->m_dimLigne; i++)
	{
		for(int j = 1; j <= this->m_dimCol; j++)
		{
			mat.assign(i,j,a*this->operator()(i,j));
		}
	}
	return mat;
}
