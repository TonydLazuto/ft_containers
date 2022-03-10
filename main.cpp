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
	// #include "Map.hpp"
	#include "Stack.hpp"
	#include "Vector.hpp"
	#include "AvlTree.hpp"
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



void	printSize(ft::stack<int> const &stck)
{
	std::cout << "size: " << stck.size() << std::endl;
	std::cout << "Content is:" << std::endl;
	// for (unsigned long int i = 0; i < stck.size(); ++i)
	// 	std::cout << "- " << *(stck) << std::endl;
	// std::cout << "###############################################" << std::endl;
}

#define cout std::cout 
#define endl std::endl
#define cin std::cin

int main(int argc, char** argv) {
	
	ft::AvlTree<int, int> obj;
	int option = 0, key;
	static int val = 0;

	do {
		cout << "What operation do you want to perform? " <<
		" Select Option number. Enter 0 to exit." << endl;
		cout << "1. Insert Node" << endl;
		cout << "2. Search Node" << endl;
		cout << "3. Delete Node" << endl;
		cout << "4. Print/Traversal AVL Tree values" << endl;
		cout << "5. Height of Tree" << endl;
		cout << "6. Clear Screen" << endl;
		cout << "0. Exit Program" << endl;

		cin >> option;
		//Node n1;
		ft::Node<int, int>* new_node = new ft::Node<int, int>();

		switch (option) {
			case 0:
				break;
			case 1:
			{
				cout << "AVL INSERT" << endl;
				cout << "Enter VALUE of TREE NODE to INSERT in AVL Tree: ";
				cin >> key;
				
				new_node->_pr = ft::make_pair<int,int> (key, val);
				obj._root = obj.insert(obj._root, new_node);
				cout << endl;
				val++;
			}
				break;
			case 2:
			{
				cout << "SEARCH" << endl;
				cout << "Enter VALUE of TREE NODE to SEARCH in AVL Tree: ";
				cin >> key;
				// new_node = obj.iterativeSearch(key);
				ft::pair<int,int> tmp2(key, val);
				new_node = obj.recursiveSearch(obj._root, tmp2);
				if (new_node != NULL) {
					cout << "Value found" << endl;
				} else {
					cout << "Value NOT found" << endl;
				}
			}
				break;
			case 3:
			{
				cout << "DELETE" << endl;
				cout << "Enter VALUE of TREE NODE to DELETE in AVL: ";
				cin >> key;
				ft::pair<int,int> tmp3(key, val);
				new_node = obj.recursiveSearch(obj._root, tmp3);
				if (new_node != NULL) {
					obj._root = obj.deleteNode(obj._root, tmp3);
					cout << "Value Deleted" << endl;
				} else {
					cout << "Value NOT found" << endl;
				}
			}
				break;
			case 4:
			{
				cout << "PRINT 2D: " << endl;
				obj.print2D(obj._root, 5);
				cout << endl;
			}
				break;
			case 5:
				cout << "TREE HEIGHT" << endl;
				// cout << "Height : " << obj.height(obj._root) << endl;
				break;
			case 6:
				system("cls");
				break;
			default:
				cout << "Enter Proper Option number " << endl;
		}

	} while (option != 0);
	

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
