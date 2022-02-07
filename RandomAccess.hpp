#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft 
{
	template <class T>
	class RandomAccessIterator : public IteratorTraits
	{
		private:
			T*	_itor;
			RandomAccessIterator( void ) {}
		public:
			RandomAccessIterator( RandomAccessIterator itor ) : _itor(itor) {}
			virtual ~RandomAccessIterator( void ) {}
			RandomAccessIterator(RandomAccessIterator const & src)
			{
				this->_itor = src._itor;
			}
			RandomAccessIterator& operator=(RandomAccessIterator const & rhs)
			{
				this->_itor = src._itor;
				return *this;
			}

			bool operator==(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs == rhs); }
			bool operator!=(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs != rhs); }

			RandomAccessIterator* operator*(RandomAccessIterator const &src) { return (*this->iterator); }
			RandomAccessIterator& operator=(pointer t)
			{
				this->_itor = t;
				return *this;
			}

			RandomAccessIterator operator++(void)
			{
				RandomAccessIterator tmp = *this;
				++*this->_itor;
				return tmp;
			}
			RandomAccessIterator& operator++(void)
			{
				this->_itor++;
				return *this;
			}
			RandomAccessIterator& operator++(void)
			{
				*(this->_itor)++;
				return *this;
			}
			
			RandomAccessIterator operator--(void)
			{
				RandomAccessIterator tmp = *this;
				--*this->_itor;
				return tmp;
			}
			RandomAccessIterator& operator--(void)
			{
				this->_itor--;
				return *this;
			}
			RandomAccessIterator& operator--(void)
			{
				*(this->_itor)--;
				return *this;
			}
			
			RandomAccessIterator operator+(int n)
			{
				return this->_itor + n;
			}
			RandomAccessIterator operator-(int n)
			{
				return this->_itor - n;
			}
			RandomAccessIterator operator-(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs)
			{
				return lhs - rhs;
			}
			bool operator<(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs < rhs); }
			bool operator>(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs > rhs); }
			bool operator<=(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs <= rhs); }
			bool operator>=(RandomAccessIterator const &lhs
				, RandomAccessIterator const &rhs) { return (lhs >= rhs); }

			RandomAccessIterator operator+=(int n)
			{
				this->_itor += n;
				return *this;
			}
			RandomAccessIterator operator-=(int n)
			{
				this->_itor -= n;
				return *this;
			}
	};
}

#endif
