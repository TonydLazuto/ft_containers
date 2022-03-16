#ifndef AVLITERATOR_HPP
# define AVLITERATOR_HPP

#include <iostream>
#include <iterator>
#include "AvlTree.hpp"

namespace ft 
{
	template < class T >
	class AvlIterator
	{
		private:
			T*	_itor;

		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::reference			reference;

			AvlIterator( void ) : _itor(NULL) {}
			AvlIterator( pointer itor ) : _itor(itor) {}
			virtual ~AvlIterator( void ) {}
			AvlIterator(AvlIterator const & src) : _itor(src._itor) {}
			AvlIterator& operator=(AvlIterator const & rhs)
			{
				if (*this != rhs)
					this->_itor = rhs._itor;
				return *this;
			}
			AvlIterator* operator*(void) { return (*this->_itor->pr); }
			pointer operator->(void) { return &(this->operator*()); }
			
			AvlIterator& operator++(void)
			{
				if (_itor->right)
					_itor = _itor->right;
				else
				{
					while (_itor->parent && !_itor->right)
						_itor = _itor->parent;
					_itor = _itor->right;
				}
				return *this;
			}
			AvlIterator operator++(int)
			{
				AvlIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			
			AvlIterator& operator--(void)
			{
				if (_itor->left)
					_itor = _itor->left;
				else
				{
					while (_itor->parent && !_itor->left)
						_itor = _itor->parent;
					_itor = _itor->left;
				}
				return *this;
			}
			AvlIterator operator--(int)
			{
				AvlIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}

	};
	template <typename T>
	bool operator==(const ft::AvlIterator<T> lhs,
		const ft::AvlIterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator==(const ft::AvlIterator<T_L> lhs,
		const ft::AvlIterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const ft::AvlIterator<T> lhs,
		const ft::AvlIterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
	bool operator!=(const ft::AvlIterator<T_L> lhs,
		const ft::AvlIterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif
