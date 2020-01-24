
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAXSIZE 1000000
#define BILLION  1000000000L

//TODO: Bit hacks used for min of two elements
int min(int x, int y) { return y ^ ((x ^ y) & -(x <= y)); }
// void merge(int arr[], int l, int m, int r);

static inline void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int a[n1], b[n2];
    int e = 0, t = 1;

    for (i = 0; i < n1; i++)
    { 
        //  a[i] = arr[l + i];
        //TODO: Added assembly instructions
         asm("movl %1, %0;":"=r"(a[i]):"r"(arr[l+i]));
        
    }
    for (j = 0; j < n2; j++)
    {
        // b[j] = arr[m + 1 + j];
        //TODO: Added assembly instructions
        asm("movl %1, %0;":"=r"(b[j]):"r"(arr[m+1+j]));

    }
    
    asm("movl %1, %0;":"=r"(i):"r"(0));
    asm("movl %1, %0;":"=r"(j):"r"(0));
    asm("movl %1, %0;":"=r"(k):"r"(l));

    // i = 0;
    // j = 0;
    // k = l;
    while (i < n1 && j < n2)
    {
        //TODO: Change2: Rewriting the method to calculate the minimum
        int comp = (a[i] <= b[j]);
        arr[k] = b[j] ^ ((a[i] ^ b[j]) & -comp);
        i += comp;
        j += !comp;
        k++;
    }

    while (i < n1)
    {
        // arr[k] = a[i];
        asm("movl %1, %0;":"=r"(arr[k]):"r"(a[i]));
        i++;
        k++;
    }

    while (j < n2)
    {
        // arr[k] = b[j];
        asm("movl %1, %0;":"=r"(arr[k]):"r"(b[j]));
        j++;
        k++;
    }
}

static inline int *merge_sort(int *arr, int n)
{
    int *ret;
    ret = malloc(sizeof(int) * n);

    /*
	Maximum value of n can be 10^6.
	Your Code goes here. The sorted array should be stored in ret
	and returned. Just code this function, no need to write anything in main().
	This function will be called directly.
	
	Also note you can write any other function that you might need.
	*/

    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
        {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
            //TODO: Including inline functions to prevent branching
        }
    }
    for (int i = 0; i < n; i++)
    {
        // ret[i] = arr[i];
        asm("movl %1, %0;":"=r"(ret[i]):"r"(arr[i]));
    }

    return ret;
}

void show(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    srand(time(0));
    int iter = 10,n=1000000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *r = (int *)malloc(n * sizeof(int));
    double sum = 0;
    struct timespec start, stop;

    // n=MAXSIZE;
    // printf("%d\n",n);
    for (int x = 0; x < iter; x++)
    {
        for (long int i = 0; i < n; i++)
        {
            arr[i] = rand() % 10;
        }

        //TODO: JYOTI HELP!!!

        // show(arr, n);
        if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}
        r = merge_sort(arr, n);
        if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			return EXIT_FAILURE;
		}
        // show(r, n);

        double S = ( stop.tv_sec - start.tv_sec );
        double NS =  (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;

        double final=S+NS;

        // printf("total seconds: %e\n\n\n", (double)sec + (double)ns / (double)1000000000);
        sum += final / 10;
    }
    printf("Avg Run Time: %lfns\n\n", sum);

    return 0;
}
