#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"

#include <stdlib.h>
#include <chrono>
using namespace std::chrono;

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define TESTED_NAMESPACE ft

#define _pair TESTED_NAMESPACE::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
	typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}
// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo


#define T1 int
#define T2 char
typedef _pair<const T1, T2> T3;

int		main(void)
{

	std::list<T3> lst;
	unsigned int lst_size = 91;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, i + 65));
	TESTED_NAMESPACE::map<T1, T2> mp;

	unsigned int nb_lists = 100000;

	auto start = high_resolution_clock::now();
	for (unsigned int i = 0; i < nb_lists ; ++i)
	{
		std::list<T3> tmp;
		for (unsigned int j = 0; j < lst_size; ++j)
			tmp.push_back(T3(i, j + 65));
		mp.insert(tmp.begin(), tmp.end());
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	// To get the value of duration use the count()
	// member function on the duration object
	std::cout << "Time taken for insert: " << duration.count() << std::endl;

	// mp.print();
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int val = rand() % nb_lists + 1;
		std::cout << "val: " << mp.find(val)->first << std::endl;
	}

	std::cout << "mp.size(): " << mp.size() << std::endl;
	std::cout << "mp.max_size(): " << mp.max_size() << std::endl;

	auto start2 = high_resolution_clock::now();
	for (unsigned int i = 0; i < nb_lists ; ++i)
	{
		mp.erase(i);
	}
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<milliseconds>(stop2 - start2);
	std::cout << "Time taken for erase: " << duration2.count() << std::endl;

return (0);
}
