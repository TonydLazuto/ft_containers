#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Nullptr.hpp"

template < class Key, class T >
class Node
{
	public:

		Node*		parent;
		Node*		left;
		Node*		right;
		ft::pair<Key, T>	pr;
		

		Node( void ) : left(NULL), right(NULL), pr() {}

		Node( Node<Key, T>* theparent, ft::pair<Key, T> a_pr )
		: parent(theparent), left(NULL), right(NULL), pr(a_pr) {}

		virtual ~Node( void ) {}

		Node(Node const & src)
		{
			parent = src.parent;
			left = src.left;
			right = src.right;
			pr = src.pr;
		}

		Node& operator=(Node const & rhs)
		{
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			pr = rhs.pr;
			return *this;
		}
};

#endif
