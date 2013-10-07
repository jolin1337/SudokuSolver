#include "SudokuFunctions.h"

Square readNextSquare(std::ifstream &fstream, char &emptySquare, bool isFirstSquare) {
	char readInfo;
	fstream >> readInfo;
	while(!(readInfo > '0' && readInfo <= '9') && readInfo != emptySquare && fstream.good()){
		if(isFirstSquare)	// only available until first square has been detected
			switch(readInfo) {
				case 'E':
					std::string line;
					std::getline(fstream, line, '=');
					if(line == "MPTYSQUARE"){
						char tmp = fstream.get();
						if(tmp > '0' && tmp <= '9')
							throw 1;
						emptySquare = tmp;
						// std::cout << "EMPTYSQUARE = " << emptySquare << "\n";
					}
					break;
			}
		fstream >> readInfo;
	}
	return Square(readInfo);
}