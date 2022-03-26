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
			NodePair& operator*(void) const { return (this->_itor->pr); }
			NodePair* operator->(void) const { return &(this->operator*()); }
			
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
			// operator MapIterator<const Node> () const
			// { return (MapIterator<const Node>(this->_itor)); }
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

	template < class Node >
	class MapConstIterator
	{
		private:
			const Node*	_itor;

		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::iterator_category	iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::value_type			value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::difference_type		difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::pointer				pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, Node>::reference			reference;
			typedef typename Node::value_type															NodePair;

			MapConstIterator( void ) : _itor(NULL) {}
			MapConstIterator( pointer itor ) : _itor(itor) {}
			virtual ~MapConstIterator( void ) {}
			MapConstIterator(MapConstIterator const & src) : _itor(src._itor) {}
			MapConstIterator& operator=(MapConstIterator const & rhs)
			{
				this->_itor = rhs._itor;
				return *this;
			}
			const NodePair& operator*(void) const { return (this->_itor->pr); }
			const NodePair* operator->(void) const { return &(this->operator*()); }
			
			const MapConstIterator& operator++(void)
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

			const  MapConstIterator operator++(int)
			{
				MapConstIterator tmp = *this;
				tmp._itor = this->_itor++;
				return tmp;
			}
			
			const  MapConstIterator& operator--(void)
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
			const MapConstIterator operator--(int)
			{
				MapConstIterator tmp = *this;
				tmp._itor = this->_itor--;
				return tmp;
			}
	};
	template <typename Node>
	bool operator==(ft::MapConstIterator<Node> lhs,
		ft::MapConstIterator<Node> rhs)
	{
		return (*lhs == *rhs);
	}

	template<typename Node_L, typename Node_R>
	bool operator==(ft::MapConstIterator<Node_L> lhs,
		ft::MapConstIterator<Node_R> rhs)
	{
		return (*lhs == *rhs);
	}

	template <typename Node>
	bool operator!=(ft::MapConstIterator<Node> lhs,
		ft::MapConstIterator<Node> rhs)
	{
		return (*lhs != *rhs);
	}

	template<typename Node_L, typename Node_R>
	bool operator!=(ft::MapConstIterator<Node_L> lhs,
		ft::MapConstIterator<Node_R> rhs)
	{
		return (*lhs != *rhs);
	}
}

#endif
