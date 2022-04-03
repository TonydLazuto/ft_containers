#ifndef AVLTREE_HPP
# define AVLTREE_HPP

#include <iostream>
#include "Maptools.hpp"
#include "Node.hpp"
#include "MapIterator.hpp"
#include "ReverseMapIterator.hpp"
#include "Lexicographical.hpp"

#define SPACE 10

namespace ft
{
	template < class NodePair, class NodeTree, bool isConst >
	class MapIterator;

	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair<Key, T> > >
	class AvlTree
	{
		public:
			typedef ft::pair<Key, T> value_type;
			typedef	Node<Key, T> NodeTree;
			typedef size_t	size_type;
			typedef Compare key_compare;

			typedef Alloc alloc_pair;
			typedef typename Alloc::template rebind<NodeTree>::other alloc_node;

			typedef ft::MapIterator<value_type, NodeTree, false> iterator;
    		typedef ft::MapIterator<const value_type, NodeTree, true> const_iterator;
			typedef ft::ReverseMapIterator<value_type, iterator> reverse_iterator;
			typedef ft::ReverseMapIterator<const value_type, const_iterator> const_reverse_iterator;

			AvlTree( const key_compare& comp = key_compare(),
				const alloc_node& alloc_n = alloc_node(),
				const Alloc& alloc_pair = Alloc() )
			: _root(NULL), _begin(NULL), _end(NULL), _alloc_n(alloc_n)
				, _alloc_pair(alloc_pair), _nb_nodes(0), _comp(comp)
			{
				createSentinelNodes();
			}

			virtual ~AvlTree( void ) {
				deleteSentinelNodes();
			}

			AvlTree(AvlTree const & src) : _root(src._root), _begin(src._begin)
				, _end(src._end), _alloc_n(src._alloc_n), _alloc_pair(src._alloc_pair)
				, _nb_nodes(src._nb_nodes), _comp(src._comp) {}

			AvlTree& operator=(AvlTree const & rhs)
			{
				_root = rhs._root;
				_begin = rhs._begin;
				_end = rhs._end;
				_alloc_n = rhs._alloc_n;
				_alloc_pair = rhs._alloc_pair;
				_nb_nodes = rhs._nb_nodes;
				_comp = rhs._comp;
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
				if (_comp(k, r->pr.first))
					return searchByKey(r->left, k);
				else if (_comp(r->pr.first, k))
					return searchByKey(r->right, k);
				return r;
			}

			void	iterativeSearch(NodeTree*& r, value_type& val)
			{
				while (r != NULL)
				{
					if (_comp(val.first, r->pr.first))
						r = r->left;
					else if (_comp(r->pr.first, val.first))
						r = r->right;
					else
						return ;
				}
			}
			
			NodeTree* insertNode(NodeTree* r, NodeTree* parent
				, const value_type& val, NodeTree*& new_insert)
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
				else if (_comp(val.first, r->pr.first))
				{
					r->left = insertNode(r->left, r, val, new_insert);
				}
				else if (_comp(r->pr.first, val.first))
					r->right = insertNode(r->right, r, val, new_insert);
				else
					return r;
				r = balanceInsert(r, val);
				return r;
			}

			NodeTree*	balanceInsert(NodeTree* r, const value_type& val)
			{				
				int bf = getBalanceFactor(r);
				// Left Left Case
				if (bf > 1 && _comp(val.first, r->left->pr.first))
					return rightRotate(r);
				// Right Right Case  
				if (bf < -1 && _comp(r->right->pr.first, val.first))
					return leftRotate(r);
				// Left Right Case  
				if (bf > 1 && _comp(r->left->pr.first, val.first))
				{
					r->left = leftRotate(r->left);
					return rightRotate(r);
				}
				// Right Left Case  
				if (bf < -1 && _comp(val.first, r->right->pr.first))
				{
					r->right = rightRotate(r->right);
					return leftRotate(r);
				}
				return (r);
			}

