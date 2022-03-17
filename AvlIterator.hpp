#ifndef AVLITERATOR_HPP
# define AVLITERATOR_HPP

#include <iostream>
#include <iterator>
#include "AvlTree.hpp"

namespace ft 
{
	template < class T, class Pair >
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
			Pair& operator*(void) { return (this->_itor->pr); }
			Pair* operator->(void) { return &(this->operator*()); }
			
			AvlIterator& operator++(void)
			{
				// std::cout << "--- START pre incr ---" << std::endl;
				Pair	save = _itor->pr;
				
				if (_itor)
				{
					if (!_itor->right && _itor->parent) // _itor == LeftChild || RightChild
					{
						while (_itor->pr <= save && _itor->parent)
							_itor = _itor->parent;
					}
					else if (_itor->right) // _itor == Parent
					{
						_itor = _itor->right;
						while (_itor->left)
						{
							_itor = _itor->left;
						}
					}
				}
				// std::cout << "--- END pre incr ---" << std::endl;
				return *this;
			}

			AvlIterator operator++(int)
			{
				std::cout << "post incr" << std::endl;
				AvlIterator tmp = operator++();
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
				AvlIterator tmp = operator--();
				return tmp;
			}

	};
	template <typename T, typename Pair>
	bool operator==(ft::AvlIterator<T,Pair> lhs,
		ft::AvlIterator<T,Pair> rhs)
	{
		std::cout << "lhs.first: " << lhs->first << std::endl;
		std::cout << "lhs.second: " << lhs->second << std::endl;
		std::cout << "rhs.first: " << rhs->first << std::endl;
		std::cout << "rhs.second: " << rhs->second << std::endl;
		return (*lhs == *rhs);
	}

	template<typename T_L, typename T_R, typename Pair>
	bool operator==(ft::AvlIterator<T_L,Pair> lhs,
		ft::AvlIterator<T_R,Pair> rhs)
	{
		return (*lhs == *rhs);
	}

	template <typename T, typename Pair>
	bool operator!=(ft::AvlIterator<T,Pair> lhs,
		ft::AvlIterator<T,Pair> rhs)
	{
		return (*lhs != *rhs);
	}

	template<typename T_L, typename T_R, typename Pair>
	bool operator!=(ft::AvlIterator<T_L,Pair> lhs,
		ft::AvlIterator<T_R,Pair> rhs)
	{
		return (*lhs != *rhs);
	}
}

#endif
