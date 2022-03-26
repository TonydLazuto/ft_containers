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

			typedef typename ft::MapIterator<NodeTree> iterator;
			typedef typename ft::MapIterator<const NodeTree> const_iterator; //2eme classe const ?
			typedef typename ft::ReverseMapIterator<iterator> reverse_iterator;
			typedef typename ft::ReverseMapIterator<const_iterator> const_reverse_iterator;

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
				: _avl(), _alloc(alloc), _comp(comp) {}

			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
					: _avl(), _alloc(alloc), _comp(comp)
				{
					this->insert(first, last);
				}

			virtual ~map( void ) { this->clear(); }

			map(const map& x) : _avl(x._avl), _alloc(x._alloc), _comp(x.comp)
			{
				this->insert(x.begin(), x.end());
			}

			map& operator=(map const & x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
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
				NodeTree*	match_node = _avl.searchByKey(_avl.getRoot(), val.first);
				NodeTree*	new_insert = NULL;

				_avl.insert(val, new_insert);
				// printNode(_avl.getRoot());
				// match_node == NULL => true => insertion has been done
				if (match_node == NULL)
					match_node = new_insert;
				ft::pair<iterator, bool> pair_ret(match_node, match_node == NULL);
				_avl.linkEnd();	

				return (pair_ret);
			}

			iterator insert (iterator position, const value_type& val)
			{
				_avl.unlinkEnd();
				NodeTree*	insertNode = _avl.searchByKey(_avl.getRoot(), val.first);

				_avl.insertAtPosition(*position, val, insertNode);

				_avl.linkEnd();
				return (insertNode);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
				{
					iterator cpy = first;
					++first;
					this->insert(*cpy);
				}
			}

			void erase (iterator position,
				typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type* = NULL)
			{
				this->erase(position->first);
			}

			size_type erase (const key_type& k)
			{
				_avl.unlinkEnd();
				NodeTree*	to_del;

				to_del = _avl.searchByKey(_avl.getRoot(), k);
				if (!to_del)
					return (0);
				_avl.erase(to_del->pr);
				_avl.linkEnd();
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					iterator cpy = first;
					++first;
					this->erase(cpy->first);
				}
			}

			void swap (map& x) { _avl.swap(x._avl); }

			void clear(void)
			{
				_avl.clear(); // check leaks
			}

			mapped_type& operator[](const key_type& k)
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				if (match_elet)
					return (match_elet->pr.second);
				ft::pair<iterator, bool> ret_pair = insert(ft::make_pair(k, mapped_type()));
				return ((ret_pair.first)->second);
			}

			key_compare key_comp(void) const { return (key_compare()); }

			value_compare value_comp(void) const
			{
				return (value_compare(key_compare()));
			}

			iterator find (const key_type& k)
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				if (match_elet)
					return (match_elet);
				return (end());
			}
			const_iterator find (const key_type& k) const
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				if (match_elet)
					return (match_elet);
				return (end());
			}

			size_type count (const key_type& k) const
			{
				NodeTree*	match_elet;

				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				return (match_elet != NULL);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator first = begin();
				iterator last = end();
				for (; first != last; ++first)
				{
					if (!_comp(first->first, k))
						break ;
				}
				return first;
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(this->lower_bound(k)));
			}

			iterator upper_bound (const key_type& k)
			{
				iterator first = begin();
				iterator last = end();
				for (; first != last; ++first)
				{
					if (_comp(k, first->first))
						break ;
				}
				return first;
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(this->upper_bound(k)));
			}

			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}
			pair<iterator,iterator>				equal_range (const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			allocator_type get_allocator(void) const { return this->_alloc; }

		private:
			ft::AvlTree<Key, T>	_avl;
			allocator_type		_alloc;
			key_compare			_comp;

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
