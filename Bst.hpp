#ifndef Node_HPP
# define Node_HPP

#include <iostream>
#include "Maptools.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key> >
	class Node
	{
		public:

			Node*			_left;
			Node*			_right;
			pair<Key, T>	_pr;

			Node( void ) : _left(NULL), _right(NULL), _pr() {}

			Node( ft::pair<Key, T> pr() ) : _left(NULL), _right(NULL)
			, _pr(pr) {}

			virtual ~Node( void ) {}

			Node(Node const & src)
			{
				_left = src._left;
				_right = src._right;
				_pr(src._pr);
			}

			Node& operator=(Node const & rhs)
			{
				_left = rhs._left;
				_right = rhs._right;
				_pr(rhs._pr);
				return *this;
			}
	};
}

#endif
