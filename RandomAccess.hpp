#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include "Bidirectional.hpp"

namespace ft 
{
	template <class T>
	class RandomAccessIterator : public BidirectionalIterator
	{
		private:
			T*	p;
		public:
			RandomAccessIterator( void ) {}
			virtual ~RandomAccessIterator( void ) {}
			RandomAccessIterator(RandomAccessIterator const & src) {}
			RandomAccessIterator& operator=(RandomAccessIterator const & rhs) {}
			
	};
}

#endif
