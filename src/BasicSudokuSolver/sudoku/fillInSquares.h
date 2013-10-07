 
#include <map>

template<class T>
bool fillInSquares(PQueue<T &> &queue, const char emptySquare){
	bool hasChanged = false;
	while(!queue.empty()) {
		T &queueType = queue.pop();
		std::map<int, std::pair<int, int> > fitts;
		for (int i = 0; i < SUDOKU_SIZE; i++){
			Square *square = queueType.getSinglePointer(i);
			
			if(*square == emptySquare) {
				for (int num = 1; num < 10; num++)
					if(!(square->column->hasNumber(num)) && !(square->bigSquare->hasNumber(num)) && !(square->row->hasNumber(num))) {
						fitts[num].first++;
						fitts[num].second = i;
					}	
			}
		}
		for (int i = 1; i < 10; i++) {
			std::map<int, std::pair<int, int> >::iterator num = fitts.find(i);
			if(num != fitts.end() && num->second.first == 1) {
				queueType.getSinglePointer(num->second.second)->value(num->first+'0');
				hasChanged = true;
			}
		}
	}
	return hasChanged;
}