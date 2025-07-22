/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:26:06 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/22 20:22:13 by ojacobs          ###   ########.fr       */
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

// int main(int ac, const char **av)
// {
// 	try {
// 		PmergeMe sorter;
// 		sorter.CheckAndPrintArgs(ac, av);
// 		std::vector<unsigned int> sorted = sorter.fordJohnson(sorter.getVec());
// 		std::deque<unsigned int> sorted2 = sorter.fordJohnsonDeque(sorter.getDeq());

// 		std::cout << "Sorted: ";
// 		for (size_t i = 0; i < sorted.size(); ++i)
// 			std::cout << sorted[i] << " ";
// 		std::cout << std::endl;

// 		std::cout << "Sorted2: ";
// 		for (size_t i = 0; i < sorted2.size(); ++i)
// 			std::cout << sorted2[i] << " ";
// 		std::cout << std::endl;
// 	} catch (std::exception &e) {
// 		std::cerr << "Error: " << e.what() << std::endl;
// 	}
// }

int main(int ac, const char **av)
{
	try {
		PmergeMe sorter;
		sorter.CheckAndPrintArgs(ac, av);

		

		// Timing for deque
		std::clock_t start_deq = std::clock();
		std::deque<unsigned int> sorted2 = sorter.fordJohnsonDeque(sorter.getDeq());
		std::clock_t end_deq = std::clock();
		double time_deq = 1000000.0 * (end_deq - start_deq) / CLOCKS_PER_SEC;

		// Timing for vector
		std::clock_t start_vec = std::clock();
		std::vector<unsigned int> sorted = sorter.fordJohnson(sorter.getVec());
		std::clock_t end_vec = std::clock();
		double time_vec = 1000000.0 * (end_vec - start_vec) / CLOCKS_PER_SEC;

		// Output
		std::cout << "Sorted: ";
		for (size_t i = 0; i < sorted.size(); ++i)
			std::cout << sorted[i] << " ";
		std::cout << std::endl;

		std::cout << "Sorted2: ";
		for (size_t i = 0; i < sorted2.size(); ++i)
			std::cout << sorted2[i] << " ";
		std::cout << std::endl;

		std::cout << "Time to process a range of " << sorted.size()
		          << " elements with std::vector: " << time_vec << " us" << std::endl;

		std::cout << "Time to process a range of " << sorted2.size()
		          << " elements with std::deque: " << time_deq << " us" << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
