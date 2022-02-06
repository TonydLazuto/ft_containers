#ifndef BIDERECTIONALITERATOR_HPP
# define BIDERECTIONALITERATOR_HPP

#include <iostream>

namespace ft 
{
	class BiderectionalIterator
	{
		private:
			

		public:
			BiderectionalIterator( void );
			virtual ~BiderectionalIterator( void );
			BiderectionalIterator(BiderectionalIterator const & src);
			BiderectionalIterator& operator=(BiderectionalIterator const & rhs);

			
	};
}

#endif
