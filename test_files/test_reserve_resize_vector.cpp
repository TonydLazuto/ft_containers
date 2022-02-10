std::vector<int> myvector;
	myvector.reserve(10);
	std::cout << myvector.capacity() << std::endl;
	for (int i=1;i<10;i++) myvector.push_back(i);
	for (int i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << " ";
	}
	std::cout << std::endl;
	myvector.resize(5);
	std::cout << myvector.capacity() << std::endl;
	for (int i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << " ";
	}
	std::cout << std::endl;
	myvector.resize(8,100);
	std::cout << myvector.capacity() << std::endl;
	for (int i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << " ";
	}
	std::cout << std::endl;
	myvector.resize(12);
	std::cout << myvector.capacity() << std::endl;
	for (int i = 0; i < myvector.size(); i++)
	{
		std::cout << myvector[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;



	ft::Vector<int> vector2 (5, 100);
	vector2.reserve(7);
	std::cout << vector2.capacity() << std::endl;
	std::cout << "size: "<< vector2.size() << std::endl;
	// ft::Vector<int> vector(true_vector.begin(), true_vector.end());
	// std::cout << vector2[2] << std::endl;
	vector2.resize(3);
	std::cout << vector2.capacity() << std::endl;
	std::cout << "size: "<< vector2.size() << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << vector2[i] << " ";
	}
	std::cout << std::endl;
	vector2.resize(8, 50);
	std::cout << vector2.capacity() << std::endl;
	std::cout << "size: "<< vector2.size() << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << vector2[i] << " ";
	}
	std::cout << std::endl;
	vector2.resize(12);
	std::cout << vector2.capacity() << std::endl;
	std::cout << "size: "<< vector2.size() << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << vector2[i] << " ";
	}
	std::cout << std::endl;

