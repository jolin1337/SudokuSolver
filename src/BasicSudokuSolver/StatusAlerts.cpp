#include "StatusAlerts.h"
#include <iostream>


void printSudoku(const SudokuBoard *sud) {
	if(!sud->hasMemory()) return;
	// for (int i = 0; i < SUDOKU_SIZE*SUDOKU_SIZE; i++)
	// 	std::cout << (*sud)[i];
	// std::cout << "\n";
	// return;
	std::cout << "-------------------------\n";
	for (int i = 0; i < SUDOKU_SIZE; i++){
		std::cout << "| ";
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			std::cout << (*sud)[i*SUDOKU_SIZE + j] << " ";
			if(j%SUDOKU_MINI_SIZE == 2)
				std::cout << "| ";
		}
		std::cout << "\n";
		if(i%SUDOKU_MINI_SIZE == 2)
			std::cout << "-------------------------\n";
	}
}

int noSudokuFile(std::string filename) {
	std::cout << "Could not open/parse file, " << filename << ", as a sudoku file!\n";
	return 1;
}