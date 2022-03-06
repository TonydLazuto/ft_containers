#ifndef BIDERECTIONALITERATOR_HPP
# define BIDERECTIONALITERATOR_HPP

#include <iostream>
#include <iterator>

namespace ft 
{
	template <class T>
	class BiderectionalIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		private:
			T*	_itor;
		
		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::reference			reference;

			BiderectionalIterator( void ) : _itor(NULL) {}
			BiderectionalIterator( BiderectionalIterator itor ) : _itor(itor) {}
			virtual ~BiderectionalIterator( void ) {}
			BiderectionalIterator(BiderectionalIterator const & src) : _itor(src._itor) {}
			RandomAccessIterator& operator=(RandomAccessIterator const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}

			BiderectionalIterator* operator*(void) { return (*this->_itor); }
			pointer operator->(void) { return &(this->operator*()); }

			BiderectionalIterator& operator++(void)
			{
				this->_itor++;
				return *this;
			}
			BiderectionalIterator operator++(int)
			{
				BiderectionalIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			
			BiderectionalIterator& operator--(void)
			{
				this->_itor--;
				return *this;
			}
			BiderectionalIterator operator--(int)
			{
				BiderectionalIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}

	};

	template <typename T>
	bool operator==(const ft::BiderectionalIterator<T> lhs,
		const ft::BiderectionalIterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator==(const ft::BiderectionalIterator<T_L> lhs,
		const ft::BiderectionalIterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const ft::BiderectionalIterator<T> lhs,
		const ft::BiderectionalIterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator!=(const ft::BiderectionalIterator<T_L> lhs,
		const ft::BiderectionalIterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

}

#endif
