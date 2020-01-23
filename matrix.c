#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix
{
	int matrix[1000][1000];
} Matrix;

Matrix *matrix_multiply(Matrix *a, Matrix *b, int p, int q, int r)
{
	Matrix *result;
	result = malloc(sizeof(Matrix));
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

Matrix *add1(Matrix *A, long int p, long int q)
{
	Matrix *result;
	result = malloc(sizeof(Matrix));
	for (long int i = 0; i < p; i++)
	{
		for (long int j = 0; j < q; j++)
		{
			result->matrix[i][j] = A->matrix[i][j] * 10;
		}
	}
	return result;
}

void fill(Matrix *A, long int p, long int q)
{
	for (long int i = 0; i < p; i++)
	{
		for (long int j = 0; j < q; j++)
			scanf("%ld", &A->matrix[i][j]);
	}
}

void print(Matrix *A, long int p, long int q)
{
	for (long int i = 0; i < p; i++)
	{
		for (long int j = 0; j < q; j++)
			printf("%ld ", A->matrix[i][j]);
		printf("\n");
	}
}

int main()
{
	Matrix *A, *B;
	long int p, q;
	scanf("%ld %ld", &p, &q);
	fill(A, p, q);
	// print(A, p, q);
	fill(B, p, q);
	// Matrix *final  =add1(A,p,q);
	// print(final, p,q);

	return 0;
}
