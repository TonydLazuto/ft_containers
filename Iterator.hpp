#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>
#include <iostream>
#include <cstddef>

template < class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
class Iterator
{
	private:
		Iterator( void ) {}
		virtual ~Iterator( void ) {}
		Iterator(Iterator const & src) { (void)src; }
		Iterator& operator=(Iterator const & rhs) {
			(void)rhs;
			return *this;
		}
	protected:
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;

};

#endif
