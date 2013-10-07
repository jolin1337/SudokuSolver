#include "SudokuSolutions.h"
#include "BasicSudokuSolver/sudoku/InvalidSudoku.h"

#include <iostream>
#include <algorithm>
SudokuSolutions::SudokuSolutions(std::string filename) {
	Sudoku sud(filename);
	std::cout << sud.getEmptySquare() << "\n";
	*this = &sud;
}
SudokuSolutions::SudokuSolutions(const SudokuBoard *val) {
	if(val == 0) return;

	memStored = val->hasMemory();
	emptySquare = val->getEmptySquare();
	if(memStored == false) return;

	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			int dataIndex = i*SUDOKU_SIZE+j;
			data[dataIndex] = (*val)[dataIndex];

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
				square.row->increaseNonEmptyCount();
				square.column->increaseNonEmptyCount();
				square.bigSquare->increaseNonEmptyCount();
			}
		}
	}
}

SudokuSolutions &SudokuSolutions::operator=(const SudokuBoard *rhs) {
	if(rhs == 0);
	SudokuSolutions tmpBoard(rhs);
	emptySquare = tmpBoard.emptySquare;
	memStored = tmpBoard.memStored;
	if(!memStored) return *this;
	for (int i = 0; i < SUDOKU_SIZE; i++){
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			Square tmp = tmpBoard.data[i*SUDOKU_SIZE + j];
			Square &square = data[i*SUDOKU_SIZE + j];
			square = tmp;
			int c = j/SUDOKU_MINI_SIZE+(i/SUDOKU_MINI_SIZE)*SUDOKU_MINI_SIZE;
			squares[c][i%SUDOKU_MINI_SIZE][j%SUDOKU_MINI_SIZE] = &square;
			rows[i][j] = &square;
			columns[j][i] = &square;
			square.row = &rows[i];
			square.column = &columns[j];
			square.bigSquare = &squares[c];

			if(square != emptySquare) {
				square.row->increaseNonEmptyCount();
				square.column->increaseNonEmptyCount();
				square.bigSquare->increaseNonEmptyCount();
			}
		}
	}
	return *this;
	// if(!rhs.hasMemory()) return *this;
	// memStored = true;
	// emptySquare = rhs.getEmptySquare();

	// for (int i = 0; i < SUDOKU_SIZE; i++) {
	// 	for (int j = 0; j < SUDOKU_SIZE; j++) {
	// 		int dataIndex = i*SUDOKU_SIZE+j;
	// 		data[dataIndex] = rhs[dataIndex];

	// 		Square &square = data[dataIndex];

	// 		Row &row = rows[i];
	// 		row[j] = &square;
	// 		square.row = &row;

	// 		Row &column = columns[j];
	// 		column[i] = &square;
	// 		square.column = &column;

	// 		BigSquare &bSquare = squares[j/SUDOKU_MINI_SIZE+(i/SUDOKU_MINI_SIZE)*SUDOKU_MINI_SIZE];
	// 		bSquare[i%SUDOKU_MINI_SIZE][j%SUDOKU_MINI_SIZE] = &square;
	// 		square.bigSquare  = &bSquare;

	// 		if(square != emptySquare) {
	// 			row.increaseNonEmptyCount();
	// 			column.increaseNonEmptyCount();
	// 			bSquare.increaseNonEmptyCount();
	// 		}
	// 	}
	// }
	// return *this;
}
bool SudokuSolutions::operator==(const SudokuSolutions &rhs) {
	for (int i = 0; i < SUDOKU_SIZE*SUDOKU_SIZE; i++)
		if(data[i] != rhs[i])
			return false;
	return true;
}
SudokuSolutions::~SudokuSolutions() {
	// for (std::vector<Sudoku *>::iterator it = solutions.begin(); it != solutions.end(); ++it)
	// 	if(*it != 0)
	// 		delete *it;
}

unsigned int SudokuSolutions::currentSolutionSize() const {
	return solutions.size();
}

