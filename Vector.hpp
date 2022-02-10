#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include "RandomAccess.hpp"
#include "ReverseIterator.hpp"

namespace ft 
{
	template <typename T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			class ValueOutOfRange : public std::exception
			{
				public:
					ValueOutOfRange( void ) throw() {}
					virtual ~ValueOutOfRange( void ) throw() {}
					virtual const char* what() const throw()
					{
						return "Error: try to reach a value greater than the vector size";
					}
			};
			typedef	T value_type;
			typedef Alloc allocator_type;

			typedef typename Alloc::size_type size_type;
			typedef typename Alloc::difference_type difference_type;

			typedef typename ft::RandomAccessIterator<T> iterator;
			typedef typename ft::RandomAccessIterator<const T> const_iterator;
			typedef ft::ReverseIterator<iterator> reverse_iterator;
			typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;

			explicit Vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				this->_v = _alloc.allocate(0);
				this->_v_start = NULL;
				this->_v_end = NULL;
				this->_v_end_alloc = NULL;
			}
			explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					_v = _alloc.allocate(n);
					pointer p = _v;
					this->_v_start = p;
					while (p < _v + n)
						_alloc.construct(p++, val);
					this->_v_end = p + 1;
					this->_v_end_alloc = p;
				}
			// template <typename InputIt,
			// std::enable_if<
			//     std::is_base_of<std::input_iterator_tag,typename std::iterator_traits<
			// 						InputIt>::iterator_category
			//                     >::value,
			//     bool>::type = true>
			// template <class InputIterator>
			// Vector (InputIterator first, InputIterator last,
			// const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			// 	{
					// if (last - first < 1)
					// 	throw std::exception();
					
					// std::cout << first << std::endl;
					// std::cout << last << std::endl;
					// std::cout << &first << std::endl;
					// std::cout << &last << std::endl;
					// this->_v_start = first;
					// difference_type d = last - first;
					// _v = this->_alloc.allocate(d);
					// for (int i = 0; i < d - 1; i++)
					// {
					// 	// std::cout << first << std::endl;
					// 	this->_alloc.construct(_v++, *first);
					// 	first++;
					// }
					// this->_v_end = last;
					// this->_v_end_alloc = last;
				// }
			virtual ~Vector( void )
			{
				// if (_v_end != _v_start)
				// 	;
			}
			// Vector(Vector const & x) {}
			// Vector& operator=(const Vector& x) {}

			iterator begin(void) { return _v_start; }
			const_iterator begin(void) const { return const_cast<const_iterator>(this->_v_start); }
			iterator end(void)
			{
				if (empty())
					return _v_start;
				return _v_end;
			}
			const_iterator end(void) const { return const_cast<const_iterator>(this->_v_end); }
			size_type size(void) const 
			{
				return static_cast<size_type>((this->_v_end - 1) - this->_v_start);
			}
			size_type max_size(void) const
			{
				return static_cast<size_type>(std::numeric_limits<difference_type>::max());
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					size_type i = n;
					while (i < size())
					{
						_alloc.destroy(_v + i);
						_alloc.construct(_v + i, val);
						i++;
					}
					this->_v_end = _v + n + 1;
				}
				else if (n > size())
				{
					if (n > capacity())
						realloc(capacity() * 2);
					for (size_type it = size(); it < n; it++)
						push_back(val);
				}
			}
			size_type capacity(void) const
			{
				return static_cast<size_type>(this->_v_end_alloc - this->_v);
			}
			bool empty(void) const { return (this->size() == 0 ? true : false); }
			void reserve (size_type n)
			{
				if (n > capacity())
					realloc(n);
			}

			reference operator[] (size_type n) { return (this->_v[n]); }
			const_reference operator[] (size_type n) const { return (const_cast<const_reference>(&this->_v[n])); }

			reference at (size_type n)
			{
				try
				{
					if (n >= size())
						throw ValueOutOfRange();
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
				return (this->_v[n]);
			}

			const_reference at (size_type n) const
			{
				try
				{
					if (n >= size())
						throw ValueOutOfRange();
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
				return (const_cast<const_reference>(this->_v[n]));
			}

			/*
				Indexing is done by operator[]() and at();
				operator[]() provides unchecked access,
				whereas at() does a range check and throws out_of_range
				if an index is out of range (try catch)
			 */

			reference front(void) { return *this->_v_start; }

			// const_reference front(void) const { return const_cast<const_iterator>(&this->_v_start); }

			reference back(void) { return (*(this->_v_end - 1)); }

			// const_reference back(void) const { return const_cast<const_iterator>(&this->_v_end); }

			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last);

			// void assign (size_type n, const value_type& val);

			void push_back (const value_type& val)
			{
				if (size() >= capacity())
					realloc(capacity() * 2);
				this->_v[this->size()] = val;
				this->_v_end++;
			}

			void pop_back(void)
			{
				iterator save;
				if (size() <= 0)
					return ;
				save = size() == 1 ? this->_v : this->_v_end - 1;
				_alloc.destroy(this->_v_end);
				this->_v_end = save;
			}

			// iterator insert (iterator position, const value_type& val);

			// void insert (iterator position, size_type n, const value_type& val);

			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			// iterator erase (iterator position);

			// iterator erase (iterator first, iterator last);

			// void swap (Vector& x);

			// void clear(void);

			// allocator_type get_allocator(void) const;
			
			// template <class T, class Alloc>
			// bool operator==(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// bool operator!=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// bool operator<(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// bool operator<=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// bool operator>(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// bool operator>=(const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)

			// template <class T, class Alloc>
			// void swap (Vector<T, Alloc>& x, Vector<T, Alloc>& y);


		private:
			allocator_type	_alloc;
			pointer			_v;
			iterator		_v_start;
			iterator		_v_end;
			iterator		_v_end_alloc;

			Vector&	realloc(size_t new_capacity)
			{
				size_type	new_size = new_capacity < this->size() ? new_capacity : this->size();
				pointer		new_v = _alloc.allocate(new_capacity);

				for (size_type i = 0; i < new_size; i++)
					_alloc.construct(new_v + i, this->_v[i]);
				for (size_type i = new_size; i < new_capacity; i++)
					_alloc.construct(new_v + i, 0);
				for (size_type i = 0; i < this->size(); i++)
					_alloc.destroy(this->_v + i);
				_alloc.deallocate(this->_v, capacity());
				this->_v = new_v;
				this->_v_start = new_v;
				this->_v_end = _v_start + new_size + 1;
				this->_v_end_alloc = _v_start + new_capacity;
				return *this;
			}
	};
}

#endif
