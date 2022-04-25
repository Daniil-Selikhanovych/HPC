#!/bin/sh
rm -f ping_pong_v1.out ping_pong_v1_res.txt
mpicc ping_pong_v1.c -o ping_pong_v1.out
name="process"
mpirun -np 3 ./ping_pong_v1.out $name >> ping_pong_v1_res.txt
