from matplotlib import pyplot as plt
from sys import stderr


def create_graph(data):
    filename = "entropy_graph.png"
    # y_max = int(round(data[-1]/100, 0) * 100)
    graph = plt.figure(figsize=(16, 9))
    axes = graph.add_axes([0.07, 0.07, 0.9, 0.9])
    axes.plot(range(len(data)), data)

    axes.set_title("Entropia układu")
    axes.set_xlabel("Tick")
    axes.set_ylabel("Wartość entropii")
    # axes.set_yticks((range(0, y_max+1, int(y_max/50))))

    axes.set_xlim([0, len(data)*1.01])
    # axes.set_ylim([0, y_max*1.01])

    graph.savefig(filename)
    stderr.write("[INFO] Graph has been saved.\n")
    plt.close(graph)
    return data[-1]
