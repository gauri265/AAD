#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 999999

#define WHITE 0
#define GRAY 1
#define BLACK 2

int **adj;
int color[MAX];
int dist[MAX];
int pred[MAX];
int vertices;

void BFS(int source)
{
    int *queue = (int *)malloc(vertices * sizeof(int));

    if (queue == NULL)
    {
        printf("Queue memory allocation failed!\n");
        return;
    }

    int front = 0;
    int rear = 0;

    for (int i = 0; i < vertices; i++)
    {
        color[i] = WHITE;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    color[source] = GRAY;
    dist[source] = 0;

    queue[rear++] = source;

    while (front < rear)
    {
        int u = queue[front++];

        for (int v = 0; v < vertices; v++)
        {
            if (adj[u][v] && color[v] == WHITE)
            {
                color[v] = GRAY;
                dist[v] = dist[u] + 1;
                pred[v] = u;

                queue[rear++] = v;
            }
        }

        color[u] = BLACK;
    }

    printf("\nFirst 10 elements:\n");

    int limit = (rear < 10) ? rear : 10;

    for (int i = 0; i < limit; i++)
    {
        printf("%d ", queue[i]);
    }

    printf("\n");

    free(queue);
}

void readEdgeList(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Cannot open %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int edges;
    if (fscanf(file, "%d %d", &vertices, &edges) != 2)
    {
        printf("Invalid file format.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (vertices > MAX)
    {
        printf("Graph exceeds maximum size.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    adj = (int **)malloc(vertices * sizeof(int *));

    if (adj == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++)
    {
        adj[i] = (int *)calloc(vertices, sizeof(int));

        if (adj[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);

            for (int j = 0; j < i; j++)
                free(adj[j]);

            free(adj);
            exit(EXIT_FAILURE);
        }
    }

    int u, v;

    for (int i = 0; i < edges; i++)
    {
        if (fscanf(file, "%d %d", &u, &v) == 2)
        {
            if (u >= 0 && u < vertices &&
                v >= 0 && v < vertices)
            {
                adj[u][v] = 1;
                adj[v][u] = 1;
            }
        }
    }

    fclose(file);
}

void readAdjMatrix(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Cannot open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &vertices) != 1)
    {
        printf("Invalid file format.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (vertices > MAX)
    {
        printf("Graph exceeds maximum size.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    adj = (int **)malloc(vertices * sizeof(int *));

    if (adj == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++)
    {
        adj[i] = (int *)malloc(vertices * sizeof(int));

        if (adj[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);

            for (int j = 0; j < i; j++)
                free(adj[j]);

            free(adj);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < vertices; j++)
        {
            fscanf(file, "%d", &adj[i][j]);
        }
    }

    fclose(file);
}

void freeGraph()
{
    for (int i = 0; i < vertices; i++)
    {
        free(adj[i]);
    }

    free(adj);
}

int main()
{
    clock_t start, stop;

    //readEdgeList("graph6_edgelist.txt");
    readAdjMatrix("graph2_adj.txt");

    start = clock();

    BFS(0);

    stop = clock();

    double elapsed =
        (double)(stop - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %.6f seconds\n", elapsed);

    freeGraph();

    return 0;
}