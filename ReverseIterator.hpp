#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft
{
	template <class Iter>
	class ReverseIterator
	{
		private:
			Iter _itor;

		public:
			typedef Iter	iterator_type;
			typedef typename ft::IteratorTraits<Iter>::iterator_category	iterator_category;
			typedef typename ft::IteratorTraits<Iter>::value_type			value_type;
			typedef typename ft::IteratorTraits<Iter>::difference_type		difference_type;
			typedef typename ft::IteratorTraits<Iter>::pointer				pointer;
			typedef typename ft::IteratorTraits<Iter>::reference			reference;

			ReverseIterator( void ) : _itor() {}
			explicit ReverseIterator(Iter x) : _itor(x) {}
			virtual ~ReverseIterator( void );
			template < class U >
			ReverseIterator (const ReverseIterator &src) : _itor(src.base()) {}

			ReverseIterator& operator=(ReverseIterator const & rhs);

			iterator_type base(void) const { return _itor; }

			reference operator*(void) const
			{
				Iter tmp = _itor;
				return (*(--tmp));
			}
			pointer operator->(void) const { return &(operator*()); }
			reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

			ReverseIterator& operator++(void)
			{
				--_itor;
				return *this;
			}
			ReverseIterator operator++(int)
			{
				ReverseIterator tmp = _itor;
				--_itor;
				return tmp;
			}
			ReverseIterator& operator--(void)
			{
				++_itor;
				return *this;
			}
			ReverseIterator operator--(int)
			{
				ReverseIterator tmp = _itor;
				++_itor;
				return tmp;
			}
			ReverseIterator operator+(difference_type n) const { return (reverse_iterator(_itor - n)); }
			ReverseIterator&operator+=(difference_type n)
			{
				_itor -= n;
				return (*this);
			}
			ReverseIterator operator-(difference_type n) const { return (reverse_iterator(_itor + n)); }
			ReverseIterator&operator-=(difference_type n)
			{
				_itor += n;
				return (*this);
			}

			bool operator==(ReverseIterator const &rhs) { return (this->_itor == rhs._itor); }
			bool operator!=(ReverseIterator const &rhs) { return (this->_itor != rhs._itor); }
			bool operator<(ReverseIterator const &rhs) { return (this->_itor < rhs._itor); }
			bool operator>(ReverseIterator const &rhs) { return (this->_itor > rhs._itor); }
			bool operator<=(ReverseIterator const &rhs) { return (this->_itor <= rhs._itor); }
			bool operator>=(ReverseIterator const &rhs) { return (this->_itor >= rhs._itor); }
			
	};
}

#endif
