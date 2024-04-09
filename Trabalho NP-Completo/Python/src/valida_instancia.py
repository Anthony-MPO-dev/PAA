def is_independent_set(graph, vertices):
    """
    Verifica se um conjunto de vértices é um conjunto independente em um grafo.

    Argumentos:
    graph -- O grafo representado como um dicionário de adjacência.
    vertices -- O conjunto de vértices a ser verificado.

    Retorna:
    True se o conjunto de vértices é um conjunto independente, False caso contrário.
    """
    for u in vertices:
        for v in vertices:
            if u != v and v in graph[u]:
                return False
    return True



def C(I,S):
    graph = I

    independent_set = S

    result = is_independent_set(graph, independent_set)

    return result