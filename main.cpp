#include <iostream>
#include <string>
#include <list>
#include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
// 	namespace ft = std;
// #else
	#include "Map.hpp"
	#include "Stack.hpp"
	#include "Vector.hpp"
	// #include "AvlTree.hpp"
// #endif

// #include "TestAvlTree.hpp"
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))
/*
template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};
*/

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

	#define T1 char
	#define T2 foo<std::string>

	int		main(void)
	{
		TESTED_NAMESPACE::map<T1, T2> mp;

		mp['a'] = "an element";
		mp['b'] = "another element";
		mp['c'] = mp['b'];
		mp['b'] = "old element";

		printSize(mp);

		std::cout << "insert a new element via operator[]: " << mp['d'] << std::endl;

		printSize(mp);

// int main(void) {
// 	ft::map<char,int> mymap;

//   // first insert function version (single parameter):
//   mymap.insert ( ft::pair<char,int>('a',100) );
//   mymap.insert ( ft::pair<char,int>('z',200) );

//   ft::pair<ft::map<char,int>::iterator,bool> ret;
//   ret = mymap.insert ( ft::pair<char,int>('z',500) );
//   if (ret.second==false) {
//     std::cout << "element 'z' already existed";
//     std::cout << " with a value of " << ret.first->second << '\n';
//   }

//   // second insert function version (with hint position):
//   ft::map<char,int>::iterator it = mymap.begin();
//   mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
//   mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

//   // third insert function version (range insertion):
//   ft::map<char,int> anothermap;
//   anothermap.insert(mymap.begin(),mymap.find('c'));

//   // showing contents:
//   std::cout << "mymap contains:\n";
//   for (it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

//   std::cout << "anothermap contains:\n";
//   for (it=anothermap.begin(); it!=anothermap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';
	// while (1);
	
	// ft::map<char,int>::iterator it;
	// for (it=mymap.begin(); it!=mymap.end(); ++it)
    // 	std::cout << it->first << " => " << it->second << std::endl;

	// map1.erase(pr1.first);
	// map1.erase(pr3.first);
	// map1.erase(pr4.first);
	// map1.erase(pr5.first);
	// map1.erase(pr6.first);
	// map1.erase(pr7.first);

	// map1['a'] = 0;
	// map1['b'] 5= 1;
	// map1['c'] = 2;
	// map1['d'] = 3;
	// map1['e'] = 4;
	// map1['f'] = 5;

	// std::map<char,int>::iterator it2 = map1.begin();
	// it2++;
	// // it2++;
	// if (it2->first)
	// 	std::cout << "YO" << std::endl;
	// for (std::map<char,int>::iterator it=map1.begin(); it!=map1.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << std::endl;


	// if (argc != 2)
	// {
	// 	std::cerr << "Usage: ./test seed" << std::endl;
	// 	std::cerr << "Provide a seed please" << std::endl;
	// 	std::cerr << "Count value:" << COUNT << std::endl;
	// 	return 1;
	// }
	// const int seed = atoi(argv[1]);
	// srand(seed);
	// ft::Vector<int> true_vector;
	// for (int i = 0; i < 5; i++)
	// 	true_vector.push_back(i);
	
	// ft::Vector<int> vector (true_vector);
	// for (int i = 0; i < vector.size(); i++)
	// 	std::cout << "vector["<<i<<"]: " << vector[i] << std::endl;

	// std::cout << "size: " << true_vector.size() << std::endl;

	// vector.reserve(10);
	// std::cout << "capacity: " << vector.capacity() << std::endl;
	// std::cout << "size: " << vector.size() << std::endl;
	// vector.resize(40);
	// std::cout << "capacity: " << vector.capacity() << std::endl;
	// std::cout << "size: " << vector.size() << std::endl;
	// for (int i = 0; i < vector.size(); i++)
	// 	std::cout << "vector["<<i<<"]: " << vector[i] << std::endl;
	// std::cout << vector[6] << std::endl;
	// std::cout << vector.at(6) << std::endl;
	
	// std::vector<int> myvector (4, 100);
	// std::vector<int>::iterator it;

	// it = myvector.begin();
	// it = myvector.insert ( it, 200 );

	// myvector.insert (it + 2, 2, 300);

	// it = myvector.begin();

	// std::vector<int> anothervector (2,400);
	// myvector.insert (it+6,anothervector.begin(),anothervector.end());

	// int myarray [] = { 501,502,503 };
	// myvector.insert (myvector.begin(), myarray, myarray+3);

	// std::cout << "myvector contains:";
	// for (size_t i = 0; i < myvector.size(); i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << std::endl;

	// std::vector<int> thevector (4, 100);
	// std::vector<int>::iterator it2;

	// it2 = thevector.begin();
	// it2 = thevector.insert ( it2, 200 );

	// thevector.insert (it2 + 2, 2, 300);

	// it2 = thevector.begin();

	// std::vector<int> anothervector2 (2,400);
	// thevector.insert (it2+6,anothervector2.begin(),anothervector2.end());

	// int myarray2 [] = { 501,502,503 };
	// thevector.insert (thevector.begin(), myarray2, myarray2+3);

	// std::cout << "thevector contains:";
	// for (size_t i = 0; i < thevector.size(); i++)
	// 	std::cout << ' ' << thevector[i];
	// std::cout << std::endl;

// 	class B {
// 		public:
// 			char *l;
// 			int i;
// 			B():l(nullptr), i(1) {};
// 			B(const int &ex) {
// 				this->i = ex;
// 				this->l = new char('a');
// 			};
// 			virtual ~B() {
// 				delete this->l;
// 				this->l = nullptr;
// 			};
// 	};

// 	class A : public B {
// 		public:
// 		A():B(){};
// 		A(const B* ex){
// 			this->l = new char(*(ex->l));
// 			this->i = ex->i;
// 			if (ex->i == -1) throw "n";
// 		}
// 		~A() {
// 			delete this->l;
// 			this->l = nullptr;
// 		};
// 	};

// 	int val = 600;
// 	std::vector<int> vector;
// 	vector.assign(2600 * val, 1);

// 	std::vector<int> v;
//     v.push_back(*(vector.insert(vector.end() - 800 * val, 44)));
//     v.push_back(vector.size());
//     v.push_back(vector.capacity());
//     std::unique_ptr<B> k2(new B(3));
//     std::unique_ptr<B> k3(new B(4));
//     std::unique_ptr<B> k4(new B(-1));
//     std::vector<A> vv;
//     std::vector<B*> v1;

//     v1.push_back(&(*k2));
//     v1.push_back(&(*k3));
//     v1.push_back(&(*k4));
//     try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//     catch (...) {
//     	v.push_back(vv.size());
//     	v.push_back(vv.capacity());
//     }

// 	std::cout << "vector contains:";
// 	for (int i = 0; i < v.size(); i++)
// 		std::cout << ' ' << v[i];
// 	std::cout << std::endl;


// 	ft::Vector<int> vector2;
// 	vector2.assign(2600 * val, 1);

// 	ft::Vector<int> v2;
//     v2.push_back(*(vector2.insert(vector2.end() - 800 * val, 44)));
//     v2.push_back(vector2.size());
//     v2.push_back(vector2.capacity());
//     std::unique_ptr<B> k5(new B(3));
//     std::unique_ptr<B> k6(new B(4));
//     std::unique_ptr<B> k7(new B(-1));
//     ft::Vector<A> vv2;
//     ft::Vector<B*> v1_bis;

//     v1_bis.push_back(&(*k5));
//     v1_bis.push_back(&(*k6));
//     v1_bis.push_back(&(*k7));
//     try { vv2.insert(vv2.begin(), v1_bis.begin(), v1_bis.end()); }
//     catch (...) {
//     	v2.push_back(vv2.size());
//     	v2.push_back(vv2.capacity());
//     }


// // std::cout << &*v2.rbegin() << std::endl;
// 	std::cout << "vector contains:";
// 	for (int i = 0; i < v2.size(); i++)
// 		std::cout << ' ' << v2[i];
// 	std::cout << std::endl;




	// (void)argc;
	// (void)argv;
	
/*
	std::vector<std::string> vector_str;
	std::vector<int> vector_int;
	ft::stack<int> stack_int;
	std::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	std::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	*/
	return (0);
}
