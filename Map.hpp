#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "Maptools.hpp"
#include "Bidirectional.hpp"
#include "IteratorTraits.hpp"

namespace ft
{

	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
	class map
	{
		private:
			

		public:
			typedef pair<const Key, T> value_type;

			typedef	Key key_type;
			typedef	T mapped_type;
			typedef Compare key_compare;
			// typedef value_comp value_compare;

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

			map( void );
			virtual ~map( void );
			map(map const & src);
			map& operator=(map const & rhs);

			map( std::string type );

			
	};

}

#endif
