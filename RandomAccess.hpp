#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include "IteratorTraits.hpp"

namespace ft 
{
	template <class T>
	class RandomAccessIterator
	{
		private:
			T*	_itor;

		public:
			RandomAccessIterator( void ) : _itor(NULL) {}
			RandomAccessIterator(T* itor) : _itor(itor) {}
			virtual ~RandomAccessIterator( void ) {}
			RandomAccessIterator(RandomAccessIterator const & src)
			{
				this->_itor = src._itor;
			}
			RandomAccessIterator& operator=(RandomAccessIterator const & rhs)
			{
				this->_itor = rhs._itor;
				return *this;
			}
		
			bool operator==(RandomAccessIterator const &rhs) { return (this->_itor == rhs._itor); }
			bool operator!=(RandomAccessIterator const &rhs) { return (this->_itor != rhs._itor); }

			RandomAccessIterator* operator*(void) { return (*this->iterator); }
			RandomAccessIterator operator=(T t)
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
			RandomAccessIterator& operator++(int)
			{
				this->_itor++;
				return *this;
			}
			// RandomAccessIterator& operator++(int)
			// {
			// 	*(this->_itor)++;
			// 	return *this;
			// }
			
			RandomAccessIterator operator--(void)
			{
				RandomAccessIterator tmp = *this;
				--*this->_itor;
				return tmp;
			}
			RandomAccessIterator& operator--(int)
			{
				this->_itor--;
				return *this;
			}
			// RandomAccessIterator& operator--(int)
			// {
			// 	*(this->_itor)--;
			// 	return *this;
			// }
			
			RandomAccessIterator operator+(int n)
			{
				return (*this->_itor + n);
			}
			RandomAccessIterator operator-(int n)
			{
				return (*this->_itor - n);
			}
			int operator-(RandomAccessIterator const &rhs)
			{
				return (*this->_itor - *rhs._itor);
			}
			bool operator<(RandomAccessIterator const &rhs) { return (this->_itor < rhs._itor); }
			bool operator>(RandomAccessIterator const &rhs) { return (this->_itor > rhs._itor); }
			bool operator<=(RandomAccessIterator const &rhs) { return (this->_itor <= rhs._itor); }
			bool operator>=(RandomAccessIterator const &rhs) { return (this->_itor >= rhs._itor); }

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
