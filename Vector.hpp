#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include "RandomAccess.hpp"

namespace ft 
{
	template <typename T, class Alloc = std::allocator<T> >
	class Vector : public RandomAccess
	{
		public:
			typedef	T value_type;
			typedef Alloc allocator_type;

			typedef Alloc::size_type size_type;
			typedef Alloc::difference_type difference_type;

			typedef typename ft::RandomAccessIterator<T> iterator;
			// typedef typename ft::RandomAccessIterator<T> const_iterator;
			typedef ft::reverse_iterator<iterator>reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>const_reverse_iterator;

			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;

			typedef typename size_type;

			
			explicit Vector( void )
			{
				this->_v_start = alloc.allocate(0, 0);
				this->_v_end = this->_v_start;
				this->_v_end_alloc = this->_v_end;
			}
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					_v = alloc.allocate(n);
					for (iterator it = _v; it < _v + n; it++)
					{
						alloc.construct(p, val);
					}
				}
			// explicit Vector( size_type n )
			// {
			// 	this->_v_start = alloc.allocate(n, 0);
			// 	this->_v_end = this->_v_start;
			// 	this->_v_end_alloc = this->_v_end;
			// }
			template <class InputIterator>
			vector (InputIterator first, InputIterator last )
			{
				;
			}
			virtual ~Vector( void ) {}
			Vector(Vector const & x) { (void)x; }

			Vector& operator=(const Vector& x) {}

			iterator begin(void)
			{
				return iterator(this->_v_start); // ?
			}
			const_iterator begin(void) const
			{
				// return this->
			}
			iterator end(void)
			{
				// return this->
			}
			const_iterator end(void) const
			{
				// return this->
			}
			size_type size(void) const 
			{
				// return size_type(this->_M_impl._M_finish - this->_M_impl._M_start);
			}
			size_type max_size(void) const;

			void resize (size_type n, value_type val = value_type(void));

			size_type capacity(void) const;

			bool empty(void) const;

			void reserve (size_type n)
			{
				if (n <= capacity())
					return ;
				iterator my_v = alloc.allocate(n);
				iterator tmp = _v;

				while (tmp < _v + size())
				{
					alloc.construct(my_v++, tmp);
					alloc.destroy(tmp++);
				}
				alloc.deallocate(_v, capacity());
				_v = my_v;
			}

			reference operator[] (size_type n);

			const_reference operator[] (size_type n) const;

			reference at (size_type n);
			/*
			Indexing is done by operator[]() and at();
			operator[]() provides unchecked access,
			whereas at() does a range check and throws out_of_range
			if an index is out of range
			try catch
			 */

			const_reference at (size_type n) const;

			reference front(void);

			const_reference front(void) const;

			reference back(void);

			const_reference back(void) const;

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last);

			void assign (size_type n, const value_type& val);

			void push_back (const value_type& val);

			void pop_back(void);

			iterator insert (iterator position, const value_type& val);

			void insert (iterator position, size_type n, const value_type& val);

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);

			iterator erase (iterator first, iterator last);

			void swap (Vector& x);

			void clear(void);

			allocator_type get_allocator(void) const;
			
			template <class T, class Alloc>
			bool operator==(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			bool operator!=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			bool operator<(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			bool operator<=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			bool operator>(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			bool operator>=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			template <class T, class Alloc>
			void swap (Vector<T, Alloc>& x, Vector<T, Alloc>& y);


		private:
			allocator_type	_alloc;
			iterator		_v;
			pointer			_v_start;
			pointer 		_v_end;
			pointer			_v_end_alloc;
	};
}

#endif
