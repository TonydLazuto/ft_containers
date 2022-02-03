#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

#include <iostream>
#include <Iterator>

template <class Iterator>
class IteratorTraits
{
	public:
		IteratorTraits( void ) {}
		virtual ~IteratorTraits( void ) {}
		IteratorTraits(IteratorTraits const & src) { (void)src; }
		IteratorTraits& operator=(IteratorTraits const & rhs) {
			(void)rhs;
			return *this;
		}
};

template <class T>
class IteratorTraits<T*>
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
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
class IteratorTraits<const T*>
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
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
};

#endif
