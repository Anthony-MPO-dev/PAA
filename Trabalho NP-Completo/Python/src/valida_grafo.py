def is_valid_graph(graph):
    """
    Verifica se o dicionário fornecido representa um grafo válido.

    Argumentos:
    graph -- O grafo representado como um dicionário de adjacência.

    Retorna:
    Uma string indicando o motivo da invalidade se o dicionário não representa um grafo válido,
    ou None se o grafo for válido.
    """
    if not isinstance(graph, dict):
        return "O argumento fornecido não é um dicionário."

    for vertex, neighbors in graph.items():
        if not isinstance(neighbors, list):
            return f"Os vizinhos de '{vertex}' não são representados como uma lista."
        for neighbor in neighbors:
            if neighbor not in graph:
                return f"O vértice '{neighbor}' em 'graph['{vertex}']' não está presente como um vértice válido."