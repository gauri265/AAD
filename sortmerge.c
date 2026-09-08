#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int temp[500000];

void merge(int arr[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main()
{
    int sizes[] = {1000, 2000, 5000, 7000, 10000, 50000, 500000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    /* ---------------- MERGE SORT ---------------- */

    printf("MERGE SORT:\n\n");

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        printf("Test Case %d (Array with %d elements)\n",
               s + 1, n);

        int *arr1 = (int *)malloc(n * sizeof(int));

        if (arr1 == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        /* Generate array in descending order */
        for (int i = 0; i < n; i++)
            arr1[i] = n - i;

        clock_t start = clock();

        mergeSort(arr1, 0, n - 1);

        clock_t stop = clock();

        double mergeTime =
            (double)(stop - start) / CLOCKS_PER_SEC;

        printf("Time taken = %.6f seconds\n\n", mergeTime);

        free(arr1);
    }


    /* ---------------- SELECTION SORT ---------------- */

    printf("\nSELECTION SORT:\n\n");

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        printf("Test Case %d (Array with %d elements)\n",
               s + 1, n);

        int *arr2 = (int *)malloc(n * sizeof(int));

        if (arr2 == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        /* Generate array in descending order */
        for (int i = 0; i < n; i++)
            arr2[i] = n - i;

        clock_t start = clock();

        selectionSort(arr2, n);

        clock_t stop = clock();

        double selectionTime =
            (double)(stop - start) / CLOCKS_PER_SEC;

        printf("Time taken = %.6f seconds\n\n", selectionTime);

        free(arr2);
    }

    return 0;
}