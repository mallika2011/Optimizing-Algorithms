#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1000
#define BILLION 1000000000L

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
	//TODO: Initialize result matrix to all 0s
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < r; j++)
		{
			result->matrix[i][j] = 0;
		}
	}
	//TODO: Loop reordering and unrolling
	for (int i = 0; i < p; i++)
	{
		/* code */
		for (int k = 0; k < q; k++)
		{
			/* code */
			for (int j = 0; j < r; j += 4)
			{
				/* code */
				result->matrix[i][j] = result->matrix[i][j] + (a->matrix[i][k] * b->matrix[k][j]);
				result->matrix[i][j + 1] = result->matrix[i][j + 1] + (a->matrix[i][k] * b->matrix[k][j + 1]);
				result->matrix[i][j + 2] = result->matrix[i][j + 2] + (a->matrix[i][k] * b->matrix[k][j + 2]);
				result->matrix[i][j + 3] = result->matrix[i][j + 3] + (a->matrix[i][k] * b->matrix[k][j + 3]);
			}
		}
	}
	return result;
}

void printMatrix(Matrix *R, int m, int n)
{

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			/* code */
			printf("%d ", R->matrix[i][j]);
		}
		printf("\n");
	}
}

void readMatrix(Matrix *R, int m, int n)
{

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			/* code */
			scanf("%d", &(R->matrix[i][j]));
		}
	}
}

void randMatrix(Matrix *R, int m, int n)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			/* code */
			R->matrix[i][j] = rand();
		}
	}
}

int main()
{

	struct timespec start, stop;
	int iter = 1;
	double sum=0;
	// int p, q, r;
	// scanf("%d%d%d", &p, &q, &r);
	Matrix *A = malloc(sizeof(Matrix));
	Matrix *B = malloc(sizeof(Matrix));

	for (int x = 0; x < iter; x++)
	{
		// readMatrix(A, p, q);
		// readMatrix(B, q, r);
		// printMatrix(A, p, q);
		// printMatrix(B, q, r);

		randMatrix(A, MAXSIZE, MAXSIZE);
		randMatrix(B, MAXSIZE, MAXSIZE);

		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}

		Matrix *R = matrix_multiply(A, B, MAXSIZE, MAXSIZE, MAXSIZE);
		// Matrix *R = matrix_multiply(A, B, p, q, r);

		if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}

		// printMatrix(R, p, r);

		double S = (stop.tv_sec - start.tv_sec);
		double NS = (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;
		sum+=(S+NS)/iter;
	}

	printf("Avg Run Time: %lf\n", sum);

	return 0;
}