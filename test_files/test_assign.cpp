	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;

	for (int i = 0; i < 5; i++)
		first.push_back(i);
	first.assign (7,100);             // 7 ints with a value of 100

	second.assign (first.begin(),first.end()); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	for (int i = 0; i < first.size(); i++)
		std::cout << "first["<<i<<"]: " << first[i] << std::endl;
	for (int i = 0; i < second.size(); i++)
		std::cout << "second["<<i<<"]: " << second[i] << std::endl;
	for (int i = 0; i < third.size(); i++)
		std::cout << "third["<<i<<"]: " << third[i] << std::endl;
