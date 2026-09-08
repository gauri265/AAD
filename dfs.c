#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int **adj;
int *color, *pred, *discover, *finish, *dfsOrder;
int vertices, Time;
int dfsCount = 0;
int edges = 0;

void DFSVisit(int u)
{
    color[u] = GRAY;
    dfsOrder[dfsCount++] = u;
    discover[u] = ++Time;

    for (int v = 0; v < vertices; v++)
    {
        if (adj[u][v] && color[v] == WHITE)
        {
            pred[v] = u;
            DFSVisit(v);
        }
    }

    color[u] = BLACK;
    finish[u] = ++Time;
}

void DFS()
{
    color = (int *)malloc(vertices * sizeof(int));
    pred = (int *)malloc(vertices * sizeof(int));
    discover = (int *)malloc(vertices * sizeof(int));
    finish = (int *)malloc(vertices * sizeof(int));
    dfsOrder = (int *)malloc(vertices * sizeof(int));

    dfsCount = 0;

    for (int i = 0; i < vertices; i++)
    {
        color[i] = WHITE;
        pred[i] = -1;
        discover[i] = 0;
        finish[i] = 0;
    }

    Time = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (color[i] == WHITE)
        {
            DFSVisit(i);
        }
    }

    printf("Number of vertices = %d\n", vertices);
    printf("Number of edges = %d\n", edges);

    printf("Vertices visited:\n");

    int limit = (dfsCount < 5) ? dfsCount : 5;

    for (int i = 0; i < limit; i++)
    {
        printf("%d ", dfsOrder[i]);
    }

    printf(". . .");

    if (dfsCount >= 2)
    {
        printf("%d %d\n",
               dfsOrder[dfsCount - 2],
               dfsOrder[dfsCount - 1]);
    }
    else if (dfsCount == 1)
    {
        printf("%d\n", dfsOrder[0]);
    }
    else
    {
        printf("No vertices visited\n");
    }
}

void readEdgeList(const char *filename)
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
        exit(EXIT_FAILURE);
    }

    adj = (int **)malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++)
    {
        adj[i] = (int *)calloc(vertices, sizeof(int));
    }

    int u, v;

    while (fscanf(file, "%d %d", &u, &v) == 2)
    {
        if (u >= 0 && u < vertices &&
            v >= 0 && v < vertices)
        {
            if (adj[u][v] == 0)
            {
                adj[u][v] = 1;
                edges++;
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
        exit(EXIT_FAILURE);
    }

    adj = (int **)malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++)
    {
        adj[i] = (int *)malloc(vertices * sizeof(int));

        for (int j = 0; j < vertices; j++)
        {
            fscanf(file, "%d", &adj[i][j]);
        }
    }

    fclose(file);

    edges = 0;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (adj[i][j])
            {
                edges++;
            }
        }
    }
}

void freeGraph()
{
    for (int i = 0; i < vertices; i++)
    {
        free(adj[i]);
    }

    free(adj);
    free(color);
    free(pred);
    free(discover);
    free(finish);
    free(dfsOrder);
}

int main()
{
    clock_t start, stop;

    /* For Edge List */
    //readEdgeList("graph6_directed_edgelist.txt");

    /* For Adjacency Matrix, comment the above line
       and uncomment the line below */

    readAdjMatrix("graph2_directed_adj.txt");

    start = clock();

    DFS();

    stop = clock();

    double elapsed =
        (double)(stop - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %.6f seconds\n", elapsed);

    freeGraph();

    return 0;
}