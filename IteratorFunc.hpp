#include "IteratorTraits.hpp"

template <class InputIterator, class Distance>
void advance (InputIterator& it, Distance n);

template <class Container>
back_insert_iterator<Container> back_inserter (Container& x);

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance (InputIterator first, InputIterator last);

template <class Container>
front_insert_iterator<Container> front_inserter (Container& x);

template <class Container, class Iterator>
insert_iterator<Container> inserter (Container& x, Iterator it);
