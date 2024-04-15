import matplotlib.pyplot as plt
import networkx as nx

def read_graph(filename):
    with open(filename, 'r') as file:
        num_vertices = int(file.readline().strip())
        adjacency_list = {}

        for _ in range(num_vertices):
            line = file.readline().strip().split()
            vertex = int(line[0].rstrip(':'))
            neighbors = [int(n) for n in line[1:]]
            adjacency_list[vertex] = neighbors

        independent_set = []

        # Ignoramos a linha que indica o início do conjunto independente
        file.readline()

        # Agora, lemos todos os conjuntos independentes do arquivo
        for line in file:
            if line.strip() == "":  # Verifica se alcançamos o final do arquivo
                break
            vertices = [int(n) for n in line.strip().split()]
            independent_set.append(vertices)

        # print(independent_set)

    return adjacency_list, independent_set


def draw_graph(adjacency_list, independent_set):
    G = nx.Graph()
    for vertex, neighbors in adjacency_list.items():
        G.add_node(vertex)
        for neighbor in neighbors:
            G.add_edge(vertex, neighbor)
    pos = nx.circular_layout(G)
    
    # Combina todos os vértices presentes em todos os conjuntos independentes
    all_independent_vertices = [v for vertices in independent_set for v in vertices]
    
    # Desenha os vértices
    nx.draw_networkx_nodes(G, pos, node_size=700)
    # Desenha as arestas
    nx.draw_networkx_edges(G, pos)
    # Desenha as etiquetas dos vértices
    nx.draw_networkx_labels(G, pos)

    # Destaca o conjunto independente em vermelho
    nx.draw_networkx_nodes(G, pos, nodelist=all_independent_vertices, node_color='r', node_size=700)

    plt.title('Grafo')
    plt.axis('off')
    plt.show()


if __name__ == "__main__":
    adjacency_list, independent_set = read_graph("grafo.txt")
    draw_graph(adjacency_list, independent_set)