			void	swapNodes(NodeTree*& r, NodeTree*& minright)
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
				if (r_parent && (_comp(r->pr.first, r_parent->pr.first)))
					r_parent->left = minright;
				else if (r_parent && (_comp(r_parent->pr.first, r->pr.first)))
					r_parent->right = minright;
				/**
				 * @brief 
				 * check if "r->right" point directly on "minright"
				 * to avoid "r" self pointing on "r->right"
				 */
				if (r_right && r_right->pr == minright->pr)
				{
					minright->right = r;
					r->parent = minright;
				}
				else
				{
					r->parent = save_minright_parent;
					if (save_minright_parent && (_comp(r->pr.first, save_minright_parent->pr.first)))
						save_minright_parent->left = r;
					else if (save_minright_parent && (_comp(save_minright_parent->pr.first, r->pr.first)))
						save_minright_parent->right = r;
				}
			}

			NodeTree*	destroyNode(NodeTree*& r, NodeTree*& minright)
			{
				NodeTree*	r_parent = r->parent;
				if (r_parent)
				{
					if (_comp(minright->pr.first, r_parent->pr.first))
						r_parent->left = NULL;
					else
						r_parent->right = r->right;
				}
				_alloc_n.destroy(r);
				_alloc_n.deallocate(r, 1);
				r = NULL;
				_nb_nodes--;
				return r_parent;
			}

			NodeTree*	recursiveDeletion(NodeTree*	r, value_type val)
			{
				if (r == NULL)
					return NULL;
				if (r && _comp(val.first, r->pr.first))
					r->left = recursiveDeletion(r->left, val);
				if (r && _comp(r->pr.first, val.first))
					r->right = recursiveDeletion(r->right, val);
				if (r && val == r->pr)
				{
					NodeTree*	temp = r->left;
					if (r->right)
						temp = r->right;
					if (temp)
						temp->parent = r->parent;
					_alloc_n.destroy(r);
					_alloc_n.deallocate(r, 1);
					r = NULL;
					_nb_nodes--;
					return temp;
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
				if (r->parent)
					node_start = r->parent;
				if (r->left && r->right)
				{
					swapNodes(r, minright);
					r = destroyNode(r, minright);
				}
				else
					r = recursiveDeletion(node_start, val);
				r = balanceDeletion(r);
				while (r && r->parent)
				{
					r = balanceDeletion(r->parent);
				}
				return r;
			}

			NodeTree*	balanceDeletion(NodeTree* r)
			{
				int bf = getBalanceFactor(r);
				// Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && getBalanceFactor(r->left) >= 0){
					return rightRotate(r);}
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
					positionNode = balanceInsert(positionNode->parent, val);
				}
				_root = positionNode;
			}

			void		erase(value_type to_del)
			{
				_root = deleteNode(_root, to_del);
			}

			NodeTree	*getBegin(void) const {
				if (!_begin->parent)
					_begin->parent = _end;
				return (_begin->parent);
			}

			NodeTree	*getRoot(void) const { return _root; }

			NodeTree	*getEnd(void) const { return _end; }

			iterator begin(void) { return (iterator(getBegin())); }
			const_iterator begin(void) const { return (const_iterator(getBegin())); }
			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(getEnd()));
			}
			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(getEnd()));
			}
			
			iterator end(void) { return (iterator(getEnd())); }
			const_iterator end(void) const { return (const_iterator(getEnd())); }
			reverse_iterator rend(void)
			{
				return (reverse_iterator(getBegin()));
			}
			const_reverse_iterator rend(void) const
			{
				return (reverse_iterator(getBegin()));
			}


			size_type	getNbElets(NodeTree *node) const
			{
				if (node)
					return getNbElets(node->right) + getNbElets(node->left) + 1;
				return (0);
			}
			size_type	getSize(void) const
			{
				return (_nb_nodes);
			}
			

			void swap (AvlTree& x)
			{
				NodeTree* tmp_begin = x._begin;
				NodeTree* tmp_end = x._end;
				NodeTree* tmp_root = x._root;
				size_type tmp_nb_nodes = x._nb_nodes;

				x._begin = this->_begin;
				x._end = this->_end;
				x._root = this->_root;
				x._nb_nodes = this->_nb_nodes;

				this->_begin = tmp_begin;
				this->_end = tmp_end;
				this->_root = tmp_root;
				this->_nb_nodes = tmp_nb_nodes;
			}

			size_type max_size(void) const { return (_alloc_n.max_size()); }

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
					r = NULL;
					_nb_nodes--;
				}
				return r;
			}
			void	clear(void)
			{
				unlinkSentinels();
				_root = recursiveClear(_root);
			}


			/**
			 * @brief Sentinel SECTION
			 */
			void	linkSentinels(void) const
			{
				NodeTree	*first_node = minValueNode(_root);
				NodeTree	*last_node = maxValueNode(_root);

				if (_root)
				{
					first_node->left = _begin;
					_begin->parent = first_node;
					last_node->right = _end;
					_end->parent = last_node;
				}
			}

			void	unlinkSentinels(void) const
			{
				if (!_root)
					return ;
				NodeTree	*first_node = minValueNode(_root);
				NodeTree	*last_node = maxValueNode(_root);

				if (first_node && (first_node->parent))
					first_node = first_node->parent;
				if (first_node)
				{
					first_node->left = NULL;
					_begin->parent = NULL;
				}
				if (last_node && (last_node->parent))
					last_node = last_node->parent;
				if (last_node)
				{
					last_node->right = NULL;
					_end->parent = NULL;
				}
			}

			void	createSentinelNodes(void)
			{
				_begin = _alloc_n.allocate(1);
				_alloc_n.construct(_begin, NodeTree(NULL));
				_end = _alloc_n.allocate(1);
				_alloc_n.construct(_end, NodeTree(NULL));
			}

			void	deleteSentinelNodes(void)
			{
				_alloc_n.destroy(_begin);
				_alloc_n.deallocate(_begin, 1);
				_alloc_n.destroy(_end);
				_alloc_n.deallocate(_end, 1);
			}


			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator==(const AvlTree<First, Second, MyComp, MyAlloc> &lhs,
					const AvlTree<First, Second, MyComp, MyAlloc> &rhs);

			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator<(const AvlTree<First, Second, MyComp, MyAlloc> &lhs,
					const AvlTree<First, Second, MyComp, MyAlloc> &rhs);

		private:

			NodeTree*		_root;
			NodeTree*		_begin;
			NodeTree*		_end;
			alloc_node		_alloc_n;
			Alloc			_alloc_pair;
			size_type		_nb_nodes;
			key_compare		_comp;

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
					if (_comp(y->pr.first, grandad->pr.first))
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
					if (_comp(y->pr.first, grandad->pr.first))
						grandad->left = y;
					else
						grandad->right = y;
				}
				return y;
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const AvlTree<Key, T, Compare, Alloc> &lhs,
		const AvlTree<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs.getSize() == rhs.getSize() 
			&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const AvlTree<Key, T, Compare, Alloc> &lhs,
		const AvlTree<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
}

#endif
