#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include "RandomAccess.hpp"
#include "ReverseIterator.hpp"
#include "IsIntegral.hpp"


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

			explicit Vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				this->_v = _alloc.allocate(1);
				this->_v_start = _v;
				this->_v_end = _v + 1;
				this->_v_end_alloc = _v + 1;
			}
			explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					_v = _alloc.allocate(n);
					pointer p = _v;
					while (p < _v + n)
						_alloc.construct(p++, val);
					this->_v_start = this->_v;
					this->_v_end = p + 1;
					this->_v_end_alloc = p;
				}
	

			template <class InputIterator>
			Vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _alloc(alloc)
				{
					if (last - first < 1)
					{
						this->_v = _alloc.allocate(1);
						this->_v_start = _v;
						this->_v_end = _v + 1;
						this->_v_end_alloc  = _v + 1;
						return ;
					}
					difference_type diff = last - first;
					_v = this->_alloc.allocate(diff);
					this->_v_start = this->_v;
					for (int i = 0; i < diff; i++)
					{
						this->_alloc.construct(&_v[i], *first);
						first++;
					}
					this->_v_end = _v_start + diff + 1;
					this->_v_end_alloc = _v_start + diff;
				}
			virtual ~Vector( void )
			{
				clear();
				if (this->capacity())
					this->_alloc.deallocate(_v, this->capacity());
			}
			
			Vector(Vector const & x)
			{
				this->_alloc = x._alloc;
				this->_v = x._v;
				this->_v_start = x._v_start;
				this->_v_end = x._v_end;
				this->_v_end_alloc = x._v_end_alloc;
			}
			Vector& operator=(const Vector& x)
			{
				this->_alloc = x._alloc;
				this->_v = x._v;
				this->_v_start = x._v_start;
				this->_v_end = x._v_end;
				this->_v_end_alloc = x._v_end_alloc;
				return *this;
			}

			iterator begin(void) { return _v_start; }
			reverse_iterator rbegin(void)
			{
				if (_v_end == _v_start)
					return reverse_iterator(_v_end);
				return reverse_iterator(_v_end - 1);
			}
			
			iterator end(void)
			{
				if (empty())
					return _v_start;
				return (_v_end - 1);
			}
			reverse_iterator rend(void) { return reverse_iterator(_v_start); }
			
			size_type size(void) const 
			{
				return static_cast<size_type>((this->_v_end - 1) - this->_v_start);
			}
			size_type max_size(void) const
			{
				return static_cast<size_type>(std::numeric_limits<difference_type>::max());
			}

			void resize(size_type n, value_type val = value_type())
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
						realloc(n);
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

			reference operator[] (size_type n) { return (*(this->_v + n)); }
			const_reference operator[] (size_type n) const { return (const_cast<const_reference>(*(this->_v + n))); }
			
			reference at (size_type n)
			{
				if (n >= size())
				{
					// clear();
					throw ValueOutOfRange();
				}
				return (this->_v[n]);
			}

			const_reference at (size_type n) const
			{
				if (n >= size())
				{
					// clear();
					throw ValueOutOfRange();
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

			const_reference front(void) const { return const_cast<const_iterator>(*this->_v_start); }

			reference back(void) { return (*(this->_v_end - 1)); }

			const_reference back(void) const { return const_cast<const_iterator>(*(this->_v_end - 1)); }

			template <class InputIterator>
  				void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				{
					difference_type	diff = last - first;

					this->clear();
					if (static_cast<size_type>(diff) > this->capacity())
						realloc(diff);
					for (int i = 0; i < diff; i++)
					{
						_alloc.construct(_v + i, *first);
						first++;
					}
					this->_v_end = _v + diff + 1;
				}

			void assign (size_type n, const value_type& val)
			{
					this->clear();
					if (n > this->capacity())
						realloc(n);
					for (int i = 0; i < n; i++)
						_alloc.construct(_v + i, val);
					this->_v_end = _v + n + 1;
			}

			void push_back (const value_type& val)
			{
				if (size() >= capacity())
					realloc(capacity() * 2);
				if (capacity() == 0)
					realloc(1);
				this->_v[this->size()] = val;
				this->_v_end++;
			}

			void pop_back(void)
			{
				if (size() <= 0)
					return ;
				_alloc.destroy(&this->back());
				this->_v_end--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type pos = position - this->begin();

				if (position > this->end() || this->size() <= 0)
					throw ValueOutOfRange();
				if (this->size() == this->capacity())
					realloc(capacity() * 2);
				for (iterator it = this->end(); it != this->begin() + pos; it--)
				{
					_alloc.construct(&*it, *(it - 1));
					_alloc.destroy(&(*(it - 1)));
				}
				_alloc.construct((_v_start + pos), val);
				this->_v_end++;
				return (this->begin() + pos);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type pos = position - this->begin();

				if (position > this->end() || this->size() <= 0)// || position + n > this->end()
					throw ValueOutOfRange();
				if (this->size() + n >= this->capacity())
					realloc(capacity() + n);
				for (iterator it = this->end(); it != this->begin() + pos; it--)
				{
					_alloc.construct(&(*(it - 1 + n)), *(it - 1));
					_alloc.destroy(&(*(it - 1)));
				}
				for (int i = 0; i < n; i++)
				{
					_alloc.construct(&this->front() + pos + i, val);
				}
				this->_v_end += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				difference_type pos = position - this->begin();
				difference_type n = last - first;

				if (position > this->end() || this->size() <= 0)
					throw ValueOutOfRange();
				if (this->size() + n >= this->capacity())
					realloc(capacity() + n);
				for (iterator it = this->end(); it != this->begin() + pos; it--)
				{
					_alloc.construct(&(*(it - 1 + n)), *(it - 1));
					_alloc.destroy(&(*(it - 1)));
				}
				for (int i = 0; i < n; i++)
				{
					_alloc.construct(&this->front() + pos + i, *first);
					first++;
				}
				this->_v_end += n;
			}

			iterator erase (iterator position)
			{
				if (position >= this->end() || this->size() <= 0)
					throw ValueOutOfRange();

				_alloc.destroy(&(*position));
				for (iterator it = position; it < this->end(); it++)
				{
					_alloc.construct(&(*it), *(it + 1));
					_alloc.destroy(&(*(it + 1)));
				}
				this->_v_end--;
				return (position + 1);
			}

			iterator erase (iterator first, iterator last)
			{
				iterator	cpy_last = last;
				difference_type	diff = last - first;

				if (last >= this->end() || this->size() <= 0)
					throw ValueOutOfRange();

				for (iterator it = first; it < this->end(); it++)
				{
					_alloc.destroy(&(*(it)));
					if (cpy_last < this->end())
					{
						_alloc.construct(&(*it), *cpy_last);
						cpy_last++;
					}
				}
				this->_v_end = this->_v + size() - diff + 1;
				return (last);
			}

			void swap (Vector& x)
			{
				pointer tmp_v = x._v;
				pointer tmp_v_start = x._v_start;
				pointer tmp_v_end = x._v_end;
				pointer tmp_v_end_alloc = x._v_end_alloc;
				allocator_type tmp_alloc = x._alloc;

				x._v = this->_v;
				x._v_start = this->_v_start;
				x._v_end = this->_v_end;
				x._v_end_alloc = this->_v_end_alloc;
				x._alloc = this->_alloc;

				this->_v = tmp_v;
				this->_v_start = tmp_v_start;
				this->_v_end = tmp_v_end;
				this->_v_end_alloc = tmp_v_end_alloc;
				this->_alloc = tmp_alloc;
			}

			void clear(void)
			{
				if (this->capacity())
				{
					while (this->size() != 0)
					{
						this->_alloc.destroy(&this->back());
						this->_v_end--;
					}
				}
			}

			allocator_type get_allocator(void) const { return this->_alloc; }
			
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
			pointer			_v_start;
			pointer			_v_end;
			pointer			_v_end_alloc;

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
				this->_v_end = new_v + new_size + 1;
				this->_v_end_alloc = new_v + new_capacity;
				return *this;
			}
			
	};
}

#endif
