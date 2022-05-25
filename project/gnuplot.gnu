f(x) = a
g(x) = b
fit f(x) '<python3 split.py' using 1:2 via a
fit g(x) '<python3 split.py' using 1:3 via b

set terminal png size 1200, 600
set output 'plot.png'
set xlabel 'step'
set ylabel 'energy'
set title sprintf("potential energy = %f, kinetic energy = %f", a, b)

plot 'core_logs.log' using 1:2 title 'potential' with lines, \
	'core_logs.log' using 1:3 title 'kinetic' with lines, \
	'core_logs.log' using 1:4 title 'full energy' with lines lw 2, \
	f(x) title 'approximation of potential energy' lw 2, \
	g(x) title 'approximation of kinetic energy' lw 2
