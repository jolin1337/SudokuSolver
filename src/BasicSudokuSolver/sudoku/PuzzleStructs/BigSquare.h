#ifndef BIGSQUARE_H
#define BIGSQUARE_H

#include "PuzzleStructs.h"
#include "Square.h"

class BigSquare {
public:
	BigSquare();

	bool operator <(const BigSquare &rhs) const;
	Square **operator [](int i);
	// const Square * const* operator [](int i) const;
	unsigned int nonEmptyCount() const;
	void increaseNonEmptyCount();
	bool hasNumber(int num) const;
	Square *getSinglePointer(int i);
private:
	Square *data[SUDOKU_MINI_SIZE][SUDOKU_MINI_SIZE];
	unsigned int count;
};

#endif