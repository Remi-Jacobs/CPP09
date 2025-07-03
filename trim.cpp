#include <iostream>
#include <string>

std::string Trim(const std::string& str)
{
    std::string::size_type start = 0;
    while( start < str.size() && std::isspace(static_cast<unsigned char> (str[start])))
        ++start;
    std::string::size_type end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char> (str[end -1])))
        --end;
    return str.substr(start, end - start);
}
int main(int ac, char **av)
{
	
	int i = 1;
	while(i < ac)
	{
		std::string res = Trim(av[i]);
		std::cout << av[i] << std::endl;
		std::cout << res << std::endl;
		i++;
	}
}