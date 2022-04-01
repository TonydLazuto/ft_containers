#ifndef REVERSEMAPITERATOR_HPP
# define REVERSEMAPITERATOR_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft
{
	template <class NodePair, class Iter>
	class ReverseMapIterator
	{
		private:
			Iter _itor;

		public:
			typedef Iter	iterator_type;

			ReverseMapIterator( void ) : _itor() {}
			explicit ReverseMapIterator(iterator_type itor) : _itor(itor) {}
			virtual ~ReverseMapIterator( void ) {}
			ReverseMapIterator (ReverseMapIterator const& rev_it)
			: _itor(rev_it._itor) {}
			template < class MyPair, class OtherIter >
			ReverseMapIterator (const ReverseMapIterator<MyPair, OtherIter> &rev)
			: _itor(rev.base()) {}
			ReverseMapIterator& operator=(ReverseMapIterator<NodePair, Iter> const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}

			iterator_type base(void) const { return _itor; }

			NodePair& operator*(void) const
			{
				iterator_type tmp = _itor;
				return (*--tmp);
			}
			NodePair* operator->(void) const { return &(operator*()); }

			ReverseMapIterator operator++(int)
			{
				ReverseMapIterator tmp(*this);
				operator++();
				return tmp;
			}
			ReverseMapIterator& operator++(void)
			{
				--this->_itor;
				return *this;
			}
			ReverseMapIterator operator--(int)
			{
				ReverseMapIterator tmp(*this);
				operator--();
				return tmp;
			}
			ReverseMapIterator& operator--(void)
			{
				++this->_itor;
				return *this;
			}

			operator ReverseMapIterator<const NodePair, const Iter> ()
			{ return (ReverseMapIterator<NodePair, Iter>(this->_itor)); }
			
			bool operator!=(ReverseMapIterator<NodePair, Iter> rhs)
			{
				return this->_itor != rhs._itor;
			}
			bool operator==(ReverseMapIterator<NodePair, Iter> rhs)
			{
				return this->_itor == rhs._itor;
			}

			bool operator==(ReverseMapIterator<const NodePair, const Iter> rhs) const
			{
				return this->_itor == rhs._itor;
			}
			bool operator!=(ReverseMapIterator<const NodePair, const Iter> rhs) const
			{
				return this->_itor != rhs._itor;
			}
	};

}

#endif
