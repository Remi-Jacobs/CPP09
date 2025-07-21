/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:26:06 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/21 13:00:10 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// int main(int ac, const char**av)
// {
// 	if (ac < 2)
// 		std::cout << "Invalid number of arguments" << std::endl;
// 	PmergeMe a;
// 	try
// 	{
// 		a.CheckAndPrintArgs(ac, av);
// 		a.fordJohnson(a.getVec());
// 	}
// 	catch (std::exception &e)
// 	{
// 		std::cerr << e.what() <<std::endl;
// 	}
// 	return 0;
// }

// int main(int argc, const char **argv)
// {
// 	try
// 	{
// 		if (argc < 2)
// 			throw std::runtime_error("Usage: ./PmergeMe <numbers...>");

// 		PmergeMe sorter;
// 		sorter.CheckAndPrintArgs(argc, argv);  // Validates and fills Vec

// 		// std::vector<unsigned int> &data = sorter.getVec();  // Access parsed input
// 		std::vector<unsigned int> result = sorter.fordJohnson(sorter.getVec());  // Run Ford-Johnson logic

// 		std::cout << "Final main chain: ";
// 		for (size_t i = 0; i < result.size(); ++i)
// 		{
// 			std::cout << result[i] << " ";
// 		}
// 		std::cout << std::endl;
// 	}
// 	catch (const std::exception &e)
// 	{
// 		std::cerr << "Error: " << e.what() << std::endl;
// 		return 1;
// 	}

// 	return 0;
// }

int main(int ac, const char **av)
{
	try {
		PmergeMe sorter;
		sorter.CheckAndPrintArgs(ac, av);
		std::vector<unsigned int> sorted = sorter.fordJohnson(sorter.getVec());

		std::cout << "Sorted: ";
		for (size_t i = 0; i < sorted.size(); ++i)
			std::cout << sorted[i] << " ";
		std::cout << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}