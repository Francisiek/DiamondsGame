//Francisiek 2020
#ifndef _SCIN
#define _SCIN

#include <iostream>

template <class type>
type& sinput(type& x)
{
	std::cin>>x;
	while(std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cerr<<"[INPUT ERROR] Failed to load value, try again.\n";
		std::cin>>x;
	}
	return x;
}

template <class type>
int ssinput(type& x)
{
	std::cin>>x;
	if(std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cout<<"[INPUT ERROR] Failed to load value.\n";
		return -1;
	}
	return 0;
}
#endif
