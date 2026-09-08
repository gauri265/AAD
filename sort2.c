#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
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

void copyArray(int source[], int destination[], int n)
{
    for(int i = 0; i < n; i++)
        destination[i] = source[i];
}

int main()
{
    int sizes[] = {10000, 50000, 100000, 200000, 300000};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));
    printf("QUICK SORT:\n\n");
    for(int s = 0; s < count; s++)
    {
        int n = sizes[s];
        printf("Test Case %d (Array with %d elements)\n",
               s + 1, n);
        int *original = malloc(n * sizeof(int));
        int *arr = malloc(n * sizeof(int));
        if(original == NULL || arr == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 0; i < n; i++)
            original[i] = rand() % 100000;
        copyArray(original, arr, n);
        clock_t start = clock();
        quickSort(arr, 0, n - 1);
        clock_t stop = clock();
        double quickTime =(double)(stop - start) / CLOCKS_PER_SEC;
        printf("Time taken = %.6f seconds\n\n", quickTime);
        free(original);
        free(arr);
    }
    printf("\nBUBBLE SORT:\n\n");
    for(int s = 0; s < count; s++)
    {
        int n = sizes[s];
        printf("Test Case %d (Array with %d elements)\n",s + 1, n);
        int *original = malloc(n * sizeof(int));
        int *arr = malloc(n * sizeof(int));
        if(original == NULL || arr == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
        for(int i = 0; i < n; i++)
            original[i] = rand() % 100000;
        copyArray(original, arr, n);
        clock_t start = clock();
        bubbleSort(arr, n);
        clock_t stop = clock();
        double bubbleTime =(double)(stop - start) / CLOCKS_PER_SEC;
        printf("Time taken = %.6f seconds\n\n", bubbleTime);
        free(original);
        free(arr);
    }
    return 0;
}