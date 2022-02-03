#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft 
{
	template <typename T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			typedef	T value_type;
			typedef typename std::allocator<T> allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef typename  iterator;

			
			explicit Vector( void )
			{
				this->elets = test.allocate(0, 0);
				std::cout << "test address : " << test.address(*p) << std::endl;
				test.construct(p, "hello");
				std::cout << *p << std::endl;
				test.destroy(p);
				// test.deallocate(p);
			// explicit Vector( size_type n, const value_type& val = value_type() )
			}
			// {
			// 	;
			// }
			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last )
			// {
			// 	;
			// }
			virtual ~Vector( void ) {}
			Vector(Vector const & x)
			{ (void)x; }
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

		private:
			allocator_type				test;
			T							*elets;
			random_access_iterator_tag	it;
			// typedef typename std::vector::allocator_type::allocator allocator;
	};
}

#endif
