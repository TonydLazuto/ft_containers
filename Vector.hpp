#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft 
{
	template <typename T, class Alloc = allocator<T> >
	class Vector
	{
		private:
			typedef typename std::vector::allocator_type::allocator allocator;
			typedef typename std::vector::iterator iterator;
			typedef typename std::vector::allocator_type::allocator allocator;
			typedef typename std::vector::allocator_type::allocator allocator;

		public:
			Vector( void )
			{
				allocator();
			}
			Vector(  )
			{
				;
			}
			Vector(  )
			{
				;
			}
			virtual ~Vector( void )
			{
				;
			}
			Vector(Vector const & src)
			{
				;
			}
			Vector& operator=(Vector const & rhs)
			{
				;
			}
			
	};
}


#endif
