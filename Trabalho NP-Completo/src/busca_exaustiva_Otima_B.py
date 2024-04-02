from src.valida_instancia import C

def recursive_exhaustive_search(graph, candidates, current_set, max_set):
    """
    Realiza busca exaustiva para encontrar o maior conjunto independente em um grafo.

    Argumentos:
    graph -- O grafo representado como um dicionário de adjacência.
    candidates -- Lista de vértices candidatos.
    current_set -- Conjunto atual sendo considerado na busca.
    max_set -- Conjunto independente máximo encontrado até agora.

    Retorna:
    O conjunto independente máximo encontrado.
    """
    if len(candidates) == 0:
        if len(current_set) > len(max_set) and C(graph, current_set):
            return current_set
        else:
            return max_set

    v = candidates[0]
    new_candidates = candidates[1:]

    max_set = exhaustive_search(graph, new_candidates, current_set + [v], max_set)
    max_set = exhaustive_search(graph, new_candidates, current_set, max_set)

    return max_set

def exhaustive_search(graph):
    """
    Realiza busca exaustiva para encontrar o maior conjunto independente em um grafo.

    Argumentos:
    graph -- O grafo representado como um dicionário de adjacência.

    Retorna:
    O conjunto independente máximo encontrado.
    """
    max_set = []
    for vertex in graph.keys():
        current_set = [vertex]
        candidates = [v for v in graph.keys() if v != vertex]

        while candidates:
            v = candidates.pop()
            if all(v not in graph[u] for u in current_set):
                current_set.append(v)

        if len(current_set) > len(max_set):
            max_set = current_set

    return max_set