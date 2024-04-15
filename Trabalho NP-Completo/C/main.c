#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_LITERALS 3

// Estrutura para representar um nó de uma lista encadeada
struct Node {
    int data;
    struct Node* next;
};

// Estrutura para representar uma lista encadeada
struct List {
    struct Node* head;
};

// Estrutura para representar um grafo
struct Graph {
    int numVertices;
    struct List* adjLists[MAX_VERTICES];
};

// Função para criar um novo nó em uma lista encadeada
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com n vértices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    // Inicializando as listas de adjacências com NULL
    for (int i = 0; i < numVertices; ++i) {
        graph->adjLists[i] = (struct List*)malloc(sizeof(struct List));
        graph->adjLists[i]->head = NULL;
    }

    return graph;
}

// Função para adicionar uma aresta entre os vértices src e dest
void addEdge(struct Graph* graph, int src, int dest) {
    // Adicionando uma aresta de src para dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src]->head;
    graph->adjLists[src]->head = newNode;

    // Adicionando uma aresta de dest para src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest]->head;
    graph->adjLists[dest]->head = newNode;
}

// Função para verificar se um conjunto de vértices é um conjunto independente C(I, S)
bool isIndependentSet(struct Graph* graph, int vertices[], int size) {
    // Verifica se cada vértice no conjunto não é adjacente a nenhum outro vértice no conjunto
    for (int i = 0; i < size; ++i) {
        struct Node* current = graph->adjLists[vertices[i]]->head;
        while (current != NULL) {
            for (int j = 0; j < size; ++j) {
                if (current->data == vertices[j]) {
                    return false; // Encontrou uma aresta entre dois vértices no conjunto
                }
            }
            current = current->next;
        }
    }
    return true; // Nenhum par de vértices no conjunto é adjacente
}

// Função para realizar a redução da instância do problema A' para B'
struct Graph* reduction(char* clauses[], int numClauses) {
    int totalVertices = 0;

    // Calcula o número total de vértices
    for (int i = 0; i < numClauses; ++i) {
        totalVertices += strlen(clauses[i]);
    }

    // Cria um grafo com número de vértices igual ao número total de literais
    struct Graph* graph = createGraph(totalVertices);

    int vertexIndex = 0;

    // Adiciona as arestas correspondentes para cada cláusula
    for (int i = 0; i < numClauses; ++i) {
        // Adiciona as arestas entre os vértices da cláusula
        for (int j = 0; j < strlen(clauses[i]); ++j) {
            int literalIndex = vertexIndex + j; // Índice do literal no grafo
            for (int k = j + 1; k < strlen(clauses[i]); ++k) {
                int otherLiteralIndex = vertexIndex + k; // Índice do outro literal no grafo
                addEdge(graph, literalIndex, otherLiteralIndex); // Adiciona uma aresta entre os literais na mesma cláusula
            }
        }
        vertexIndex += strlen(clauses[i]); // Atualiza o índice para o próximo conjunto de vértices
    }

    // Adiciona arestas adicionais entre vértices que representam literais opostos
    for (int i = 0; i < numClauses; ++i) {
        int clauseOffset_i = i * MAX_LITERALS; // Deslocamento para o início dos vértices da cláusula i
        for (int j = i + 1; j < numClauses; ++j) {
            int clauseOffset_j = j * MAX_LITERALS; // Deslocamento para o início dos vértices da cláusula j
            for (int k = 0; k < strlen(clauses[i]); ++k) {
                int literalIndex_i = clauseOffset_i + k; // Índice do literal na cláusula i
                for (int l = 0; l < strlen(clauses[j]); ++l) {
                    int literalIndex_j = clauseOffset_j + l; // Índice do literal na cláusula j
                    // Verifica se os literais são opostos
                    if (clauses[i][k] != clauses[j][l] && (clauses[i][k] == clauses[j][l] + 32 || clauses[i][k] == clauses[j][l] - 32)) {
                        addEdge(graph, literalIndex_i, literalIndex_j); // Adiciona uma aresta entre os literais opostos
                    }
                }
            }
        }
    }

    return graph;
}

void writeGraphToFile(struct Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "%d\n", graph->numVertices);

    for (int i = 0; i < graph->numVertices; ++i) {
        fprintf(file, "%d:", i);
        struct Node* current = graph->adjLists[i]->head;
        while (current != NULL) {
            fprintf(file, " %d", current->data);
            current = current->next;
        }
        fprintf(file, "\n");
    }

    fclose(file);
}



