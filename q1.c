#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAXSIZE 5000
#define BILLION  1000000000L


typedef struct Matrix {
	int matrix[5000][5000];
} Matrix;

Matrix * restrict result;
Matrix * restrict t;

	

  
Matrix *matrix_multiply(Matrix * restrict a, Matrix * restrict b, register int p, register int q, register int r) {


	/*
	size of matrix a is pxq
	size of matrix b is qxr
	Maximum value of p,q or r can be 5000.
	Your Code goes here. The output of their matrix multiplication
	should be stored in result and returned. Just code this function,
	no need to write anything in main(). This function will be called directly.
	We are dealing with pointers so use result->matrix and not result.matrix

	Also note you can write any other function that you might need.
	*/ 
	register int * restrict A;
	register int * restrict B;
	register int * restrict C;

    result = malloc(sizeof(Matrix));

	register int max = q ^ ((q ^ r) & -(q < r));
    //Transpose
	for (register int i = 0; i < max; ++i) {
		for (register int j = 0; j < i; ++j) {
			b->matrix[i][j] =  b->matrix[i][j] ^ b->matrix[j][i];
            b->matrix[j][i] =  b->matrix[i][j] ^ b->matrix[j][i];
            b->matrix[i][j] =  b->matrix[i][j] ^ b->matrix[j][i];
		}		
	}
register int temporary; 
register int k;

	for (register int i = 0; i < p; ++i)	{
        A = *(a->matrix + i);
        C = *(result->matrix + i);
		for (register int j = 0; j < r; ++j) {
            B = *(b->matrix + j);				
			temporary = 0;
            k = 0;
			for ( ; k < q - 16; k += 16) {
				temporary += *(A + k) * *(B + k) + *(A + k+1) * *(B + k+1) + *(A + k+2) * *(B + k+2)+ *(A + k+3) * *(B + k+3) + *(A + k+4) * *(B + k+4) + *(A + k+5) * *(B + k+5) + *(A + k+6) * *(B + k+6) + *(A + k+7) * *(B + k+7) + *(A + k+8) * *(B + k+8) + *(A + k+9) * *(B + k+9) + *(A + k+10) * *(B + k+10) + *(A + k+11) * *(B + k+11) + *(A + k+12) * *(B + k+12) + *(A + k+13) * *(B + k+13) + *(A + k+14) * *(B + k+14) + *(A + k+15) * *(B + k+15);
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
				temporary += a->matrix[i][k]*b->matrix[j][k];
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
     
	randMatrix(A, 5000, 5000);
	randMatrix(B, 5000, 5000);
	
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

	Matrix * restrict R = matrix_multiply(A, B, 5000, 5000, 5000);
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

	double S = ( stop.tv_sec - start.tv_sec );
    double NS =  (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

	printf("Time: %lf\n", S + NS);
	// printMatrix(R, p, r);
    // test_multilpy(A, B, 5000, 5000, 5000, R);

	return 0;
}

