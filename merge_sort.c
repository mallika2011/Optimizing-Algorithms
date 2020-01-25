#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAXSIZE 1000
#define BILLION  1000000000L


typedef struct Matrix {
	int matrix[1000][1000];
} Matrix;

Matrix * restrict result;
Matrix * restrict t;

	
int * restrict A;
int * restrict B;
int * restrict C;
  
Matrix *matrix_multiply(Matrix * restrict a, Matrix * restrict b, int p, int q, int r) {


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

    result = malloc(sizeof(Matrix));
    t = malloc(sizeof(Matrix));

    for (int i = 0; i < p; ++i) {
		for (int j = 0; j < r; ++j) {
			result->matrix[i][j] = 0;
		}
	}
    //Transpose
	for (int i = 0; i < q; ++i) {
		for (int j = 0; j < r; ++j) {
			t->matrix[j][i] = b->matrix[i][j];
		}		
	}
    
	for (int i = 0; i < p; ++i)	{
        A = *(a->matrix + i);
        C = *(result->matrix + i);
		for (int j = 0; j < r; ++j) {
            B = *(t->matrix + j);				
			int temporary = 0;
            int k = 0;
			for ( ; k < q - 16; k += 16) {
				temporary += *(A + k) * *(B + k);
				temporary += *(A + k+1) * *(B + k+1);
				temporary += *(A + k+2) * *(B + k+2);
				temporary += *(A + k+3) * *(B + k+3);
				temporary += *(A + k+4) * *(B + k+4);
				temporary += *(A + k+5) * *(B + k+5);
				temporary += *(A + k+6) * *(B + k+6);
				temporary += *(A + k+7) * *(B + k+7);
				temporary += *(A + k+8) * *(B + k+8);
				temporary += *(A + k+9) * *(B + k+9);
                temporary += *(A + k+10) * *(B + k+10);
				temporary += *(A + k+11) * *(B + k+11);
				temporary += *(A + k+12) * *(B + k+12);
				temporary += *(A + k+13) * *(B + k+13);
				temporary += *(A + k+14) * *(B + k+14);
                temporary += *(A + k+15) * *(B + k+15);
            }

            for ( ; k < q; ++k) {
				temporary += *(A + k) * *(B + k);
            }
			*(C + j) = temporary;		
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

void test_multilpy(Matrix *a, Matrix *b, int p, int q, int r, Matrix *R) {

    result = malloc(sizeof(Matrix));

	for (int i = 0; i < p; ++i)	{
		for (int j = 0; j < r; ++j) {
            int temporary = 0;
			for (int k = 0; k < q; ++k) {
				temporary += a->matrix[i][k]*b->matrix[k][j];
            }


			result->matrix[i][j] = temporary;
            if (R->matrix[i][j] != result->matrix[i][j]) {
                printf("Wrong!");
            }		
		}
	}
}

int main() {

	struct timespec start, stop;
	// int p, q, r;
	// scanf("%d%d%d", &p, &q, &r);
	Matrix * restrict A = malloc(sizeof(Matrix));
	Matrix * restrict B = malloc(sizeof(Matrix));

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

	Matrix * restrict R = matrix_multiply(A, B, 1000, 1000, 1000);
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

	double S = ( stop.tv_sec - start.tv_sec );
    double NS =  (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

	printf("Time: %lf\n", S + NS);
	// printMatrix(R, p, r);
    test_multilpy(A, B, 1000,1000,1000, R);

	return 0;
}

