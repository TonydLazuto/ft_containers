#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
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

			
			explicit Vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				this->_v = alloc.allocate(0);
				this->_v_start = this->_v;
				this->_v_end = this->_v;
				this->_v_end_alloc = this->_v;
			}
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					_v = _alloc.allocate(n);
					iterator it = _v;
					this->_v_start = it;
					while (it < _v + n)
						_alloc.construct(it++, val);
					this->_v_end = it;
					this->_v_end_alloc = it;
				}
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type() : _alloc(alloc)
				{
					if (last - first < 1)
						throw std::exception();
					
					this->_v_start = first;
					_v = _alloc.allocate(last - first);
					while (first <= last)
					{
						_alloc.construct(_v++, *first);
						first++;
					}
					this->_v_end = last;
					this->_v_end_alloc = last;
				}
			virtual ~Vector( void ) {}
			Vector(Vector const & x) {}
			Vector& operator=(const Vector& x) {}

			iterator begin(void) { return _v_start; }
			// const_iterator begin(void) const { return const_cast<const_iterator>this->(_v_start); }
			iterator end(void) { return _v_end; }
			// const_iterator end(void) const { return const_cast<const_iterator>this->(_v_end); }
			size_type size(void) const 
			{
				return static_cast<size_type>(this->_v_end - this->_v);
			}
			size_type max_size(void) const
			{
				return static_cast<size_type>(std::numeric_limits<difference_type>::max());
			}

			void resize (size_type n, value_type val = value_type(void))
			{
				if (n < size())
				{
					for (int i = n - 1 ; i < size(); i++)
					{
						_alloc.destroy(&_v[i]);
						if (val)
							_alloc.construct(&_v[i], val);
						i++;
					}
					this->_v_end = _v[i - 1];
				}
				else
				{
					if (!val)
						val = static_cast<value_type>(0); // ?
					for (int i = size(); i < n; i++)
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
				if (n <= capacity())
					return ;
				iterator new_v = _alloc.allocate(n);
				iterator v_saved = this->_v;
				while (v_saved < this->_v + size())
				{
					_alloc.construct(new_v++, *v_saved);
					_alloc.destroy(v_saved++);
				}
				_alloc.deallocate(this->_v, capacity());
				this->_v = new_v;
			}

			reference operator[] (size_type n) { return (&this->_v[n]); }
			const_reference operator[] (size_type n) const { return (const_cast<const_reference>(&this->_v[n])); }

			reference at (size_type n);
			{
				if (n > size())
					throw std::exception();
				return (&this->_v[n]);
			}

			const_reference at (size_type n) const;
			{
				if (n > size())
					throw std::exception();
				return (const_cast<const_reference>(&this->_v[n]));
			}

			/*
			Indexing is done by operator[]() and at();
			operator[]() provides unchecked access,
			whereas at() does a range check and throws out_of_range
			if an index is out of range (try catch)
			 */

			reference front(void) { return &this->_v_start; }

			// const_reference front(void) const { return const_cast<const_iterator>(&this->_v_start); }

			reference back(void) { return &this->_v_end; }

			// const_reference back(void) const { return const_cast<const_iterator>(&this->_v_end); }

			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last);

			// void assign (size_type n, const value_type& val);

			void push_back (const value_type& val)
			{
				if (size() >= capacity())
				{
					realloc(capacity() * 2);
					this->_v_end_alloc = this->_v_start + capacity() * 2;
				}
				this->_v[this->size() - 1] = val;
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
			pointer		_v;
			iterator	_v_start;
			iterator	_v_end;
			iterator	_v_end_alloc;

			Vector&	realloc(size_t new_capacity)
			{
				size_t new_size;

				new_size = new_capacity < this->size() ? new_capacity : this->size();
				new_v = _alloc.allocate(new_capacity);
				for (int i = 0; i < new_size; i++)
					alloc.construct(new_v[i], this->_v[i]);	
				for (int i = 0; i < this->size(); i++)
					alloc.destroy(this->_v[i]);
				_alloc.deallocate(this->v, capacity());
				this->_v = new_v;
				this->_v_start = new_v;
				this->_v_end_alloc = _v_start + new_capacity;
				return *this;
			}
	};
}

#endif
