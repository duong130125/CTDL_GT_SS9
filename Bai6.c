#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void findMaxDegree(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int isDirected)
{
    int degrees[MAX_VERTICES] = {0};

    // Tính bậc của từng đỉnh
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j])
            {
                degrees[i]++;
                if (!isDirected)
                {
                    degrees[j]++; // Với đồ thị vô hướng, tính cả chiều ngược lại
                }
            }
        }
    }

    // Tìm đỉnh có bậc cao nhất
    int maxDegree = -1;
    int maxVertex = -1;
    for (int i = 0; i < numVertices; i++)
    {
        if (degrees[i] > maxDegree)
        {
            maxDegree = degrees[i];
            maxVertex = i;
        }
    }

    // In kết quả
    printf("\nĐỉnh có bậc cao nhất là: %d với bậc %d\n", maxVertex, maxDegree);
}

int main()
{
    int numVertices, numEdges, isDirected;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("Nhập số đỉnh: ");
    scanf("%d", &numVertices);

    printf("Nhập số cạnh: ");
    scanf("%d", &numEdges);

    printf("Đồ thị có hướng? (1: Có, 0: Không): ");
    scanf("%d", &isDirected);

    printf("\nNhập các cạnh (đỉnh bắt đầu, đỉnh kết thúc):\n");
    for (int i = 0; i < numEdges; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
        if (!isDirected)
        {
            adjMatrix[v][u] = 1; // Với đồ thị vô hướng, thêm cạnh ngược lại
        }
    }

    findMaxDegree(adjMatrix, numVertices, isDirected);

    return 0;
}
