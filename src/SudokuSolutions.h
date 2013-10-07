#ifndef SUDOKUEXTEND_H
#define SUDOKUEXTEND_H

#include "BasicSudokuSolver/sudoku/Sudoku.h"
#include "BasicSudokuSolver/sudoku/SudokuBoard.h"

#include "Guess.h"
#include <string>
#include <vector>

class SudokuSolutions : public SudokuBoard {
public:
	SudokuSolutions(std::string filename="");
	SudokuSolutions(const SudokuBoard *val);
	// SudokuSolutions(const SudokuSolutions &assign);
	SudokuSolutions &operator=(const SudokuBoard *rhs);
	bool operator==(const SudokuSolutions &rhs);
	~SudokuSolutions();

	unsigned int currentSolutionSize() const;
	bool solve();
	bool nextSolution();
	
	bool isSolved() const;
	const char &getEmptySquare() const;
	bool validCharacter(char v) const;

protected:
	bool guess(int position=0, int startValue=1);

	std::vector<Guess> guesses;
	std::vector<Sudoku> solutions;
};

#endif