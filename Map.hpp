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
			typedef ft::ReverseMapIterator<iterator> reverse_iterator;
			typedef ft::ReverseMapIterator<const_iterator> const_reverse_iterator;

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
					// std::cout << "--------ConstructorRange---------" << std::endl;
					// _avl.print2D(_avl.getRoot(), 5);
				}

			void	print(void)
			{
				_avl.print2D(_avl.getRoot(), 5);
			}

			virtual ~map( void )
			{
				this->clear();
				_avl.deleteSentinelNode();
			}

			map(const map& x) : _alloc(x._alloc)
			{
				for (const_iterator it = x.begin(); it != x.end(); ++it)
					this->insert(*it);
			}

			map& operator=(map const & x)
			{
				// _avl.print2D(_avl.getRoot(), 5);
				// std::cout << "-----------------" << std::endl;
				this->clear();
				// _avl.createSentinelNode();				
				for (const_iterator it = x.begin(); it != x.end(); ++it)
					this->insert(*it);
				// _avl.print2D(_avl.getRoot(), 5);
				// std::cout << "--------END---------" << std::endl;
				return *this;
			}

			// iterator begin(void) { return (_avl.begin()); }
			// const_iterator begin(void) const { return (_avl.begin()); }
			// reverse_iterator rbegin(void) { return (_avl.rbegin()); }
			// const_reverse_iterator rbegin(void) const { return (_avl.rbegin()); }
			
			// iterator end(void) { return (_avl.end()); }
			// const_iterator end(void) const { return (_avl.end()); }
			// reverse_iterator rend(void)  { return (_avl.rend()); }
			// const_reverse_iterator rend(void) const { return (_avl.rend()); }

			iterator begin(void) { return (iterator(_avl.getBegin())); }
			const_iterator begin(void) const { return (const_iterator(_avl.getBegin())); }
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
				return (const_reverse_iterator(it));
			}
			
			iterator end(void) { return (iterator(_avl.getEnd())); }
			const_iterator end(void) const { return (const_iterator(_avl.getEnd())); }
			reverse_iterator rend(void) { return (reverse_iterator(_avl.getBegin())); }
			const_reverse_iterator rend(void) const { return (const_reverse_iterator(_avl.getBegin())); }
			
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
				NodeTree*	new_insert = _avl.searchByKey(_avl.getRoot(), val.first);

				if (!_avl.getRoot())
					_avl.insert(val, new_insert);
				else
				{
					value_type hint_val = findInsertFromHint(position, val);
					_avl.insertAtPosition(hint_val, val, new_insert);
				}
				_avl.linkEnd();
				// std::cout << "new_insert.first: " << new_insert->pr.first << std::endl;
				// std::cout << "new_insert.second: " << new_insert->pr.second << std::endl;
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
				// _avl.unlinkEnd();
				NodeTree*	to_del;

				to_del = _avl.searchByKey(_avl.getRoot(), k);
				if (!to_del)
					return (0);
				_avl.erase(to_del->pr);
				// _avl.linkEnd();
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
				_avl.clear();
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
				const_iterator first = begin();
				const_iterator last = end();
				for (; first != last; ++first)
				{
					if (!_comp(first->first, k))
						break ;
				}
				return first;
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
				const_iterator first = begin();
				const_iterator last = end();
				for (; first != last; ++first)
				{
					if (_comp(k, first->first))
						break ;
				}
				return first;
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

			value_type	findInsertFromHint(iterator hint, const value_type& val) //private
			{
				if (val > _avl.maxValueNode(_avl.getRoot())->pr)
					return (_avl.maxValueNode(_avl.getRoot())->pr);
				if (val < _avl.minValueNode(_avl.getRoot())->pr)
					return (_avl.minValueNode(_avl.getRoot())->pr);
				if (*hint > val)
					while (*hint > val)
						--hint;
				else
				{
					while (*hint < val)
						++hint;
					--hint;
				}
				return *hint;
			}

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
