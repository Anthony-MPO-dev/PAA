#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

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

// Função para verificar se um conjunto de vértices é um conjunto independente
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
    printf("========================================\n");
    printf("========EXECUCAO PRIMEIRO PASSO=========\n");
    if (Primeiro() == 0)  {
        printf("\nCodigo Executado com Sucesso!\n");
    } else {
        printf("\nErro na funcao Primeiro!\n");
    }
}
