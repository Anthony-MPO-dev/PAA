#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    int numClauses;
    char instanceStr[] = "(A v B v Z) ∧ (X v Y v C) ∧ (A v Y v C)";
    char* clauses[MAX_CLAUSES];

    parseInstance(instanceStr, clauses, &numClauses);

    printf("Claúsulas separadas:\n");
    for (int i = 0; i < numClauses; i++) {
        printf("Cláusula %d: %s\n", i + 1, clauses[i]);
    }

    return 0;
}
