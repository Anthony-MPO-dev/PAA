def reduce_3CNF_to_Independent_Set(clauses):
    """
    Reduz uma instância do problema 3CNF-SAT para uma instância do problema Independent Set.

    Argumentos:
    clauses -- Lista de cláusulas na forma de listas de literais.

    Retorna:
    Um grafo representado como um dicionário de adjacência, que é uma instância do problema Independent Set.
    """
    # Inicialize o grafo como um dicionário de adjacência
    graph = {}
    
    # Função para obter o literal oposto
    def get_opposite(literal):
        if literal.startswith('-'):
            return literal[1:]  # Remover o sinal de negação
        else:
            return '-' + literal  # Adicionar o sinal de negação
    
    # Inicializar o contador para diferenciar literais iguais em cláusulas diferentes
    counter = 0
    
    # Iterar sobre cada cláusula
    for clause in clauses:
        # Criar um triângulo para cada cláusula
        vertices = []
        for literal in clause:
            # Criar um nome de vértice com um sufixo baseado no contador para diferenciar literais iguais em cláusulas diferentes
            vertex = literal + str(counter)
            vertices.append(vertex)
            
            # Adicionar o vértice ao grafo, se ainda não estiver presente
            if vertex not in graph:
                graph[vertex] = []
        
        # Adicionar as arestas para formar o triângulo
        for i in range(len(vertices)):
            for j in range(i + 1, len(vertices)):
                v1, v2 = vertices[i], vertices[j]
                if v2 not in graph[v1]:
                    graph[v1].append(v2)
                if v1 not in graph[v2]:
                    graph[v2].append(v1)
        
        # Incrementar o contador para diferenciar os vértices
        counter += 1
    
    # Adicionar arestas entre vértices opostos de diferentes cláusulas
    for clause1 in clauses:
        for clause2 in clauses:
            if clause1 != clause2:
                for literal1 in clause1:
                    opposite1 = get_opposite(literal1)
                    for literal2 in clause2:
                        opposite2 = get_opposite(literal2)
                        # Verificar se os literais são opostos
                        if literal1 == opposite2 or literal2 == opposite1:
                            # Obter os vértices correspondentes
                            v1 = literal1 + str(clauses.index(clause1))
                            v2 = literal2 + str(clauses.index(clause2))
                            # Adicionar arestas entre os vértices opostos
                            if v1 not in graph[v2]:
                                graph[v2].append(v1)
                            if v2 not in graph[v1]:
                                graph[v1].append(v2)
    
    return graph