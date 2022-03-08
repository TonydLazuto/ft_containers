#ifndef AVL_HPP
# define AVL_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Bst.hpp"

namespace ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
	class Avl
	{
		private:
			Alloc			_alloc;
			Node<Key, T>*	_root;
			int				_nb_nodes;

		public:
			Avl( void ) : _root(NULL), _alloc(NULL), _nb_nodes(0) {}

			virtual ~Avl( void ) {}

			Avl(Avl const & src) {}

			Avl& operator=(Avl const & rhs) {}

			bool isTreeEmpty()
			{
				if (root == NULL)
					return true;
				else
					return false;
			}

			// Get Height  
			int getHeight(Node* r)
			{
				if (r == NULL)
					return -1;
				else
				{
					/* compute the height of each subtree */
					int lheight = getHeight(r -> left);
					int rheight = getHeight(r -> right);

					/* use the larger one */
					if (lheight > rheight)
						return (lheight + 1);
					else
						return (rheight + 1);
				}
			}

			// Get Balance factor of node N
			int getBalanceFactor(TreeNode * n)
			{
				if (n == NULL)
					return (-1);
				return (height(n -> left) - height(n -> right));
			}

			Node* rightRotate(Node* y)
			{
				Node* x = y -> left;
				Node* grand_child = x -> right;

				// Perform rotation  
				x -> right = y;
				y -> left = grand_child;

				return x;
			}

			Node* leftRotate(Node* x)
			{
				Node* y = x -> right;
				Node* grand_child = y -> left;

				// Perform rotation  
				y -> left = x;
				x -> right = grand_child;

				return y;
			}

			TreeNode* insert(TreeNode* r, TreeNode* new_node)
			{
				if (r == NULL)
				{
					r = new_node;
					cout << "Value inserted successfully" << endl;
					return r;
				}

				if (new_node -> value < r -> value)
					r -> left = insert(r -> left, new_node);
				else if (new_node -> value > r -> value)
					r -> right = insert(r -> right, new_node);
				else
				{
					cout << "No duplicate values allowed!" << endl;
					return r;
				}

				int bf = getBalanceFactor(r);
				// Left Left Case  
				if (bf > 1 && new_node -> value < r -> left -> value)
					return rightRotate(r);

				// Right Right Case  
				if (bf < -1 && new_node -> value > r -> right -> value)
					return leftRotate(r);

				// Left Right Case  
				if (bf > 1 && new_node -> value > r -> left -> value)
				{
				r -> left = leftRotate(r -> left);
					return rightRotate(r);
				}

				// Right Left Case  
				if (bf < -1 && new_node -> value < r -> right -> value)
				{
				r -> right = rightRotate(r -> right);
					return leftRotate(r);
				}

				/* return the (unchanged) node pointer */
				return r;

			}
			/*
			void	insertNode(Node *node, ft::pair<Key, T> pr, Node *parent)
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

			Node* search(Node* root, int key)
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
			*/
	};
}

#endif
