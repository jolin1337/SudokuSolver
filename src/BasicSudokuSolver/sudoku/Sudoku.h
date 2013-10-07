#ifndef SUDOKU_H
#define SUDOKU_H

#include "PuzzleStructs/Square.h"
#include "PuzzleStructs/BigSquare.h"
#include "PuzzleStructs/Row.h"
#include "SudokuBoard.h"

#include <string>
#include <fstream>

class Sudoku : public SudokuBoard{
public:
	Sudoku(std::string filename="");
	Sudoku(const SudokuBoard *val);
	Sudoku &operator=(const SudokuBoard *rhs);
	bool operator ==(const Sudoku &rhs);

	/**
	 * This is the call to make me solve the sudoku puzzle
	 * This method can't be called if not init has been 
	 * called before
	 * @return true if i was able to solve the puzzle false 
	 * otherwise
	 */
	virtual bool solve();
	bool isSolved() const;
	/**
	 * This method are equality to show me the sudoku puzzle
	 * so that I can memorize it
	 * @param  filename the name of the file where the sudoku
	 *                  are placed
	 * @return          error codes if something goes wrong
	 */
	int init(std::string filename);
	virtual int init(std::ifstream &filestream);

	char operator[](int i) const;
	virtual bool validCharacter(char v) const;

private:
	bool fillInBigSquares();
	bool fillInRows();
	bool fillInColumns();
};

#endif