int Primeiro() {
    int numVertices;
    char choice;

    // Solicita ao usuário que digite uma aresta
    printf("Deseja Usar o Funcionamento estatico ou manual de criação de Grafo?(S:estatico, M:Manual): ");
    scanf("%c", &choice);

    if (choice == 'M' || choice == 'm') {
        int src, dest;
        choice = 's';

        printf("========================================\n");
        printf("==========CRIACAO DO GRAFO==============\n");
        printf("Digite o número de vértices do grafo: ");
        scanf("%d", &numVertices);

        // Criando o grafo
        struct Graph* graph = createGraph(numVertices);

        do {
            // Solicita ao usuário que digite uma aresta
            printf("Digite a aresta (formato src dest): ");
            scanf("%d %d", &src, &dest);
            
            // Adiciona a aresta ao grafo
            addEdge(graph, src, dest);

            // Pergunta ao usuário se ele deseja adicionar mais arestas
            printf("Deseja adicionar mais arestas? (s/n): ");
            scanf(" %c", &choice);
        } while (choice == 's' || choice == 'S');

        // Definindo um conjunto independente para verificar
        int independentSet[numVertices];
        int setSize = 0;
        choice = 's';   

        printf("========================================\n");
        printf("===DEFINICAO DO CONJUNTO INDEPENDENTE===\n");
        do {
            // Solicita ao usuário que digite um vértice do conjunto independente
            printf("Digite o vértice do conjunto independente: ");
            scanf("%d", &independentSet[setSize]);
            setSize++;

            // Verifica se já foram escolhidos todos os vértices possíveis no grafo
            if (setSize == numVertices) {
                printf("Numero maximo de vertices ja selecionados\n");
                break;
            }

            // Pergunta ao usuário se ele deseja adicionar mais vértices ao conjunto
            printf("Deseja adicionar mais vértices ao conjunto independente? (s/n): ");
            scanf(" %c", &choice);
        } while (choice == 's' || choice == 'S');

        printf("========================================\n");
        printf("==============RESPOSTA==================\n");

        // Verificando se o conjunto é um conjunto independente
        if (isIndependentSet(graph, independentSet, setSize)) {       // AQUI SERIA NOSSA FUNCAO 'C'
            printf("O conjunto dado é um conjunto independente.\n");
        } else {
            printf("O conjunto dado NÃO é um conjunto independente.\n");
        }

    }else if (choice == 'S' || choice == 's'){

        struct Graph* graph = createGraph(5);

        // Adicionando as arestas conforme a instância fornecida
        addEdge(graph, 0, 1);
        addEdge(graph, 0, 2);
        addEdge(graph, 1, 2);
        addEdge(graph, 1, 3);
        addEdge(graph, 2, 3);
        addEdge(graph, 2, 4);

        // Definindo um conjunto independente para verificar
        int independentSet[] = {0, 3, 4};
        int setSize = sizeof(independentSet) / sizeof(independentSet[0]);

        // Verificando se o conjunto é um conjunto independente
        if (isIndependentSet(graph, independentSet, setSize)) {       // AQUI SERIA NOSSA FUNCAO 'C'
            printf("O conjunto dado é um conjunto independente.\n");
        } else {
            printf("O conjunto dado NÃO é um conjunto independente.\n");
        }

    }else {
        printf("\nEscolha Invalida!\n");
        return 1;
    }

    return 0;
}

int main() {
    char* clauses[] = {"aBc", "AbC", "ABC", "ab"};
    int numClauses = sizeof(clauses) / sizeof(clauses[0]);

    // Realiza a redução da instância do problema A' para B'
    struct Graph* graph = reduction(clauses, numClauses);

    writeGraphToFile(graph, "grafo.txt");

    // Exibe o grafo resultante
    printf("Grafo resultante:\n");
    printf("Número de vértices: %d\n", graph->numVertices);
    printf("Arestas:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("Vértice %d:", i);
        struct Node* current = graph->adjLists[i]->head;
        while (current != NULL) {
            printf(" %d", current->data);
            current = current->next;
        }
        printf("\n");
    }

    // Libera a memória alocada para o grafo
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* current = graph->adjLists[i]->head;
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
        free(graph->adjLists[i]);
    }
    free(graph);

    return 0;
}


// int main() {
//     printf("========================================\n");
//     printf("========EXECUCAO PRIMEIRO PASSO=========\n");
//     if (Primeiro() == 0)  {
//         printf("\nCodigo Executado com Sucesso!\n");
//     } else {
//         printf("\nErro na funcao Primeiro!\n");
//     }
// }
