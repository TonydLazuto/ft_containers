#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"

#define SPACE 10

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< pair<const Key, T> >  >
	class AvlTree
	{
		friend class TestAvlTree;
		private:
			typedef struct s_node {
				struct s_node*		left;
				struct s_node*		right;
				ft::pair<Key, T>	pr;
			}				t_node;

			t_node*		_root;

			// Get Height
			int getHeight(t_node* r)
			{
				if (r == NULL)
					return -1;
				else
				{
					/* compute the height of each subtree */
					int lheight = getHeight(r->left);
					int rheight = getHeight(r->right);
					/* use the larger one */
					if (lheight > rheight)
						return (lheight + 1);
					else
						return (rheight + 1);
				}
			}

			// Get Balance factor of t_node N
			int getBalanceFactor(t_node* n)
			{
				if (n == NULL)
					return (-1);
				return (getHeight(n->left) - getHeight(n->right));
			}

			t_node* minValueNode(t_node* node)
			{
				t_node* mint_node = node;
				/* loop down to find the leftmost leaf */
				while (mint_node->left != NULL)
					mint_node = mint_node->left;				
				return mint_node;
			}

			t_node* rightRotate(t_node* y)
			{
				t_node* x = y->left;
				t_node* grand_child = x->right;

				// Perform rotation  
				x->right = y;
				y->left = grand_child;
				return x;
			}

			t_node* leftRotate(t_node* x)
			{
				t_node* y = x->right;
				t_node* grand_child = y->left;

				// Perform rotation  
				y->left = x;
				x->right = grand_child;
				return y;
			}

			t_node*	balanceInsert(int bf, t_node* r, t_node* new_node)
			{
				// Left Left Case
				if (bf > 1 && new_node->pr < r->left->pr)
					return rightRotate(r);
				// Right Right Case  
				if (bf < -1 && new_node->pr > r->right->pr)
					return leftRotate(r);
				// Left Right Case  
				if (bf > 1 && new_node->pr > r->left->pr)
				{
					r->left = leftRotate(r->left);
						return rightRotate(r);
				}
				// Right Left Case  
				if (bf < -1 && new_node->pr < r->right->pr)
				{
					r->right = rightRotate(r->right);
						return leftRotate(r);
				}
				return (r);
			}

			t_node*	balanceDeletion(int bf, t_node* r)
			{
				// Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && getBalanceFactor(r->left) >= 0)
					return rightRotate(r);
				// Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && getBalanceFactor(r->left) == -1)
				{
					r->left = leftRotate(r->left);
					return rightRotate(r);
				}
				// Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && getBalanceFactor(r->right) <= 0)
					return leftRotate(r);
				// Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && getBalanceFactor(r->right) == 1)
				{
					r->right = rightRotate(r->right);
					return leftRotate(r);
				}
				return (r);
			}

		public:
			AvlTree( void ) : _root(NULL) {}

			virtual ~AvlTree( void ) {}

			AvlTree(AvlTree const & src)
			{
				_root = src._root;
			}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				return *this;
			}

			void print2D(t_node* r, int space) {
				if (r == NULL) // Base case  1
					return;
				space += SPACE; // Increase distance between levels   2
				print2D(r->right, space); // Process right child first 3 
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++) // 5 
					std::cout << " "; // 5.1  
				std::cout << "Key="<< r->pr.first << ", Val=" << r->pr.second << "\n"; // 6
				print2D(r->left, space); // Process left child  7
			}

			bool isTreeEmpty()
			{
				if (_root == NULL)
					return true;
				else
					return false;
			}

			t_node* recursiveSearch(t_node* r, ft::pair<Key, T>& pr)
			{
				if (r->pr == pr)
					return r;
				if (r == NULL)
					return NULL;
				else if (pr < r->pr)
					return recursiveSearch(r->left, pr);
				else if (pr > r->pr)
					return recursiveSearch(r->right, pr);
				return r; // NULL
			}

			t_node* insertNode(t_node* r, t_node* new_node)
			{
				if (r == NULL)
				{
					// deallocate + allocate + construct in MAP!
					r = new_node;
					std::cout << "Value inserted successfully" << std::endl;
					return r;
				}
				if (new_node->pr < r->pr)
					r->left = insertNode(r->left, new_node);
				else if (new_node->pr > r->pr)
					r->right = insertNode(r->right, new_node);
				else
				{
					std::cout << "Value already exists!" << std::endl;
					return r;
				}
				int bf = getBalanceFactor(r);
				r = balanceInsert(bf, r, new_node);

				return r;

			}

			t_node* deleteNode(t_node* r, ft::pair<Key, T>& pr) {
				// base case 
				if (r == NULL)
					return NULL;
				else if (pr < r->pr)
					r->left = deleteNode(r->left, pr);
				else if (pr > r->pr)
					r->right = deleteNode(r->right, pr);
				else
				{
					// t_node with only one child or no child 
					if (r->left == NULL)
					{
						t_node* temp = r->right;
						delete temp;
						return temp; //destroy
					}
					else if (r->right == NULL)
					{
						t_node* temp = r->left;
						return temp; //destroy
					}
					else
					{
						// t_node with two children: Get the inorder successor (smallest 
						// in the right subtree) 
						t_node* minright = minValueNode(r->right);
						// Copy the inorder successor's content to this t_node 
						r->pr = minright->pr;
						// Delete the inorder successor 
						r->right = deleteNode(r->right, minright->pr);
						//deleteNode(r->right, minright->pr); 
					}
				}

				int bf = getBalanceFactor(r);
				r = balanceDeletion(bf, r);
				return r;
			}
	};
}

#endif
