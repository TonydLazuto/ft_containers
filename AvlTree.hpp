#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Node.hpp"
#include "Nullptr.hpp"

#define SPACE 10

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class AvlTree
	{
		// friend class TestAvlTree;
		template < class Key2, class T2, class Compare2, class Alloc2 >
		friend class map;

		public:
			typedef ft::pair<const Key, T> value_type;
			typedef	Node<Key, T> NodeTree;

			typedef typename Alloc::template rebind<NodeTree>::other alloc_node;


			AvlTree( const alloc_node& alloc = alloc_node() ) : _root(NULL)
			, _begin(NULL), _end(NULL), _nb_nodes(0), _alloc_n(alloc)
			{
				_end = _alloc_n.allocate(1);
				_alloc_n.construct(_end, NodeTree());
				_root = NULL;
				_begin = NULL;
			}

			virtual ~AvlTree( void ) {}

			AvlTree(AvlTree const & src) : _root(src._root), _alloc_n(src._alloc_n)
			, _begin(src._begin), _end(src._end), _nb_nodes(src._nb_nodes) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				_begin = rhs._begin;
				_end = rhs._end;
				_nb_nodes = rhs._nb_nodes;
				_alloc_n = rhs._alloc_n;
				return *this;
			}

			void print2D(NodeTree* r, int space) {
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


			// NodeTree* searchByPair(NodeTree* r, NodeTree *parent, const ft::pair<Key, T>& pr)
			// {
			// 	if (r == NULL)
			// 		return NULL;
			// 	if (pr < r->pr)
			// 	{
			// 		parent = r;
			// 		return searchByPair(r->left, parent, pr);
			// 	}
			// 	else if (pr > r->pr)
			// 	{
			// 		parent = r;
			// 		return searchByPair(r->right, parent, pr);
			// 	}
			// 	return r;
			// }

			NodeTree* searchByKey(NodeTree* r, Key k)
			{
				if (r == NULL)
					return NULL;
				if (r->pr.first && r->pr.first == k)
					return r;
				else if (k < r->pr.first)
					return searchByKey(r->left, k);
				else if (k > r->pr.first)
					return searchByKey(r->right, k);
				return NULL; // NULL
			}
			// 1st arg always root?
			NodeTree *iterativeSearch(NodeTree* r, NodeTree*& parent, const ft::pair<Key, T>& val)
			{
				while (r != NULL)
				{
					parent = r;
					if (val < r->pr)
						r = r->left;
					else if (val > r->pr)
						r = r->right;
					else
						return r;
				}
				return r;
			}
			// 1st arg always root?
			NodeTree* insertNode(NodeTree* r, NodeTree* parent, const ft::pair<Key, T>& val)
			{
				if (r == NULL)
				{
					// if (parent)
					// 	std::cout << "parent.first: " << parent->pr.first << std::endl;
					r = _alloc_n.allocate(1);
					_alloc_n.construct(r, NodeTree(parent, val));
					_nb_nodes++;
					// if (_nb_nodes == 1)
					// 	_root = r;
					std::cout << "Value inserted successfully" << std::endl;
					return r;
				}
				else if (val < r->pr)
					r->left = insertNode(r->left, r, val);
				else if (val > r->pr)
					r->right = insertNode(r->right, r, val);
				else
					return r;
				r = balanceInsert(r, val);
				return r;
			}

			NodeTree*	balanceInsert(NodeTree* r, const ft::pair<Key, T>& val)
			{				
				int bf = getBalanceFactor(r);
				// Left Left Case
				if (bf > 1 && val < r->left->pr)
					return rightRotate(r);
				// Right Right Case  
				if (bf < -1 && val > r->right->pr)
					return leftRotate(r);
				// Left Right Case  
				if (bf > 1 && val > r->left->pr)
				{
					r->left = leftRotate(r->left);
						return rightRotate(r);
				}
				// Right Left Case  
				if (bf < -1 && val < r->right->pr)
				{
					r->right = rightRotate(r->right);
						return leftRotate(r);
				}
				return (r);
			}

			NodeTree* deleteNode(NodeTree* r, NodeTree* parent, NodeTree* node) {
				// base case 
				if (r == NULL)
					return NULL;
				else if (node->pr < r->pr)
					r->left = deleteNode(r->left, parent, node);
				else if (node->pr > r->pr)
					r->right = deleteNode(r->right, parent, node);
				else
				{
					this->print2D(_root, 5);
					_nb_nodes--;
					// Node with only one child or no child 
					if (r->left == NULL)
					{
						NodeTree* temp = r->right;
						_alloc_n.destroy(temp);
						_alloc_n.deallocate(temp, 1);
						return parent;
					}
					else if (r->right == NULL)
					{
						NodeTree* temp = r->left;
						_alloc_n.destroy(temp);
						_alloc_n.deallocate(temp, 1);
						return parent;
					}
					else
					{
						// Node with two children: Get the inorder successor (smallest 
						// in the right subtree) 
						NodeTree* minright = minValueNode(r->right);
						// Copy the inorder successor's content to this Node 
						r->pr = minright->pr;
						// Delete the inorder successor 
						r->right = deleteNode(r->right, r, minright);
						//deleteNode(r->right, minright->pr); 
					}
				}

				int bf = getBalanceFactor(r);
				r = balanceDeletion(bf, r);
				return r;
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

		private:

			NodeTree*		_root;
			NodeTree*		_begin;
			NodeTree*		_end;
			size_t			_nb_nodes;
			alloc_node		_alloc_n;


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

			// Get Balance factor of t_node N
			int getBalanceFactor(NodeTree* n)
			{
				if (n == NULL)
					return (-1);
				return (getHeight(n->left) - getHeight(n->right));
			}

			NodeTree* rightRotate(NodeTree* z)
			{
				NodeTree* y = z->left;
				NodeTree* Tx = y->right;

				// Perform rotation
				y->right = z;
				z->left = Tx;
				y->parent = z->parent;
				z->parent = y;
				if (Tx)
					Tx->parent = z;
				return y;
			}

			NodeTree* leftRotate(NodeTree* z)
			{
				NodeTree* y = z->right;
				NodeTree* Tx = y->left;

				// Perform rotation
				y->left = z;
				z->right = Tx;
				y->parent = z->parent;
				z->parent = y;
				if (Tx)
					Tx->parent = z;
				return y;
			}

			

			
	};
}

#endif
