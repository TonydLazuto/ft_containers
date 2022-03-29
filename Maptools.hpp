#ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>

namespace ft 
{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1 first_type;
		typedef	T2 second_type;

		first_type	first;
		second_type	second;
		
		pair( void ) : first(), second() {}
		virtual ~pair( void ) {}

		template<class U, class V>
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator=(pair const& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}

		pair& operator=(pair const* pr) // ...
		{
			this->first = pr->first;
			this->second = pr->second;
			return *this;
		}
	};

	// template <class T1, class T2>
	// std::ostream & operator<<(std::ostream &o, const ft::pair<T1, T2> pair)
	// {
	// 	o << "pair.first: " << pair.first << std::endl << "pair.second: " << pair.second << std::endl;
	// 	return o;
	// }

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs.first == rhs.first); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs.first < lhs.first); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (rhs.first < lhs.first); }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs.first < rhs.first); }


	template <class T1,class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x, y) );
	}

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return (x < y); }
	};
}

#endif
