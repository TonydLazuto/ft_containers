#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

#include <iostream>
#include <iterator>
#include "AvlTree.hpp"

namespace ft 
{

	template < class NodePair, class NodeTree, bool isConst = false >
	class MapIterator
	{
		public:
			typedef	NodeTree*			pointer;

			MapIterator( void ) : _itor(NULL) {}
			MapIterator( pointer itor ) : _itor(itor) {}
			virtual ~MapIterator( void ) {}
			MapIterator(MapIterator const & src) : _itor(src._itor) {}
			MapIterator& operator=(MapIterator const & rhs)
			{
				this->_itor = rhs._itor;
				return *this;
			}
			NodePair& operator*(void) { return (this->_itor->pr); }
			const NodePair& operator*(void) const { return (this->_itor->pr); }

			NodePair* operator->(void) { return &(this->operator*()); }
			const NodePair* operator->(void) const { return &(this->operator*()); }
			
			MapIterator& operator++(void)
			{
				// std::cout << "--- START pre incr ---" << std::endl;
				// std::cout << "_itor.first: " << _itor->pr.first << std::endl;
				// std::cout << "_itor.second: " << _itor->pr.second << std::endl;
				if (_itor)
				{
					NodePair	save = _itor->pr;
					if (!_itor->right && _itor->parent)
					{
						while (_itor->pr <= save && _itor->parent)
							_itor = _itor->parent;
					}
					else if (_itor->right) // _itor == Parent
					{
						// std::cout << "_itor.first: " << _itor->pr.first << std::endl;
						// std::cout << "_itor.second: " << _itor->pr.second << std::endl;
						_itor = _itor->right;
						// std::cout << "yo4" << std::endl;

						while (_itor && _itor->left){
							// std::cout << "yo5" << std::endl;
							_itor = _itor->left;
							}
						// std::cout << "yo6" << std::endl;
					}
				}
				// std::cout << "_itor.first: " << _itor->pr.first << std::endl;
				// std::cout << "_itor.second: " << _itor->pr.second << std::endl;
				// std::cout << "--- END pre incr ---" << std::endl;
				return *this;
			}

			MapIterator operator++(int)
			{
				MapIterator tmp(*this);
				operator++();
				return tmp;
			}
			
			MapIterator& operator--(void)
			{
				NodePair	save = _itor->pr;
				pointer		tmp = _itor->getEndNode();

				if (_itor)
				{
					// _itor == LeftChild || _itor == RightChild
					if (!_itor->left && _itor->parent)
					{
						if (tmp->pr == save)
							_itor = _itor->parent;
						else
							while (_itor->pr >= save && _itor->parent)
								_itor = _itor->parent;
						}
					else if (_itor->left) // _itor == Parent
					{
						_itor = _itor->left;
						while (_itor->right)
							_itor = _itor->right;
					}
				}
				return *this;
			}
			MapIterator operator--(int)
			{
				MapIterator tmp(*this);
				operator--();
				return tmp;
			}

			operator MapIterator <const NodePair, NodeTree, true> () const
			{ return (MapIterator<const NodePair, NodeTree, true>(this->_itor)); }


			bool operator!=(MapIterator<NodePair, NodeTree, false> rhs) const
			{
				return this->_itor != rhs._itor;
			}
			bool operator==(MapIterator<NodePair, NodeTree, false> rhs) const
			{
				return this->_itor == rhs._itor;
			}

			bool operator==(MapIterator<const NodePair, NodeTree, true> rhs) const
			{
				return this->_itor == rhs._itor;
			}
			bool operator!=(MapIterator<const NodePair, NodeTree, true> rhs) const
			{
				return this->_itor != rhs._itor;
			}


			private:
				NodeTree*	_itor;
	};
}

#endif
