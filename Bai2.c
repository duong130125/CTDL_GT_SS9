#include <stdio.h>

void createAdjacencyMatrix(int n, int edges, int matrix[][n])
{
    // Khởi tạo tất cả phần tử trong ma trận là 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }

    // Nhập danh sách các cạnh và cập nhật ma trận kề
    printf("\nNhập danh sách các cạnh:\n");
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        printf("Cạnh %d: ", i + 1);
        scanf("%d %d", &u, &v);

        // Giả sử các đỉnh được đánh số từ 0 đến n-1
        matrix[u][v] = 1;
        matrix[v][u] = 1; // Đảm bảo tính đối xứng
    }
}

void printAdjacencyMatrix(int n, int matrix[][n])
{
    printf("\nMa trận kề của đồ thị:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int isSymmetric(int n, int matrix[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                return 0; // Không đối xứng
            }
        }
    }
    return 1; // Đối xứng
}

int main()
{
    int n, edges;

    // Nhập số lượng đỉnh và cạnh
    printf("Nhập số lượng đỉnh: ");
    scanf("%d", &n);
    printf("Nhập số lượng cạnh: ");
    scanf("%d", &edges);

    int matrix[n][n];

    // Tạo ma trận kề
    createAdjacencyMatrix(n, edges, matrix);

    // In ma trận kề
    printAdjacencyMatrix(n, matrix);

    // Kiểm tra tính đối xứng
    if (isSymmetric(n, matrix))
    {
        printf("\nMa trận kề đối xứng.\n");
    }
    else
    {
        printf("\nMa trận kề không đối xứng.\n");
    }

    return 0;
}
