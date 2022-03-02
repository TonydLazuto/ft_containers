#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <iterator>
#include "RandomAccess.hpp"
#include "IteratorTraits.hpp"
#include "ReverseIterator.hpp"
#include "Lexicographical.hpp"
#include "IsIntegral.hpp"
#include "EnableIf.hpp"


namespace ft 
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
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
			typedef typename ft::ReverseIterator<iterator> reverse_iterator;
			typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;

			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				this->_v = NULL;
				this->_v_start = NULL;
				this->_v_end = NULL;
				this->_v_end_alloc = NULL;
			}

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
				{
					this->_v = NULL;
					this->_v_start = NULL;
					this->_v_end = NULL;
					this->_v_end_alloc = NULL;
					if (!n)
						return ;
					else if (n < 0)
						return ;
					_v = _alloc.allocate(n);
					pointer p = _v;
					while (p < _v + n)
					{
						_alloc.construct(p, val);
						p++;
					}
					this->_v_start = this->_v;
					this->_v_end = p;
					this->_v_end_alloc = p;
				}
	
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _alloc(alloc), _v(NULL), _v_start(NULL), _v_end(NULL), _v_end_alloc(NULL)
				{
					size_type diff = 0;
					InputIterator first_cpy = first;

					this->_v = NULL;
					this->_v_start = NULL;
					this->_v_end = NULL;
					this->_v_end_alloc = NULL;
					for (; first_cpy != last; first_cpy++)
						diff++;
					if (!diff)
						return ;
					_v = this->_alloc.allocate(diff);
					this->_v_start = this->_v;
					for (size_type i = 0; i < diff; i++)
						this->_alloc.construct(_v + i, *first++);
					this->_v_end = _v_start + diff;
					this->_v_end_alloc = _v_start + diff;
					// this->insert(this->begin(), first, last);
				}

			virtual ~vector( void )
			{
				clear();
				this->_alloc.deallocate(_v, this->capacity());
			}
			
			vector(const vector& x)
			{
				this->_alloc = x._alloc;
				this->_v = NULL;
				this->_v_start = NULL;
				this->_v_end = NULL;
				this->_v_end_alloc = NULL;
				this->insert(this->begin(), x.begin(), x.end());
			}
			vector& operator=(const vector& x)
			{
				this->_alloc = x._alloc;
				this->_v = NULL;
				this->_v_start = NULL;
				this->_v_end = NULL;
				this->_v_end_alloc = NULL;
				this->clear();
				this->insert(this->begin(), x.begin(), x.end());
				return *this;
			}

			iterator begin(void) { return _v_start; }
			const_iterator begin(void) const { return _v_start; }
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
					return _v_start;
				return (_v_end);
			}
			const_iterator end(void) const
			{
				if (empty())
					return _v_start;
				return (_v_end);
			}
			reverse_iterator rend(void) { return (reverse_iterator(_v_start)); }
			const_reverse_iterator rend(void) const { return (reverse_iterator(_v_start)); }
			
			size_type size(void) const 
			{
				return static_cast<size_type>(this->_v_end - this->_v_start);
			}
			size_type max_size(void) const
			{
				return (_alloc.max_size());
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n == 0)
					this->clear();
				else if (n < this->size())
					erase(this->begin() + n, this->end());
				else if (n > this->size())
					insert(this->end(), n - this->size(), val);
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
					throw std::out_of_range("");
				}
				return ((*this)[n]);
			}

			const_reference at (size_type n) const
			{
				if (n >= size())
				{
					throw std::out_of_range("");
				}
				return (const_cast<const_reference>((*this)[n]));
			}

			/*
				Indexing is done by operator[]() and at();
				operator[]() provides unchecked access,
				whereas at() does a range check and throws out_of_range
				if an index is out of range (try catch)
			 */

			reference front(void) { return *this->_v_start; }

			const_reference front(void) const { return *this->_v_start; }

			reference back(void)
			{
				return (*(this->_v_end - 1));
			}

			const_reference back(void) const
			{
				return (*(this->_v_end - 1));
			}

			template <class InputIterator>
  				void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				{
					erase(this->begin(), this->end());
					insert(this->begin(), first, last);
				}

			void assign(size_type n, const value_type& val)
			{
				erase(this->begin(), this->end());
				insert(this->begin(), n, val);
			}

			void push_back(const value_type& val)
			{
				if (capacity() == 0)
					realloc(1);
				else if (size() >= capacity())
					realloc(capacity() * 2);
				_alloc.construct(_v_end, val);
				this->_v_end++;
			}

			void pop_back(void)
			{
				_alloc.destroy(&this->back());
				this->_v_end--;
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type pos = static_cast<size_type>(position - this->begin());

				if (this->size() + 1 > this->capacity())
				{
					size_type	new_capacity = 1;
					size_type	new_size = this->size() + 1;
					pointer		new_v = insert_alloc(new_size, &new_capacity);

					insert_start_values(new_v, pos);
					_alloc.construct(new_v + pos, val);
					insert_end_values(new_v, 1, pos);
					insert_destroy_old_vec();
					insert_init_new_vec(new_v, new_size, new_capacity);
				}
				else
				{
					insert_end_values(NULL, 1, pos);
					_alloc.construct(this->_v + pos, val);
					this->_v_end++;
				}
				return (iterator(this->_v_start + pos));
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				size_type pos = static_cast<size_type>(position - this->begin());
				// if (position > this->end() || this->size() < 0)
				// 	throw ValueOutOfRange();
				if (this->size() + n > this->capacity())
				{
					size_type	new_capacity = n;
					size_type	new_size = this->size() + n;
					pointer		new_v = insert_alloc(new_size, &new_capacity);

					insert_start_values(new_v, pos);
					for (size_type i = pos; i < pos + n; i++)
						_alloc.construct(new_v + i, val);
					insert_end_values(new_v, n, pos);
					insert_destroy_old_vec();
					insert_init_new_vec(new_v, new_size, new_capacity);
				}
				else
				{
					insert_end_values(NULL, n, pos);
					for (size_type i = pos; i < pos + n; i++)
						_alloc.construct(this->_v + i, val);
					this->_v_end += n;
				}
			}
			

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type pos = static_cast<size_type>(position - this->begin());
				size_type n = 0;
				InputIterator first_cpy = first;
				for (; first_cpy != last; ++first_cpy)
					n++;
				// if (position > this->end() || this->size() < 0)
				// 	throw ValueOutOfRange();
				if (this->size() + n > this->capacity())
				{
					size_type	new_capacity = n;
					size_type	new_size = this->size() + n;
					pointer		new_v = insert_alloc(new_size, &new_capacity);

					insert_start_values(new_v, pos);
					for (size_type i = pos; i < pos + n; i++)
					{
						_alloc.construct(new_v + i, *first);
						first++;
					}
					insert_end_values(new_v, n, pos);
					insert_destroy_old_vec();
					insert_init_new_vec(new_v, new_size, new_capacity);
				}
				else
				{
					insert_end_values(NULL, n, pos);
					for (size_type i = pos; i < pos + n; i++)
					{
						_alloc.construct(this->_v + i, *first);
						first++;
					}
					this->_v_end += n;
				}
			}

			void	insert_start_values(pointer new_v, size_type pos)
			{
				for (size_type i = 0; i < pos; i++)
					_alloc.construct(new_v + i, *(this->_v + i));
			}
			void	insert_destroy_old_vec(void)
			{
				// for (size_type i = 0; i < this->size(); i++)
				// 	_alloc.destroy(this->_v + i);
				_alloc.deallocate(this->_v, capacity());
			}

			void	insert_end_values(pointer new_v, size_type n, size_type pos)
			{
				pointer my_v = new_v != NULL ? new_v : this->_v;

				for (size_type i = this->size(); i > pos; i--)
					_alloc.construct(my_v + i + n - 1, *(this->_v + i - 1));
			}


			iterator erase(iterator position)
			{
				// if (position >= this->end() || this->size() <= 0)
					// throw ValueOutOfRange();
				size_type pos = static_cast<size_type>(position - this->begin());

				_alloc.destroy(&*position);
				if (this->size() > 1)
				{
					for (size_type i = pos; i < this->size() - 1; i++)
						_alloc.construct(_v + i, *(_v + i + 1));
					_alloc.destroy(&this->back());
				}
				this->_v_end--;
				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				// if (last >= this->end() || this->size() <= 0)
					// throw ValueOutOfRange();
				size_type len = static_cast<size_type>(last - first);
				size_type fpos = static_cast<size_type>(first - this->begin());
				
				if (&*first == _v_start)
					erase_start(&fpos, len);
				else if (&*last == _v_end)
					erase_end(&fpos, len);
				else
					erase_middle(&fpos, len);

				// bool select_erase[3] = {
				// 	&*first == _v_start,
				// 	&*last == _v_end,
				// 	true
				// };

				// EraseMemFn ft_erase[] = {
				// 	&vector::erase_start(&fpos, len),
				// 	&vector::erase_end(&fpos, len),
				// 	&vector::erase_middle(&fpos, len)
				// };
				// int i = 0;
				// while (!select_erase[i])
				// 	i++;
				// (this->*ft_erase[i])(&fpos, len);

				if (len != 0)
					this->_v_end -= len;
				return (first);
			}

			void swap(vector& x)
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
				size_type tmp_size = this->size();
				if (this->capacity())
				{
					while (tmp_size != 0)
					{
						this->_alloc.destroy(&this->back());
						this->_v_end--;
						tmp_size--;
					}
				}
			}

			allocator_type get_allocator(void) const { return this->_alloc; }


		private:
			allocator_type	_alloc;
			pointer			_v;
			pointer			_v_start;
			pointer			_v_end;
			pointer			_v_end_alloc;

			vector&	realloc(size_t new_capacity)
			{
				size_type	new_size = new_capacity < this->size() ? new_capacity : this->size();
				pointer		new_v = _alloc.allocate(new_capacity);

				for (size_type i = 0; i < new_size; i++)
					_alloc.construct(new_v + i, this->_v[i]);
				// for (size_type i = new_size; i < new_capacity; i++)
				// 	_alloc.construct(new_v + i, 0);
				for (size_type i = 0; i < this->size(); i++)
					_alloc.destroy(this->_v + i);
				if (this->_v_start)
					_alloc.deallocate(this->_v, capacity());
				this->_v = new_v;
				this->_v_start = new_v;
				this->_v_end = new_v + new_size;
				this->_v_end_alloc = new_v + new_capacity;
				return *this;
			}

			void	erase_start(size_type *fpos, size_type len)
			{
				size_type	i = len;
				size_type	j = *fpos;

				for ( ; i < size(); ++i)
					_alloc.construct(_v + j++, *(_v + i));
				for ( ; j < len; ++j)
					_alloc.destroy(_v + j);
			}
			void	erase_end(size_type *fpos, size_type len)
			{
				for (size_type i = *fpos + len; i < size(); ++i)
					_alloc.destroy(_v + i);
			}
			void	erase_middle(size_type *fpos, size_type len)
			{
				for (; *fpos < len; (*fpos)++)
					_alloc.construct(_v + *fpos, *(_v + *fpos + len));
				erase_end(fpos, len);
			}

			pointer	insert_alloc(size_type new_size, size_type *new_capacity)
			{
				size_type	double_cap = this->capacity() * 2;
				
				if (this->capacity())
				{
					if (new_size > double_cap)
						*new_capacity = new_size;
					else
						*new_capacity = double_cap;
				}
				return (_alloc.allocate(*new_capacity));
			}

			void	insert_init_new_vec(pointer new_v, size_type new_size,
						size_type new_capacity)
			{
				this->_v = new_v;
				this->_v_start = new_v;
				this->_v_end = new_v + new_size;
				this->_v_end_alloc = new_v + new_capacity;
			}
			
			// typedef void (vector::*EraseMemFn)( size_type, size_type );
	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
				return (false);
			typename ft::vector<T>::const_iterator first1 = lhs.begin();
			typename ft::vector<T>::const_iterator first2 = rhs.begin();
			while (first1 != lhs.end())
			{
				if (first2 == rhs.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
