#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Số đỉnh tối đa

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    int isDirected;
    int adjMatrix[MAX][MAX];
    Node *adjList[MAX];
} Graph;

// Tạo một đỉnh mới cho danh sách kề
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Khởi tạo đồ thị
Graph *createGraph(int numVertices, int isDirected)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->isDirected = isDirected;

    // Khởi tạo ma trận kề với giá trị 0
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Thêm cạnh vào đồ thị
void addEdge(Graph *graph, int src, int dest)
{
    // Thêm cạnh vào ma trận kề
    graph->adjMatrix[src][dest] = 1;
    if (!graph->isDirected)
    {
        graph->adjMatrix[dest][src] = 1;
    }

    // Thêm cạnh vào danh sách kề
    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!graph->isDirected)
    {
        newNode = createNode(src);
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    }
}

// Thêm đỉnh vào đồ thị
void addVertex(Graph *graph)
{
    graph->numVertices++;
}

// Hiển thị đồ thị dưới dạng ma trận kề
void displayAdjMatrix(Graph *graph)
{
    printf("Ma trận kề:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Hiển thị đồ thị dưới dạng danh sách kề
void displayAdjList(Graph *graph)
{
    printf("Danh sách kề:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d: ", i);
        Node *temp = graph->adjList[i];
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    int numVertices, isDirected;
    printf("Nhập số lượng đỉnh: ");
    scanf("%d", &numVertices);

    printf("Đồ thị có hướng? (1: Có, 0: Không): ");
    scanf("%d", &isDirected);

    Graph *graph = createGraph(numVertices, isDirected);

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Thêm cạnh\n");
        printf("2. Hiển thị ma trận kề\n");
        printf("3. Hiển thị danh sách kề\n");
        printf("4. Thêm đỉnh\n");
        printf("0. Thoát\n");
        printf("Lựa chọn: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int src, dest;
            printf("Nhập đỉnh nguồn và đỉnh đích (src dest): ");
            scanf("%d %d", &src, &dest);
            addEdge(graph, src, dest);
            break;
        }
        case 2:
            displayAdjMatrix(graph);
            break;
        case 3:
            displayAdjList(graph);
            break;
        case 4:
            addVertex(graph);
            printf("Đã thêm một đỉnh mới. Số đỉnh hiện tại: %d\n", graph->numVertices);
            break;
        case 0:
            printf("Thoát chương trình.\n");
            break;
        default:
            printf("Lựa chọn không hợp lệ.\n");
        }
    } while (choice != 0);

    return 0;
}
