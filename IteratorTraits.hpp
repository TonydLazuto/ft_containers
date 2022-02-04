#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

#include <iostream>
#include <Iterator>
#include <cstddef>
#include "RandomAccess.hpp"

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
	typedef Iterator::difference_type difference_type;
	typedef Iterator::value_type value_type;
	typedef Iterator::pointer pointer;
	typedef Iterator::reference reference;
	typedef Iterator::iterator_category iterator_category
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
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef RandomAccessIterator iterator_category;
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
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef RandomAccessIterator iterator_category;
};

#endif
