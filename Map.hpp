#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include <limits>
#include "MapIterator.hpp"
#include "ReverseMapIterator.hpp"
#include "IteratorTraits.hpp"
#include "AvlTree.hpp"
#include "Nullptr.hpp"
#include "IsIntegral.hpp"
#include "EnableIf.hpp"

namespace ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef ft::pair<Key, T> value_type;

			typedef	Key key_type;
			typedef	T mapped_type;
			typedef Compare key_compare;

			typedef	Node<Key, T> NodeTree;

			typedef Alloc allocator_type;
			typedef typename Alloc::template rebind<NodeTree>::other alloc_node;

			typedef T*        pointer;
			typedef const T*  const_pointer;
			typedef T&        reference;
			typedef const T&  const_reference;

			typedef typename ft::MapIterator<NodeTree, value_type> iterator;
			typedef typename ft::MapIterator<const NodeTree, value_type> const_iterator; //2eme classe const ?
			typedef typename ft::ReverseMapIterator<iterator, value_type> reverse_iterator;
			typedef typename ft::ReverseMapIterator<const_iterator, value_type> const_reverse_iterator;

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
				: _avl(), _alloc(alloc)
				{
					(void)comp;
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

			virtual ~map( void ) {}

			map(const map& x) : _avl(x._avl), _alloc(x._alloc) {}

			map& operator=(map const & x)
			{
				_avl(x._avl);
				_alloc(x._alloc);
				return *this;
			}

			iterator begin(void) { return (_avl.getBegin()); }
			const_iterator begin(void) const { return (_avl.getBegin()); }
			reverse_iterator rbegin(void)
			{
				iterator it = _avl.getEnd();
				--it;
				return (reverse_iterator(it));
			}
			const_reverse_iterator rbegin(void) const
			{
				iterator it = _avl.getEnd();
				--it;
				return (reverse_iterator(it));
			}
			
			iterator end(void) { return (_avl.getEnd()); }
			const_iterator end(void) const { return (_avl.getEnd()); }
			reverse_iterator rend(void) { return (reverse_iterator(_avl.getBegin())); }
			const_reverse_iterator rend(void) const { return (reverse_iterator(_avl.getBegin())); }
			
			bool empty(void) const{ return (this->size() == 0 ? true : false); }
			size_type size(void) const { return (_avl.getSize()); }
			size_type max_size(void) const {
				// return (std::numeric_limits<difference_type>::max() / (sizeof(T) / 2 < 1 ? 1 : sizeof(T) / 2 / 2));
				return std::numeric_limits<size_type>::max() / sizeof(T) / 2 / 10;
			}

			ft::pair<iterator, bool> insert (const value_type& val)
			{
				_avl.unlinkEnd();
				NodeTree*	match_node = _avl.searchByKey(_avl._root, val.first);
				NodeTree*	new_insert = NULL;

				_avl._root = _avl.insertNode(_avl._root, NULL, val, &new_insert);
				// if (_avl._root)
				// {
				// 	std::cout << "_avl._root.first: " << _avl._root->pr.first << std::endl;
				// 	std::cout << "_avl._root.second: " << _avl._root->pr.second << std::endl;
				// }
				// match_node == NULL => true => insertion has been done
				if (match_node == NULL)
					match_node = new_insert;
				ft::pair<iterator, bool> pair_ret(match_node, match_node == NULL);
				_avl.linkEnd();	

				return (pair_ret);
			}

			// iterator insert (iterator position, const value_type& val);

			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			void erase (iterator position,
				typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type* = NULL)
			{
				erase(position->first);
			}

			size_type erase (const key_type& k)
			{
				_avl.unlinkEnd();
				_avl.print2D(_avl._root, 5);
				std::cout << "------------------------------------------------------------" << std::endl;
				NodeTree*	to_del;

				std::cout << "yo" << std::endl;
				to_del = _avl.searchByKey(_avl._root, k);
				if (!to_del)
					return (0);
				std::cout << "yo" << std::endl;
				_avl._root = _avl.deleteNode(_avl._root, to_del);
				_avl.print2D(_avl._root, 5);
				std::cout << "------------------------------------------------------------" << std::endl;
				_avl.linkEnd();
				return (1);
			}

			// void erase (iterator first, iterator last);

			// void swap (map& x);

			// void clear(void)
			// {
			// }

			mapped_type& operator[](const key_type& k)
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl._root, k);
				if (match_elet)
					return (match_elet->pr.second);
				value_type val(k, 0);
				ft::pair<iterator, bool> ret_pair = insert(val);
				return ((ret_pair.first)->second);
			}

			// key_compare key_comp(void) const;

			// value_compare value_comp(void) const;

			iterator find (const key_type& k)
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl._root, k);
				if (match_elet)
					return (match_elet);
				return (end());
			}
			const_iterator find (const key_type& k) const
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl._root, k);
				if (match_elet)
					return (match_elet);
				return (end());
			}

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
			allocator_type		_alloc;

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
