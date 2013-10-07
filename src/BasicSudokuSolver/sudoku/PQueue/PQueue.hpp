#ifndef PQUEUE_TEMPLATE
#define PQUEUE_TEMPLATE 
#include <algorithm>

template<class T, class C>
PQueue<T, C>::PQueue(const C& compare):compare(compare), head(0), usize(0) {}
template<class T, class C>
PQueue<T, C>::PQueue(const PQueue &pq):compare(pq.compare), head(0), usize(pq.usize) {
	Node *it = pq.head;
	while(it) {
		push(it->value);
		it = it->next;
	}
}
template<class T, class C>
PQueue<T, C> &PQueue<T,C>::operator=(const PQueue&rhs) {
	PQueue<T, C> tmp(rhs);
	std::swap(tmp.head, head);
	std::swap(tmp.usize, usize);
	return *this;
}
template<class T, class C>
PQueue<T, C>::~PQueue() {
	while(!empty()) pop();
}

template<class T, class C>
T PQueue<T, C>::pop(){ 
	if(head == 0) throw PQueueException(); // if the list is empty
	Node *new_head = head->next;	// the next head after removal
	T first = *head;				// the value to be returned
	delete head;					// delete the head of this list
	head = new_head;				// set new head to the second element in the list
	usize--;						// decrese size of elements by 1
	return first;					// returns the value of the previous head
}
template<class T, class C>
void PQueue<T,C>::push(T element) {
	if(!empty()) {						// if the list is not empty
		Node *it = head;				// store the head pointer into it
		if(!compare(element, *head))	// if  element > head
			head = new Node(element, head);	// set the new head to be the new node with element as value
											// make the new head point to the previous head
		else {							// then element < head

			// move the pointer it to the position where element will be inserted
			while(it->next && compare(element, it->next->value)) // while element < it->next->value
				it = it->next;

			// insert on the right position
			it->next = new Node(element, it->next);
		}
		usize++;					// increase the size of elements by 1
		return;						// exit push function
	}

	// the first element pushed into this list will become head
	head = new Node(element);
	usize++;// increase the size of elements by 1
}

#endif