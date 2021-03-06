#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

#include <iostream>

namespace ft 
{

	template <class Iterator>
	struct IteratorTraits
	{
		public:
			IteratorTraits( void ) {}
			virtual ~IteratorTraits( void ) {}
			IteratorTraits(IteratorTraits const & src) { (void)src; }
			IteratorTraits& operator=(IteratorTraits const & rhs) {
				(void)rhs;
				return *this;
			}
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;

	};

	template <class T>
	struct IteratorTraits<T*>
	{
		protected:

		public:
			IteratorTraits( void ) {}
			virtual ~IteratorTraits( void ) {}
			IteratorTraits(IteratorTraits const & src) { (void)src; }
			IteratorTraits& operator=(IteratorTraits const & rhs) {
					(void)rhs;
					return *this;
			}
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct IteratorTraits<const T*>
	{
		protected:

		public:
			IteratorTraits( void ) {}
			virtual ~IteratorTraits( void ) {}
			IteratorTraits(IteratorTraits const & src) { (void)src; }
			IteratorTraits& operator=(IteratorTraits const & rhs) {
					(void)rhs;
					return *this;
			}
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef std::random_access_iterator_tag iterator_category;
	};
}

#endif
