#include <iostream>
#include <string>
#include <map>

int main()
{
	std::map<std::string, int> Maps;
	Maps["History"] = 19;
	Maps["Cartoon Network"] = 100;
	Maps["BBC"] = 2;
	Maps["CNN"] = 9;

	std::map<std::string, int>::const_iterator it = Maps.begin();

	while(it != Maps.end())
	{
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
		it++;
	}

}