# Descrição dos Algoritmos

Este repositório contém implementações de algoritmos relacionados aos problemas A' (3CNF-SAT) e B' (Independent Set), conforme definido no enunciado fornecido.

## Problema A' = 3CNF-SAT

O problema A' consiste em determinar se uma fórmula lógica está na forma normal conjuntiva de 3 literais (3CNF) é satisfatível.

### Algoritmos Implementados:

1. **Validação de Instância**: Implementação da função `C(I, S)` que verifica se uma solução proposta `S` é válida para uma instância `I` do problema B'.

2. **Tratamento de Instância do Problema A'**: Implementação da função `parse_3CNF_instance(I)` que recebe uma instância do problema A' e a converte para uma lista de cláusulas.

3. **Transformação de A' para B'**: Implementação da função `reduce_3CNF_to_Independent_Set(clauses)` que reduz uma instância do problema A' para uma instância do problema B' (Independent Set) por meio de um grafo.

## Problema B' = Independent Set

O problema B' consiste em encontrar o maior conjunto de vértices independentes em um grafo.

### Algoritmos Implementados:

1. **Transformação de B' para A'**: Implementação da função `h(S)` que recebe uma solução ótima `S` do problema B' e a converte para uma resposta do problema A' (3CNF-SAT).

2. **Busca Exaustiva para Solução Ótima em B'**: Implementação de um algoritmo de busca exaustiva que encontra uma solução ótima para o problema B' (Independent Set) em um grafo.

## Execução do Código

O arquivo `main.py` contém a função principal `main()` que demonstra como usar os algoritmos implementados para resolver instâncias dos problemas A' e B'. É possível alternar entre as chamadas dos métodos `Primeiro()` e `Segundo()` para testar os algoritmos.
