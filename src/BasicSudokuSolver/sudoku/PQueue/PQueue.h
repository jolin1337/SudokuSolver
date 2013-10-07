#ifndef P_QUEUEH
#define P_QUEUEH 
#include "Compare.h"
#include <cstdlib>
#include <exception>

/**
 * This class will represent a priorised queue with the 
 * value/list-type as a template and implementation with 
 * a single linked list.
 *
 * Why implementation are in .h file:
 * 		When the compiler compiles a template class it needs to have access to the implementation
 * 		because for each usage of the template type it will create a similar class, example:
 * 			template<typename T>
			class TemplateClass {
				T variable;
				void someFunc(T param) {/* do stuff using T *\/}
			};

			// somewhere in a source file
			TemplateClass<int> tc; // this will create a new class that looks something similar to the following:
			/*
			 *	class TemplateClass_int/*som unique name*\/ {
			 * 		int variable;
			 * 		void someFunc(int param) {/* do stuff using int *\/}
			 * 	}
			 *\/

		 And with only a object file or library this can't be accomplished with any compiler today, and 
		 therefore a template class needs to be declared inside a header file
 */

// T is the type of element data, C is the sort function/object default is the Compare object
template<class T, class C = Compare<T> >
class PQueue
{
public:
	/**
	 * PQueue();
	 * @param compareThe  constructor takes a compare object/function to sort the list 
	 *                    with as parameter
	 */
	PQueue(const C& compare = C());
	PQueue(const PQueue &);
	PQueue &operator=(const PQueue&);
	~PQueue();

	/**
	 * T pop();
	 * 		removes an element at the front of the list.
	 * @return returns the value removed
	 */
	T pop();
	/**
	 * void push(T element);
	 * 		adds a element to this list at the position where the priority are correct
	 * @param element the element to be added.
	 */
	void push(T element);
	/**
	 * size_t size();
	 * @return the size of this list
	 */
	size_t size(){ return usize; }
	/**
	 * bool empty();
	 * @return true if the list is empty
	 */
	bool empty(){ return head == 0; }

private:
	const C &compare;	// the list sorter/organizer

	// This describes a node in the linked list
	struct Node {
		/**
		 * Node(T element, Node *next=0);
		 * @param element  the element value of this node in the list
		 * @param next  a pointer to next node in the list
		 */
		Node(T element, Node *next=0):value(element), next(next) {}
		/**
		 * operator T();
		 * @return returns the value of this node
		 */
		operator T(){ return value; }
		Node *next;	// a pointer to next node in the list
		T value;	// the element value of this node in the list
	} *head;		// the head/top of this list

	size_t usize;	// size of the list

	// Exception for pop function when no more elements exists in the list
	struct PQueueException : public std::exception {
		virtual const char* what() const throw() {
			return "No more elements to pop";
		}
	};
};

// Implementation of PQueue in PQueue.hpp
#include "PQueue.hpp"
// .hpp has the same mening as .h file, but this way we can keep the default syntax of the file in sublime_text

#endif