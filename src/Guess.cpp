#include "Guess.h"

Guess::Guess(char val, int pos, Sudoku state):val(val), pos(pos)/*, stateAtGuess(state)*/ {
}
char Guess::value() {
	return val;
}
void Guess::value(char val) {
	this->val = val;
}

int Guess::position() {
	return pos;
}
void Guess::position(int pos) {
	this->pos = pos;
}

// Sudoku &Guess::sudokuState() {
// 	return stateAtGuess;
// }
// void Guess::sudokuState(Sudoku state) {
// 	stateAtGuess = state;
// }

bool Guess::operator ==(const Guess &g) {
	return g.pos == pos && g.val == val;
}