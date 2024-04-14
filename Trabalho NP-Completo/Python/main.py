from src.valida_grafo import is_valid_graph
from src.valida_instancia import C
from src.trata_clausulas_A import parse_3CNF_instance
from src.trata_A_para_B import reduce_3CNF_to_Independent_Set
from src.trata_B_para_A import h
from src.busca_exaustiva_Otima_B import exhaustive_search
import os

# Problema A' = 3CNF-SAT
# Problema B' = Independent set

def Primeiro():
    from src.desenha_grafo import draw_graph
    
    # instancia I de B' ou grafo
    I = {
        'A': ['B', 'C'],
        'B': ['A', 'C', 'D'],
        'C': ['A', 'B', 'D', 'K'],
        'K': ['C'],
        'D': ['B', 'C']
    }

    S = ['A', 'D', 'K'] # é uma solução para a instância I

    valid = is_valid_graph(I)

    if valid == None:

        result = C(I,S)
        
        
        print(f' Resultado proposto é: {result}') 
        
        # Saída: True 
        if result:
            
            draw_graph(I, S)
            


    else:
        os.remove('grafo.png')
        print(f'Instancia I invalida {valid}')

def Segundo():
    from src.desenha_grafo import draw_graph
    # Transforma A' em B'

    def f(I):
        
        clauses = parse_3CNF_instance(I)
        print(clauses)

        grafo = reduce_3CNF_to_Independent_Set(clauses)
        print(grafo)

        #vertices = list(grafo.keys())
        #S = recursive_exhaustive_search(grafo, vertices, [], [])

        S = exhaustive_search(grafo)

        return grafo, S



    I = "(-x v y v -z) ∧ (x v -y v z) ∧ (x v y v z) ∧ (-x v -y)"

    grafo, S = f(I)

    valid = is_valid_graph(grafo)

    if valid == None:

        result = C(grafo, S)

        
        
        print(f'Resultado Otimo Proposto{S}')
        print(f' Resultado proposto é: {result}') 
        
        # Saída: True 
        if result:
            s_A = h(S)
            print(f"Resultao Convertido para A': {s_A}")
            
            draw_graph(grafo, S)

    # Recebe Instancia B'(grafo) agora e procura uma Solução otima por meio de um algoritmo deterministico
    
    

def main(): 

    Primeiro()
    Segundo()

if __name__ == "__main__":
    main()