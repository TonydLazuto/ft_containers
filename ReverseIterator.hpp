#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <iostream>
#include <Iterator>

namespace ft 
{
	template <class Iter>
	class ReverseIterator : public Iterator
	{
		private:
			Iter current;

		public:
			ReverseIterator( void );
			virtual ~ReverseIterator( void );
			ReverseIterator(ReverseIterator const & src);
			ReverseIterator& operator=(ReverseIterator const & rhs);

			reverse_iterator() : current() { }
			explicit reverse_iterator(Iter x) : current(x){}
			template<class U> reverse_iterator (const reverse_iterator<U>&x) : current(x.base()) {}

			Iter base()const{ return current; }//current iterator value

			reference operator*()const {
				Iter tmp=current;
				return *--tmp;
			}
			pointer operator->()const;
			reference operator[](difference_type n)const;

			reverse_iterator& operator++() { --current; return *this; } // note: not ++
			reverse_iterator operator++(int){
				reverse_iterator t=current;
				--current;
				return t;
			}
			reverse_iterator& operator--() { ++current; return *this; } // note: not – –
			reverse_iterator operator--(int) {
				reverse_iterator t=current;
				++current;
				return t;
			}
			reverse_iterator operator+(difference_type n)const;
			reverse_iterator&operator+=(difference_type n);
			reverse_iterator operator-(difference_type n)const;
			reverse_iterator&operator-=(difference_type n);
			
	};
}

#endif