bool SudokuSolutions::solve() {
	if(!hasMemory()) return false;
	Sudoku input = this;
	bool solved = false;
	while(guess()){
		Sudoku tmp = this;
		if(tmp.solve() && std::find(solutions.begin(), solutions.end(), tmp) == solutions.end()) {
			solutions.push_back(tmp);
			// return true;
		}
		*this = &input;
	}

	return currentSolutionSize();
}
bool SudokuSolutions::isSolved() const {
	if(!hasMemory()) return false;
	for (int i = 0; i < SUDOKU_SIZE*SUDOKU_SIZE; i++)
		if(data[i] < '0' || data[i] > '9') {
			if(data[i] != emptySquare)
				throw InvalidSudoku();
			return false;
		}
	return true;
}

bool SudokuSolutions::validCharacter(char v) const {
	return !(v < '0' || v > '9') || v == emptySquare;
}
bool SudokuSolutions::guess(int position, int startValue) {
	if(!hasMemory() || position < 0) return false;
	if(startValue < 1 || startValue > 9) startValue = 1;

	for (int i = position; i < SUDOKU_SIZE*SUDOKU_SIZE; i++) {
		if(data[i] == emptySquare) {
			Square *square = &data[i];
			for (int j = startValue; j < 10; j++) {
				if(!(square->column->hasNumber(j)) && !(square->bigSquare->hasNumber(j)) && !(square->row->hasNumber(j))) {
					Guess g =  Guess(j+'0', i);
					if(std::find(guesses.begin(), guesses.end(), g) == guesses.end()){
						guesses.push_back(g);
						// std::cout << "Guess: " << j  << ", on position: " << i<< "\n";
						square->value(j+'0');
						return true;
					}
				}
			}
			startValue = 1;
		}
	}
	return false;
}
// SudokuSolutions(const SudokuSolutions &assign):guesses(assign.guesses) {
// 	for (std::vector<Sudoku *>::iterator it = assign.solutions.begin(); it != assign.solutions.end(); ++it)
// 		solutions.push_back(new Sudoku(*it));
// }
// SudokuSolutions &operator=(const SudokuSolutions &rhs) {
// 	// TODO: implement this function!! important
// }
bool SudokuSolutions::nextSolution() {
	if(currentSolutionSize() == 0) return false;

	int c = 0;
	*this = &solutions[0];
	solutions.erase(solutions.begin());
	return true;
	// Guess g(0, 0, *this);
	// do {
	// 	*this = guesses[0].sudokuState();
	// } while(!solve());
	
	// return true;
	// return false;
	// while(gsize) {
	// 	int newGuess = 0;
	// 	gsize--;
	// 	Guess &guessToChange = guesses[gsize];
	// 	SudokuSolutions sudtmp;
	// 	sudtmp = *this;
	// 	*this = guessToChange.sudokuState();
	// 	if(gsize==0){ 	// then this is last guess made before
	// 		Guess &guessToChange2 = guesses[guesses.size()-1];
	// 		// std::cout << "GGG:" << guessToChange2.position() << "," << guessToChange2.value() << "==" << guesses.size() << "\n";
	// 		if(guess() == false)
	// 			return false;
	// 		gsize = guesses.size();
	// 		newGuess = 1;
	// 	}
	// 	if(solve() && !(*this == sudtmp))
	// 		return true;
	// 	std::vector<Guess> tmp = guesses;
	// 	*this = sudtmp;
	// 	guesses = tmp;
			// std::cout  << "==" << guesses.size() << "\n";
		// guesses.erase(guesses.begin()+gsize-newGuess);
		// c++;

		// for (int j = (guessToChange.value()+1-'0'); j < 10; j++) {
		// 	Square *square = &data[guessToChange.position()];
		// 	if(!(square->column->hasNumber(j)) && !(square->bigSquare->hasNumber(j)) && !(square->row->hasNumber(j))) {
		// 		std::cout << j << "\n";
		// 		square->value(j+'0');
		// 		guessToChange.value(j+'0');
		// 		// guessToChange.sudokuState(*this);
		// 		if(solve())
		// 			return true;
		// 		*this = guessToChange.sudokuState();
		// 	}
		// }
		// int gpos = guessToChange.position()+1;
		// guesses.erase(guesses.begin()+gsize);
		// if(gsize == 0){
		// 	if(!guess(gpos))
		// 		return false;
		// 	gsize++;
		// }
		// std::cout << gsize << "\n";
	// }
}
