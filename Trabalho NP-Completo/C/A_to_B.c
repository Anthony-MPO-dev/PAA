#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CLAUSES 100
#define MAX_LITERALS 3

struct Graph {
    int numVertices;
    int** adjMatrix;
};

struct LiteralVertex {
    char literal;
    int vertex;
};

// Função para encontrar o índice de um literal em um array de estruturas LiteralVertex
int findLiteralIndex(struct LiteralVertex* literals, int numLiterals, char literal) {
    for (int i = 0; i < numLiterals; ++i) {
        if (literals[i].literal == literal) {
            return i;
        }
    }
    return -1;
}

// Função para adicionar uma aresta entre dois literais no grafo
void addLiteralEdge(struct Graph* graph, struct LiteralVertex* literals, int srcIndex, int destIndex) {
    int srcVertex = literals[srcIndex].vertex;
    int destVertex = literals[destIndex].vertex;
    graph->adjMatrix[srcVertex][destVertex] = 1;
    graph->adjMatrix[destVertex][srcVertex] = 1;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }

    return graph;
}

void saveGraph(struct Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%d\n", graph->numVertices);
    for (int i = 0; i < graph->numVertices; ++i) {
        fprintf(file, "%d: ", i);
        int printed = 0;
        for (int j = 0; j < graph->numVertices; ++j) {
            if (graph->adjMatrix[i][j] == 1) {
                fprintf(file, "%d ", j);
                printed = 1;
            }
        }
        if (!printed) {
            fprintf(file, "Nenhum");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    char* clauses[] = {"ABZ", "XYC", "AYC"};
    int numClauses = sizeof(clauses) / sizeof(clauses[0]);
    int numVertices = 0;
    struct LiteralVertex literals[MAX_CLAUSES * MAX_LITERALS];

    // Mapeia os literais para os vértices do grafo
    for (int i = 0; i < numClauses; ++i) {
        int clauseLength = strlen(clauses[i]);
        for (int j = 0; j < clauseLength; ++j) {
            char literal = clauses[i][j];
            int literalIndex = findLiteralIndex(literals, numVertices, literal);
            if (literalIndex == -1) {
                // Literal ainda não mapeado, adiciona ao array de literais e incrementa o número de vértices
                struct LiteralVertex newLiteralVertex = {literal, numVertices};
                literals[numVertices] = newLiteralVertex;
                numVertices++;
            }
        }
    }

    struct Graph* graph = createGraph(numVertices);

    // Adiciona arestas entre literais da mesma cláusula
    for (int i = 0; i < numClauses; ++i) {
        int clauseLength = strlen(clauses[i]);
        for (int j = 0; j < clauseLength - 1; ++j) {
            for (int k = j + 1; k < clauseLength; ++k) {
                char srcLiteral = clauses[i][j];
                char destLiteral = clauses[i][k];
                int srcIndex = findLiteralIndex(literals, numVertices, srcLiteral);
                int destIndex = findLiteralIndex(literals, numVertices, destLiteral);
                addLiteralEdge(graph, literals, srcIndex, destIndex);
            }
        }
    }

    // Salva o grafo em um arquivo
    saveGraph(graph, "graph.txt");

    return 0;
}
