#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define WHITE 0
#define GRAY  1
#define BLACK 2

int **adj;
int *color;
int *pred;
int *discover;
int *finish;
int vertices;
int Time;

void DFSVisit(int u)
{
    color[u] = GRAY;
    if(u<10){
    printf("%d ",u);
    }
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
        if (u >= 0 && u < vertices && v >= 0 && v < vertices)
        {
            adj[u][v] = 1;
       
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
}


void freeGraph()
{
    for (int i = 0; i < vertices; i++)
        free(adj[i]);
        
    free(adj);
    free(color);
    free(pred);
    free(discover);
    free(finish);
}


int main()
{
    clock_t start, stop;
    readEdgeList("graph4_directed_edgelist.txt");
    //readAdjMatrix("graph1_adj.txt");
    start = clock();
    DFS();
    stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time = %.6f seconds\n", elapsed);\
    freeGraph();
    return 0;
}

 
