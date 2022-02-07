#ifndef BIDERECTIONALITERATOR_HPP
# define BIDERECTIONALITERATOR_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft 
{
	class BiderectionalIterator : public IteratorTraits
	{
		private:
			T*	_itor;
			BiderectionalIterator( void ) {}
		public:
			BiderectionalIterator( BiderectionalIterator itor ) : _itor(itor) {}
			virtual ~BiderectionalIterator( void ) {}
			BiderectionalIterator(BiderectionalIterator const & src)
			{
				this->_itor = src._itor;
			}
			BiderectionalIterator& operator=(BiderectionalIterator const & rhs)
			{
				this->_itor = src._itor;
				return *this;
			}

			bool operator==(BiderectionalIterator const &lhs
				, BiderectionalIterator const &rhs) { return (lhs == rhs); }
			bool operator!=(BiderectionalIterator const &lhs
				, BiderectionalIterator const &rhs) { return (lhs != rhs); }

			BiderectionalIterator* operator*(BiderectionalIterator const &src) { return (*this->iterator); }
			BiderectionalIterator& operator=(pointer t)
			{
				this->_itor = t;
				return *this;
			}

			BiderectionalIterator operator++(void)
			{
				BiderectionalIterator tmp = *this;
				++*this->_itor;
				return tmp;
			}
			BiderectionalIterator& operator++(void)
			{
				this->_itor++;
				return *this;
			}
			BiderectionalIterator& operator++(void)
			{
				*(this->_itor)++;
				return *this;
			}
			
			BiderectionalIterator operator--(void)
			{
				BiderectionalIterator tmp = *this;
				--*this->_itor;
				return tmp;
			}
			BiderectionalIterator& operator--(void)
			{
				this->_itor--;
				return *this;
			}
			BiderectionalIterator& operator--(void)
			{
				*(this->_itor)--;
				return *this;
			}

			
	};
}

#endif
