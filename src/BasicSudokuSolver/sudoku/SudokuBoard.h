#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H 

class SudokuBoard {
public:
	SudokuBoard(char emptySquare='_'):emptySquare(emptySquare), memStored(false){}
	virtual bool solve() = 0;
	virtual bool isSolved() const = 0;
	const char &getEmptySquare() const {
		return emptySquare;
	}
	virtual bool validCharacter(char v) const = 0;
	virtual char operator[](int i) const {
		return data[i];
	}
	bool hasMemory() const{
		return memStored;
	}
protected:

	char emptySquare;
	Square data[SUDOKU_SIZE*SUDOKU_SIZE];	// this is yust an array of squares representing a grid
											// the data array oreder it's members row-wise. eg 
											// elements 0 to 9 are first row. element 9 to 18 are 
											// secound row and so on...
// private:
	bool memStored;
						
	BigSquare squares[SUDOKU_SIZE];	// a set of boxes ordered 3*3 to fill the grid of 9*9
	Row rows[SUDOKU_SIZE];			// a set of rows to fill the grid 9*9
	Row columns[SUDOKU_SIZE];		// a set of columns to fill the grid 9*9
};

#endif