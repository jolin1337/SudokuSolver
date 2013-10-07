#ifndef INVALIDSUDOKU_H
#define INVALIDSUDOKU_H 
#include <exception>

class InvalidSudoku : public std::exception {
public:
	const char * what() {
		return "Error: The numbers don't match any valid sudoku game, this game is corrupted =(";
	}
};

#endif