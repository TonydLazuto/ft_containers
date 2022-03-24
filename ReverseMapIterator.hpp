#ifndef REVERSEMAPITERATOR_HPP
# define REVERSEMAPITERATOR_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft
{
	template <class Iter>
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
			typedef typename Iter::value_type								NodePair;

			ReverseMapIterator( void ) : _itor() {}
			explicit ReverseMapIterator(iterator_type x) : _itor(x) {}
			virtual ~ReverseMapIterator( void ) {}
			template < class OtherIter >
			ReverseMapIterator (const ReverseMapIterator<OtherIter> &rev)
			: _itor(rev.base()) {}
			ReverseMapIterator& operator=(ReverseMapIterator<Iter> const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}

			iterator_type base(void) const { return _itor; }

			NodePair& operator*(void) const
			{
				iterator_type tmp = _itor;
				return (*tmp);
			}
			NodePair* operator->(void) const { return &(operator*()); }

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

			operator ReverseMapIterator<const Iter> ()
			{ return (ReverseMapIterator<Iter>(this->_itor)); }
			
	};

	template <class Iterator>
		bool operator== (const ft::ReverseMapIterator<Iterator>& lhs,
			const ft::ReverseMapIterator<Iterator>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator_L, class Iterator_R>
		bool operator== (const ft::ReverseMapIterator<Iterator_L>& lhs,
			const ft::ReverseMapIterator<Iterator_R>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }
	template <class Iterator>
		bool operator== (ft::ReverseMapIterator<Iterator>& lhs,
			ft::ReverseMapIterator<Iterator>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator_L, class Iterator_R>
		bool operator== (ft::ReverseMapIterator<Iterator_L>& lhs,
			ft::ReverseMapIterator<Iterator_R>& rhs)
			{ return (*(lhs.base()) == *(rhs.base())); }

	template <class Iterator>
		bool operator!= (const ft::ReverseMapIterator<Iterator>& lhs,
			const ft::ReverseMapIterator<Iterator>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

	template <class Iterator_L, class Iterator_R>
		bool operator!= (const ft::ReverseMapIterator<Iterator_L>& lhs,
			const ft::ReverseMapIterator<Iterator_R>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }
			
	template <class Iterator>
		bool operator!= (ft::ReverseMapIterator<Iterator>& lhs,
			ft::ReverseMapIterator<Iterator>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

	template <class Iterator_L, class Iterator_R>
		bool operator!= (ft::ReverseMapIterator<Iterator_L>& lhs,
			ft::ReverseMapIterator<Iterator_R>& rhs)
			{ return (*(lhs.base()) != *(rhs.base())); }

}

#endif
