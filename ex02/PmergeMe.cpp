/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:07 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/19 18:01:20 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

std::vector<unsigned int>& PmergeMe:: getVec()
{
	return this->Vec;
}

void PmergeMe::CheckAndPrintArgs(int ac, const char **argv)
{
	for (int i = 1; i < ac; i++)
	{
		std::istringstream ss (argv[i]);
		long size;
		ss >> size;
		if (ss.fail() || !ss.eof() || size < 0 || size > UINT_MAX)
			throw std::runtime_error("Invalid number");
		else
		{
			Vec.push_back(size);
			//For other container
		}
	}
	//Remember to check for duplicates
	
	std::cout << "Before: ";
	for (int i = 1; i < ac; i++)
	{
		std::string tmp = argv[i];
		if (i == ac - 1)
			std::cout << tmp << std::endl;
		else
			std::cout << tmp << " ";
	}
}

std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> Arg)
{
	//  std::vector<unsigned int> result;

    if (Arg.size() <= 1)
	{
    	return Arg;
	}
	unsigned int odd;
	this->odd = false;
	if (Arg.size() % 2 == 1)
	{
		this->odd = true;
		odd = Arg.back();
		Arg.pop_back();
	}
	std::vector<std::pair<unsigned int, unsigned int> > pairs;
	for(size_t i = 0; i + 1 < Arg.size(); i+=2)
	{
		pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));
	}
	for(std::vector<std::pair<unsigned int,unsigned int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if(it->first < it->second)
			std::swap(it->first, it->second);
	}
	std::vector<unsigned int> a;
	std::vector<unsigned int> b;
	for(std::vector<std::pair<unsigned int,unsigned int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		a.push_back(it->first);
		b.push_back(it->second);
	}
	if (this->odd == true)
	{
		b.push_back(odd);
		this->odd = false;
	}
	std::vector<unsigned int> main_chain = fordJohnson(a);
	//test recursion
	std::cout << "Main chain: ";
    for (size_t i = 0; i < main_chain.size(); ++i)
    {
        std::cout << main_chain[i] << " ";
    }
    std::cout << std::endl;

    return main_chain;
	
}

// std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> &Arg)
// {
//     if (Arg.size() <= 1)
//         return Arg;

//     unsigned int odd;
//     this->odd = false;
//     if (Arg.size() % 2 == 1)
//     {
//         this->odd = true;
//         odd = Arg.back();
//         Arg.pop_back();
//     }

//     std::vector<std::pair<unsigned int, unsigned int> > pairs;
//     for (size_t i = 0; i + 1 < Arg.size(); i += 2)
//         pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));

//     for (size_t i = 0; i < pairs.size(); ++i)
//     {
//         if (pairs[i].first < pairs[i].second)
//             std::swap(pairs[i].first, pairs[i].second);
//     }

//     std::vector<unsigned int> a; // larger elements
//     std::vector<unsigned int> b; // smaller elements
//     for (size_t i = 0; i < pairs.size(); ++i)
//     {
//         a.push_back(pairs[i].first);
//         b.push_back(pairs[i].second);
//     }
//     if (this->odd)
//         b.push_back(odd);

//     // Print before sorting
//     std::cout << "Unsorted main chain (a): ";
//     for (size_t i = 0; i < a.size(); ++i)
//         std::cout << a[i] << " ";
//     std::cout << std::endl;

//     // Recursive sort of a
//     std::vector<unsigned int> sorted_a = fordJohnson(a);

//     // Print after sorting
//     std::cout << "Sorted main chain: ";
//     for (size_t i = 0; i < sorted_a.size(); ++i)
//         std::cout << sorted_a[i] << " ";
//     std::cout << std::endl;

//     return sorted_a;
// }

//temp to test pairing and sorting
// std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> Arg)
// {
//     if (Arg.size() <= 1)
//         return Arg;

//     unsigned int odd;
//     this->odd = false;
//     if (Arg.size() % 2 == 1)
//     {
//         this->odd = true;
//         odd = Arg.back();
//         Arg.pop_back();
//     }

//     std::vector<std::pair<unsigned int, unsigned int> > pairs;
//     for (size_t i = 0; i + 1 < Arg.size(); i += 2)
//         pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));

//     for (size_t i = 0; i < pairs.size(); ++i)
//     {
//         if (pairs[i].first < pairs[i].second)
//             std::swap(pairs[i].first, pairs[i].second);
//     }

//     std::vector<unsigned int> a; // main chain
//     std::vector<unsigned int> b; // pend chain
//     for (size_t i = 0; i < pairs.size(); ++i)
//     {
//         a.push_back(pairs[i].first);  // larger
//         b.push_back(pairs[i].second); // smaller
//     }

//     if (this->odd)
//         b.push_back(odd);

//     std::cout << "Unsorted main chain (a): ";
//     for (size_t i = 0; i < a.size(); ++i)
//         std::cout << a[i] << " ";
//     std::cout << std::endl;

//     // Temporarily sort main chain
//     std::sort(a.begin(), a.end());

//     std::cout << "Sorted main chain: ";
//     for (size_t i = 0; i < a.size(); ++i)
//         std::cout << a[i] << " ";
//     std::cout << std::endl;

//     return a;
// }
