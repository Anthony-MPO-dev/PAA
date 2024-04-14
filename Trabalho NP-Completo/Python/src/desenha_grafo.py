import matplotlib
matplotlib.use('Agg')  # Use the 'Agg' backend, que não requer exibição
import networkx as nx
import matplotlib.pyplot as plt
from datetime import datetime

def draw_graph(graph, independent_set, layout='circular'):
    """
    Desenha o grafo usando NetworkX com o layout especificado.
    
    Argumentos:
    graph -- Um dicionário representando o grafo.
    independent_set -- Lista de vértices no conjunto independente para destacar.
    layout -- O layout de disposição dos vértices. Pode ser 'circular', 'shell', 'spring', ou 'spectral'.
    """
    # Nome do arquivo para salvar o gráfico
    data = str(datetime.now()).replace(" ", "_").replace(":", "-")
    filename = f'GRAFO_{data}.png'

    # Limpa a figura antes de desenhar o próximo gráfico
    plt.clf()

    # Cria o objeto Graph
    G = nx.Graph(graph)

    # Escolhe o layout com base na opção fornecida
    if layout == 'circular':
        pos = nx.circular_layout(G)
    elif layout == 'shell':
        pos = nx.shell_layout(G)
    elif layout == 'spring':
        pos = nx.spring_layout(G)
    elif layout == 'spectral':
        pos = nx.spectral_layout(G)
    else:
        pos = nx.spring_layout(G)  # Padrão se o layout especificado não for reconhecido

    # Desenha os vértices
    nx.draw_networkx_nodes(G, pos, node_size=700)
    # Desenha as arestas
    nx.draw_networkx_edges(G, pos)
    # Desenha as etiquetas dos vértices
    nx.draw_networkx_labels(G, pos)

    # Destaca o conjunto independente em vermelho
    nx.draw_networkx_nodes(G, pos, nodelist=independent_set, node_color='r', node_size=700)

    # Adiciona o título do gráfico
    plt.title('Grafo com conjunto independente destacado')
    # Remove os eixos
    plt.axis('off')

    # Salva o gráfico como uma imagem
    plt.savefig(filename)

    # Exibe a mensagem indicando onde o gráfico foi salvo
    print(f'Gráfico gerado em: {filename}')