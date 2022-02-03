#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <iostream>
#include <Iterator>

template <class Iterator>
class ReverseIterator : public Iterator
{
	private:
		

	public:
		ReverseIterator( void );
		virtual ~ReverseIterator( void );
		ReverseIterator(ReverseIterator const & src);
		ReverseIterator& operator=(ReverseIterator const & rhs);

		Iterator:: base(void) const
		{
			;
		}
		
};

#endif
