#!/bin/sh
rm -f ping_pong_v2.out ping_pong_v2_res.txt
mpicc ping_pong_v2.c -o ping_pong_v2.out
name="pr"
for ((i=0; i <= 15; i++))
do
    echo $i
    mpirun -np 4 ./ping_pong_v2.out $name >> ping_pong_v2_res.txt
    name=$name$name

done