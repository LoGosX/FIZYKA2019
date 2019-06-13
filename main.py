import subprocess
from src import graph
from sys import argv

def execute(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield float(stdout_line.strip()) 
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)


if __name__ == "__main__":
    if "-c" in argv:
        argv.remove('-c')
        subprocess.Popen("cmake ..", cwd="./build").wait()
        subprocess.Popen("cmake --build . --config Release", cwd="./build").wait()
    if len(argv) >= 3:
        width = argv[1]
        height = argv[2]
    else:
        width = 800
        height = 800

    entropy_vals = list()
    delay = 5
    max_entropy = 0
    for entropy in execute(f'build/FIZYKA2019 {width} {height}'):
        if entropy > max_entropy:
            max_entropy = entropy
        entropy_vals.append(entropy)

        if not (len(entropy_vals) % delay):
            graph.create_graph(entropy_vals, max_entropy)

    print(f'Final state:\n\tentropy value: {entropy_vals[-1]}\n\tafter {len(entropy_vals)} ticks')
    graph.create_graph(entropy_vals, max_entropy)
