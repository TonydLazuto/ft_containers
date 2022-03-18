#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Node.hpp"
#include "Nullptr.hpp"

#define SPACE 10

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair<Key, T> > >
	class AvlTree
	{
		// friend class TestAvlTree;
		template < class Key2, class T2, class Compare2, class Alloc2 >
		friend class map;

		public:
			typedef ft::pair<Key, T> value_type;
			typedef	Node<Key, T> NodeTree;

			typedef Alloc alloc_pair;
			typedef typename Alloc::template rebind<NodeTree>::other alloc_node;


			AvlTree( const alloc_node& alloc_n = alloc_node() )
			: _root(NULL), _end(NULL), _nb_nodes(0), _alloc_n(alloc_n)
			{
				_end = _alloc_n.allocate(1);
				_alloc_n.construct(_end, NodeTree());
			}

			virtual ~AvlTree( void ) {
			}

			AvlTree(AvlTree const & src) : _root(src._root), _end(src._end)
			, _nb_nodes(src._nb_nodes), _alloc_n(src._alloc_n) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
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
				std::cout << "Key="<< r->pr.first << ", Val=" << r->pr.second << std::endl; // 6
				// if (r && r->parent)
				// 	std::cout << ", Parent=" << r->parent->pr.first << std::endl;
				// else
				// 	std::cout << std::endl;
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
				while (min_node && min_node->left != NULL)
					min_node = min_node->left;				
				return min_node;
			}

			NodeTree* maxValueNode(NodeTree* node)
			{
				NodeTree* max_node = node;
				/* loop down to find the rightmost leaf */
				while (max_node && max_node->right)
					max_node = max_node->right;
				return max_node;
			}

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
			NodeTree *iterativeSearch(NodeTree* r, const ft::pair<Key, T>& val)
			{
				while (r != NULL)
				{
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
			NodeTree* insertNode(NodeTree* r, NodeTree* parent
				, const ft::pair<Key, T>& val)
			{
				if (r == NULL)
				{
					r = _alloc_n.allocate(1);
					_alloc_n.construct(r, NodeTree(parent));
					r->pr = val;
					_nb_nodes++;
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
					r->left = deleteNode(r->left, r, node);
				else if (node->pr > r->pr)
					r->right = deleteNode(r->right, r, node);
				else
				{
					// Node with only one child or no child 
					if (r->left == NULL)
					{
						_nb_nodes--;
						NodeTree* temp = r->right;
						_alloc_n.destroy(temp);
						_alloc_n.deallocate(temp, 1);
						return parent;
					}
					else if (r->right == NULL)
					{
						_nb_nodes--;
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
						_nb_nodes--;
					}
				}
				r = balanceDeletion(r);
				return r;
			}

			NodeTree*	balanceDeletion(NodeTree* r)
			{

				int bf = getBalanceFactor(r);
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

			NodeTree	*getBegin(void)
			{
				return minValueNode(_root);
			}
			
			NodeTree	*getEnd(void)
			{
				return _end;
			}

			void	linkEnd(void)
			{
				NodeTree	*last_node = maxValueNode(_root);

				if (last_node)
				{
					last_node->right = _end;
					_end->parent = last_node;
				}
			}

			void	unlinkEnd(void)
			{
				NodeTree	*last_node = maxValueNode(_root);
				if (last_node && (last_node->parent))
					last_node = last_node->parent;
				if (last_node)
				{
					last_node->right = NULL;
					_end->parent = NULL;
				}
			}

			alloc_node		getAlloc(void)
			{ return this->_alloc_n; }

		private:

			NodeTree*		_root;
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

			// Get Balance factor of Node N
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
