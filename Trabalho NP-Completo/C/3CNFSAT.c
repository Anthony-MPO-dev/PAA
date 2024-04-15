#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CLAUSES 100
#define MAX_LITERALS 3

void parseInstance(char* instanceStr, char* clauses[], int* numClauses) {
    char* token;
    char* clauseStrs[MAX_CLAUSES]; // Array para armazenar as strings de cláusulas
    int clauseIndex = 0;

    // Divide a string da instância em strings de cláusulas
    token = strtok(instanceStr, "∧");
    while (token != NULL) {
        // Remove os espaços em branco à esquerda
        while (*token == ' ') {
            token++;
        }

        // Remove os espaços em branco à direita
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') {
            *end = '\0';
            end--;
        }

        // Remove o caractere 'v' entre os vértices
        char* vertex = token;
        char* cleanToken = token; // Token limpo sem 'v' e parênteses
        while (*vertex != '\0') {
            if (*vertex == 'v' || *vertex == '(' || *vertex == ')' || *vertex == ' ') {
                vertex++;
            } else {
                *cleanToken = *vertex;
                cleanToken++;
                vertex++;
            }
        }
        *cleanToken = '\0'; // Finaliza a string limpa

        // Copia a cláusula limpa para o array de cláusulas
        clauseStrs[clauseIndex] = token;
        clauseIndex++;
        token = strtok(NULL, "∧");
    }
    *numClauses = clauseIndex;

    // Para cada string de cláusula, copia-a para o array de cláusulas
    for (int i = 0; i < *numClauses; i++) {
        clauses[i] = strdup(clauseStrs[i]);
    }
}

// Função para verificar se uma solução satisfaz as cláusulas
bool testSolution(char* clauses[], int numClauses, bool solution[]) {
    // Para cada cláusula
    for (int i = 0; i < numClauses; i++) {
        bool clauseSatisfied = false;
        // Para cada literal na cláusula
        char* token = clauses[i];
        while (*token != '\0') { // Alteração feita aqui
            char literal = *token;
            bool isNegated = (literal >= 'a' && literal <= 'z'); // Verifica se é negado
            char variable = (isNegated) ? (literal - ('a' - 'A')) : literal; // Pega a variável
            // Se o literal estiver negado, inverte o valor da variável
            bool value = (isNegated) ? !solution[variable - 'A'] : solution[variable - 'A'];
            
            // Verifica se o valor da variável satisfaz a cláusula
            if (value) {
                clauseSatisfied = true;
                break;
            }
            token++;
        }
        // Se nenhuma das variáveis na cláusula for satisfeita, retorne falso
        if (!clauseSatisfied) {
            return false;
        }
    }
    // Se todas as cláusulas forem satisfeitas, retorne verdadeiro
    return true;
}

int main() {
    int numClauses;
    char instanceStr[] = "(A v B v c) ∧ (a v B v C)";
    char* clauses[MAX_CLAUSES];

    // Parse da instância
    parseInstance(instanceStr, clauses, &numClauses);

    // Atribuição de valores às variáveis (true = 1, false = 0)
    bool solution[26] = {0, 0, 0}; // A=false, B=false, C=false

    // Testa a solução
    if (testSolution(clauses, numClauses, solution)) {
        printf("A solução é válida para as cláusulas fornecidas.\n");
    } else {
        printf("A solução não é válida para as cláusulas fornecidas.\n");
    }

    // Liberar memória alocada para as cláusulas
    for (int i = 0; i < numClauses; i++) {
        free(clauses[i]);
    }

    return 0;
}
