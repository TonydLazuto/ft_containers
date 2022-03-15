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

			iterator begin(void) { iterator(_avl._root); }
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

			ft::pair<iterator, bool> insert (const value_type& val)
			{
				NodeTree*	match_node = _avl.searchByPair(_avl._root, val);
				//NodeTree*	new_node = 
				_avl.insertNode(_avl._root, val);
				_avl._root = _avl.balanceInsert(val);
				// if (match_node) does not exist in _avl
				// match_node == NULL => true => insertion has been done
				ft::pair<iterator, bool> pair_ret(_avl._root, match_node == NULL);
				// std::cout << pair_ret;
				// std::cout << "new_node.first: " << new_node->pr.first << std::endl;
				// std::cout << "new_node.second: " << new_node->pr.second << std::endl;
				std::cout << "_avl._root.first: " << _avl._root->pr.first << std::endl;
				std::cout << "_avl._root.second: " << _avl._root->pr.second << std::endl;
				// new_tree._root = new_tree.insertNode(new_tree._root, new_node);
				return (pair_ret);
			}

			// iterator insert (iterator position, const value_type& val);

			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			// void erase (iterator position);

			size_type erase (const key_type& k)
			{
				NodeTree*	to_del;

				to_del = _avl.searchByKey(_avl._root, k);
				if (!to_del)
					return (0);
				_avl._root = _avl.deleteNode(_avl._root, NULL, to_del);
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

			allocator_type get_allocator(void) const { return this->_alloc; }

		private:
			ft::AvlTree<Key, T>	_avl;

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
