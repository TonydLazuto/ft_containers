#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Node.hpp"
#include "MapIterator.hpp"

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
			: _root(NULL), _end(NULL), _alloc_n(alloc_n), _nb_nodes(0)
			{
				createSentinelNode();
			}

			virtual ~AvlTree( void ) {
			}

			AvlTree(AvlTree const & src) : _root(src._root), _end(src._end)
			, _alloc_n(src._alloc_n), _nb_nodes(src._nb_nodes) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				_end = rhs._end;
				_alloc_n = rhs._alloc_n;
				_nb_nodes = rhs._nb_nodes;
				return *this;
			}

			void print2D(NodeTree* r, int space) const {
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
					// std::cout << ", r: " << &r->pr;
					std::cout<< std::endl;
				}
				else
					std::cout << std::endl;
				print2D(r->left, space); // Process left child  7
			}

			NodeTree* minValueNode(NodeTree* node) const
			{
				NodeTree* min_node = node;
				/* loop down to find the leftmost leaf */
				while (min_node && min_node->left != NULL)
					min_node = min_node->left;				
				return min_node;
			}

			NodeTree* maxValueNode(NodeTree* node) const
			{
				NodeTree* max_node = node;
				/* loop down to find the rightmost leaf */
				while (max_node && max_node->right)
					max_node = max_node->right;
				return max_node;
			}

			NodeTree* searchByKey(NodeTree* r, Key k) const
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

			void	iterativeSearch(NodeTree*& r, value_type& val)
			{
				while (r != NULL)
				{
					if (val < r->pr)
						r = r->left;
					else if (val > r->pr)
						r = r->right;
					else
						return ;
				}
			}
			
			NodeTree* insertNode(NodeTree* r, NodeTree* parent
				, const ft::pair<Key, T>& val, NodeTree*& new_insert)
			{
				if (r == NULL)
				{
					r = _alloc_n.allocate(1);
					_alloc_n.construct(r, NodeTree(parent));
					r->pr = val;
					new_insert = r;
					_nb_nodes++;
					return r;
				}
				else if (val < r->pr)
				{
					r->left = insertNode(r->left, r, val, new_insert);
				}
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

			void	swap_nodes(NodeTree*& r, NodeTree*& minright)// ou swap les addresses de pair???
			{
				NodeTree*	r_left = r->left;
				NodeTree*	r_right = r->right;
				NodeTree*	r_parent = r->parent;
				NodeTree*	save_minright_left = minright->left;
				NodeTree*	save_minright_right = minright->right;
				NodeTree*	save_minright_parent = minright->parent;

				r_left->parent = minright;
				r_right->parent = minright;
				minright->left = r_left;
				minright->right = r_right;
				minright->parent = r_parent;

				r->right = save_minright_right;
				r->left = save_minright_left;
				if (save_minright_left)
					save_minright_left->parent = r;
				if (r_parent && (r->pr < r_parent->pr))
					r_parent->left = minright;
				else if (r_parent && (r->pr > r_parent->pr))
					r_parent->right = minright;

				// check if r->right point directly on minright
				// to avoid self pointing on r->right
				if (r_right && r_right->pr == minright->pr)
				{
					minright->right = r;
					r->parent = minright;
				}
				else
				{
					r->parent = save_minright_parent;
					if (save_minright_parent && (r->pr < save_minright_parent->pr))
						save_minright_parent->left = r;
					else if (save_minright_parent && (r->pr > save_minright_parent->pr))
						save_minright_parent->right = r;
				}
			}

			NodeTree*	recursiveDeletion(NodeTree*	r, value_type val)
			{
				if (r == NULL)
					return NULL;
				else if (r && val < r->pr)
					r->left = recursiveDeletion(r->left, val);
				else if (r && val > r->pr)
					r->right = recursiveDeletion(r->right, val);
				else
				{
					NodeTree	*temp = r->left;
					if (r->right)
						temp = r->right;
					if (temp)
					{
						temp->parent = r->parent;
					}
					
					_alloc_n.destroy(r);
					_alloc_n.deallocate(r, 1);
					_nb_nodes--;
					return (temp);
				}
				return (r);
			}

			NodeTree*	deleteNode(NodeTree* r, value_type val) {
				// base case
				NodeTree* minright = NULL;
				NodeTree* node_start = _root;
				
				iterativeSearch(r, val);
				minright = minValueNode(r->right);
				if (!r)
					return _root;
				// std::cout << "-------------------------deleteNode-----------------------------------" << std::endl;
				// std::cout << "r: " << &r->pr << std::endl;
				if (r->left && r->right)
					swap_nodes(r, minright);
				if (r->parent)
					node_start = r->parent;
				r = recursiveDeletion(node_start, val);
				// std::cout << "-------------------------beforeBalance-----------------------------------" << std::endl;
				r = balanceDeletion(r);
				while (r && r->parent)
				{
					r->parent = balanceDeletion(r->parent);
					r = r->parent;
				}
				return r;
			}

			NodeTree*	balanceDeletion(NodeTree* r)
			{
				int bf = getBalanceFactor(r);
				// Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && getBalanceFactor(r->left) >= 0){
					// std::cout << "1" << std::endl;
					return rightRotate(r);}
				// Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && getBalanceFactor(r->left) == -1)
				{
					// std::cout << "2" << std::endl;
					r->left = leftRotate(r->left);
					return rightRotate(r);
				}
				// Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && getBalanceFactor(r->right) <= 0)
				{
					// std::cout << "3" << std::endl;
					return leftRotate(r);
				}
				// Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && getBalanceFactor(r->right) == 1)
				{
					// std::cout << "4" << std::endl;
					r->right = rightRotate(r->right);
					return leftRotate(r);
				}
				return (r);
			}

			void	printNode(NodeTree *r, std::string name)
			{
				if (r)
				{
					std::cout << name << ".first: " << r->pr.first;
					std::cout << ", " << name << ".second: " << r->pr.second;
					if (r->left)
						std::cout << ", Left=" << r->left->pr.first;
					if (r->right)
						std::cout << ", Right=" << r->right->pr.first;
					if (r->parent)
						std::cout << ", Parent=" << r->parent->pr.first;
					// std::cout << ", r: " << &r->pr;
					std::cout<< std::endl;
				}
			}

			void		insert(const value_type& val, NodeTree*& new_insert)
			{
				_root = insertNode(_root, NULL, val, new_insert);
			}

			void		insertAtPosition(value_type& hint_val, const value_type& val
							, NodeTree*& new_insert)
			{
				NodeTree* positionNode = _root;

				iterativeSearch(positionNode, hint_val);
				positionNode = insertNode(positionNode, NULL, val, new_insert);
				while (positionNode && positionNode->parent)
				{
					positionNode->parent = balanceInsert(positionNode->parent, val);
					positionNode = positionNode->parent;
				}
				_root = positionNode;
			}

			void		erase(value_type to_del)
			{
				_root = deleteNode(_root, to_del);
			}

			NodeTree	*getBegin(void) const
			{
				if (!_root)
					return _end;
				return minValueNode(_root);
			}
			
			NodeTree	*getEnd(void) const { return _end; }

			NodeTree	*getRoot(void) const { return _root; }

			void		setRootToNULL(void) { this->_root = NULL; }

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
				if (!_root)
					return ;
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
				// std::cout << "_______________________________________________" << std::endl;
				// print2D(_root, 5);
				return (_nb_nodes - 1);
			}
			void	createSentinelNode(void)
			{
				_end = _alloc_n.allocate(1);
				_alloc_n.construct(_end, NodeTree(NULL));
				_nb_nodes++;
			}

			void	deleteSentinelNode(void)
			{
				_alloc_n.destroy(_end);
				_alloc_n.deallocate(_end, 1);
			}
			void swap (AvlTree& x)
			{
				AvlTree	tmp(x);
				x = *this;
				*this = tmp;
			}
			NodeTree*	recursiveClear(NodeTree* r)
			{
				if (r == NULL)
					return r;
				r->right = recursiveClear(r->right);
				r->left = recursiveClear(r->left);
				if (!r->left && !r->right)
				{
					_alloc_n.destroy(r);
					_alloc_n.deallocate(r, 1);
					_nb_nodes--;
					r = NULL;
				}
				return r;
			}
			void	clear(void)
			{
				unlinkEnd();
				_root = recursiveClear(_root);
			}

		private:

			NodeTree*		_root;
			NodeTree*		_end;
			alloc_node		_alloc_n;
			size_type		_nb_nodes;

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
				NodeTree* grandad = z->parent;

				// Perform rotation
				y->parent = grandad;
				y->right = z;
				z->left = Tx;
				z->parent = y;
				if (Tx)
					Tx->parent = z;
				if (grandad)
				{
					if (y->pr < grandad->pr)
						grandad->left = y;
					else
						grandad->right = y;
				}
				return y;
			}

			NodeTree* leftRotate(NodeTree* z)
			{
				NodeTree* y = z->right;
				NodeTree* Tx = y->left;
				NodeTree* grandad = z->parent;

				// Perform rotation
				y->parent = grandad;
				y->left = z;
				z->right = Tx;
				z->parent = y;
				if (Tx)
					Tx->parent = z;
				if (grandad)
				{
					if (y->pr < grandad->pr)
						grandad->left = y;
					else
						grandad->right = y;
				}
				return y;
			}
			
	};
}

#endif
