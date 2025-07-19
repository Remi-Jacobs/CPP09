#include <vector>
#include <iostream>
#include <sstream>
#include <climits>

int main(int ac, char **av)
{
	std::vector<unsigned int> Vec;
	for (int i = 1; i < ac; i++)
	{
		std::istringstream ss (av[i]);

		long size;
		ss >> size;
			Vec.push_back(size);
			//For other container
	}

	if (Vec.size() % 2 == 1)
	{
		unsigned int odd = Vec.back();
		Vec.pop_back();

		std::cout << "odd "<< odd << std::endl;
	}
	
	for(std::vector<unsigned int>::iterator it = Vec.begin(); it != Vec.end(); it++)
		std::cout << *it << std::endl;

	return 0;
}