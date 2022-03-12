#ifndef TESTAVLTREE_HPP
# define TESTAVLTREE_HPP

#include <iostream>
#include "AvlTree.hpp"

#define cout std::cout 
#define endl std::endl
#define cin std::cin

namespace ft
{
	static int val = 0;

	class	TestAvlTree
	{
		public:
			
			ft::AvlTree<int, int> obj;
			int option, key;
			

			TestAvlTree( void ) : option(0) {}

			virtual ~TestAvlTree( void ) {}
			
			void	make (void)
			{
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
					ft::AvlTree<int, int>::t_node* new_node = new ft::AvlTree<int, int>::t_node();

					switch (option) {
						case 0:
							break;
						case 1:
						{
							cout << "AVL INSERT" << endl;
							cout << "Enter VALUE of TREE NODE to INSERT in AVL Tree: ";
							cin >> key;
							
							new_node->pr = ft::make_pair<int,int> (key, val);
							obj._root = obj.insertNode(obj._root, new_node);
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
							ft::pair<int, int> tmp2(key, val);
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
							ft::pair<int, int> tmp3(key, val);
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
			}
	};
}

#endif
