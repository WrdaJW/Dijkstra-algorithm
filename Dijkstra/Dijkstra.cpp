#include <iostream>

#define MAX_VERTICES 7

typedef struct {
    int n;
    int* visited;
    int** adj_mat;
    int* distance;
}GraphType;

void makeGraph(GraphType* gr, int no) {
    gr->n = no;
    gr->visited = (int*)malloc(sizeof(int) * (no + 1));
    gr->distance = (int*)malloc(sizeof(int) * (no + 1));
    gr->adj_mat = (int**)malloc((sizeof(int*) * (no + 1)));


    for (int i = 1; i <= no; i++) {
        gr->adj_mat[i] = (int*)malloc(sizeof(int) * (no + 1));
        gr->visited[i] = 0;
    }

    for (int i = 1; i <= no; i++) {
        gr->visited[i] = 0;
        for (int j = 1; j <= no; j++)
            gr->adj_mat[i][j] = 0;
    }

    for (int i = 1; i <= no; i++) {
        gr->distance[i] = 0;
    }
}

void addGragphEdge(GraphType* gr, int a, int b, int weight) {
    gr->adj_mat[a][b] = weight;
    gr->adj_mat[b][a] = weight;
}

void init_visited(GraphType* gr) {
    for (int i = 0; i <= gr->n; i++)
        gr->visited[i] = 0;
}

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = 2147483647;
    minpos = -1; 
    for (i = 1; i <= n; i++) {
        //방문노드가 아니고 최소거리의 노드를 선택
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i; 
        }
    }
    return minpos; //인접 노드중 최소거리의 노드 반환
}

void shortest_path(GraphType* gr, int start, int n) {
    int i, u, w;
    for (i = 0; i < n; i++) {
        gr->distance[i] = gr->adj_mat[start][i];
        gr->visited[i] = 0;
    }

    gr->visited[start] = 1;
    gr->distance[start] = 0;
    for (i = 1; i < n; i++) {
        u = choose(gr->distance, n, gr->visited);
        gr->visited[u] = 1;
        for (w = 0; w < n; w++)
            if (!gr->visited[w])
                if (gr->distance[u] + gr->adj_mat[u][w] < gr->distance[w])
                    gr->distance[w] = gr->distance[u] + gr->adj_mat[u][w];

    }
}

int main()
{
    std::cout << "Hello World!\n";
}

