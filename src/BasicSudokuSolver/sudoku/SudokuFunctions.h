#ifndef SUDOKUFUNC_H
#define SUDOKUFUNC_H 

#include "PQueue/PQueue.h"
#include "PuzzleStructs/Square.h"
#include "PuzzleStructs/BigSquare.h"
#include "PuzzleStructs/Row.h"

#include <fstream>

Square readNextSquare(std::ifstream &fstream, char &emptySquare, bool isFirstSquare);

template<class T>
bool fillInSquares(PQueue<T &> &queue, const char emptySquare);

#include "fillInSquares.h"
#endif