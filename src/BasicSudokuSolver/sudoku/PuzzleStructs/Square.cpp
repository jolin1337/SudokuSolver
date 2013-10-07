#include "Square.h"


Square::Square(char val, Row *column, Row *row, BigSquare *bigSquare):val(val), column(column), row(row), bigSquare(bigSquare) {
}

char Square::value() const{
	return val;
}
void Square::value(int val) {
	this->val = val;
}