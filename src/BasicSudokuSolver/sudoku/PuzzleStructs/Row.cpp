#include "Row.h"

Row::Row():count(0) {}

bool Row::operator <(const Row &rhs) const {
	return nonEmptyCount() < rhs.nonEmptyCount();
}
Square *&Row::operator [](int i){
	return data[i];
}
const Square *Row::operator [](int i) const {
	return data[i];
}
unsigned int Row::nonEmptyCount() const {
	return count;
}
void Row::increaseNonEmptyCount() {
	count++;
}
bool Row::hasNumber(int num) const {
	for(int i=0;i<SUDOKU_SIZE;i++)
		if(num == *data[i] - '0')
			return true;
	return false;
}

Square *Row::getSinglePointer(int i) {
	return data[i];
}