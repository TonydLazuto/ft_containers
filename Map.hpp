#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "Maptools.hpp"
#include "AvlIterator.hpp"
#include "ReverseIterator.hpp"
#include "IteratorTraits.hpp"
#include "AvlTree.hpp"
#include "Nullptr.hpp"

namespace ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef ft::pair<const Key, T> value_type;

			typedef	Key key_type;
			typedef	T mapped_type;
			typedef Compare key_compare;

			typedef	Node<Key, T> NodeTree;

			typedef Alloc allocator_type;

			// typedef typename alloc_node::reference reference;
			// typedef typename alloc_node::const_reference const_reference;
			// typedef typename alloc_node::pointer pointer;
			// typedef typename alloc_node::const_pointer const_pointer;

			typedef T*        pointer;
			typedef const T*  const_pointer;
			typedef T&        reference;
			typedef const T&  const_reference;


			typedef typename ft::AvlIterator<NodeTree> iterator;
			typedef typename ft::AvlIterator<const NodeTree> const_iterator; //2eme classe const
			typedef typename ft::ReverseIterator<iterator> reverse_iterator;
			typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

			typedef typename IteratorTraits<iterator>::difference_type difference_type;
			typedef size_t	size_type;

			class value_compare : public binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare _comp;
					value_compare(Compare comp) : _comp(comp) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const
					{ return _comp(x.first, y.first); }
			};

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _avl()
				{
					(void)comp;
					(void)alloc;
					_avl._root = _alloc.allocate(1);
					_alloc.construct(_avl._root, _avl._root->pr);
					_avl._begin = _avl._root;
					_avl._end = _avl._root;
				}

			// template <class InputIterator>
			// 	map (InputIterator first, InputIterator last,
			// 		const key_compare& comp = key_compare(),
			// 		const allocator_type& alloc = allocator_type())
			// 		: _avl(), _alloc(alloc), _nb_nodes(0)
			// 	{
			// 		insert(first, last);
			// 		(void)comp;
			// 	}

			virtual ~map( void )
			{
				// if (size())
				// 	_alloc.deallocate(_avl.getRoot(), size());
			}

			map(const map& x)
			{
				this->_avl(x._avl);
			}

			map& operator=(map const & x)
			{
				this->_avl(x._avl);
				return *this;
			}

			iterator begin(void) { iterator(_avl._begin); }
			// const_iterator begin(void) const;
			// reverse_iterator rbegin(void)
			// {
			// 	return (reverse_iterator(_v_end));
			// }
			// const_reverse_iterator rbegin(void) const
			// {
			// 	return (reverse_iterator(_v_end));
			// }
			
			iterator end(void) { iterator(_avl._end); }
			// const_iterator end(void) const {}
			// reverse_iterator rend(void) { return (reverse_iterator(_v)); }
			// const_reverse_iterator rend(void) const { return (reverse_iterator(_v)); }
			
			bool empty(void) const
			{
				return (this->size() == 0 ? true : false);
			}

			size_type size(void) const 
			{
				return (_avl._nb_nodes);
			}

			// size_type max_size(void) const
			// {
			// 	return (_alloc.max_size());
			// }

			void	growSizeTree(void)
			{
				size_type	cpysize = size() == 0 ? 1 : size();
				ft::AvlTree<Key, T>	tmp_tree;
				tmp_tree._root = _alloc.allocate(cpysize + 1);
				while (size())
				{
					NodeTree*	cpy_node = NULL;
					_alloc.construct(cpy_node, _avl._root->pr);
					tmp_tree.insertNode(tmp_tree._root, cpy_node);
					erase(_avl._root->pr.first);
					tmp_tree._nb_nodes++;
				}
				_alloc.deallocate(_avl._root, tmp_tree._nb_nodes);
				_avl = tmp_tree;
			}

			ft::pair<iterator, bool> insert (const value_type& val)
			{
				ft::AvlTree<Key, T>	new_tree;
				NodeTree*	new_node = _avl.searchByPair(_avl._root, val);

				if (new_node == NULL)
				{
					growSizeTree();	
					_alloc.construct(new_node, val);
					new_node = new_tree.insertNode(new_tree._root, new_node);
					_avl.maxValueNode(_avl._root)->right = _avl._end;
					_avl._nb_nodes++;
				}
				// new_tree._root = new_tree.insertNode(new_tree._root, new_node);
				return (new_node->pr);
			}

			// iterator insert (iterator position, const value_type& val);

			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			// void erase (iterator position);

			size_type erase (const key_type& k)
			{
				// if (size() == 0)
				// 	return (0);
				NodeTree*	to_del;

				to_del = _avl.searchByKey(_avl._root, k);		
				if (!to_del)
					return (0);
				to_del = _avl.deleteNode(_avl._root, to_del);
				_alloc.destroy(to_del);
				_avl._nb_nodes--;
				return (1);
			}

			// void erase (iterator first, iterator last);

			// void swap (map& x);

			// void clear(void)
			// {
			// 	while (size() > 0)
			// 		_alloc.destroy(_avl._root);
			// }

			mapped_type& operator[](const key_type& k)
			{
				(*((this->insert(ft::make_pair(k, mapped_type() ))).first))->second;
			}

			// key_compare key_comp(void) const;

			// value_compare value_comp(void) const;

			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;

			// size_type count (const key_type& k) const;

			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;

			// iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;

			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// pair<iterator,iterator>             equal_range (const key_type& k);

			allocator_type get_allocator(void) const { return this->_alloc_save; }

		private:
			ft::AvlTree<Key, T>	_avl;
			allocator_type		_alloc_save;
			alloc_node			_alloc;
			// size_type			_nb_nodes;

	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
		map<Key,T,Compare,Allocator>& y)
		{ x.swap(y); }

}

#endif
