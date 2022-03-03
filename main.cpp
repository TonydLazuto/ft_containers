#include <iostream>
#include <string>
#include <list>
#include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
	#include <vector>
// 	namespace ft = std;
// #else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include "Vector.hpp"
// #endif

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



void	printSize(std::vector<int> const &vct)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size:" << vct.max_size() << std::endl << std::endl;
	std::cout << "Content is:" << std::endl;
	for (unsigned long int i = 0; i < vct.size(); ++i)
		std::cout << "- " << vct[i] << std::endl;
	std::cout << "###############################################" << std::endl;
}

class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template <class T>
void	print(std::vector<T> &test)
{
	typename std::vector<T>::iterator		beg = test.begin();
	typename std::vector<T>::iterator		end = test.end();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename std::vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void	push_pop_back_tests(void)
{
	std::cout << std::endl << "PUSH BACK & POP BACK TESTS" << std::endl;
	std::vector<T> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(i);
		std::cout << test.size() << ": " << test.capacity() << " - ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	print<T>(test);
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	print<T>(test);
}

template <class T>
void	resize_tests(void)
{
	std::cout << std::endl << "RESIZE TESTS" << std::endl;
	std::vector<T> test(12, 12);

	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
}

template <class T>
void	insert_tests()
{
	std::cout << std::endl << "INSERT TESTS" << std::endl;
	std::vector<T> test(1, 1);
	std::vector<T> test2(5, 5);

	test.insert(test.begin(), 200, 12);
	print<T>(test);
	test.insert(test.begin() + 12, 200, 30);
	print<T>(test);
	test.insert(test.end(), 12, 50);
	print<T>(test);
	test.insert(test.end() - 1, 0, 60);
	print<T>(test);
	test.insert(test.end() - 1, 1, 70);
	print<T>(test);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	print<T>(test);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	print<T>(test);
	test.insert(test.end(), test2.begin(), test2.end());
	print<T>(test);
}

template <class T>
void	reserve_tests(void)
{
	std::cout << std::endl << "RESERVE TESTS" << std::endl;
	std::vector<T> test(65, 7);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(66);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(128);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(1023);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(10252);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	try
	{
		test.reserve(test.max_size() + 1);
	}
	catch(std::length_error &le)
	{
		std::cout << "length error" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	print<T>(test);
}

template <class T>
void	copy_swap_tests(void)
{
	std::cout << std::endl << "COPY && SWAP TESTS" << std::endl;
	std::vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	std::vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	print<T>(test_copy);
	std::vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print<T>(test_range);
	test_copy.swap(test);
	print<T>(test);
	print<T>(test_copy);
	test_copy.swap(test_range);
	print<T>(test_range);
	print<T>(test_copy);
	test.swap(test_copy);
	print<T>(test);
	print<T>(test_copy);
}

template <class T>
void	reverse_it_tests(void)
{
	std::cout << std::endl << "REVERSE IT TESTS" << std::endl;
	std::vector<T> test;
	for (size_t i = 0; i < 12; i++) { test.push_back(i); }
	typename std::vector<T>::reverse_iterator		revbeg = test.rbegin();
	for (typename std::vector<T>::reverse_iterator it = revbeg; it != test.rend(); it++)
	{
		std::cout << *it << " ";
		if (!((revbeg - it) % 10) && it != revbeg)
			std::cout << std::endl;
	}
	std::cout << *(test.rbegin() + 2) << std::endl;
	std::cout << *(test.rend() - 8) << std::endl;
	std::cout << (test.rbegin() == revbeg) << std::endl;
	revbeg++;
	std::cout << *revbeg << std::endl;
	std::cout << (test.rbegin() == test.rend()) << std::endl;
	std::cout << (test.rbegin() <= test.rbegin()) << std::endl;
	std::cout << (test.rbegin() < test.rend()) << std::endl;
	std::cout << (test.rbegin() >= test.rend()) << std::endl;
	revbeg += 3;
	std::cout << *revbeg << std::endl;
	std::cout << std::endl;
}

template <class T>
void	erase_clear_tests(void)
{
	std::cout << std::endl << "ERASE && CLEAR TESTS" << std::endl;
	std::vector<T> test(31, 12);
	test.erase(test.begin(), test.begin() + 5);
	print<T>(test);
	test.erase(test.begin() + 12, test.begin() + 16);
	print<T>(test);
	test.clear();
	print<T>(test);
}

void	max_size_tests(void)
{
	std::cout << std::endl << "MAX SIZE TESTS" << std::endl;
	std::vector<int> test(31, 12);
	std::vector<std::string> test2;
	std::vector<long long int> test3;
	std::vector<Awesome> test4;
	std::vector<unsigned int> test5(12, 340);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
}

void	awesome_tests(void)
{
	std::cout << std::endl << "AWESOME TESTS" << std::endl;
	std::vector<Awesome> test(21, 12);
	print<Awesome>(test);
	std::vector<Awesome> test2;
	print<Awesome>(test2);
	test2.push_back(12);
	test2.push_back(8);
	test2.push_back(16);
	print<Awesome>(test2);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.assign(test2.begin(), test2.end());
	print<Awesome>(test);
	test = test2;
	print<Awesome>(test);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.insert(test.end(), test2.begin(), test2.end());
	print<Awesome>(test);
	test.insert(test.begin(), test2.begin(), test2.end());
	test2 = test;
	print<Awesome>(test);
	std::cout << "end awesome test" << std::endl;
}

int main(int argc, char** argv) {
	

	push_pop_back_tests<int>();
	resize_tests<int>();
	insert_tests<int>();
	reserve_tests<int>();
	copy_swap_tests<int>();
	reverse_it_tests<int>();
	erase_clear_tests<int>();
	max_size_tests();
	awesome_tests();
	push_pop_back_tests<Awesome>();
	resize_tests<Awesome>();
	// insert_tests<Awesome>();
	// reserve_tests<Awesome>();
	// copy_swap_tests<Awesome>();
	// reverse_it_tests<Awesome>();
	// erase_clear_tests<Awesome>();



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




	(void)argc;
	(void)argv;
	
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
