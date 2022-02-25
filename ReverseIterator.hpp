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
			explicit ReverseIterator(iterator_type x) : _itor(x) {}
			virtual ~ReverseIterator( void ) {}

			template < class Myiter >
			ReverseIterator (const ReverseIterator<Myiter> &rev) : _itor(rev.base()) {}

			iterator_type base(void) const { return _itor; }

			reference operator*(void) const
			{
				iterator_type tmp = _itor;
				return (*(--tmp));
			}
			pointer operator->(void) const { return &(operator*()); }
			reference operator[](difference_type n) const { return (this->base()[-n - 1]); }

			ReverseIterator operator++(int)
			{
				ReverseIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}
			ReverseIterator operator++(void)
			{
				ReverseIterator tmp = *this;
				tmp._itor = --this->_itor;
				return tmp;
			}
			ReverseIterator operator--(int)
			{
				ReverseIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			ReverseIterator operator--(void)
			{
				ReverseIterator tmp = *this;
				tmp._itor = ++this->_itor;
				return tmp;
			}
			ReverseIterator operator+(difference_type n) const {
				return (ReverseIterator(_itor - n));
			}
			ReverseIterator&operator+=(difference_type n)
			{
				_itor -= n;
				return (*this);
			}
			ReverseIterator operator-(difference_type n) const {
				return (ReverseIterator(_itor + n));
			}
			ReverseIterator&operator-=(difference_type n)
			{
				_itor += n;
				return (*this);
			}

			operator ReverseIterator<const Iter> () const
			{ return (ReverseIterator<Iter>(this->_itor)); }
			
	};

	template <class Iterator>
		bool operator== (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() == rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator== (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() == rhs.base()); }

	template <class Iterator>
		bool operator!= (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() != rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator!= (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() != rhs.base()); }

	template <class Iterator>
		bool operator< (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() < rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator< (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() < rhs.base()); }

	template <class Iterator>
		bool operator<= (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() <= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator<= (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() <= rhs.base()); }

	template <class Iterator>
		bool operator> (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() > rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator> (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() > rhs.base()); }

	template <class Iterator>
		bool operator>= (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() >= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator>= (const ft::ReverseIterator<Iterator_L>& lhs,
			const ft::ReverseIterator<Iterator_R>& rhs)
			{ return (lhs.base() >= rhs.base()); }

	template <class Iterator>
		ft::ReverseIterator<Iterator>
		operator+ (typename ft::ReverseIterator<Iterator>::difference_type n,
			const ft::ReverseIterator<Iterator>& rev_it)
			{ return (rev_it + n); }

	template <class Iterator>
		typename ft::ReverseIterator<Iterator>::difference_type
		operator- (const ft::ReverseIterator<Iterator>& lhs,
			const ft::ReverseIterator<Iterator>& rhs)
			{ return (lhs.base() - rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		typename ft::ReverseIterator<Iterator_L>::difference_type
		operator-(const ft::ReverseIterator<Iterator_L>& lhs,
		const ft::ReverseIterator<Iterator_R>& rhs)
		{ return (lhs.base() - rhs.base()); }
}

#endif
