//RUDIMENTARY CODE

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

void merge(int arr[], int l, int m, int r);
// int min(int x, int y) { return (x<y)? x :y; }

//TODO: Change1: rewriting the min function
int min(int x, int y) { return y ^ ((x ^ y) & -(x <= y)); }

void mergeSort(int arr[], int n)
{
	int curr_size;
	int left_start;

	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			int mid = min(left_start + curr_size - 1, n - 1);
			int right_end = min(left_start + 2 * curr_size - 1, n - 1);
			// merge(arr, left_start, mid, right_end);
			int i, j, k;
			int l=left_start;
			int m=mid;
			int r=right_end;
			int n1 = m - l + 1;
			int n2 = r - m;

			int L[n1], R[n2];

			for (i = 0; i < n1; i++)
				L[i] = arr[l + i];
			for (j = 0; j < n2; j++)
				R[j] = arr[m + 1 + j];

			i = 0;
			j = 0;
			k = l;
			while (i < n1 && j < n2)
			{
				//TODO: Change2: Rewriting the method to calculate the minimum
				// if (L[i] <= R[j])
				// {
				// 	arr[k] = L[i];
				// 	i++;
				// }
				// else
				// {
				// 	arr[k] = R[j];
				// 	j++;
				// }
				// k++;

				int comp = (L[i] <= R[j]);
				arr[k] = R[j] ^ ((L[i] ^ R[j]) & -comp);
				i += comp;
				j += !comp;
				k++;
			}

			while (i < n1)
			{
				arr[k] = L[i];
				i++;
				k++;
			}

			while (j < n2)
			{
				arr[k] = R[j];
				j++;
				k++;
			}
		}
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		//TODO: Change2: Rewriting the method to calculate the minimum
		// if (L[i] <= R[j])
		// {
		// 	arr[k] = L[i];
		// 	i++;
		// }
		// else
		// {
		// 	arr[k] = R[j];
		// 	j++;
		// }
		// k++;

		int comp = (L[i] <= R[j]);
		arr[k] = R[j] ^ ((L[i] ^ R[j]) & -comp);
		i += comp;
		j += !comp;
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	srand(time(NULL));
	int SIZE = 10;
	int arr[SIZE];
	for (long int i = 0; i < SIZE; i++)
	{
		arr[i] = rand()%10;
	}

	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, n);

	struct timespec start, finish;

	clock_gettime(CLOCK_REALTIME, &start);
	mergeSort(arr, n);
	clock_gettime(CLOCK_REALTIME, &finish);

	printf("\nSorted array is \n");
	printArray(arr, n);

	long sec = finish.tv_sec - start.tv_sec;
	long ns = finish.tv_nsec - start.tv_nsec;

	if (start.tv_nsec > finish.tv_nsec)
	{
		sec--;
		ns += 1000000000;
	}

	printf("SECONDS = %ld\n", sec);
	printf("NS = %ld\n", ns);
	printf("NS = %lf\n", (double)(ns) / (double)1000000000);
	printf("total seconds: %e\n", (double)sec + (double)ns / (double)1000000000);

	return 0;
}
