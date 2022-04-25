#!/bin/sh
rm -f cellular_automata_1d_mpi.out
mpicc cellular_automata_1d_mpi.c -o cellular_automata_1d_mpi.out
N=10
m=8
n=8
prefix="cellular_automata_1d_mpi_res_"

for ((i=1; i<m; i++))
do
    echo "i="$i", N="$N
    for ((j=1; j<n; j++))
    do
        echo "j="$j
        mpirun -np $j ./cellular_automata_1d_mpi.out 100 $N >> $prefix$i
    done
    N=$((10*N))
done