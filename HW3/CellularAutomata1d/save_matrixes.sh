#!/bin/sh
rm -f save_rule_outputs.out
mpicc save_rule_outputs.c -o save_rule_outputs.out
mpirun -np 2 ./save_rule_outputs.out 103 periodic 1
mpirun -np 2 ./save_rule_outputs.out 41 constant 2
mpirun -np 2 ./save_rule_outputs.out 33 constant 3
mpirun -np 2 ./save_rule_outputs.out 155 constant 4