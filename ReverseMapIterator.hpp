#ifndef REVERSEMAPITERATOR_HPP
# define REVERSEMAPITERATOR_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft
{
	template <class Iter, class Pair>
	class ReverseMapIterator
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

			ReverseMapIterator( void ) : _itor() {}
			explicit ReverseMapIterator(iterator_type x) : _itor(x) {}
			virtual ~ReverseMapIterator( void ) {}
			template < class OtherIter, class Pr >
			ReverseMapIterator (const ReverseMapIterator<OtherIter, Pr> &rev)
			: _itor(rev.base()) {}
			ReverseMapIterator& operator=(ReverseMapIterator<Iter, Pair> const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}

			iterator_type base(void) const { return _itor; }

			Pair& operator*(void) const
			{
				iterator_type tmp = _itor;
				return (*tmp);
			}
			Pair* operator->(void) const { return &(operator*()); }

			ReverseMapIterator operator++(int)
			{
				ReverseMapIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}
			ReverseMapIterator& operator++(void)
			{
				--this->_itor;
				return *this;
			}
			ReverseMapIterator operator--(int)
			{
				ReverseMapIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			ReverseMapIterator& operator--(void)
			{
				++this->_itor;
				return *this;
			}

			operator ReverseMapIterator<const Iter, class Pr> ()
			{ return (ReverseMapIterator<Iter, Pr>(this->_itor)); }
			
	};

	template <class Iterator, class Pair>
		bool operator== (const ft::ReverseMapIterator<Iterator, Pair>& lhs,
			const ft::ReverseMapIterator<Iterator, Pair>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator_L, class Iterator_R, class Pair>
		bool operator== (const ft::ReverseMapIterator<Iterator_L, Pair>& lhs,
			const ft::ReverseMapIterator<Iterator_R, Pair>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }
	template <class Iterator, class Pair>
		bool operator== (ft::ReverseMapIterator<Iterator, Pair>& lhs,
			ft::ReverseMapIterator<Iterator, Pair>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator_L, class Iterator_R, class Pair>
		bool operator== (ft::ReverseMapIterator<Iterator_L, Pair>& lhs,
			ft::ReverseMapIterator<Iterator_R, Pair>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator, class Pair>
		bool operator!= (const ft::ReverseMapIterator<Iterator, Pair>& lhs,
			const ft::ReverseMapIterator<Iterator, Pair>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

	template <class Iterator_L, class Iterator_R, class Pair>
		bool operator!= (const ft::ReverseMapIterator<Iterator_L, Pair>& lhs,
			const ft::ReverseMapIterator<Iterator_R, Pair>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }
			
	template <class Iterator, class Pair>
		bool operator!= (ft::ReverseMapIterator<Iterator, Pair>& lhs,
			ft::ReverseMapIterator<Iterator, Pair>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

	template <class Iterator_L, class Iterator_R, class Pair>
		bool operator!= (ft::ReverseMapIterator<Iterator_L, Pair>& lhs,
			ft::ReverseMapIterator<Iterator_R, Pair>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

}

#endif
