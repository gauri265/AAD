#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int sizes[] = {10000, 50000, 100000,500000, 5000000, 10000000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int pos;
    double linearTime, binaryTime;

    printf("LINEAR SEARCH:\n\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("Test Case %d (Array with %d number of elements)\n",s + 1, n);

        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            arr[i] = i * 2;
        int key;
        printf("Enter the element to be searched: ");
        scanf("%d", &key);
        int repetitions = 500;
        clock_t start = clock();
        for (int r = 0; r < repetitions; r++)
            pos = linearSearch(arr, n, key);
        clock_t stop = clock();
        linearTime =
            (double)(stop - start) / CLOCKS_PER_SEC;
        if (pos == -1)
            printf("%d not found\n", key);
        else
            printf("%d found at position %d\n", key, pos);
        printf("Time taken = %f seconds\n\n", linearTime);
        free(arr);
    }
    printf("\n\nBINARY SEARCH:\n\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        printf("Test Case %d (Array with %d number of elements)\n",
               s + 1, n);
        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            arr[i] = i * 2;
        int key;
        printf("Enter the element to be searched: ");
        scanf("%d", &key);
        int repetitions = 500;
        clock_t start = clock();
        for (int r = 0; r < repetitions; r++)
            pos = binarySearch(arr, n, key);
        clock_t stop = clock();
        binaryTime =(double)(stop - start) / CLOCKS_PER_SEC;
        if (pos == -1)
            printf("%d not found\n", key);
        else
            printf("%d found at position %d\n", key, pos);
        printf("Time taken = %f seconds\n\n", binaryTime);
        free(arr);
    }
    return 0;
}





