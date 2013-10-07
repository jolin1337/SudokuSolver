#include <iostream>
#include "SudokuSolutions.h"
#include "BasicSudokuSolver/StatusAlerts.h"


int main(int argc, char const *argv[]) {
	SudokuBoard *activeBoard;
	Sudoku sudokuPuzzle;
	if(argc > 1) {
		if(sudokuPuzzle.init(argv[1]) != 0)
			return noSudokuFile(argv[1]);
	}
	else if(sudokuPuzzle.init("sudokus/1sudoku.txt") != 0)
		return noSudokuFile("sudokus/1sudoku.txt");
	activeBoard = &sudokuPuzzle;
	SudokuSolutions solutions(activeBoard);
	printSudoku(&solutions);
	if(solutions.solve()){
		while(solutions.nextSolution())
			printSudoku(&solutions);
	}
	// std::cout << solutions.currentSolutionSize() << "\n";
	// std::cout << "Solutions:" << "\n";
	// int s = 1;
	// while(sud.nextSolution()){
	// 	std::cout << "Solution: " << s << "\n";
	// 	printSudoku(sud);
	// 	s++;
	// }
	// if(!sud.solve())
	// 	std::cout << "Could not be solved =(\n";
	// else{
	// 	std::cout << "           ||\n";
	// 	std::cout << "           \\/  \n";
	// 	printSudoku(sud);
	// }
	return 0;
}