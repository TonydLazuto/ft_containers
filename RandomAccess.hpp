#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include "Iterator.hpp"

namespace ft 
{
	template <class T>
	class RandomAccessIterator : public ft::Iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
			T*	_itor;

		public:
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;

			RandomAccessIterator( void ) : _itor(NULL) {}
			RandomAccessIterator(pointer itor) : _itor(itor) {}
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

			value_type operator*(void) { return (*this->_itor); }
			pointer operator->(void) { return &(this->operator*()); }

			RandomAccessIterator operator++(void)
			{
				RandomAccessIterator tmp = *this;
				++(*(this->_itor));
				return tmp;
			}
			RandomAccessIterator& operator++(int)
			{
				this->_itor++;
				return *this;
			}
			
			RandomAccessIterator operator--(void)
			{
				RandomAccessIterator tmp = *this;
				--(*(this->_itor));
				return tmp;
			}
			RandomAccessIterator& operator--(int)
			{
				this->_itor--;
				return *this;
			}
			
			RandomAccessIterator operator+(difference_type n) const
			{
				return (this->_itor + n);
			}
			RandomAccessIterator operator-(difference_type n) const
			{
				return (this->_itor - n);
			}
			difference_type operator-(RandomAccessIterator const &rhs) const
			{
				return (this->_itor - rhs._itor);
			}

			RandomAccessIterator operator+=(difference_type n)
			{
				this->_itor += n;
				return *this;
			}
			RandomAccessIterator operator-=(difference_type n)
			{
				this->_itor -= n;
				return *this;
			}

			reference operator[](difference_type n) { return (*(operator+(n))); }
			
			bool operator==(RandomAccessIterator const &rhs) { return (this->_itor == rhs._itor); }
			bool operator!=(RandomAccessIterator const &rhs) { return (this->_itor != rhs._itor); }
			bool operator<(RandomAccessIterator const &rhs) { return (this->_itor < rhs._itor); }
			bool operator>(RandomAccessIterator const &rhs) { return (this->_itor > rhs._itor); }
			bool operator<=(RandomAccessIterator const &rhs) { return (this->_itor <= rhs._itor); }
			bool operator>=(RandomAccessIterator const &rhs) { return (this->_itor >= rhs._itor); }
	};


	

}

#endif
