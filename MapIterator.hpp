#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

#include <iostream>
#include <iterator>
#include "AvlTree.hpp"

namespace ft 
{
	template < class Node >
	class MapIterator
	{
		private:
			Node*	_itor;

		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::iterator_category	iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::difference_type		difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::pointer				pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::reference			reference;
			typedef typename Node::value_type													NodePair;

			MapIterator( void ) : _itor(NULL) {}
			MapIterator( pointer itor ) : _itor(itor) {}
			virtual ~MapIterator( void ) {}
			MapIterator(MapIterator const & src) : _itor(src._itor) {}
			MapIterator& operator=(MapIterator const & rhs)
			{
				this->_itor = rhs._itor;
				return *this;
			}
			NodePair& operator*(void) { return (this->_itor->pr); }
			NodePair* operator->(void) { return &(this->operator*()); }
			
			MapIterator& operator++(void)
			{
				// std::cout << "--- START pre incr ---" << std::endl;
				NodePair	save = _itor->pr;

				// std::cout << "_itor.first: " << _itor->pr.first << std::endl;
				// std::cout << "_itor.second: " << _itor->pr.second << std::endl;
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
						while (_itor->left)
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
				MapIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			
			MapIterator& operator--(void)
			{
				NodePair	save = _itor->pr;

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
				MapIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}

	};
	template <typename Node>
	bool operator==(ft::MapIterator<Node> lhs,
		ft::MapIterator<Node> rhs)
	{
		return (*lhs == *rhs);
	}

	template<typename Node_L, typename Node_R>
	bool operator==(ft::MapIterator<Node_L> lhs,
		ft::MapIterator<Node_R> rhs)
	{
		return (*lhs == *rhs);
	}

	template <typename Node>
	bool operator!=(ft::MapIterator<Node> lhs,
		ft::MapIterator<Node> rhs)
	{
		return (*lhs != *rhs);
	}

	template<typename Node_L, typename Node_R>
	bool operator!=(ft::MapIterator<Node_L> lhs,
		ft::MapIterator<Node_R> rhs)
	{
		return (*lhs != *rhs);
	}
}

#endif
