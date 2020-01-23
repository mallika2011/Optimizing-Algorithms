#include<stdio.h>
#include<stdlib.h>

typedef struct Matrix
{
	int matrix[1000][1000];
}Matrix;

Matrix *matrix_multiply(Matrix *a,Matrix *b,int p,int q,int r)
{
	Matrix *result;
	result=malloc(sizeof(Matrix));
	/*
	size of matrix a is pxq
	size of matrix b is qxr
	Maximum value of p,q or r can be 1000.
	Your Code goes here. The output of their matrix multiplication
	should be stored in result and returned. Just code this function,
	no need to write anything in main(). This function will be called directly.
	We are dealing with pointers so use result->matrix and not result.matrix

	Also note you can write any other function that you might need.
	*/ 

	return result;
}
int main()
{
	return 0;
}
