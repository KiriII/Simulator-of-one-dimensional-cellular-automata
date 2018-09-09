all: SimulatorOfCellularAutomata
SimulatorOfCellularAutomata: main.o
	gcc -std=c11 -pedantic -Wall -Wextra -o SimulatorOfCellularAutomata main.o

main.o: main.c 
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

clean: main.o