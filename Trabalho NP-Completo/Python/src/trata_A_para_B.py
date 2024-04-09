def reduce_3CNF_to_Independent_Set(clauses):
    """
    Reduz uma instância do problema 3CNF-SAT para uma instância do problema Independent Set.

    Argumentos:
    clauses -- Lista de cláusulas na forma de listas de literais.

    Retorna:
    Um grafo representado como um dicionário de adjacência, que é uma instância do problema Independent Set.
    

    Funcionamento: 

        Inicialização do Grafo:

        Exemplo : [['A', 'B', '¬C'], ['¬A', '¬B', 'C'], ['A', '¬B', 'C']]

        Inicializamos um dicionário vazio para representar o grafo.
        Iteração sobre as Cláusulas:

        Iteramos sobre cada cláusula na lista de cláusulas.
        Iteração sobre os Literais:

        Para cada literal em cada cláusula, verificamos se ele já está presente como uma chave no grafo.
        Para a primeira cláusula ['A', 'B', '¬C']:

        'A', 'B' e '¬C' não estão presentes no grafo, então adicionamos esses literais como chaves e listas vazias como seus valores.
        Para a segunda cláusula ['¬A', '¬B', 'C']:

        '¬A', '¬B' e 'C' não estão presentes no grafo, então adicionamos esses literais como chaves e listas vazias como seus valores.
        Para a terceira cláusula ['A', '¬B', 'C']:

        'A', '¬B' e 'C' já estão presentes no grafo, então não fazemos nada.
        Conexões entre Vértices:

        Para cada par de literais diferentes na mesma cláusula, verificamos se há uma conexão entre os vértices correspondentes no grafo.
        Para a primeira cláusula ['A', 'B', '¬C']:

        Adicionamos conexões entre 'A' e 'B', 'A' e '¬C', e 'B' e '¬C' no grafo.
        Para a segunda cláusula ['¬A', '¬B', 'C']:

        Adicionamos conexões entre '¬A' e '¬B', '¬A' e 'C', e '¬B' e 'C' no grafo.
        Para a terceira cláusula ['A', '¬B', 'C']:

        Adicionamos conexões entre 'A' e '¬B', 'A' e 'C', e '¬B' e 'C' no grafo.
        Resultado do Grafo:

        O grafo resultante é {'A': ['B', '¬C', '¬B', 'C'], 'B': ['A', '¬C', '¬A', 'C'], '¬C': ['A', 'B', '¬A', '¬B'], '¬A': ['¬B', 'C'], '¬B': ['¬A', 'C'], 'C': ['¬A', '¬B', 'A', 'B']}. Cada literal na cláusula se tornou um vértice no grafo, e as conexões entre os literais na cláusula se tornaram arestas no grafo.
            
    
    """
    graph = {}

    for clause in clauses:
        for literal in clause:
            if literal not in graph:
                graph[literal] = []

            for other_literal in clause:
                if literal != other_literal:
                    if other_literal not in graph[literal]:
                        graph[literal].append(other_literal)

    return graph