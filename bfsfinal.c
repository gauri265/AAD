#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

#define WHITE 0
#define GRAY 1
#define BLACK 2

int adj[N][N];
int color[N];
int d[N];
int pred[N];

// Function to read adjacency matrix from file
void readGraphFromFile()
{
    FILE *fp;
    int i, j;

    fp = fopen("graph.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening graph.txt!\n");
        exit(1);
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            fscanf(fp, "%d", &adj[i][j]);
        }
    }

    fclose(fp);
}

// BFS Function
void BFS(int s)
{
    int queue[N];
    int front = 0, rear = 0;
    int u, v;

    // Initialize all vertices
    for (u = 0; u < N; u++)
    {
        color[u] = WHITE;
        d[u] = 9999;
        pred[u] = -1;
    }

    // Initialize source vertex
    color[s] = GRAY;
    d[s] = 0;
    pred[s] = -1;

    // Enqueue source
    queue[rear++] = s;

    printf("BFS Traversal: ");

    // While queue is not empty
    while (front < rear)
    {
        u = queue[front++];
        printf("%d ", u);

        // Check all adjacent vertices
        for (v = 0; v < N; v++)
        {
            if (adj[u][v] == 1 && color[v] == WHITE)
            {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                pred[v] = u;
                queue[rear++] = v;
            }
        }

        color[u] = BLACK;
    }
}

int main()
{
    clock_t start, stop;

    // Read graph from file
    readGraphFromFile();

    start = clock();

    // Call BFS with source vertex 0
    BFS(0);

    stop = clock();

    double time_elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

    printf("\n\nVertex\tDistance\tPredecessor\n");

    for (int i = 0; i < N; i++)
    {
        printf("%d\t%d\t\t%d\n", i, d[i], pred[i]);
    }

    printf("\nBFS Execution Time = %f seconds\n", time_elapsed);

    return 0;
