#include <unistd.h>

int ft_atoi(const char *strt)
{

	// char str[10] = "0123456789";

	int sign = 1;
	int i = 0;

	while(strt[i] == '\t' || strt[i] == '\v' || strt[i] == 32)
		i++;
	if(strt[i] == '-'|| strt[i] == '+')
	{
		if(strt[i] == '-')
			sign = -1;
		i++;
	}
	
	int res = 0;
	while (strt[i] && (strt[i] >= '0' && strt[i] <= '9'))
	{
		res = (res * 10) + (strt[i] - 48);
		i++;
	}
	
	return res * sign; 
}



#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Invalid number of variables\n"), 1);
	int result = ft_atoi(av[1]);
		printf("%d \n", result);
}