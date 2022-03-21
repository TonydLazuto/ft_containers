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

		public:
			typedef ft::pair<Key, T> value_type;
			typedef	Node<Key, T> NodeTree;
			typedef size_t	size_type;

			typedef Alloc alloc_pair;
			typedef typename Alloc::template rebind<NodeTree>::other alloc_node;


			AvlTree( const alloc_node& alloc_n = alloc_node() )
			: _root(NULL), _end(NULL), _alloc_n(alloc_n)
			{
				_end = _alloc_n.allocate(1);
				_alloc_n.construct(_end, NodeTree());
			}

			virtual ~AvlTree( void ) {
			}

			AvlTree(AvlTree const & src) : _root(src._root), _end(src._end)
			, _alloc_n(src._alloc_n) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				_end = rhs._end;
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
				if (r)
				{
					std::cout << "Key="<< r->pr.first << ", Val=" << r->pr.second;// << std::endl; // 6
					if (r->left)
						std::cout << ", Left=" << r->left->pr.first;
					if (r->right)
						std::cout << ", Right=" << r->right->pr.first;
					if (r->parent)
						std::cout << ", Parent=" << r->parent->pr.first;
					std::cout<< std::endl;
				}
				else
					std::cout << std::endl;
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
				, const ft::pair<Key, T>& val, NodeTree** new_insert)
			{
				if (r == NULL)
				{
					r = _alloc_n.allocate(1);
					_alloc_n.construct(r, NodeTree(parent));
					r->pr = val;
					*new_insert = r;
					std::cout << "Value inserted successfully" << std::endl;
					return r;
				}
				else if (val < r->pr)
					r->left = insertNode(r->left, r, val, new_insert);
				else if (val > r->pr)
					r->right = insertNode(r->right, r, val, new_insert);
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
			NodeTree	*delSingleChild(NodeTree* r, NodeTree* side)
			{
				std::cout << "delSingleChild" << std::endl;

				if (!r)
					return (NULL);
				if (!r->left)
					side = r->right;
				else if (!r->right)
					side = r->left;
				if (side)
					side->parent = r->parent;
				// r->left = NULL;
				// r->right = NULL;
				// r->parent = NULL;
				_alloc_n.destroy(r);
				_alloc_n.deallocate(r, 1);
				return side;
			}

			void	redefineMinrightchildParent (NodeTree* minright)
			{
				NodeTree* minright_child = NULL;

				// printNode(minright, "minright");
				// std::cout << "redefineMinrightchildParent" << std::endl;
				if (minright->right)
				{
					minright_child = minright->right;
					minright_child->parent = minright_child->parent->parent;
				}
				else if (minright->left)
				{
					minright_child = minright->left;
					minright_child->parent = minright_child->parent->parent;
				}
				// else
				// 	std::cout << "no redefined grandchild" << std::endl;
			}

			NodeTree*	deleteNode(NodeTree* r, NodeTree* node) {
				// base case 
				if (r == NULL)
					return NULL;
				else if (node->pr < r->pr)
					r->left = deleteNode(r->left, node);
				else if (node->pr > r->pr)
					r->right = deleteNode(r->right, node);
				else
				{
					// Node with only one child or no child 
					if (!r->left)
						return (delSingleChild(r, r->right));
					else if (!r->right)
						return (delSingleChild(r, r->left));
					else
					{
						std::cout << "deleteNode" << std::endl;
						// Node with two children: Get the inorder successor
						// (smallest in the right subtree)
						NodeTree* minright = minValueNode(r->right);
						redefineMinrightchildParent(minright);
						// Copy the inorder successor's content to this Node
						r->pr = minright->pr;
						// Delete the inorder successor
						r->right = deleteNode(r->right, minright);
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

			void	printNode(NodeTree *node, std::string name)
			{
				if (node)
				{
					std::cout << name << ".first: " << node->pr.first << std::endl;
					std::cout << name << ".second: " << node->pr.second << std::endl;
				}
			}

			void		insert(const value_type& val, NodeTree** new_insert)
			{
				_root = insertNode(_root, NULL, val, new_insert);
			}

			void		erase(NodeTree* to_del)
			{
				_root = deleteNode(_root, to_del);
			}

			NodeTree	*getBegin(void)
			{
				if (!_root)
					return _end;
				return minValueNode(_root);
			}
			
			NodeTree	*getEnd(void) { return _end; }

			NodeTree	*getRoot(void) { return _root; }

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

			size_type	getNbElets(NodeTree *node) const
			{
				if (node)
					return getNbElets(node->right) + getNbElets(node->left) + 1;
				return (0);
			}
			size_type	getSize(void) const
			{
				size_type	size;

				size = getNbElets(_root);
				return (size);
			}

		private:

			NodeTree*		_root;
			NodeTree*		_end;
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
