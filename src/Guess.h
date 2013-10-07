#ifndef GUESS_H
#define GUESS_H 

#include "BasicSudokuSolver/sudoku/Sudoku.h"

class Guess {
public:
	explicit Guess(char val='0', int pos=-1, Sudoku state=Sudoku());
	char value();
	void value(char val);

	int position();
	void position(int pos);

	Sudoku &sudokuState();
	// void sudokuState(Sudoku state);
	bool operator ==(const Guess &g);
private:
	char val;
	int pos;
	// Sudoku stateAtGuess;
};

#endif