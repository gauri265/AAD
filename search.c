#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void linearSearch(int arr[], int n, int key)
{
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == key)
        {
            return;
        }
    }
}

void binarySearch(int arr[], int n, int key)
{
    int l = 0;
    int h = n - 1;

    while(l <= h)
    {
        int mid = (l + h) / 2;

        if(arr[mid] == key)
        {
            return;
        }
        else if(key > arr[mid])
        {
            l = mid + 1;
        }
        else
        {
            h = mid - 1;
        }
    }
}

int main()
{
    int sizes[] = {10000, 50000, 100000, 500000, 5000000, 10000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("n\t\tLinear Search time (s)\tBinary Search time (s)\n");

    for(int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        int *arr = (int *)malloc(n * sizeof(int));

        if(arr == NULL)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }

        for(int i = 0; i < n; i++)
        {
            arr[i] = i * 2;
        }

        int key = -999;      // Worst case (element not present)
        int repetitions = 500;

        clock_t start = clock();

        for(int r = 0; r < repetitions; r++)
        {
            linearSearch(arr, n, key);
        }

        clock_t stop = clock();

        double linearTime = (double)(stop - start) / CLOCKS_PER_SEC;

        start = clock();

        for(int r = 0; r < repetitions; r++)
        {
            binarySearch(arr, n, key);
        }

        stop = clock();

        double binaryTime = (double)(stop - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.6f\t\t\t%.6f\n", n, linearTime, binaryTime);

        free(arr);
    }

    printf("\nConclusion:\n");
    printf("Linear Search has O(n) time complexity and becomes slower as the array size increases.\n");
    printf("Binary Search has O(log n) time complexity and remains much faster for searching in sorted arrays.\n");
    printf("Therefore, Binary Search is the preferred searching algorithm when the data is sorted.\n");

    return 0;
}