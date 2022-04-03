#ifndef RANDOMACCESS_HPP
# define RANDOMACCESS_HPP

#include <iostream>
#include <iterator>

namespace ft 
{
	template <class T>
	class RandomAccessIterator
	{
		private:
			T*	_itor;

		public:
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;

			RandomAccessIterator( void ) : _itor(NULL) {}
			RandomAccessIterator(pointer itor) : _itor(itor) {}
			virtual ~RandomAccessIterator( void ) {}
			RandomAccessIterator(RandomAccessIterator const & src) : _itor(src._itor) {}
			RandomAccessIterator& operator=(RandomAccessIterator const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}

			pointer					base() const { return this->_itor; }
			reference				operator*(void) { return (*this->_itor); }
			pointer					operator->(void) { return &(this->operator*()); }

			RandomAccessIterator&	operator++(void)
			{
				this->_itor++;
				return *this;
			}
			RandomAccessIterator	operator++(int)
			{
				RandomAccessIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			
			RandomAccessIterator&	operator--(void)
			{
				this->_itor--;
				return *this;
			}
			RandomAccessIterator	operator--(int)
			{
				RandomAccessIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}
			
			RandomAccessIterator	operator+(difference_type n) const
			{
				return (this->_itor + n);
			}
			RandomAccessIterator	operator-(difference_type n) const
			{
				return (this->_itor - n);
			}

			RandomAccessIterator&	operator+=(difference_type n)
			{
				this->_itor += n;
				return *this;
			}
			RandomAccessIterator&	operator-=(difference_type n)
			{
				this->_itor -= n;
				return *this;
			}

			reference				operator[](difference_type n) { return (*(this->_itor + n)); }

			operator RandomAccessIterator<const T> () const { return (RandomAccessIterator<const T>(this->_itor)); }

	};

	template <typename T>
	bool operator==(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator==(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator!=(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator<(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator<(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool operator<=(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator<=(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator>(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator>=(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator>=(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	ft::RandomAccessIterator<T>
	operator+(typename ft::RandomAccessIterator<T>::difference_type n,
		typename ft::RandomAccessIterator<T>& rai)
	{
		return (&*(rai + n));
	}
	template <typename T>
	typename ft::RandomAccessIterator<T>::difference_type
	operator-(const ft::RandomAccessIterator<T> lhs,
		const ft::RandomAccessIterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::RandomAccessIterator<T_L>::difference_type
	operator-(const ft::RandomAccessIterator<T_L> lhs,
		const ft::RandomAccessIterator<T_R> rhs)
	{
		return (lhs.base() - rhs.base());
	}

}

#endif
