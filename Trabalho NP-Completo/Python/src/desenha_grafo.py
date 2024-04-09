import matplotlib
matplotlib.use('Agg')  # Use the 'Agg' backend which doesn't require a display
import networkx as nx
import matplotlib.pyplot as plt
from datetime import datetime

def draw_graph(graph, independent_set):

    data = str(datetime.now()).replace(" ", "_").replace(":", "-")

    filename = 'GRAFO_'+data+'.png'

    # Limpa a figura antes de desenhar o próximo gráfico
    plt.clf()

    G = nx.Graph(graph)
    pos = nx.spring_layout(G)
    
    nx.draw_networkx_nodes(G, pos, node_size=700)
    nx.draw_networkx_labels(G, pos)
    nx.draw_networkx_edges(G, pos)
    
    nx.draw_networkx_nodes(G, pos, nodelist=independent_set, node_color='r', node_size=700)
    
    print(f'Grafico Gerado em: {filename}')

    plt.title('Grafo com conjunto independente destacado')
    plt.axis('off')
    plt.savefig(filename)