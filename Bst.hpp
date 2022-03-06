#ifndef BST_HPP
# define BST_HPP

#include <iostream>
#include "Maptools.hpp"

namespace ft
{
	template < class Key, class T, class Compare >
	class Bst
	{
		private:
			Bst*	_parent;
			Bst*	_left;
			Bst*	_right;
			int		_nb_nodes;

			ft::pair<Key, T> _pr;

		public:

			Bst( void ) : _parent(NULL), _left(NULL), _right(NULL)
			, _nb_nodes(0), _pr(NULL) {}

			Bst( ft::pair(Key, T) pr, Bst *parent ) : _parent(parent)
			, _left(NULL), _right(NULL), _nb_nodes(0), _pr(pr) {}

			virtual ~Bst( void ) {}

			Bst(Bst const & src);

			Bst& operator=(Bst const & rhs);

			void	insertNode(Bst *node, ft::pair<Key, T> pr, Bst *parent)
			{
				if (!node)
				{
					node(ft::make_pair<Key, T>(pr.first, pr.second), parent);
					balance_tree();
				}
				
				if (pr < node._pr)
					insertNode(node->left, pr, node);
				else
					insertNode(node->right, pr, node);
				
			}
			void	deleteNode(ft::pair<Key, T> pr);

			Bst* search(Bst* root, int key)
			{
				// Base Cases: root is null or key is present at root
				if (root == NULL || root->key == key)
				return root;
				
				// Key is greater than root's key
				if (root->key < key)
				return search(root->right, key);
			
				// Key is smaller than root's key
				return search(root->left, key);
			}
	};
}

#endif
	