#!/usr/bin/python
import subprocess
import sys

argv = sys.argv[1:]
CLUSTER_NUM = 7

for i in range(CLUSTER_NUM):
    test_params = [argv[j] for j in range(i, len(argv), CLUSTER_NUM)]
    ssh_command = "\'"
    for param in test_params:
        ssh_command += "./main.o {};".format(param)
    ssh_command += "\'"
    bash_command = """ssh kim@node{}-bigdata << EOF
cd xresearch                  
screen -d -m bash -c {}
logout
EOF""".format(i+10, ssh_command)
    p = subprocess.Popen(bash_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
