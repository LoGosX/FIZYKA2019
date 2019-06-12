from matplotlib import pyplot as plt


def create_graph(data, max_val):
    filename = "entropy_graph.png"
    graph = plt.figure(figsize=(16, 9))
    axes = graph.add_axes([0.07, 0.07, 0.9, 0.9])
    axes.plot(range(len(data)), data)

    axes.set_title("Entropia układu")
    axes.set_xlabel("tick")
    axes.set_ylabel("wartość entropii")

    axes.set_xlim([0, len(data)*1.01])
    axes.set_ylim([0, max_val*1.01])

    graph.savefig(filename)
    plt.close(graph)
    return data[-1]
