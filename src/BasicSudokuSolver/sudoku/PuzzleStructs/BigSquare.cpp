#include "BigSquare.h"

BigSquare::BigSquare():count(0) {}

bool BigSquare::operator <(const BigSquare &rhs) const{
	return nonEmptyCount() < rhs.nonEmptyCount();
}
Square **BigSquare::operator [](int i){
	return data[i];
}

unsigned int BigSquare::nonEmptyCount() const{
	return count;
}
void BigSquare::increaseNonEmptyCount() {
	count++;
}
bool BigSquare::hasNumber(int num) const{
	for(int i=0;i<SUDOKU_MINI_SIZE;i++)
		for (int j = 0; j < SUDOKU_MINI_SIZE; j++)
			if(num == data[i][j]->value()-'0')
				return true;
	return false;
}

Square *BigSquare::getSinglePointer(int i) {
	return data[i/3][i%3];
}