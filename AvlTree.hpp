#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Bst.hpp"
#include "Map.hpp"

#define SPACE 10

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key> >
	class AvlTree
	{
		// friend class TestAvlTree;
		template<>
		friend class ft::map<Key, T>;
		private:
			typedef Node<Key, T>	NodeTree;
			NodeTree*				_root;

			// Get Height  
			int getHeight(NodeTree* r)
			{
				if (r == NULL)
					return -1;
				else
				{
					/* compute the height of each subtree */
					int lheight = getHeight(r->_left);
					int rheight = getHeight(r->_right);
					/* use the larger one */
					if (lheight > rheight)
						return (lheight + 1);
					else
						return (rheight + 1);
				}
			}

			// Get Balance factor of NodeTree N
			int getBalanceFactor(NodeTree* n)
			{
				if (n == NULL)
					return (-1);
				return (getHeight(n->_left) - getHeight(n->_right));
			}

			NodeTree* minValueNode(NodeTree* node)
			{
				NodeTree* minNodeTree = node;
				/* loop down to find the leftmost leaf */
				while (minNodeTree->_left != NULL)
					minNodeTree = minNodeTree->_left;				
				return minNodeTree;
			}

			NodeTree* rightRotate(NodeTree* y)
			{
				NodeTree* x = y->_left;
				NodeTree* grand_child = x->_right;

				// Perform rotation  
				x->_right = y;
				y->_left = grand_child;
				return x;
			}

			NodeTree* leftRotate(NodeTree* x)
			{
				NodeTree* y = x->_right;
				NodeTree* grand_child = y->_left;

				// Perform rotation  
				y->_left = x;
				x->_right = grand_child;
				return y;
			}

			NodeTree*	balanceInsert(int bf, NodeTree* r, NodeTree* new_node)
			{
				// Left Left Case
				if (bf > 1 && new_node->_pr < r->_left->_pr)
					return rightRotate(r);
				// Right Right Case  
				if (bf < -1 && new_node->_pr > r->_right->_pr)
					return leftRotate(r);
				// Left Right Case  
				if (bf > 1 && new_node->_pr > r->_left->_pr)
				{
					r->_left = leftRotate(r->_left);
						return rightRotate(r);
				}
				// Right Left Case  
				if (bf < -1 && new_node->_pr < r->_right->_pr)
				{
					r->_right = rightRotate(r->_right);
						return leftRotate(r);
				}
				return (r);
			}

			NodeTree*	balanceDeletion(int bf, NodeTree* r)
			{
				// Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && getBalanceFactor(r->_left) >= 0)
					return rightRotate(r);
				// Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && getBalanceFactor(r->_left) == -1)
				{
					r->_left = leftRotate(r->_left);
					return rightRotate(r);
				}
				// Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && getBalanceFactor(r->_right) <= 0)
					return leftRotate(r);
				// Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && getBalanceFactor(r->_right) == 1)
				{
					r->_right = rightRotate(r->_right);
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

			void print2D(NodeTree* r, int space) {
				if (r == NULL) // Base case  1
					return;
				space += SPACE; // Increase distance between levels   2
				print2D(r->_right, space); // Process right child first 3 
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++) // 5 
					std::cout << " "; // 5.1  
				std::cout << "Key="<< r->_pr.first << ", Val=" << r->_pr.second << "\n"; // 6
				print2D(r->_left, space); // Process left child  7
			}

			bool isTreeEmpty()
			{
				if (_root == NULL)
					return true;
				else
					return false;
			}

			NodeTree* recursiveSearch(NodeTree* r, ft::pair<Key, T>& pr) //value_type instead of ft::pair()
			{
				if (r->_pr == pr)
					return r;
				if (r == NULL)
					return NULL;
				else if (pr < r->_pr)
					return recursiveSearch(r->_left, pr);
				else if (pr > r->_pr)
					return recursiveSearch(r->_right, pr);
				return r; // NULL
			}

			NodeTree* insertNode(NodeTree* r, NodeTree* new_node)
			{
				if (r == NULL)
				{
					// deallocate + allocate + construct in MAP!
					r = new_node;
					std::cout << "Value inserted successfully" << std::endl;
					return r;
				}
				if (new_node->_pr < r->_pr)
					r->_left = insertNode(r->_left, new_node);
				else if (new_node->_pr > r->_pr)
					r->_right = insertNode(r->_right, new_node);
				else
				{
					std::cout << "Value already exists!" << std::endl;
					return r;
				}
				int bf = getBalanceFactor(r);
				r = balanceInsert(bf, r, new_node);

				return r;

			}

			NodeTree* deleteNode(NodeTree* r, ft::pair<Key, T>& pr) {
				// base case 
				if (r == NULL)
					return NULL;
				else if (pr < r->_pr)
					r->_left = deleteNode(r->_left, pr);
				else if (pr > r->_pr)
					r->_right = deleteNode(r->_right, pr);
				else
				{
					// NodeTree with only one child or no child 
					if (r->_left == NULL)
					{
						NodeTree* temp = r->_right;
						return temp; //destroy
					}
					else if (r->_right == NULL)
					{
						NodeTree* temp = r->_left;
						return temp; //destroy
					}
					else
					{
						// NodeTree with two children: Get the inorder successor (smallest 
						// in the right subtree) 
						NodeTree* min_right = minValueNode(r->_right);
						// Copy the inorder successor's content to this NodeTree 
						r->_pr = min_right->_pr;
						// Delete the inorder successor 
						r->_right = deleteNode(r->_right, min_right->_pr);
						//deleteNode(r->_right, min_right->_pr); 
					}
				}

				int bf = getBalanceFactor(r);
				r = balanceDeletion(bf, r);
				return r;
			}
	};
}

#endif
