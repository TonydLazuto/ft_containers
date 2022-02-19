	ft::Vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=11; i++) 
		myvector.push_back(i);

	// erase the 6th element
	std::cout << "capcity: " << myvector.capacity() << std::endl;
	std::cout << "size: " << myvector.size() << std::endl;
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin()+2,myvector.begin()+5);
	std::cout << "capcity: " << myvector.capacity() << std::endl;
	std::cout << "size: " << myvector.size() << std::endl;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
