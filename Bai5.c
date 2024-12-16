#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Cấu trúc để biểu diễn một cạnh
struct Edge
{
    int to;
    int weight;
    struct Edge *next;
};

// Cấu trúc để biểu diễn một danh sách kề
struct AdjList
{
    struct Edge *head;
};

// Cấu trúc để biểu diễn một đồ thị
struct Graph
{
    int V;
    struct AdjList *array;
};

// Hàm tạo một cạnh mới
struct Edge *newEdge(int to, int weight)
{
    struct Edge *edge = (struct Edge *)malloc(sizeof(struct Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

// Hàm tạo một đồ thị với V đỉnh
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Hàm thêm một cạnh vào đồ thị
void addEdge(struct Graph *graph, int from, int to, int weight)
{
    struct Edge *edge = newEdge(to, weight);
    edge->next = graph->array[from].head;
    graph->array[from].head = edge;
}

// Hàm tìm đỉnh có khoảng cách nhỏ nhất chưa được duyệt
int minDistance(int dist[], int visited[], int V)
{
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Hàm triển khai thuật toán Dijkstra
void dijkstra(struct Graph *graph, int src)
{
    int V = graph->V;
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        struct Edge *edge = graph->array[u].head;
        while (edge != NULL)
        {
            int v = edge->to;
            int weight = edge->weight;
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
            edge = edge->next;
        }
    }

    printf("Khoảng cách ngắn nhất từ đỉnh %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("\u0110\u1ec9nh %d: %d\n", i, dist[i]);
}

int main()
{
    int V, E, src;
    printf("Nhập số lượng đỉnh: ");
    scanf("%d", &V);

    struct Graph *graph = createGraph(V);

    printf("Nhập số lượng cạnh: ");
    scanf("%d", &E);

    printf("Nhập các cạnh với trọng số dương (from, to, weight):\n");
    for (int i = 0; i < E; i++)
    {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        addEdge(graph, from, to, weight);
    }

    printf("Nhập đỉnh nguồn: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}
