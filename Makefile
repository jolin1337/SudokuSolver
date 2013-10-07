main_cpps = StatusAlerts.cpp
sudoku_cpps = Sudoku.cpp readNextSquare.cpp
puzzle_cpps = Square.cpp BigSquare.cpp Row.cpp 

main_header = StatusAlerts.h
sudoku_header = Sudoku.h PQueue/PQueue.h PQueue/PQueue.h SudokuFunctions.h fillInSquares.h
puzzle_header = PuzzleStructs.h Square.h BigSquare.h Row.h 


src_main_headers = $(addprefix src/BasicSudokuSolver/,$(main_header))
src_main_cpps = $(addprefix src/BasicSudokuSolver/,$(main_cpps))

src_sudoku_headers = $(addprefix src/BasicSudokuSolver/sudoku/,$(sudoku_header))
src_sudoku_cpps = $(addprefix src/BasicSudokuSolver/sudoku/,$(sudoku_cpps))

src_puzzle_headers = $(addprefix src/BasicSudokuSolver/sudoku/PuzzleStructs/,$(puzzle_header))
src_puzzle_cpps = $(addprefix src/BasicSudokuSolver/sudoku/PuzzleStructs/,$(puzzle_cpps))

src_cpps = $(src_main_cpps) $(src_sudoku_cpps) $(src_puzzle_cpps)
src_headers = $(src_main_headers) $(src_sudoku_headers) $(src_puzzle_headers)



cpps_extend = SudokuSolutions.cpp Guess.cpp
headers_extend = SudokuSolutions.h Guess.h

src_extend_headers = $(addprefix src/,$(headers_extend))
src_extend_cpps = $(addprefix src/,$(cpps_extend))



sudoku_out = ./bin/sudoku_solver

all: sudoku sudokuExtend

sudoku: $(sudoku_out)
sudokuExtend: $(sudoku_out)extend

$(sudoku_out): sudokus/5sudoku.txt src/BasicSudokuSolver/main.cpp $(src_cpps) $(src_headers)
	g++ -o $(sudoku_out) src/BasicSudokuSolver/main.cpp $(src_cpps)

$(sudoku_out)extend: sudokus/5sudoku.txt ./src/main.cpp $(src_cpps) $(src_headers) $(src_extend_headers) $(src_extend_cpps)
	g++ -o $(sudoku_out)extend ./src/main.cpp $(src_cpps) $(src_extend_cpps)

