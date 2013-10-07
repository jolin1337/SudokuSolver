#ifndef COMPARER
#define COMPARER

// This class are an example of a comparer for PQueue class
template<class T>
class Compare
{
public:
	/**
	 * ool operator() (const T &lhs, const T &rhs) const;
	 * 		This function is called in PQueue and sorts the queue acording to the value
	 * @param  lhs one element in the list
	 * @param  rhs another element in the list
	 * @return     true if rhs is bigger than lhs otherwise false
	 */
	bool operator() (const T &lhs, const T &rhs) const {
		return lhs < rhs;
	}
};

#endif