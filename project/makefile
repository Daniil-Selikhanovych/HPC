CC = g++
CP = -c -O3 -Wall -Werror -Wextra
LIBS = -lsfml-window -lsfml-audio -lsfml-system -lsfml-graphics -lpthread

core.o: core.cpp particle.hpp box.hpp plotter.hpp periodic_box.hpp
	$(CC) $(CP) -fopenmp core.cpp -o core.o

all: core.o
	$(CC) core.o -fopenmp $(LIBS) -o run_core






