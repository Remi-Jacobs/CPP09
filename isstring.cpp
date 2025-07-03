#include <iostream>
#include <string>
#include <sstream>

void isValid(std::string str)
{
	int y, m, d;
    char dash1, dash2;
    std::istringstream ss(str);
	ss >> y >> dash1 >> m >> dash2 >> d;
	std::cout << "Year " << y << std::endl;
	std::cout << "break " << dash1 << std::endl;
	std::cout << "Month " << m << std::endl;
	std::cout << "break " << dash2 << std::endl;
	std::cout << "Day " << d << std::endl;
	
}

int main(int ac, char **av)
{
	int i = 1;

	while(i < ac)
	{
		isValid(av[i]);
		i++;
	}
}