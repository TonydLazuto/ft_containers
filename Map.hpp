#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include <limits>
#include "MapIterator.hpp"
#include "IteratorTraits.hpp"
#include "AvlTree.hpp"
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

			typedef ft::MapIterator<value_type, NodeTree, false> iterator;
    		typedef ft::MapIterator<const value_type, NodeTree, true> const_iterator;
			typedef ft::ReverseMapIterator<value_type, iterator> reverse_iterator;
			typedef ft::ReverseMapIterator<const value_type, const_iterator> const_reverse_iterator;

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
					for (; first != last; ++first)
						this->insert(*first);
				}

			void	print(void) const
			{
				_avl.print2D(_avl.getRoot(), 5);
			}

			virtual ~map( void )
			{
				this->clear();
			}

			map(const map& x) : _alloc(x._alloc)
			{
				for (const_iterator it = x.begin(); it != x.end(); ++it)
					this->insert(*it);
			}

			map& operator=(map const & x)
			{
				this->clear();
				_avl.deleteSentinelNodes();
				_avl.createSentinelNodes();
				for (const_iterator it = x.begin(); it != x.end(); ++it)
					this->insert(*it);
				return *this;
			}

			iterator begin(void) { return (_avl.begin()); }
			const_iterator begin(void) const { return (_avl.begin()); }
			reverse_iterator rbegin(void) { return (_avl.rbegin()); }
			const_reverse_iterator rbegin(void) const { return (_avl.rbegin()); }
			
			iterator end(void) { return (_avl.end()); }
			const_iterator end(void) const { return (_avl.end()); }
			reverse_iterator rend(void)  { return (_avl.rend()); }
			const_reverse_iterator rend(void) const { return (_avl.rend()); }

			bool empty(void) const{ return (this->size() == 0 ? true : false); }
			size_type size(void) const { return (_avl.getSize()); }
			size_type max_size(void) const {
				// return (std::numeric_limits<size_type>::max() / (sizeof(T) / 2 < 1 ? 1 : sizeof(T)));
				return this->_avl.max_size();
			}

			ft::pair<iterator, bool> insert (const value_type& val)
			{
				_avl.unlinkSentinels();
				NodeTree*	match_node = _avl.searchByKey(_avl.getRoot(), val.first);
				NodeTree*	new_insert = NULL;
				bool		pr_sec = match_node == NULL;

				_avl.insert(val, new_insert);
				// printNode(_avl.getRoot());
				// match_node == NULL => true => insertion has been done
				if (!match_node)
					match_node = new_insert;
				ft::pair<iterator, bool> pair_ret(match_node, pr_sec);
				_avl.linkSentinels();	

				return (pair_ret);
			}

			iterator insert (iterator position, const value_type& val)
			{
				_avl.unlinkSentinels();
				NodeTree*	new_insert = _avl.searchByKey(_avl.getRoot(), val.first);
				
				if (!_avl.getRoot() || new_insert)
					_avl.insert(val, new_insert);
				else
				{
					if (position == begin())
						position = _avl.minValueNode(_avl.getRoot());
					if (position == end())
						position = _avl.maxValueNode(_avl.getRoot());
					value_type hint_val = findInsertFromHint(position, val);
					_avl.insertAtPosition(hint_val, val, new_insert);
				}
				_avl.linkSentinels();
				return (new_insert);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
				{
					InputIterator cpy = first;
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
				_avl.unlinkSentinels();
				NodeTree*	to_del;

				to_del = _avl.searchByKey(_avl.getRoot(), k);
				if (to_del)
					_avl.erase(to_del->pr);
				_avl.linkSentinels();
				return (to_del ? 1 : 0);
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
				_avl.clear();
			}

			mapped_type& operator[](const key_type& k)
			{
				iterator it = lower_bound(k);
				if (it == end() || key_comp()(k, it->first))
					it = insert(it, ft::make_pair(k, mapped_type()));
				return (it->second);
			}

			key_compare key_comp(void) const { return (key_compare()); }

			value_compare value_comp(void) const
			{
				return (value_compare(key_compare()));
			}

			iterator find (const key_type& k)
			{
				NodeTree*	match_elet = NULL;

				_avl.unlinkSentinels();
				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				_avl.linkSentinels();
				if (match_elet)
					return (match_elet);
				return (end());
			}
			const_iterator find (const key_type& k) const
			{
				NodeTree*	match_elet = NULL;

				_avl.unlinkSentinels();
				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				_avl.linkSentinels();
				if (match_elet)
					return (match_elet);
				return (end());
			}

			size_type count (const key_type& k) const
			{
				NodeTree*	match_elet = NULL;

				_avl.unlinkSentinels();
				match_elet = _avl.searchByKey(_avl.getRoot(), k);
				_avl.linkSentinels();
				return (match_elet != NULL);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator elet = begin();
				iterator last = end();
				for (; elet != last; ++elet)
				{
					if (!_comp(elet->first, k))
						break ;
				}
				return elet;
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator elet = begin();
				const_iterator last = end();
				for (; elet != last; ++elet)
				{
					if (!_comp(elet->first, k))
						break ;
				}
				return elet;
			}

			iterator upper_bound (const key_type& k)
			{
				iterator elet = begin();
				iterator last = end();
				for (; elet != last; ++elet)
				{
					if (_comp(k, elet->first))
						break ;
				}
				return elet;
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator elet = begin();
				const_iterator last = end();
				for (; elet != last; ++elet)
				{
					if (_comp(k, elet->first))
						break ;
				}
				return elet;
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

			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator==(const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);
			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator!=(const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);
			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator< (const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);
			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator<=(const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);
			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator> (const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);
			template <class First, class Second, class MyComp, class MyAlloc>
				friend bool operator>=(const map<First,Second,MyComp,MyAlloc>& lhs,
					const map<First,Second,MyComp,MyAlloc>& rhs);

		private:
			ft::AvlTree<Key, T>	_avl;
			allocator_type		_alloc;
			key_compare			_comp;

			value_type	findInsertFromHint(iterator hint, const value_type& val)
			{	
				if (val.first > _avl.maxValueNode(_avl.getRoot())->pr.first)
					return (_avl.maxValueNode(_avl.getRoot())->pr);
				if (val.first < _avl.minValueNode(_avl.getRoot())->pr.first)
					return (_avl.minValueNode(_avl.getRoot())->pr);
				if (hint->first > val.first)
					while (hint->first > val.first)
						--hint;
				else
				{
					while (hint->first < val.first)
						++hint;
					--hint;
				}
				return *hint;
			}

	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return (lhs._avl == rhs._avl); }

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return !(lhs == rhs); }

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return (lhs._avl < rhs._avl); }

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return !(rhs < lhs); }

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return (rhs < lhs); }

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& lhs,
		const map<Key,T,Compare,Allocator>& rhs)
		{ return !(lhs < rhs); }

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
		map<Key,T,Compare,Allocator>& y)
		{ x.swap(y); }

}

#endif
