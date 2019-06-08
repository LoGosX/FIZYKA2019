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
    for entropy in execute('build/FIZYKA2019'):
        entropy_vals.append(entropy)

        if not (len(entropy_vals) % delay):
            graph.create_graph(entropy_vals)
