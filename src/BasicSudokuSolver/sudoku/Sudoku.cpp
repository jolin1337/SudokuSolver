#include "Sudoku.h"
#include <iostream>
#include "SudokuFunctions.h"
#include "InvalidSudoku.h"

Sudoku::Sudoku(std::string filename):SudokuBoard('_'){
	if(filename.empty())
		return;
	init(filename);
}
Sudoku::Sudoku(const SudokuBoard *val):SudokuBoard(val->getEmptySquare()) {
	emptySquare = val->getEmptySquare();
	memStored = val->hasMemory();
	if(!memStored) return;

	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			int dataIndex = i*SUDOKU_SIZE+j;
			data[dataIndex] = Square((*val)[dataIndex]);

			Square &square = data[dataIndex];

			Row &row = rows[i];
			row[j] = &square;
			square.row = &row;

			Row &column = columns[j];
			column[i] = &square;
			square.column = &column;

			BigSquare &bSquare = squares[j/SUDOKU_MINI_SIZE+(i/SUDOKU_MINI_SIZE)*SUDOKU_MINI_SIZE];
			bSquare[i%SUDOKU_MINI_SIZE][j%SUDOKU_MINI_SIZE] = &square;
			square.bigSquare  = &bSquare;

			if(square != emptySquare) {
				row.increaseNonEmptyCount();
				column.increaseNonEmptyCount();
				bSquare.increaseNonEmptyCount();
			}
		}
	}
}

Sudoku &Sudoku::operator=(const SudokuBoard *rhs) {
	Sudoku tmp(rhs);
	emptySquare = tmp.getEmptySquare();
	memStored = tmp.hasMemory();
	std::swap(data, tmp.data);
	std::swap(squares, tmp.squares);
	std::swap(rows, tmp.rows);
	std::swap(columns, tmp.columns);
	return *this;
}
bool Sudoku::operator ==(const Sudoku &rhs) {
	for (int i = 0; i < SUDOKU_SIZE*SUDOKU_SIZE; i++)
		if(data[i] != rhs[i])
			return false;
	return true;
}

bool Sudoku::fillInRows() {
	PQueue<Row & > queue;
	for (int i = 0; i < SUDOKU_SIZE; i++)
		queue.push(rows[i]);

	return fillInSquares(queue, emptySquare);
}
bool Sudoku::fillInColumns() {
	PQueue<Row & > queue;
	for (int i = 0; i < SUDOKU_SIZE; i++)
		queue.push(columns[i]);

	return fillInSquares(queue, emptySquare);
}
bool Sudoku::fillInBigSquares() {
	PQueue<BigSquare & > queue;
	for (int i = 0; i < SUDOKU_SIZE; i++)
		queue.push(squares[i]);

	return fillInSquares(queue, emptySquare);
}
bool Sudoku::solve() {
	if(!hasMemory()) return false;
	try {
		while(!isSolved()) {
			if(!fillInBigSquares() && !fillInRows() && !fillInColumns())
				return false;
		}
	} catch(InvalidSudoku &err) {
		std::cerr << err.what() << "\n";
	}
	return true;
}
bool Sudoku::isSolved() const {
	if(!hasMemory()) return false;
	for (int i = 0; i < SUDOKU_SIZE*SUDOKU_SIZE; i++)
		if(data[i] < '0' || data[i] > '9') {
			if(data[i] != emptySquare)
				throw InvalidSudoku();
			return false;
		}
	return true;
}


int Sudoku::init(std::string filename) {
	std::ifstream filestream(filename.c_str());
	return init(filestream);
}

int Sudoku::init(std::ifstream &filestream) {
	int emptySquareTmp = '_';
	memStored = false;
	if(!filestream.good()) return 1;
	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			int dataIndex = i*SUDOKU_SIZE+j;
			data[dataIndex] = readNextSquare(filestream, emptySquare, (i == 0 && j == 0));
			if(!filestream.good()){
				return 2;
			}

			Square &square = data[dataIndex];
			if(square == emptySquare)
				square = emptySquareTmp;
			Row &row = rows[i];
			row[j] = &square;
			square.row = &row;

			Row &column = columns[j];
			column[i] = &square;
			square.column = &column;

			BigSquare &bSquare = squares[j/SUDOKU_MINI_SIZE+(i/SUDOKU_MINI_SIZE)*SUDOKU_MINI_SIZE];
			bSquare[i%SUDOKU_MINI_SIZE][j%SUDOKU_MINI_SIZE] = &square;
			square.bigSquare  = &bSquare;

			if(square != emptySquare) {
				row.increaseNonEmptyCount();
				column.increaseNonEmptyCount();
				bSquare.increaseNonEmptyCount();
			}
		}
	}
	emptySquare = emptySquareTmp;
	memStored = true;
	return 0;
}

char Sudoku::operator[](int i) const {
	isSolved();
	if(i < 0 || i > SUDOKU_SIZE*SUDOKU_SIZE || !hasMemory()) return '\0';
	return data[i];
}


bool Sudoku::validCharacter(char v) const {
	return !(v < '0' || v > '9') || v == emptySquare;
}