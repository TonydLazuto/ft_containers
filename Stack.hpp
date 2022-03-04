#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include "Vector.hpp"

namespace ft 
{
	template <class T, class Container = vector<T> >
	class stack
	{

		public:
			typedef	T value_type;
			typedef	Container container_type;
			typedef size_t size_type;

			explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {}
			
			virtual ~stack( void ) {}

			bool empty() const
			{
				if (_ctnr.empty())
					return (true);
				return (false);
			}

			size_type size() const { return _ctnr.size(); }

			value_type& top() { return _ctnr.back(); }

			const value_type& top() const { return _ctnr.back(); }

			void push (const value_type& val)
			{
				_ctnr.push_back(val);
			}

			void pop()
			{
				_ctnr.pop_back();
			}


		private:
			container_type _ctnr;
			
			
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return ft::stack<T, Container>:c.operator==(lhs, rhs);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif
