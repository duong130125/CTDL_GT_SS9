#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Giới hạn số lượng đỉnh tối đa

// Cấu trúc danh sách kề
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

Node *adjacencyList[MAX];
bool visited[MAX];

// Hàng đợi để hỗ trợ BFS
int queue[MAX];
int front = -1, rear = -1;

// Hàm thêm phần tử vào hàng đợi
void enqueue(int vertex)
{
    if (rear == MAX - 1)
    {
        printf("Hàng đợi đầy!\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = vertex;
}

// Hàm lấy phần tử ra khỏi hàng đợi
int dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Hàng đợi rỗng!\n");
        return -1;
    }
    return queue[front++];
}

// Hàm kiểm tra hàng đợi có rỗng không
bool isQueueEmpty()
{
    return front == -1 || front > rear;
}

// Hàm tạo một nút mới trong danh sách kề
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm cạnh vào đồ thị
void addEdge(int u, int v)
{
    Node *newNode = createNode(v);
    newNode->next = adjacencyList[u];
    adjacencyList[u] = newNode;

    // Do đồ thị vô hướng, thêm cạnh ngược lại
    newNode = createNode(u);
    newNode->next = adjacencyList[v];
    adjacencyList[v] = newNode;
}

// Hàm thực hiện thuật toán BFS
void BFS(int startVertex)
{
    printf("Thứ tự các đỉnh được duyệt: ");

    enqueue(startVertex);
    visited[startVertex] = true;

    while (!isQueueEmpty())
    {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Duyệt qua danh sách kề của đỉnh hiện tại
        Node *temp = adjacencyList[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                enqueue(adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main()
{
    int vertices, edges;

    // Nhập số lượng đỉnh và cạnh
    printf("Nhập số lượng đỉnh: ");
    scanf("%d", &vertices);
    printf("Nhập số lượng cạnh: ");
    scanf("%d", &edges);

    // Khởi tạo danh sách kề và mảng visited
    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = NULL;
        visited[i] = false;
    }

    // Nhập danh sách các cạnh
    printf("Nhập các cạnh (đỉnh1 đỉnh2):\n");
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Nhập đỉnh bắt đầu
    int startVertex;
    printf("Nhập đỉnh bắt đầu: ");
    scanf("%d", &startVertex);

    // Thực hiện BFS
    BFS(startVertex);

    return 0;
}
