#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>

template <class T>
class RandomAccessIterator
{
	private:

	public:
		RandomAccessIterator( void );
		virtual ~RandomAccessIterator( void );
		RandomAccessIterator(RandomAccessIterator const & src);
		RandomAccessIterator& operator=(RandomAccessIterator const & rhs);
		T*	first( void ) = 0;
		T*	next( void ) = 0;
};

#endif
