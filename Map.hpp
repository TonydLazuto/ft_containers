#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "Maptools.hpp"
#include "Bidirectional.hpp"
#include "IteratorTraits.hpp"
#include "AvlTree.hpp"

namespace ft
{

	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
	class map
	{
		private:
			Avl*	_root;
			Alloc	_alloc;

		public:
			typedef pair<const Key, T> value_type;

			typedef	Key key_type;
			typedef	T mapped_type;
			typedef Compare key_compare;

			typedef Alloc allocator_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;

			typedef typename ft::BiderectionalIterator<T> iterator;
			typedef typename ft::BiderectionalIterator<const T> const_iterator;
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
				const allocator_type& alloc = allocator_type());

			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());

			virtual ~map( void );

			map(const map<key_type, value_type, key_compare, allocator_type> & x);

			map& operator=(map const & x);

			iterator begin();
			const_iterator begin() const;

			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(_v_end));
			}
			const_reverse_iterator rbegin(void) const
			{
				return (reverse_iterator(_v_end));
			}
			
			iterator end(void)
			{
				if (empty())
					return _v;
				return (_v_end);
			}
			const_iterator end(void) const
			{
				if (empty())
					return _v;
				return (_v_end);
			}
			reverse_iterator rend(void) { return (reverse_iterator(_v)); }
			const_reverse_iterator rend(void) const { return (reverse_iterator(_v)); }
			
			bool empty(void) const { return (this->size() == 0 ? true : false); }

			size_type size(void) const 
			{
				return static_cast<size_type>(this->_v_end - this->_v);
			}

			size_type max_size(void) const
			{
				return (_alloc.max_size());
			}
			pair<iterator, bool> insert (const value_type& val);
			iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);

			void erase (iterator position);
			size_type erase (const key_type& k);
			void erase (iterator first, iterator last);

			void swap (map& x);

			void clear();

			mapped_type& operator[](const key_type& k) {
				(*((this->insert(make_pair(k, mapped_type() ))).first)).second;
				}

			key_compare key_comp() const;

			value_compare value_comp() const;

			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;

			size_type count (const key_type& k) const;

			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;

			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			pair<iterator,iterator>             equal_range (const key_type& k);

			allocator_type get_allocator(void) const { return this->_alloc; }

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
