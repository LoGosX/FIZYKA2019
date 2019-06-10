#taken from https://stackoverflow.com/a/4417735

import subprocess

def execute(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield float(stdout_line.strip()) 
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)

for entropia in execute('build/FIZYKA2019'):
    #ta pętla będzie się wykonywała tak długo jak działa program FIZYKA2019. Jeśli nie będzie żadnego out'a to ta pętla będzie na niego czekać
    print("Entropia:", entropia)