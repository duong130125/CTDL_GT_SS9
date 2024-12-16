#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node *adjLists[MAX_VERTICES];
    bool isDirected;
} Graph;

// Create a new node
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
Graph *createGraph(int numVertices, bool isDirected)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->isDirected = isDirected;

    for (int i = 0; i < numVertices; i++)
    {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Add edge to the graph
void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    if (!graph->isDirected)
    {
        newNode = createNode(src);
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
}

// DFS helper function to detect cycle in a directed graph
bool dfsDirected(Graph *graph, int vertex, bool *visited, bool *recStack)
{
    visited[vertex] = true;
    recStack[vertex] = true;

    Node *temp = graph->adjLists[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex] && dfsDirected(graph, adjVertex, visited, recStack))
        {
            return true;
        }
        else if (recStack[adjVertex])
        {
            return true;
        }

        temp = temp->next;
    }

    recStack[vertex] = false;
    return false;
}

// DFS helper function to detect cycle in an undirected graph
bool dfsUndirected(Graph *graph, int vertex, bool *visited, int parent)
{
    visited[vertex] = true;

    Node *temp = graph->adjLists[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex])
        {
            if (dfsUndirected(graph, adjVertex, visited, vertex))
            {
                return true;
            }
        }
        else if (adjVertex != parent)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

// Check if the graph contains a cycle
bool containsCycle(Graph *graph)
{
    bool visited[MAX_VERTICES] = {false};

    if (graph->isDirected)
    {
        bool recStack[MAX_VERTICES] = {false};

        for (int i = 0; i < graph->numVertices; i++)
        {
            if (!visited[i])
            {
                if (dfsDirected(graph, i, visited, recStack))
                {
                    return true;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (!visited[i])
            {
                if (dfsUndirected(graph, i, visited, -1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Main function
int main()
{
    int numVertices, numEdges, isDirected;

    printf("Nhap so luong dinh: ");
    scanf("%d", &numVertices);

    printf("Do thi co huong? (1: Co, 0: Khong): ");
    scanf("%d", &isDirected);

    Graph *graph = createGraph(numVertices, isDirected);

    printf("Nhap so luong canh: ");
    scanf("%d", &numEdges);

    printf("Nhap cac canh (dinh1 dinh2):\n");
    for (int i = 0; i < numEdges; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    if (containsCycle(graph))
    {
        printf("Do thi co chu ky\n");
    }
    else
    {
        printf("Do thi khong co chu ky\n");
    }

    return 0;
}
