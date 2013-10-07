#ifndef ROW_H
#define ROW_H 
#include "PuzzleStructs.h"
#include "Square.h"

class Row {
public:
	Row();

	bool operator <(const Row &rhs) const;
	Square *&operator [](int i);
	const Square *operator [](int i) const;
	unsigned int nonEmptyCount() const;
	void increaseNonEmptyCount();
	bool hasNumber(int num) const;
	Square *getSinglePointer(int i);
private:
	unsigned int count;
	Square *data[SUDOKU_SIZE];
};

#endif