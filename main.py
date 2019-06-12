import subprocess
from src import graph


def execute(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield float(stdout_line.strip()) 
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)


if __name__ == "__main__":
    entropy_vals = list()
    delay = 5
    max_entropy = 0
    for entropy in execute('build/FIZYKA2019'):
        if entropy > max_entropy:
            max_entropy = entropy
        entropy_vals.append(entropy)

        if not (len(entropy_vals) % delay):
            graph.create_graph(entropy_vals, max_entropy)

    print(f'Final state:\n\tentropy value: {entropy_vals[-1]}\n\tafter {len(entropy_vals)} ticks')
    graph.create_graph(entropy_vals, max_entropy)
