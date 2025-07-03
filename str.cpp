#include <iostream>
#include <string>
#include <cctype>

int main ()
{
	std::string str = "Tell me what you want";
	std::string::size_type counter = 0;
	while(counter < str.size())
	{
		std::cout << static_cast<unsigned int> (str[counter]) << std::endl;
		counter++;
	}
	return 0;
}