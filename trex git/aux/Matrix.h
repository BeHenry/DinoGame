#ifndef DEF_MATRIX
#define DEF_MATRIX
#include <math.h>
#include <iostream>

class Matrix
{
	public:
	
	Matrix(int dim1, int dim2);
	Matrix(float* tab, int dim);
	Matrix(const Matrix& m);
	Matrix();
	~Matrix();
	float operator()(int el1,int el2) const;
	static int getDim(Matrix mat);
	void assign(int i, int j, float val);
	Matrix operator+(const Matrix& mat2);
	Matrix operator-(const Matrix& mat2);
	Matrix operator*(const Matrix& mat2);
	Matrix& operator=(const Matrix& mat);
	void zeros();
	Matrix operator/(float a);
	void elementWise(float (*func)(float));
	Matrix cholesky(bool* flag);
	float sum();
	int getDim();
	void seeDim();
	Matrix scalarmult(float a);
	bool hasNan();
	void allocate(int ligne, int colonnes);
	int getNLigne();
	int getNCol();
	
	private:
	
	int m_dimLigne;
	int m_dimCol;
	float* m_tab;
	
	
	
	friend	Matrix outterProduct(Matrix v1, Matrix v2);
	
};

Matrix indentity(int dim);
Matrix vector(int dim, float values[]);
#endif

