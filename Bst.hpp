#ifndef Node_HPP
# define Node_HPP

#include <iostream>
#include "Maptools.hpp"

namespace ft
{
	template < class Key, class T >
	class Node
	{
			
		public:

			Node*	_parent;
			Node*	_left;
			Node*	_right;
			int		_bf; // _balance_factor
			ft::pair<Key, T> _pr;

			Node( void ) : _parent(NULL), _left(NULL), _right(NULL)
			, _pr(NULL) {}

			Node( ft::pair(Key, T) pr, Node *parent ) : _parent(parent)
			, _left(NULL), _right(NULL), _pr(pr) {}

			virtual ~Node( void ) {}

			Node(Node const & src)
			{
				_left = src._left;
				_right = src._right;
				_parent = src._parent;
				_bf = src._bf;
				_pr = src._pr;
			}

			Node& operator=(Node const & rhs)
			{
				_left = rhs._left;
				_right = rhs._right;
				_parent = rhs._parent;
				_bf = rhs._bf;
				_pr = rhs._pr;
				return *this;
			}

			
	};
}

#endif
	