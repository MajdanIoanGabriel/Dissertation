# Dissertation

## Introduction

Inter-process communication (IPC) plays a vital role in enabling efficient data exchange and collaboration between processes in modern computing systems. This project presents a comparative analysis of five popular IPC mechanisms: socket, shared memory, pipe, message queue, and file-based IPC. The behavior of each IPC mechanism is evaluated based on latency and throughput measurements across various message sizes.

## Dependencies

You need the following packages in order to run the notebook:
```bash
sudo apt install git cmake python3 g++ nlohmann-json3-dev
```

To open the notebook I used Visual Studio Code. To install, follow the instructions from https://code.visualstudio.com/docs/setup/linux.
Don't use the snap version, because the script won't be able to run commands in terminal.

You need the following extensions: Python, Jupyter

Create a python environment, then install the needed libraries:
```bash
pip install matplotlib numpy
```

In terminal, run this to configure cmake:
```bash
cmake -S . -B build
```

In order for the message queue server to work, you need to increase the max message size to 1MB.
Open /etc/sysctl.conf and add the following lines:
```
kernel.msgmax = 1048576 
kernel.msgmnb = 1048576
```

Then run this in a terminal to reload the file:
```bash
sudo sysctl -p
```

After this, you can start running the cells from the notebook. Remember to let the terminals close before running the next cell.

Open run.ipynb to see the results of the study.
