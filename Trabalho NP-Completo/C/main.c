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
    int totalVertices = 0; // ! COMPLEXIDADE = O(1)

    // Calcula o número total de vértices 
    for (int i = 0; i < numClauses; ++i) { // ! COMPLEXIDADE =  O(numClauses)
        totalVertices += strlen(clauses[i]); // ! COMPLEXIDADE = O(1)
    }

    // Cria um grafo com número de vértices igual ao número total de literais  
    struct Graph* graph = createGraph(totalVertices);// ! COMPLEXIDADE O(1)

    int vertexIndex = 0; // ! COMPLEXIDADE = O(1)

    // Adiciona as arestas correspondentes para cada cláusula
    for (int i = 0; i < numClauses; ++i) { // ! COMPLEXIDADE = O(1)
        // Adiciona as arestas entre os vértices da cláusula
        for (int j = 0; j < strlen(clauses[i]); ++j) { // ! COMPLEXIDADE = O(numClauses)   m == numero de vertices na clausula
            int literalIndex = vertexIndex + j; // Índice do literal no grafo // ! COMPLEXIDADE = O(numClauses*m)
            for (int k = j + 1; k < strlen(clauses[i]); ++k) { // ! COMPLEXIDADE = O(numClauses)
                int otherLiteralIndex = vertexIndex + k; // Índice do outro literal no grafo // ! O(numClauses*(m-1)²)
                addEdge(graph, literalIndex, otherLiteralIndex); // Adiciona uma aresta entre os literais na mesma cláusula // ! COMPLEXIDADE = O(1)
            }
        }
        vertexIndex += strlen(clauses[i]); // Atualiza o índice para o próximo conjunto de vértices // ! COMPLEXIDADE = O(numClauses)
    }

    // Adiciona arestas adicionais entre vértices que representam literais opostos
    for (int i = 0; i < numClauses; ++i) { // ! COMPLEXIDADE = O(numClauses)
        int clauseOffset_i = i * MAX_LITERALS; // Deslocamento para o início dos vértices da cláusula i
        for (int j = i + 1; j < numClauses; ++j) { // ! COMPLEXIDADE = O(numClauses^2)
            int clauseOffset_j = j * MAX_LITERALS; // Deslocamento para o início dos vértices da cláusula j
            for (int k = 0; k < strlen(clauses[i]); ++k) {  // ! COMPLEXIDADE = O(numClauses² * m)
                int literalIndex_i = clauseOffset_i + k; // Índice do literal na cláusula i
                for (int l = 0; l < strlen(clauses[j]); ++l) {  // ! COMPLEXIDADE = O(numClauses² * m²)
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
    /*
        ! Complexidade FINAL: 
        * O(1)+O(numClauses)+
        * O(numClauses∗m)+
        * O(numClauses∗(m−1)²)+
        * O(1)+O(numClauses)+
        * O(numClauses}²)+
        * O(numClauses²∗m)+
        * O(numClauses²∗m²)  
        
        ! Resultado == O(numClauses²∗m²) == O(n²*m²)
        
        * */ 
}

// Função para realizar a busca exaustiva para encontrar o maior conjunto independente em um grafo
int* exhaustiveSearch(struct Graph* graph, int* maxSize) {
    // Inicializa o conjunto independente máximo e seu tamanho
    int* maxSet = (int*)malloc(sizeof(int) * MAX_VERTICES); // ! COMPLEXIDADE O(1)
    *maxSize = 0;                                           // ! COMPLEXIDADE O(1)

    // Para cada vértice no grafo
    for (int i = 0; i < graph->numVertices; ++i) {          // ! COMPLEXIDADE O(1)
        // Inicializa o conjunto atual com o vértice i      // ! COMPLEXIDADE O(numVertices)
        int currentSet[MAX_VERTICES];
        int setSize = 1;
        currentSet[0] = i;

        // Inicializa a lista de candidatos com todos os vértices, exceto o vértice i
        bool candidates[MAX_VERTICES] = {false};
        for (int j = 0; j < graph->numVertices; ++j) { 
            if (j != i) {                                   // ! COMPLEXIDADE O(numVertices^2)
                candidates[j] = true;
            }
        }

        // Enquanto houver candidatos
        while (true) {                       // ! Complexidade: indefinida   
            int v = -1;         // ! COMPLEXIDADE O(1)
            // Encontra um candidato
            for (int j = 0; j < graph->numVertices; ++j) { // ! COMPLEXIDADE O(numVertices) 
                if (candidates[j]) {
                    v = j;
                    break;
                }
            }

            // Se não houver mais candidatos, o conjunto atual é máximo
            if (v == -1) { // ! COMPLEXIDADE O(numVertices)
                break;
            }

            // Verifica se o vértice v é adjacente a todos os vértices no conjunto atual
            bool isIndependent = true;
            for (int j = 0; j < setSize; ++j) { //!  Complexidade: O(numVertices * setSize)
                struct Node* current = graph->adjLists[currentSet[j]]->head;
                bool found = false;
                while (current != NULL) { 
                    if (current->data == v) {  //!  Complexidade: O(numVertices * (g*setSize))  g = Grau do vertice atual
                        found = true;
                        break;
                    }
                    current = current->next;  //!  Complexidade: O((numVertices * (g*setSize)-1))
                }

                if (found) { //!  Complexidade: O(numVertices*setSize)
                    isIndependent = false;
                    break;
                }
            }

            // Se o vértice v for independente, adiciona-o ao conjunto atual
            if (isIndependent) {  //!  Complexidade: O(numVertices)
                currentSet[setSize++] = v;
            }

            // Remove o vértice v da lista de candidatos
            candidates[v] = false; //!  Complexidade: O(numVertices)
        }

        // Se o conjunto atual for maior que o conjunto máximo conhecido até agora, atualize-o
        if (setSize > *maxSize) { //!  Complexidade: O(numVertices)
            *maxSize = setSize;
            memcpy(maxSet, currentSet, sizeof(int) * setSize);
        }
    }

    return maxSet;
} /*
    ! COMPLEXIDADE TOTAL == O(graph->numVertices^2 * (grau do vertice)) == O(n²*g)
*/

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

void writeGraphToFile2(struct Graph* graph, int *ind, int indSize, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "%d\n", graph->numVertices);

    // Escreve as arestas do grafo
    for (int i = 0; i < graph->numVertices; ++i) {
        fprintf(file, "%d:", i);
        struct Node* current = graph->adjLists[i]->head;
        while (current != NULL) {
            fprintf(file, " %d", current->data);
            current = current->next;
        }
        fprintf(file, "\n");
    }

    // Escreve o conjunto independente
    fprintf(file, "%d\n", indSize);
    for (int i = 0; i < indSize; ++i) {
        fprintf(file, "%d ", ind[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

// Função para converter um conjunto independente para uma lista de cláusulas do problema 3CNF-SAT
void convertTo3CNF(int* independent_set, int num_sets, char* clauses[], int numClauses) {
    // Inicializa a string de resposta
    char resp[30] = ""; // ! COMPLEXIDADE O(1)

    // Calcula o tamanho total da string resultante
    int totalLength = 0; // ! COMPLEXIDADE O(1)
    for (int i = 0; i < numClauses; ++i) { // ! COMPLEXIDADE O(numClauses)
        totalLength += strlen(clauses[i]);
    }

    // Aloca memória para a string resultante, incluindo o caractere nulo final
    char* concatenated = (char*)malloc((totalLength + 1) * sizeof(char)); // ! COMPLEXIDADE O(1)
    if (concatenated == NULL) { // ! COMPLEXIDADE O(1)
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    // Copia cada string individual para a string resultante
    int currentIndex = 0; // ! COMPLEXIDADE O(1)
    for (int i = 0; i < numClauses; ++i) { // ! COMPLEXIDADE O(numClauses)
        strcpy(concatenated + currentIndex, clauses[i]);
        currentIndex += strlen(clauses[i]);
    }

    // Adiciona o caractere nulo final
    concatenated[currentIndex] = '\0'; // ! COMPLEXIDADE O(numClauses)
    printf("\n\n%s\n",concatenated); // ! COMPLEXIDADE O(numClauses)

    for (int i = 0; i < num_sets; i++)  // ! COMPLEXIDADE O(num_sets)
    {
        resp[i] = concatenated[independent_set[i]];
    }

    printf("\nResposta para o 3CNF-SAT: %s\n",resp);   

} //! COMPLEXIDADE TOTAL O(numClauses)+O(num_sets) == O(n)


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

    int maxSize;
    int *maxIndependentSet = exhaustiveSearch(graph, &maxSize);

    // Exibe o conjunto independente máximo
    printf("Conjunto Independente Máximo:\n");
    for (int i = 0; i < maxSize; ++i) {
        printf("%d ", maxIndependentSet[i]);
    }
    printf("\nTamanho do Conjunto Independente Máximo: %d\n", maxSize);

    // Convertendo o conjunto independente encontrado para uma lista de cláusulas 3CNF-SAT
    convertTo3CNF(maxIndependentSet, maxSize, clauses, numClauses);

    // Libera a memória alocada para o grafo e para o conjunto independente máximo
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
    free(maxIndependentSet);

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
