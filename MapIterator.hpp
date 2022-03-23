#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

#include <iostream>
#include <iterator>
#include "AvlTree.hpp"

namespace ft 
{
	template < class T, class Pair >
	class MapIterator
	{
		private:
			T*	_itor;

		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::reference			reference;

			MapIterator( void ) : _itor(NULL) {}
			MapIterator( pointer itor ) : _itor(itor) {}
			virtual ~MapIterator( void ) {}
			MapIterator(MapIterator const & src) : _itor(src._itor) {}
			MapIterator& operator=(MapIterator const & rhs)
			{
				this->_itor = rhs._itor;
				return *this;
			}
			Pair& operator*(void) { return (this->_itor->pr); }
			Pair* operator->(void) { return &(this->operator*()); }
			
			MapIterator& operator++(void)
			{
				// std::cout << "--- START pre incr ---" << std::endl;
				Pair	save = _itor->pr;

				if (_itor)
				{
					if (!_itor->right && _itor->parent)
					{
						while (_itor->pr <= save && _itor->parent)
							_itor = _itor->parent;
					}
					else if (_itor->right) // _itor == Parent
					{
						_itor = _itor->right;
						while (_itor && _itor->left)
							_itor = _itor->left;
					}
				}
				// std::cout << "_itor.first: " << _itor->pr.first << std::endl;
				// std::cout << "_itor.second: " << _itor->pr.second << std::endl;
				// std::cout << "--- END pre incr ---" << std::endl;
				return *this;
			}

			MapIterator operator++(int)
			{
				MapIterator tmp = operator++();
				return tmp;
			}
			
			MapIterator& operator--(void)
			{
				Pair	save = _itor->pr;

				if (_itor)
				{
					// _itor == LeftChild || _itor == RightChild
					if (!_itor->left && _itor->parent)
					{
						if (_itor->getEndNode()->pr == save)
							_itor = _itor->parent;
						else
							while (_itor->pr >= save && _itor->parent)
								_itor = _itor->parent;
						}
					else if (_itor->left) // _itor == Parent
					{
						_itor = _itor->left;
						while (_itor->right)
							_itor = _itor->right;
					}
				}
				return *this;
			}
			MapIterator operator--(int)
			{
				MapIterator tmp = operator--();
				return tmp;
			}

	};
	template <typename T, typename Pair>
	bool operator==(ft::MapIterator<T,Pair> lhs,
		ft::MapIterator<T,Pair> rhs)
	{
		return (*lhs == *rhs);
	}

	template<typename T_L, typename T_R, typename Pair>
	bool operator==(ft::MapIterator<T_L,Pair> lhs,
		ft::MapIterator<T_R,Pair> rhs)
	{
		return (*lhs == *rhs);
	}

	template <typename T, typename Pair>
	bool operator!=(ft::MapIterator<T,Pair> lhs,
		ft::MapIterator<T,Pair> rhs)
	{
		return (*lhs != *rhs);
	}

	template<typename T_L, typename T_R, typename Pair>
	bool operator!=(ft::MapIterator<T_L,Pair> lhs,
		ft::MapIterator<T_R,Pair> rhs)
	{
		return (*lhs != *rhs);
	}
}

#endif
