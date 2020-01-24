#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAXSIZE 1000
#define BILLION  1000000000L

typedef struct Matrix {
	int matrix[1000][1000];
} Matrix;

Matrix *transpose(Matrix *T, int m, int n) {
	
	Matrix *R = malloc(sizeof(Matrix));
	
	for (int i = 0; i < m; i++) {
		/* code */
		for (int j = 0; j < n; j++) {
			/* code */
			R->matrix[j][i] = T->matrix[i][j];
		}		
	}	
}

int blockSize = 100;

Matrix *matrix_multiply(Matrix *a, Matrix *b, int p, int q, int r) {
	Matrix *result;
	result = malloc(sizeof(Matrix));

	// Matrix *t = transpose(b, q, r)

	Matrix *t = malloc(sizeof(Matrix));

	for (int i = 0; i < q; i++) {
		/* code */
		for (int j = 0; j < r; j++) {
			/* code */
			t->matrix[j][i] = b->matrix[i][j];
		}		
	}	
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

	for (int i = 0; i < p; i+= blockSize)	{
		/* code */
		for (int j = 0; j < r; j+= blockSize) {
			/* code */
			for (int blockRow = i; blockRow < i + blockSize; blockRow++) {
				/* code */
				for (int blockCol = j; blockCol < j + blockSize; blockCol++) {	
					
					
					int temporary = 0;
					for (int k = 0; k < q; k+=4) {
						/* code */
						temporary = temporary + (a->matrix[blockRow][k] * t->matrix[blockCol][k]);
						temporary = temporary + (a->matrix[blockRow][k+1] * t->matrix[blockCol][k+1]);
						temporary = temporary + (a->matrix[blockRow][k+2] * t->matrix[blockCol][k+2]);
						temporary = temporary + (a->matrix[blockRow][k+3] * t->matrix[blockCol][k+3]);

					}
					result->matrix[blockRow][blockCol] = temporary;
				}
			}		
		}
	}
	return result;
}

void printMatrix(Matrix *R, int m, int n) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			/* code */
			printf("%d ", R->matrix[i][j]);
		}
		printf("\n");
	}
}

void readMatrix(Matrix *R, int m, int n) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			/* code */
			scanf("%d", &(R->matrix[i][j]));
		}
	}
}

void randMatrix(Matrix *R, int m, int n) {
	srand(time(0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			/* code */
			R->matrix[i][j] = rand();
		}
	}	
}

int main() {

	struct timespec start, stop;
	// int p, q, r;
	// scanf("%d%d%d", &p, &q, &r);
	Matrix *A = malloc(sizeof(Matrix));
	Matrix *B = malloc(sizeof(Matrix));

	// readMatrix(A, p, q);
	// readMatrix(B, q, r);
	// printMatrix(A, p, q);
	// printMatrix(B, q, r);
     
	randMatrix(A, MAXSIZE, MAXSIZE);
	randMatrix(B, MAXSIZE, MAXSIZE);
	
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

	Matrix *R = matrix_multiply(A, B, MAXSIZE, MAXSIZE, MAXSIZE);
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

	double S = ( stop.tv_sec - start.tv_sec );
    double NS =  (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

	printf("Time: %lf\n", S + NS);
	// printMatrix(R, p, r);

	return 0;
}
