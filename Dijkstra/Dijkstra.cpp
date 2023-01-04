#include <iostream>
#include <stdio.h>

#define MAX_VERTICES 7

int path[7];
typedef struct {
    int n;
    int* visited;
    int** adj_mat;
    int* distance;
    int path[7];
}GraphType;

void makeGraph(GraphType* gr, int no) {
    gr->n = no;
    gr->visited = (int*)malloc(sizeof(int) * (no + 1));
    gr->distance = (int*)malloc(sizeof(int) * (no + 1));
    gr->adj_mat = (int**)malloc((sizeof(int*) * (no + 1)));


    for (int i = 0; i < no; i++) {
        gr->adj_mat[i] = (int*)malloc(sizeof(int) * (no + 1));
        gr->visited[i] = 0;
    }

    for (int i = 0; i < no; i++) {
        gr->visited[i] = 0;
        for (int j = 0; j < no; j++)
            gr->adj_mat[i][j] = 1000;
    }

    for (int i = 0; i < no; i++) {
        gr->distance[i] = 0;
    }
}

void addGraphEdge(GraphType* gr, int a, int b, int weight) {
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
    for (i = 0; i < n; i++) {
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
    gr->path[0] = start;
    for (i = 0; i < n; i++) {
        gr->distance[i] = gr->adj_mat[start][i]; //start노드으로부터 다른 노드까지의 거리를 distance에 저장
        gr->visited[i] = 0; //방문노드 행렬을 0으로 초기화
    }

    gr->visited[start] = 1; //start를 방문하므로 방문노드행렬중 start노드를 1로 변경
    gr->distance[start] = 0; //start에서 시작하므로 start거리를 0으로 초기화
    for (i = 0; i < n-1; i++) {
        u = choose(gr->distance, n, gr->visited); //가장 거리가 짧은 노드를 선택
        gr->visited[u] = 1; //다음 인접노드를 방문하므로 1로 변경
        for (w = 0; w < n; w++)
            if (!gr->visited[w]) //방문하지 않은 노드중에서
                if (gr->distance[u] + gr->adj_mat[u][w] < gr->distance[w]) //인접노드들은 거리가 이전가중치의 합으로 갱신된다
                    gr->distance[w] = gr->distance[u] + gr->adj_mat[u][w]; //새롭게 측정된 거리표를 갱신
        gr->path[i + 1] = u;
    }

   
}

void printGraph(GraphType* gr) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ", gr->adj_mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    GraphType gr1;
    int start, end, dist;
    int v;

    printf("Dijkstra 알고리즘\n");
    makeGraph(&gr1, MAX_VERTICES);
    while (1) {

        printf(" \n시작 >> ");
        scanf_s("%d", &start);
        printf("끝 >> ");
        scanf_s("%d", &end);
        printf("거리 >> ");
        scanf_s("%d", &dist);

        if (start == 0 && end == 0 && dist == 0)
            break;

        addGraphEdge(&gr1, start, end, dist);
    }

    printGraph(&gr1);

    printf("\n시작노드를 입력 0~%d >> ", MAX_VERTICES-1);
    scanf_s("%d", &v);

    shortest_path(&gr1, v, MAX_VERTICES);

    printf("방문순서 - ");
    for (int i = 0; i < MAX_VERTICES; i++)
        printf("%d ", gr1.path[i]);
    printf("\n");

    printf("거리 - ");
    for (int i = 0; i < MAX_VERTICES; i++)
        printf("%d ", gr1.distance[i]);
    printf("\n");
}

