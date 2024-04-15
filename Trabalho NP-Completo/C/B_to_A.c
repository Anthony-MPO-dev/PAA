#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

struct Graph {
    int numVertices;
    int** adjMatrix;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1;
    } else {
        printf("Erro: src ou dest estão fora do intervalo válido.\n");
    }
}

void readGraph(const char* filename, struct Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[256];
    int numVertices;
    if (fgets(line, sizeof(line), file)) {
        numVertices = atoi(line);
        graph->numVertices = numVertices;
    } else {
        printf("Erro ao ler o número de vértices do arquivo.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ":");
        int src = atoi(token);

        token = strtok(NULL, " ");
        while (token != NULL) {
            int dest = atoi(token);
            addEdge(graph, src, dest);
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
}

void printGraph(struct Graph* graph) {
    printf("Grafo lido do arquivo:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("%d: ", i);
        bool printed = false;
        for (int j = 0; j < graph->numVertices; ++j) {
            if (graph->adjMatrix[i][j] == 1) {
                printf("%d ", j);
                printed = true;
            }
        }
        if (!printed) {
            printf("Nenhum");
        }
        printf("\n");
    }
}

bool isIndependentSet(struct Graph* graph, int vertices[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (graph->adjMatrix[vertices[i]][vertices[j]] == 1) {
                return false;
            }
        }
    }
    return true;
}

void exhaustiveSearch(struct Graph* graph, int* max_set, int* max_size, int* current_set, int current_size, int start_vertex) {
    if (current_size > *max_size) {
        *max_size = current_size;
        for (int i = 0; i < current_size; ++i) {
            max_set[i] = current_set[i];
        }
    }

    for (int v = start_vertex; v < graph->numVertices; ++v) {
        bool valid = true;
        for (int i = 0; i < current_size; ++i) {
            if (graph->adjMatrix[current_set[i]][v] == 1) {
                valid = false;
                break;
            }
        }
        if (valid) {
            current_set[current_size] = v;
            exhaustiveSearch(graph, max_set, max_size, current_set, current_size + 1, v + 1);
        }
    }
}

int main() {
    struct Graph* graph = createGraph(MAX_VERTICES);
    readGraph("graph.txt", graph);
    printGraph(graph);

    int* max_set = (int*)malloc(MAX_VERTICES * sizeof(int));
    int max_size = 0;
    int* current_set = (int*)malloc(MAX_VERTICES * sizeof(int));
    int current_size = 0;

    exhaustiveSearch(graph, max_set, &max_size, current_set, current_size, 0);

    printf("Maior conjunto independente encontrado:\n");
    for (int i = 0; i < max_size; ++i) {
        printf("%d ", max_set[i]);
    }
    printf("\n");

    free(max_set);
    free(current_set);

    return 0;
}
