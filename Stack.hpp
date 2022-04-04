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

			explicit stack (const container_type& ctnr = container_type())
			: _ctnr(ctnr) {}
			
			virtual ~stack( void ) {}

			stack(const stack& x) : _ctnr(x._ctnr) {}

			stack& operator=(const stack& x)
			{
				_ctnr = x._ctnr;
				return *this;
			}

			bool empty() const
			{
				return (_ctnr.empty());
			}

			size_type size() const { return (_ctnr.size()); }

			value_type& top() { return (_ctnr.back()); }

			const value_type& top() const { return (_ctnr.back()); }

			void push (const value_type& val)
			{
				_ctnr.push_back(val);
			}

			void pop()
			{
				_ctnr.pop_back();
			}
			template <class Tbis, class ContainerBis>
				friend bool operator==(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);

			template <class Tbis, class ContainerBis>
				friend bool operator!=(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);
			
			template <class Tbis, class ContainerBis>
				friend bool operator<(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);

			template <class Tbis, class ContainerBis>
				friend bool operator<=(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);

			template <class Tbis, class ContainerBis>
				friend bool operator>(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);

			template <class Tbis, class ContainerBis>
				friend bool operator>=(const ft::stack<Tbis, ContainerBis>& lhs, const ft::stack<Tbis, ContainerBis>& rhs);


		protected:
			container_type _ctnr;
			
			
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr != rhs._ctnr);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr <= rhs._ctnr);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr > rhs._ctnr);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._ctnr >= rhs._ctnr);
	}

}

#endif
