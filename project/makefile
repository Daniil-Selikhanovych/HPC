CC = g++
CP = -c -O3 -Wall -Werror -Wextra
LIBS = -lsfml-window -lsfml-audio -lsfml-system -lsfml-graphics -lpthread

core_not_parallel.o: core_not_parallel.cpp particle.hpp box.hpp plotter.hpp periodic_box.hpp
	$(CC) $(CP) -fopenmp core_not_parallel.cpp -o core_not_parallel.o

run_core_not_parallel: core_not_parallel.o
	$(CC) core_not_parallel.o -fopenmp $(LIBS) -o run_core_not_parallel

core.o: core.cpp particle.hpp box.hpp plotter.hpp periodic_box.hpp
	$(CC) $(CP) -fopenmp core.cpp -o core.o

run_core: core.o
	$(CC) core.o -fopenmp $(LIBS) -o run_core







