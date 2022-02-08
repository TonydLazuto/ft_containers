#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <iostream>
#include <iterator>
#include "IteratorTraits.hpp"

namespace ft 
{
	template <class Iter>
	class ReverseIterator
	{
		private:
			Iter current;

		public:
			ReverseIterator( void ) : current() { }
			virtual ~ReverseIterator( void );
			explicit ReverseIterator(Iter x) : current(x){}
			template<class U> ReverseIterator (const ReverseIterator<U>&x) : current(x.base()) {}

			ReverseIterator(ReverseIterator const & src);
			ReverseIterator& operator=(ReverseIterator const & rhs);

			Iter base(void)const{ return current; }//current iterator value

			reference operator*(void)const {
				Iter tmp=current;
				return *--tmp;
			}
			pointer operator->(void)const;
			reference operator[](difference_type n)const;

			ReverseIterator& operator++(void) { --current; return *this; } // note: not ++
			ReverseIterator operator++(int){
				ReverseIterator t=current;
				--current;
				return t;
			}
			ReverseIterator& operator--(void) { ++current; return *this; } // note: not – –
			ReverseIterator operator--(int) {
				ReverseIterator t=current;
				++current;
				return t;
			}
			ReverseIterator operator+(difference_type n)const;
			ReverseIterator&operator+=(difference_type n);
			ReverseIterator operator-(difference_type n)const;
			ReverseIterator&operator-=(difference_type n);
			
	};
}

#endif
