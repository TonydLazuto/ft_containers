#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include "IteratorTraits.hpp"
#include "RandomAccess.hpp"

template<class T>
class Vector_itor : public Itor<T>
{
	// Vector implementation Vector<T>& v;
	size_t index; // index of current element public:
	Vector_itor(Vector<T>&vv):v(vv),index(0){}
	T* first() { return (v.size()) ? &v[index=0] : 0; }
	T* next() { return (++index<v.size()) ? &v[index] : 0; }
};

namespace ft 
{
	template <typename T, class Alloc = std::allocator<T> >
	class Vector : public RandomAccess
	{
		public:
			typedef	T value_type;
			typedef typename std::allocator<T> allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef IteratorTraits<T>::difference_type difference_type;
			typedef typename size_type;

			
			explicit Vector( void )
			{
				// this->elets = test.allocate(0, 0);
				// std::cout << "test address : " << test.address(*p) << std::endl;
				// test.construct(p, "hello");
				// std::cout << *p << std::endl;
				// test.destroy(p);
				// test.deallocate(p);
			}
			// explicit Vector( size_type n, const value_type& val = value_type() )
			// {
			// 	;
			// }
			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last )
			// {
			// 	;
			// }
			virtual ~Vector( void ) {}
			Vector(Vector const & x) { (void)x; }

			Vector& operator=(const Vector& x) {}

			iterator begin(void)
			{
				// return this->
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
			size_type size() const 
			{
				// return size_type(this->_M_impl._M_finish - this->_M_impl._M_start);
			}
			size_type max_size() const;

			void resize (size_type n, value_type val = value_type());

			size_type capacity() const;

			bool empty() const;

			void reserve (size_type n);

			reference operator[] (size_type n);

			const_reference operator[] (size_type n) const;

			reference at (size_type n);

			const_reference at (size_type n) const;

			reference front();

			const_reference front() const;

			reference back();

			const_reference back() const;

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last);

			void assign (size_type n, const value_type& val);

			void push_back (const value_type& val);

			void pop_back();

			iterator insert (iterator position, const value_type& val);

			void insert (iterator position, size_type n, const value_type& val);

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);

			iterator erase (iterator first, iterator last);

			void swap (Vector& x);

			void clear();

			allocator_type get_allocator() const;
			
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
			allocator_type			test;
			pointer					elets;
			random_access_iterator_tag	it;
			typedef struct	s_pointer_info {
				pointer _v_start;
				pointer _v_end;
				pointer _v_end_alloc;
			}				t_pointer_info;
			
			// typedef typename std::vector::allocator_type::allocator allocator;
	};
}

#endif
