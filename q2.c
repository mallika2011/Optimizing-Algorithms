
#include <unistd.h>
#include<string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAXSIZE 1000000
#define BILLION 1000000000L
#define RUN 32

//TODO: Bit hacks used for min of two elements
static inline int min(int x, int y) { return (y) ^ (((x) ^ (y)) & -((x) <= (y))); }

static inline int *merge_sort(int *arr, int n)
{
    register int * restrict ret = malloc(sizeof(int) * n);

    /*
	Maximum value of n can be 10^6.
	Your Code goes here. The sorted array should be stored in ret
	and returned. Just code this function, no need to write anything in main().
	This function will be called directly.
	
	Also note you can write any other function that you might need.
	*/
    register int temp;
    register int j;

    for (register int i = 0; i < n; i += 32)
    {
        register int left = i;
        register int right= (i+31)<(n-1)?(i+31):(n-1);

        for (register int i = left + 1; i <= right; ++i)
        {
            temp = *(arr+i);
            j = i - 1;
            while (*(arr+j) > temp && j >= left)
            {
                *(arr+j + 1) = *(arr+j);
                --j;
            }
            *(arr+j + 1) = temp;
        }
    }    
    
    register int curr_size;
    register int left_start;
    for (curr_size = 32; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start <n; left_start += 2 * curr_size)
        {
            register int mid = min(left_start + curr_size - 1, n - 1);
            
            register int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            // merge(arr, left_start, mid, right_end);
            //TODO: Including inline functions to prevent branching
            register int i, j, k;
            register int l = left_start, r = right_end, m = mid;
            register int n1 = m - l + 1;
            register int n2 = r - m;

            // register int a[n1], b[n2];
            register int * restrict a=malloc(sizeof(int)*n1);
            register int *restrict b=malloc(sizeof(int)*n2);

            memcpy(a, &arr[l],sizeof(int)*n1);
            memcpy(b, &arr[m+1],sizeof(int)*n2);
            i = 0;
            j = 0;
            k = l;
            while (i < n1 && j < n2)
            {
                //TODO: Change2: Rewriting the method to calculate the minimum
                register int comp = (a[i] <= b[j]);
                arr[k] = b[j] ^ ((a[i] ^ b[j]) & -comp);
                i += comp;
                j += !comp;
                ++k;
            }

            while (i < n1)
            {
                // arr[k] = a[i];
                *(arr + k) = *(a + i);
                ++i;
                ++k;
            }

            while (j < n2)
            {
                // arr[k] = b[j];
                *(arr + k) = *(b + j);
                ++j;
                ++k;
            }
        }
    }
    for (register int i = 0; i < n; i++)
    {
        // ret[i] = arr[i];
        *(ret +  i) = *(arr + i);
    }

    return ret;
}

void show(register int a[], register int n)
{
    for (register int i = 0; i < n; i++)
        printf("%d \n", a[i]);
    printf("\n");
}

int main()
{
    srand(time(0));
    register int iter = 1, n = 100000000, chk=0;
    register int * restrict arr = (int *)malloc(n * sizeof(int));
    register int* restrict r = (int *)malloc(n * sizeof(int));
    double sum = 0;
    struct timespec start, stop;
    for (register int x = 0; x < iter; x++)
    {
        for (long register int i = 0; i < n; i++)
        {
            // *(arr+i) = rand() % 100000;
            *(arr+i)=n-i;
        }

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

        register double S = (stop.tv_sec - start.tv_sec);
        register double NS = (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;

        register double final = S + NS;
        for(register int i=1; i<n; i++)
        {
            if(r[i]<r[i-1])
            {
                chk=1;
                break;
            }
        }
        sum += final / iter;
    }
    if(chk==0)
        printf("Avg Run Time: %lfns\n\n", sum);
    else
        printf("Wrong!\n");

    return 0;
}
