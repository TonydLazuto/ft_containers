#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Nullptr.hpp"

template < class Key, class T, class Compare = ft::less<Key> >
class Node
{
	public:

		Node*				parent;
		Node*				left;
		Node*				right;
		ft::pair<Key, T>	pr;
		

		Node( void ) : left(NULL), right(NULL), pr() {}

		Node( ft::pair<Key, T> a_pr ) : left(NULL), right(NULL)
		, pr(a_pr) {}

		virtual ~Node( void ) {}

		Node(Node const & src)
		{
			left = src.left;
			right = src.right;
			pr(src.pr);
		}

		Node& operator=(Node const & rhs)
		{
			left = rhs.left;
			right = rhs.right;
			pr(rhs.pr);
			return *this;
		}
};

#endif
