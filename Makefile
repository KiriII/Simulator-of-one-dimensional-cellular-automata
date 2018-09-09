all: SimulatorOfCellularAutomata
SimulatorOfCellularAutomata: main.c
	gcc -std=c11 -pedantic -Wall -Wextra -o SimulatorOfCellularAutomata main.c
