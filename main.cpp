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


void	printSize(ft::vector<std::string> const &vct)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size:" << vct.max_size() << std::endl << std::endl;
	std::cout << "Content is:" << std::endl;
	for (unsigned long int i = 0; i < vct.size(); ++i)
		std::cout << "- " << vct[i] << std::endl;
	std::cout << "###############################################" << std::endl;
}

void print_vector(ft::vector<int> v)
{
	ft::vector<int>::iterator it1;
	ft::vector<int>::iterator it2;

	it1 = v.begin();
	it2 = v.end();

	std::cout << "Vector=[";
	while (it1 < it2)
	{
		std::cout << *it1;
		std::cout << ", ";
		it1++;
	}
	std::cout << "]" << std::endl;
}

int main(int argc, char** argv) {

	ft::vector<int> fill1(10, 42);

	ft::vector<int> tmp1 = fill1;


	std::cout << "INITIALIZATION" << std::endl;
	std::cout << "operations..." << std::endl;
	ft::vector<int> fill(10, 42);
	ft::vector<int> tmp;
	ft::vector<int>::iterator it1;
	ft::vector<int>::iterator it2;
	std::cout << "print..." << std::endl;
	print_vector(fill);

	std::cout << "ERASE" << std::endl;
	std::cout << "operations..." << std::endl;
	it1 = fill.begin();
	it1 += 5;
	it2 = fill.end();
	it2 -=2;

	fill.erase(it1, it2);
	std::cout << "print..." << std::endl;
	print_vector(fill);

	std::cout << "POP_BACK/PUSH_BACK" << std::endl;
	std::cout << "operations..." << std::endl;
	fill.pop_back();
	fill.push_back(13);
	fill.push_back(69);
	std::cout << "print..." << std::endl;
	print_vector(fill);

	std::cout << "OPERATOR[]" << std::endl;
	std::cout << "operations..." << std::endl;
	fill[3] = -13;
	fill[5] = 123456789;
	std::cout << "print..." << std::endl;
	print_vector(fill);
	
	std::cout << "SWAP" << std::endl;
	std::cout << "operations..." << std::endl;
	fill.swap(tmp);
	fill.swap(tmp);
	std::cout << "print..." << std::endl;
	print_vector(fill);

	std::cout << "FRONT/BACK/AT" << std::endl;
	std::cout << "operations..." << std::endl;
	fill.front() = -42;
	fill.back() /= -2;
	fill.at(1) = 0;
	std::cout << "print..." << std::endl;
	print_vector(fill);

	std::cout << "INSERT" << std::endl;
	std::cout << "operations..." << std::endl;
	it1 = fill.begin();
	it1 += 2;

	fill.insert(it1, 3, 987654321);
	std::cout << "print..." << std::endl;
	print_vector(fill);


	std::cout << "RESIZE" << std::endl;
	std::cout << "operations..." << std::endl;
	fill.resize(20);
	fill.resize(13);
	std::cout << "print..." << std::endl;
	print_vector(fill);

	try
	{
		std::cout << "AT(error)" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.at(-1) = -1;
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OOR error caught\n";
	}
	try
	{
		fill.at(15) = -1;
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OOR error caught\n";
	}
	std::cout << "print..." << std::endl;
	print_vector(fill);

/*
	ft::vector<int> JOHN;
	ft::vector<int> BOB(5, 8);
	std::cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		std::cout << BOB[i] << ' ';
	std::cout << '\n';
	ft::vector<int> MIKE(BOB);

	// CTORs
	std::cout << "\nCTORS\n";
	std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;


	// RESIZE
	size_t	bob_resize = 2;
	std::cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;
	
	BOB.resize(bob_resize);
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// RESERVE
	std::cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//AT
	std::cout << "\nAT\n";
	try
	{
		std::cout << MIKE.at(2) << '\n';
		std::cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OOR error caught\n";
	}

	// FRONT / BACK
	std::cout << "\nFRONT / BACK\n";
	std::cout << "front() of MIKE : " << MIKE.front() << '\n';
	std::cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	std::cout << "\nASSIGN\n";
	BOB.assign(42, 7);

	//ASSIGN RANGE
	std::cout << "\nASSIGN RANGE\n";
	ft::vector<int>	assign_range;
	assign_range.assign(8, 5);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	std::cout << "\nEMPTY\n";
	std::cout << "BOB is empty ? " << BOB.empty() << '\n';
	std::cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	std::cout << "\nPUSH/POP_BACK\n";
	BOB.push_back(53);
	std::cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	std::cout << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	std::cout << "\nINSERT\n";
	ft::vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::const_iterator const_it(insert_in_me.begin());
	std::cout << "Const it : " << std::endl;
	std::cout << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	std::cout << "\nINSERT\n";
	ft::vector<int>	std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(i);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		std::cout << std_insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, 42);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		std::cout << std_insert_in_me.at(i) << ' ';
	std::cout << '\n';


	//INSERT RANGE
	std::cout << "\nINSERT RANGE\n";
	ft::vector<int>	insert_bis;
	for (int i = 0; i < 7; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		std::cout << insert_bis[i] << ' ';
	std::cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		std::cout << insert_bis[i] << ' ';
	std::cout << '\n';


	//ERASE
	std::cout << "\nERASE\n";
	ft::vector<int>	erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	//SWAP
	std::cout << "\nSWAP\n";
	BOB.swap(MIKE);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	MIKE.swap(JOHN);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//CLEAR
	std::cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//NON MEMBER Functions
	std::cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;
	
	//RELATIONAL OPERATORS
	std::cout << "\nRELATIONAL OPERATORS\n";
	ft::vector<int> MIKE_2(MIKE);
	std::cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	std::cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	std::cout << "\nReal ft::Vector\n";
	ft::vector<int> real;
	real.assign(5, 7);
	for (ft::vector<int>::iterator it = real.begin(); it != real.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';

	std::cout << std::endl;
*/


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
