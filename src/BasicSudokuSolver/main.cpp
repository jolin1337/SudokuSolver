#include "sudoku/Sudoku.h"
#include <iostream>
#include "StatusAlerts.h"


int main(int argc, char const *argv[]) {
	Sudoku sud;
	if(argc > 1) {
		if(sud.init(argv[1]) != 0)
			return noSudokuFile(argv[1]);
	}
	else if(sud.init("sudokus/1sudoku.txt") != 0)
		return noSudokuFile("sudokus/1sudoku.txt");

	printSudoku(&sud);
	if(!sud.solve())
		std::cout << "Could not be solved =(\n";
	else{
		std::cout << "           ||\n";
		std::cout << "           \\/  \n";
		printSudoku(&sud);
	}
	return 0;
}