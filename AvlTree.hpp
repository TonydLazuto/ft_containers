#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Node.hpp"
#include "Nullptr.hpp"

#define SPACE 10

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key> >
	class AvlTree
	{
		// friend class TestAvlTree;
		template < class Key2, class T2, class Compare2, class Alloc2 >
		friend class map;

		public:
			typedef	Node<Key, T> NodeTree;

			AvlTree( void ) : _root(NULL), _begin(NULL), _end(NULL)
			, _nb_nodes(0) {}

			virtual ~AvlTree( void ) {}

			AvlTree(AvlTree const & src) : _root(src._root)
			, _begin(src._begin), _end(src._end), _nb_nodes(src._nb_nodes) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				_begin = rhs._begin;
				_end = rhs._end;
				_nb_nodes = rhs._nb_nodes;
				return *this;
			}

			NodeTree*	getRoot(void) { return this->_root; }

			NodeTree*	getBegin(void) { return this->_begin; }
			NodeTree*	getEnd(void) { return this->_end; }
			NodeTree*	setBegin(NodeTree* node)
			{
				this->_begin = node;
			}
			NodeTree	*setEnd(NodeTree* node)
			{
				this->_end = node;
			}

			void prinTD(NodeTree* r, int space) {
				if (r == NULL) // Base case  1
					return;
				space += SPACE; // Increase distance between levels   2
				prinTD(r->right, space); // Process right child first 3
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++) // 5
					std::cout << " "; // 5.1
				std::cout << "Key="<< r->pr.first << ", Val=" << r->pr.second << "\n"; // 6
				prinTD(r->left, space); // Process left child  7
			}

			bool isTreeEmpty()
			{
				if (_root == NULL)
					return true;
				else
					return false;
			}

			NodeTree* searchByPair(NodeTree* r, const ft::pair<Key, T>& pr)
			{
				if (r->pr == pr)
					return r;
				if (r == NULL)
					return NULL;
				else if (pr < r->pr)
					return searchByPair(r->left, pr);
				else if (pr > r->pr)
					return searchByPair(r->right, pr);
				return NULL; // NULL
			}

			NodeTree* searchByKey(NodeTree* r, Key k)
			{
				if (r->pr.first && r->pr.first == k)
					return r;
				if (r == NULL)
					return NULL;
				else if (k < r->pr.first)
					return searchByKey(r->left, k);
				else if (k > r->pr.first)
					return searchByKey(r->right, k);
				return NULL; // NULL
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

			NodeTree* deleteNode(NodeTree* r, NodeTree* node) {
				// base case 
				if (r == NULL)
					return NULL;
				else if (node->pr < r->pr)
					r->left = deleteNode(r->left, node);
				else if (node->pr > r->pr)
					r->right = deleteNode(r->right, node);
				else
				{
					// t_node with only one child or no child 
					if (r->left == NULL)
					{
						NodeTree* temp = r->right;
						return temp; //to_destroy
					}
					else if (r->right == NULL)
					{
						NodeTree* temp = r->left;
						return temp; //to_destroy
					}
					else
					{
						// t_node with two children: Get the inorder successor (smallest 
						// in the right subtree) 
						NodeTree* minright = minValueNode(r->right);
						// Copy the inorder successor's content to this t_node 
						r->pr = minright->pr;
						// Delete the inorder successor 
						r->right = deleteNode(r->right, minright);
						//deleteNode(r->right, minright->pr); 
					}
				}

				int bf = getBalanceFactor(r);
				r = balanceDeletion(bf, r);
				return r;
			}

		private:

			NodeTree*		_root;
			NodeTree*		_begin;
			NodeTree*		_end;
			size_t			_nb_nodes;
			// alloc_node		_alloc;

			// Get Height
			int getHeight(NodeTree* r)
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
			void	init_node(NodeTree* node)
			{
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
			}

			// Get Balance factor of t_node N
			int getBalanceFactor(NodeTree* n)
			{
				if (n == NULL)
					return (-1);
				return (getHeight(n->left) - getHeight(n->right));
			}

			NodeTree* minValueNode(NodeTree* node)
			{
				NodeTree* min_node = node;
				/* loop down to find the leftmost leaf */
				while (min_node->left != NULL)
					min_node = min_node->left;				
				return min_node;
			}

			NodeTree* maxValueNode(NodeTree* node)
			{
				NodeTree* max_node = node;
				/* loop down to find the rightmost leaf */
				while (max_node->right != NULL)
					max_node = max_node->right;				
				return max_node;
			}

			NodeTree* rightRotate(NodeTree* y)
			{
				NodeTree* x = y->left;
				NodeTree* grand_child = x->right;

				// Perform rotation  
				x->right = y;
				y->left = grand_child;
				return x;
			}

			NodeTree* leftRotate(NodeTree* x)
			{
				NodeTree* y = x->right;
				NodeTree* grand_child = y->left;

				// Perform rotation  
				y->left = x;
				x->right = grand_child;
				return y;
			}

			NodeTree*	balanceInsert(int bf, NodeTree* r, NodeTree* new_node)
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

			NodeTree*	balanceDeletion(int bf, NodeTree* r)
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
	};
}

#endif
