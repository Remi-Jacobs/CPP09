
#include <iostream>
#include <stack>
int main()
{
	std::stack <int> s;
	std::cout << s.size() << std::endl;
	s.push(10);
	s.push(1);
	std::cout << s.size() << std::endl;
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.size() << std::endl;
	std::cout << s.top() << std::endl;
}