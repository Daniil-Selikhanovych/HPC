#!/bin/bash
rm -f *.log *.o
make run_core_not_parallel run_core
NUM_RUNS=3
for i in $(seq 1 $NUM_RUNS);
  do ./run_core && ./run_core_not_parallel;
done;
gnuplot gnuplot.gnu
python3 calculate_mean_std.py