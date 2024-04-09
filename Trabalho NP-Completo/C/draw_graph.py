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
    return adjacency_list


def draw_graph(adjacency_list):
    G = nx.Graph()
    for vertex, neighbors in adjacency_list.items():
        G.add_node(vertex)
        for neighbor in neighbors:
            G.add_edge(vertex, neighbor)
    nx.draw(G, with_labels=True, node_size=700)
    plt.title('Grafo')
    plt.axis('off')
    plt.show()

if __name__ == "__main__":
    adjacency_list = read_graph("graph.txt")
    draw_graph(adjacency_list)
