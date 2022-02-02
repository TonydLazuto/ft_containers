#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP

#include <iostream>
#include "Iterator.hpp"

template <class Iterator>
class IteratorTraits : public Iterator
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
class IteratorTraits<T*> : public Iterator
{
	protected:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;

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
class IteratorTraits<const T*> : public Iterator
{
	protected:
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;

	public:
		IteratorTraits( void ) {}
		virtual ~IteratorTraits( void ) {}
		IteratorTraits(IteratorTraits const & src) { (void)src; }
		IteratorTraits& operator=(IteratorTraits const & rhs) {
			(void)rhs;
			return *this;
		}
};

#endif
