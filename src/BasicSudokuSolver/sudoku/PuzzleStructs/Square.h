#ifndef SQUARE_H
#define SQUARE_H

class BigSquare;
class Row;
struct Square {
	Square(char val=0, Row *column=0, Row *row=0, BigSquare *bigSquare=0);
	operator char() const{
		return value();
	}
	char value() const;
	void value(int value);
	Row *row, *column;
	BigSquare *bigSquare;
private:
	char val;
};

#endif