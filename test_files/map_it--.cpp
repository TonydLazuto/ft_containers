ft::map<char, int> mymap;
	ft::pair<char, int> pr[14];

	char c = 'a';
	int	d = 1;
	for (int i = 0; i < 14; i++)
	{
		pr[i] = ft::pair<char, int> (c++, d++);
		mymap.insert(pr[i]);
	}
	for (ft::map<char,int>::iterator it=mymap.end(); it!=mymap.begin(); it--)
		std::cout << it->first << " => " << it->second << std::endl;
	ft::map<char,int>::reverse_iterator rit=mymap.rbegin();
	for (rit=mymap.rend(); rit!=mymap.rbegin(); --rit)
    	std::cout << rit->first << " => " << rit->second << std::endl;
