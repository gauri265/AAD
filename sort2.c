#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1, j, temp;

    for(j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main()
{
    int sizes[] = {10000, 50000, 100000, 200000, 300000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Size\tBubble Sort(s)\tQuick Sort(s)\n");

    srand(time(NULL));

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        
        for (int i = 0; i < n; i++)
        {
            arr1[i] = rand() % 100000;
            arr2[i] = arr1[i]; 
        }

        
        clock_t start = clock();
        bubbleSort(arr1, n);
        clock_t stop = clock();

        double bubble_time = (double)(stop - start) / CLOCKS_PER_SEC;

        
        start = clock();
        quickSort(arr2, 0, n - 1);
        stop = clock();

        double quick_time = (double)(stop - start) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t\t%.6f\n", n, bubble_time, quick_time);

        free(arr1);
        free(arr2);
    }

    return 0;
}