def convert_to_3CNF_solution(optimal_set):
    """
    Converte um conjunto independente ótimo de volta para uma resposta do problema A' (3CNF-SAT).

    Argumentos:
    optimal_set -- O conjunto independente ótimo.

    Retorna:
    Uma string representando as cláusulas na forma de cláusulas conectadas por ∧ (E lógico) e
    literais conectados por ∨ (OU lógico), com parênteses adicionados conforme necessário.
    """
    clauses = []
    for vertex in optimal_set:
        clause = []
        for neighbor in optimal_set:
            if neighbor != vertex:
                if neighbor.startswith("¬") and vertex == neighbor[1:]:
                    clause.append(neighbor[1:])  # Eliminação da dupla negação
                else:
                    clause.append("¬" + neighbor)
        clause.append(vertex)
        clauses.append("(" + " v ".join(clause) + ")")
    return " ∧ ".join(clauses)


def h(S):

    return convert_to_3CNF_solution(S)