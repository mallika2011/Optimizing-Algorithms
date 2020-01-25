
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
static inline int min(int x, int y) { return y ^ ((x ^ y) & -(x <= y)); }

static inline int *merge_sort(int *arr, int n)
{
    int * restrict ret;
    ret = malloc(sizeof(int) * n);

    /*
	Maximum value of n can be 10^6.
	Your Code goes here. The sorted array should be stored in ret
	and returned. Just code this function, no need to write anything in main().
	This function will be called directly.
	
	Also note you can write any other function that you might need.
	*/

    for (int i = 0; i < n; i += RUN)
    {
        int left = i;
        int right= (i+31)<(n-1)?(i+31):(n-1);

        for (int i = left + 1; i <= right; i++)
        {
            int temp = *(arr+i);
            int j = i - 1;
            while (*(arr+j) > temp && j >= left)
            {
                *(arr+j + 1) = *(arr+j);
                j--;
            }
            *(arr+j + 1) = temp;
        }
    }    
    
    int curr_size;
    int left_start;
    for (curr_size = RUN; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start <n; left_start += 2 * curr_size)
        {
            int mid = min(left_start + curr_size - 1, n - 1);
            
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);

            // merge(arr, left_start, mid, right_end);
            //TODO: Including inline functions to prevent branching
            int i, j, k;
            int l = left_start, r = right_end, m = mid;
            int n1 = m - l + 1;
            int n2 = r - m;

            // int a[n1], b[n2];
            int * restrict a=malloc(sizeof(int)*n1);
            int *restrict b=malloc(sizeof(int)*n2);

            memcpy(a, &arr[l],sizeof(int)*n1);
            memcpy(b, &arr[m+1],sizeof(int)*n2);
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
    for (int i = 0; i < n; i++)
    {
        // ret[i] = arr[i];
        *(ret +  i) = *(arr + i);
    }

    return ret;
}

void show(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d \n", a[i]);
    printf("\n");
}

int main()
{
    srand(time(0));
    int iter = 1, n = 1000000, chk=0;
    int * restrict arr = (int *)malloc(n * sizeof(int));
    int * restrict r = (int *)malloc(n * sizeof(int));
    double sum = 0;
    struct timespec start, stop;
    for (int x = 0; x < iter; x++)
    {
        for (long int i = 0; i < n; i++)
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

        double S = (stop.tv_sec - start.tv_sec);
        double NS = (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION;

        double final = S + NS;
        for(int i=1; i<n; i++)
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
