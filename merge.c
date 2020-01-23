
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

//TODO: Bit hacks used for min of two elements
int min(int x, int y) { return y ^ ((x ^ y) & -(x <= y)); }
// void merge(int arr[], int l, int m, int r);

static inline void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int a[n1], b[n2];

    for (i = 0; i < n1; i++)
        a[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        b[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
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
        arr[k] = a[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = b[j];
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
        ret[i] = arr[i];
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
    int S = 1000000, n = S, iter = 10;
    int *arr = (int *)malloc(S * sizeof(int));
    int *r = (int *)malloc(S * sizeof(int));
    double sum = 0;
    struct timespec start, finish;

    for (int x = 0; x < iter; x++)
    {
        for (long int i = 0; i < S; i++)
        {
            arr[i] = rand() % 10;
        }

        //TODO: JYOTI HELP!!!

        // show(arr, n);
        clock_gettime(CLOCK_REALTIME, &start);
        r = merge_sort(arr, n);
        clock_gettime(CLOCK_REALTIME, &finish);
        // show(r, n);

        long sec = finish.tv_sec - start.tv_sec;
        long ns = finish.tv_nsec - start.tv_nsec;

        if (start.tv_nsec > finish.tv_nsec)
        {
            sec--;
            ns += 1000000000;
        }

        // printf("total seconds: %e\n\n\n", (double)sec + (double)ns / (double)1000000000);
        sum += (double)ns / 10;
    }
    printf("Average Running Time for %d Iterations = %lfns\n\n", iter, sum);

    return 0;
}
