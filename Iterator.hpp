#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iostream>

namespace ft
{
	class random_access_iterator_tag {};
	class bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class Iterator
	{
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};
}

#endif
