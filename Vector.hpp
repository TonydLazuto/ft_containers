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

			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc),
				_v(NULL), _v_end(NULL), _v_end_alloc(NULL) {}

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc),
					_v(NULL), _v_end(NULL), _v_end_alloc(NULL)
				{
					if (!n)
						return ;
					else if (n < 0)
						return ;
					_v = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_v + i, val);
					init_pointers(this->_v, n, n);
				}
	
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _alloc(alloc), _v(NULL), _v_end(NULL), _v_end_alloc(NULL)
				{
					size_type diff = 0;
					InputIterator first_cpy = first;

					for (; first_cpy != last; first_cpy++)
						diff++;
					if (!diff)
						return ;
					_v = this->_alloc.allocate(diff);
					for (size_type i = 0; i < diff; i++)
						this->_alloc.construct(_v + i, *first++);
					init_pointers(this->_v, diff, diff);
				}

			virtual ~vector( void )
			{
				clear();
				this->_alloc.deallocate(_v, this->capacity());
			}
			
			vector(const vector& x) : _v(NULL), _v_end(NULL), _v_end_alloc(NULL)
			{
				this->insert(this->begin(), x.begin(), x.end());
			}

			vector& operator=(const vector& x)
			{
				size_type save_capacity = capacity();
				
				if (this->size())
					this->clear();
				if (this->capacity())
					_alloc.deallocate(_v, this->capacity());
				init_pointers(0, 0, 0);
				this->insert(this->begin(), x.begin(), x.end());
				if (capacity() < save_capacity)
					_v_end_alloc = _v + save_capacity;
				return *this;
			}

			iterator begin(void) { return _v; }
			const_iterator begin(void) const { return _v; }
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
			
			size_type size(void) const 
			{
				return static_cast<size_type>(this->_v_end - this->_v);
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
				{
					if (n > size() * 2)
						reserve(n);
					insert(this->end(), n - this->size(), val);
				}
			}
			size_type capacity(void) const
			{
				return static_cast<size_type>(this->_v_end_alloc - this->_v);
			}
			bool empty(void) const { return (this->size() == 0 ? true : false); }
			void reserve (size_type n)
			{
				size_type	save_size = this->size();
				pointer		new_v;

				if (n > max_size())
					throw std::length_error("");
				if (n > capacity())
				{
					new_v = _alloc.allocate(n);
					for (size_type i = 0; i < save_size; i++)
						_alloc.construct(new_v + i, *(this->_v + i));
					this->clear();
					_alloc.deallocate(this->_v, capacity());
					init_pointers(new_v, save_size, n);
				}
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

			reference front(void) { return *this->_v; }

			const_reference front(void) const { return *this->_v; }

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
					this->clear();
					insert(this->begin(), first, last);
				}

			void assign(size_type n, const value_type& val)
			{
				this->clear();
				insert(this->begin(), n, val);
			}

			void push_back(const value_type& val)
			{
				if (capacity() == 0)
					reserve(1);
				else if (size() >= capacity())
					reserve(capacity() * 2);
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

					init_start_values(new_v, pos);
					_alloc.construct(new_v + pos, val);
					init_end_values(new_v, 1, pos);
					destroy_old_vec();
					init_pointers(new_v, new_size, new_capacity);
				}
				else
				{
					init_end_values(NULL, 1, pos);
					_alloc.construct(this->_v + pos, val);
					this->_v_end++;
				}
				return (iterator(this->_v + pos));
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				size_type pos = static_cast<size_type>(position - this->begin());

				if (n == 0)
					return ;
				if (this->size() + n > this->capacity())
				{
					size_type	new_capacity = n;
					size_type	new_size = size() + n;
					pointer		new_v = insert_alloc(new_size, &new_capacity);

					init_start_values(new_v, pos);
					for (size_type i = pos; i < pos + n; i++)
						_alloc.construct(new_v + i, val);
					init_end_values(new_v, n, pos);
					destroy_old_vec();
					init_pointers(new_v, new_size, new_capacity);
				}
				else
				{
					init_end_values(NULL, n, pos);
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
				if (this->size() + n > this->capacity())
				{
					size_type	new_capacity = n;
					size_type	new_size = this->size() + n;
					pointer		new_v = insert_alloc(new_size, &new_capacity);

					init_start_values(new_v, pos);
					for (size_type i = pos; i < pos + n; i++)
						_alloc.construct(new_v + i, *first++);
					init_end_values(new_v, n, pos);
					destroy_old_vec();

					init_pointers(new_v, new_size, new_capacity);
				}
				else
				{
					init_end_values(NULL, n, pos);
					for (size_type i = pos; i < pos + n; i++)
						_alloc.construct(this->_v + i, *first++);
					this->_v_end += n;
				}
			}

			iterator erase(iterator position)
			{
				size_type pos = static_cast<size_type>(position - this->begin());

				_alloc.destroy(&*position);
				if (this->size() > 1)
				{
					for (size_type i = pos + 1; i < this->size(); i++)
					{
						_alloc.construct(_v + i - 1, *(_v + i));
						_alloc.destroy(_v + i);
					}
				}
				this->_v_end--;
				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type len = static_cast<size_type>(last - first);
				size_type fpos = static_cast<size_type>(first - this->begin());
				
				if (&*first == _v)
					erase_start(&fpos, len);
				else if (&*last == _v_end)
					erase_end(&fpos);
				else
					erase_middle(&fpos, len);
				if (len != 0)
					this->_v_end -= len;
				return (first);
			}

			void swap(vector& x)
			{
				pointer tmp_v = x._v;
				pointer tmp_v_end = x._v_end;
				pointer tmp_v_end_alloc = x._v_end_alloc;
				allocator_type tmp_alloc = x._alloc;

				x._v = this->_v;
				x._v_end = this->_v_end;
				x._v_end_alloc = this->_v_end_alloc;
				x._alloc = this->_alloc;

				this->_v = tmp_v;
				this->_v_end = tmp_v_end;
				this->_v_end_alloc = tmp_v_end_alloc;
				this->_alloc = tmp_alloc;
			}

			void clear(void)
			{
				if (this->capacity())
				{
					while (size() != 0)
						this->pop_back();
				}
			}

			allocator_type get_allocator(void) const { return this->_alloc; }


		private:
			allocator_type	_alloc;
			pointer			_v;
			pointer			_v_end;
			pointer			_v_end_alloc;

			void	erase_start(size_type *fpos, size_type len)
			{
				size_type	i = len;

				for ( ; i < size(); ++i)
				{
					_alloc.destroy(_v + *fpos);
					_alloc.construct(_v + (*fpos)++, *(_v + i));
				}
				for ( ; *fpos < len; ++(*fpos))
					_alloc.destroy(_v + *fpos);
			}
			void	erase_end(size_type *fpos)
			{
				for (size_type i = *fpos; i < size(); ++i)
					_alloc.destroy(_v + i);
			}
			void	erase_middle(size_type *fpos, size_type len)
			{
				for (; *fpos < size() - len; ++(*fpos))
				{
					_alloc.destroy(_v + *fpos);
					_alloc.construct(_v + *fpos, *(_v + *fpos + len));
				}
				erase_end(fpos);
			}

			pointer	insert_alloc(size_type new_size, size_type *new_capacity)
			{
				*new_capacity = new_size;
				if (_v && size() && new_size < capacity() * 2)
					*new_capacity = size() * 2;				
				return (_alloc.allocate(*new_capacity));
			}

			void	init_start_values(pointer new_v, size_type pos)
			{
				for (size_type i = 0; i < pos; i++)
					_alloc.construct(new_v + i, *(this->_v + i));
			}
			void	destroy_old_vec(void)
			{
				for (size_type i = 0; i < this->size(); i++)
					_alloc.destroy(this->_v + i);
				_alloc.deallocate(this->_v, capacity());
			}

			void	init_end_values(pointer new_v, size_type n, size_type pos)
			{
				pointer my_v = new_v != NULL ? new_v : this->_v;

				for (size_type i = this->size(); i > pos; i--)
					_alloc.construct(my_v + i + n - 1, *(this->_v + i - 1));
			}

			void	init_pointers(pointer new_v, size_type new_size,
						size_type new_capacity)
			{
				this->_v = new_v;
				this->_v_end = new_v + new_size;
				this->_v_end_alloc = new_v + new_capacity;
			}
			
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
