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
		
		Pair( void );
		virtual ~Pair( void );

		template<class U, class V>
		pair (const pair<U, V>& pr);

		pair (const first_type& a, const second_type& b);

		Pair& operator=(Pair const & rhs);

		Pair( std::string type );

		
		
	};

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



