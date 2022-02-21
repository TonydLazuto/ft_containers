#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include <iterator>

namespace ft 
{
	template <class T>
	class RandomAccessIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		private:
			T*	_itor;

		public:
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
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

			pointer base() const { return this->_itor; }
			reference operator*(void) { return (*this->_itor); }
			pointer operator->(void) { return &(this->operator*()); }

			RandomAccessIterator operator++(void)
			{
				RandomAccessIterator tmp = *this;
				this->_itor++;
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
				this->_itor--;
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

			reference operator[](difference_type n) { return (*(this->_itor + n)); }
			
			bool operator==(RandomAccessIterator const &rhs) { return (this->_itor == rhs._itor); }
			bool operator!=(RandomAccessIterator const &rhs) { return (this->_itor != rhs._itor); }
			bool operator<(RandomAccessIterator const &rhs) { return (this->_itor < rhs._itor); }
			bool operator>(RandomAccessIterator const &rhs) { return (this->_itor > rhs._itor); }
			bool operator<=(RandomAccessIterator const &rhs) { return (this->_itor <= rhs._itor); }
			bool operator>=(RandomAccessIterator const &rhs) { return (this->_itor >= rhs._itor); }
	};


	template <class T>
	class RandomAccessIterator<const T> : public std::iterator<std::random_access_iterator_tag, T>
	{
		private:
			const T*	_itor;

		public:
			typedef typename std::iterator<std::random_access_iterator_tag, const T>::iterator_category		iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, const T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, const T>::difference_type		difference_type;
			typedef const T*																				pointer;
			typedef const T&																				reference;

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

			pointer base() const { return this->_itor; }
			reference operator*(void) { return (*this->_itor); }
			pointer operator->(void) { return &(this->operator*()); }

			RandomAccessIterator operator++(void)
			{
				RandomAccessIterator tmp = *this;
				this->_itor++;
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
				this->_itor--;
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

			reference operator[](difference_type n) { return (*(this->_itor + n)); }
			
			bool operator==(RandomAccessIterator const &rhs) { return (this->_itor == rhs._itor); }
			bool operator!=(RandomAccessIterator const &rhs) { return (this->_itor != rhs._itor); }
			bool operator<(RandomAccessIterator const &rhs) { return (this->_itor < rhs._itor); }
			bool operator>(RandomAccessIterator const &rhs) { return (this->_itor > rhs._itor); }
			bool operator<=(RandomAccessIterator const &rhs) { return (this->_itor <= rhs._itor); }
			bool operator>=(RandomAccessIterator const &rhs) { return (this->_itor >= rhs._itor); }
	};

}

#endif
