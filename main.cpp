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

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

void	printSize(ft::vector<int> const &vct)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size:" << vct.max_size() << std::endl << std::endl;
	std::cout << "Content is:" << std::endl;
	for (unsigned long int i = 0; i < vct.size(); ++i)
		std::cout << "- " << vct[i] << std::endl;
	std::cout << "###############################################" << std::endl;
}

int main(int argc, char** argv) {
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

int		main(void)
{
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::iterator it_0(vct.begin());
	ft::vector<int>::iterator it_1(vct.end());
	ft::vector<int>::iterator it_mid;

	ft::vector<int>::const_iterator cit_0 = vct.begin();
	ft::vector<int>::const_iterator cit_1;
	ft::vector<int>::const_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	printSize(vct, 1);
	it_0 = vct.begin();
	cit_1 = vct.end();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

	std::cout << "\t\tft_eq_ope:" << std::endl;
	// regular it
	ft_eq_ope(it_0 + 3, it_mid);
	ft_eq_ope(it_0, it_1);
	ft_eq_ope(it_1 - 3, it_mid);
	// const it
	ft_eq_ope(cit_0 + 3, cit_mid);
	ft_eq_ope(cit_0, cit_1);
	ft_eq_ope(cit_1 - 3, cit_mid);
	// both it
	ft_eq_ope(it_0 + 3, cit_mid);
	ft_eq_ope(it_mid, cit_0 + 3);
	ft_eq_ope(it_0, cit_1);
	ft_eq_ope(it_1, cit_0);
	ft_eq_ope(it_1 - 3, cit_mid);
	ft_eq_ope(it_mid, cit_1 - 3);



	// ft::vector<int> myvector (4, 100);
	// ft::vector<int>::iterator it;

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
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
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
	ft::vector<Buffer>().swap(vector_buffer);

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
