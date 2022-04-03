#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
#include "Maptools.hpp"

template < class Key, class T >
class Node
{
	public:
		typedef ft::pair<Key, T>	value_type;
		Node*						parent;
		Node*						left;
		Node*						right;
		value_type					pr;

		Node( void ) : parent(NULL), left(NULL), right(NULL), pr() {}

		Node( Node<Key, T>* theparent )
		: parent(theparent), left(NULL), right(NULL), pr() {}

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

		Node*	getEndNode(void)
		{
			Node<Key, T>* end_node = &*this;
			/* Go to the rooftop */
			while (end_node && end_node->parent)
				end_node = end_node->parent;
			/* loop down to find the rightmost leaf */
			while (end_node && end_node->right)
				end_node = end_node->right;
			return end_node;
		}
};

#endif
