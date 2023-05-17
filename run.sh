#!/usr/bin/env bash
mpic++ 5_MPI.cpp -o 5_MPI.out
mpirun --allow-run-as-root  --oversubscribe -np 4 /home/paul/CLionProjects/OMP/5_MPI.out