/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:07 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/23 16:17:29 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	this->Vec = src.Vec;
	this->Deq = src.Deq;
}
PmergeMe& PmergeMe::operator =(const PmergeMe &src)
{
	if(this != &src)
	{
		this->Vec = src.Vec;
		this->Deq = src.Deq;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

std::vector<unsigned int>& PmergeMe:: getVec()
{
	return this->Vec;
}

std::deque<unsigned int>& PmergeMe:: getDeq()
{
	return this->Deq;
}

void PmergeMe::CheckAndPrintArgs(int ac, const char **argv)
{
	//To check to duplicates
	// std::set<unsigned int> seen;

	for (int i = 1; i < ac; i++)
	{
		std::istringstream ss(argv[i]);
		long size;
		ss >> size;

		if (ss.fail() || !ss.eof() || size < 0 || size > UINT_MAX)
			throw std::runtime_error("Invalid number");

		unsigned int value = static_cast<unsigned int>(size);

		// if (!seen.insert(value).second) {
		// 	std::ostringstream oss;
		// 	oss << value;
		// 	throw std::runtime_error("Duplicate number detected: " + oss.str());
		// }

		Vec.push_back(value);
		Deq.push_back(value);
	}

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

unsigned int jacobsthal(unsigned int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	unsigned int a = 0, b = 1, j = 0;
	for (unsigned int i = 2; i <= n; ++i)
	{
		j = b + 2 * a;
		a = b;
		b = j;
	}
	return j;
}

std::vector<size_t> PmergeMe:: jacobsthal_insertion_order_vector(size_t n)
{
	std::vector<size_t> result;
	std::vector<bool> seen(n, false);  // Marks which indices we've already added

	// Generate Jacobsthal sequence
	for (size_t j = 1; ; ++j)
	{
		size_t idx = jacobsthal(j);
		if (idx >= n)
			break;
		if (!seen[idx]) {
			result.push_back(idx);
			seen[idx] = true;
		}
	}

	// Always include 0 first if not already
	if (!seen[0])
	{
		result.insert(result.begin(), 0);
		seen[0] = true;
	}

	// Append missing indices in increasing order
	for (size_t i = 0; i < n; ++i)
	{
		if (!seen[i]) {
			result.push_back(i);
			seen[i] = true;
		}
	}

	return result;
}

std::deque<size_t> PmergeMe::jacobsthal_insertion_order_deque(size_t n)
{
    std::deque<size_t> result;
    std::set<size_t> seen; // Use set for O(log n) lookup instead of O(n)
    
    // Generate Jacobsthal sequence
    for (size_t j = 1; ; ++j)
	{
        size_t idx = jacobsthal(j);
        if (idx >= n)
            break;
            
        if (seen.find(idx) == seen.end())
		{
            result.push_back(idx);
            seen.insert(idx);
        }
    }

    // Always include 0 first if not already present
    if (n > 0 && seen.find(0) == seen.end())
	{
        result.push_front(0);
        seen.insert(0);
    }

    // Add missing indices in increasing order
    for (size_t i = 0; i < n; ++i)
	{
        if (seen.find(i) == seen.end())
		{
            result.push_back(i);
            seen.insert(i);
        }
    }

    return result;
}

std::vector<unsigned int> PmergeMe::fordJohnsonVec(std::vector<unsigned int> &Arg)
{
	// Print input at this recursion level
	// std::cout << "Input Arg: ";
	// for (size_t i = 0; i < Arg.size(); ++i)
	// 	std::cout << Arg[i] << " ";
	// std::cout << "\n";

	if (Arg.size() <= 1)
		return Arg;

	bool has_odd = Arg.size() % 2 != 0;
	unsigned int odd = 0;
	if (has_odd)
	{
		odd = Arg.back();
		Arg.pop_back();
		// std::cout << "Straggler (odd element): " << odd << "\n";
	}

	std::vector<std::pair<unsigned int, unsigned int> > pairs;
	for (size_t i = 0; i + 1 < Arg.size(); i += 2)
	{
		if (Arg[i] >= Arg[i + 1])
			pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));
		else
			pairs.push_back(std::make_pair(Arg[i + 1], Arg[i]));
	}

	// std::cout << "Pairs (larger, smaller): ";
	// for (size_t i = 0; i < pairs.size(); ++i)
	// 	std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
	// std::cout << "\n";

	std::vector<unsigned int> a, b;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		a.push_back(pairs[i].first);
		b.push_back(pairs[i].second);
	}
	if (has_odd)
	{
		b.push_back(odd);
		// std::cout << "Appended straggler to b: " << odd << "\n";
	}

	// std::cout << "Main chain before recursive sort (a): ";
	// for (size_t i = 0; i < a.size(); ++i) std::cout << a[i] << " ";
	// std::cout << "\nPending insertions (b): ";
	// for (size_t i = 0; i < b.size(); ++i) std::cout << b[i] << " ";
	// std::cout << "\n";

	std::vector<unsigned int> main_chain = fordJohnsonVec(a);  // Recursive sort on a

	// std::cout << "Sorted main chain (after recursion): ";
	// for (size_t i = 0; i < main_chain.size(); ++i) std::cout << main_chain[i] << " ";
	// std::cout << "\n";

	// Track where each a[i] came from
	std::vector<size_t> a_origin_index;
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == main_chain[i])
			{
				a_origin_index.push_back(j);
				break;
			}
		}
	}

	std::vector<size_t> pend_order = jacobsthal_insertion_order_vector(b.size());

	// std::cout << "Jacobsthal insertion order: ";
	// for (size_t i = 0; i < pend_order.size(); ++i)
	// 	std::cout << pend_order[i] << " ";
	// std::cout << "\n";

	for (size_t k = 0; k < pend_order.size(); ++k)
	{
		size_t bi = pend_order[k];
		if (bi >= b.size()) continue;

		unsigned int val = b[bi];
		// std::cout << "Inserting: " << val << " from b[" << bi << "]\n";

		// MAINNNNNN ENGINEEEE insertion limit logic
		unsigned int pair_first = pairs[bi].first;
		size_t limit_idx = 0;
		for (; limit_idx < main_chain.size(); ++limit_idx)
		{
			if (main_chain[limit_idx] == pair_first)
				break;
		}

		// std::cout << "Insertion limit (up to index): " << limit_idx << "\n";

		std::vector<unsigned int>::iterator insert_pos = 
    	std::lower_bound(main_chain.begin(), main_chain.begin() + std::min(limit_idx + 1, main_chain.size()), val);
		main_chain.insert(insert_pos, val);

		// std::cout << "Main chain after inserting " << val << ": ";
		// for (size_t i = 0; i < main_chain.size(); ++i)
		// 	std::cout << main_chain[i] << " ";
		// std::cout << "\n";
}
	// std::cout << "Final main chain at this level: ";
	// for (size_t i = 0; i < main_chain.size(); ++i)
	// 	std::cout << main_chain[i] << " ";
	// std::cout << "\n\n";

	return main_chain;
}

std::deque<unsigned int> PmergeMe::fordJohnsonDeque(std::deque<unsigned int> &Arg)
{
    if (Arg.size() <= 1)
        return Arg;

    bool has_odd = Arg.size() % 2 != 0;
    unsigned int odd = 0;
    if (has_odd)
	{
        odd = Arg.back();
        Arg.pop_back();
    }

    // Create pairs using deque
    std::deque<std::pair<unsigned int, unsigned int> > pairs;
    for (size_t i = 0; i + 1 < Arg.size(); i += 2)
	{
        if (Arg[i] >= Arg[i + 1])
            pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));
        else
            pairs.push_back(std::make_pair(Arg[i + 1], Arg[i]));
    }

    // Build sequences a and b
    std::deque<unsigned int> a, b;
    for (size_t i = 0; i < pairs.size(); ++i)
	{
        a.push_back(pairs[i].first);
        b.push_back(pairs[i].second);
    }
    if (has_odd)
        b.push_back(odd);

    // Recursively sort the main chain
    std::deque<unsigned int> main_chain = fordJohnsonDeque(a);

    // Create sorted mapping using deque of pairs for binary search lookup
    std::deque<std::pair<unsigned int, size_t> > value_to_pair_index;
    for (size_t j = 0; j < pairs.size(); ++j) {
        value_to_pair_index.push_back(std::make_pair(pairs[j].first, j));
    }
    // Sort for binary search capability
    std::sort(value_to_pair_index.begin(), value_to_pair_index.end());

    // Get insertion order using optimized set-based approach
    std::deque<size_t> pend_order = jacobsthal_insertion_order_deque(b.size());

    for (size_t k = 0; k < pend_order.size(); ++k) {
        size_t bi = pend_order[k];
        if (bi >= b.size()) 
            continue;

        unsigned int val = b[bi];
        unsigned int pair_first = pairs[bi].first;
        
        // Find position of pair_first in main_chain using binary search
        std::deque<unsigned int>::iterator found_pos = 
            std::lower_bound(main_chain.begin(), main_chain.end(), pair_first);
        
        size_t limit_idx = main_chain.size();
        if (found_pos != main_chain.end() && *found_pos == pair_first) {
            limit_idx = (found_pos - main_chain.begin()) + 1;
        }

        // Binary search for insertion position within limit
        std::deque<unsigned int>::iterator insert_pos = 
            std::lower_bound(main_chain.begin(), 
                           main_chain.begin() + std::min(limit_idx, main_chain.size()), 
                           val);
        
        main_chain.insert(insert_pos, val);
    }

    return main_chain;
}

// std::deque<unsigned int> PmergeMe::fordJohnsonDeque(std::deque<unsigned int> &Arg)
// {
//     if (Arg.size() <= 1)
//         return Arg;

//     bool has_odd = Arg.size() % 2 != 0;
//     unsigned int odd = 0;
//     if (has_odd) {
//         odd = Arg.back();
//         Arg.pop_back();
//     }

//     // Pairing elements into (larger, smaller)
//     std::deque<std::pair<unsigned int, unsigned int> > pairs;
//     for (size_t i = 0; i + 1 < Arg.size(); i += 2) {
//         if (Arg[i] >= Arg[i + 1])
//             pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));
//         else
//             pairs.push_back(std::make_pair(Arg[i + 1], Arg[i]));
//     }

//     // Split into a and b
//     std::deque<unsigned int> a, b;
//     for (size_t i = 0; i < pairs.size(); ++i) {
//         a.push_back(pairs[i].first);   // larger
//         b.push_back(pairs[i].second);  // smaller
//     }
//     if (has_odd)
//         b.push_back(odd);  // add straggler to b

//     // Recursive sort of a
//     std::deque<unsigned int> main_chain = fordJohnsonDeque(a);

//     // Track original indices of a elements
//     std::deque<size_t> a_origin_index;
//     for (size_t i = 0; i < main_chain.size(); ++i) {
//         for (size_t j = 0; j < pairs.size(); ++j) {
//             if (pairs[j].first == main_chain[i]) {
//                 a_origin_index.push_back(j);
//                 break;
//             }
//         }
//     }

//     // Get Jacobsthal insertion order
//     std::deque<size_t> pend_order = jacobsthal_insertion_order_deque(b.size());

//     for (size_t k = 0; k < pend_order.size(); ++k) {
//         size_t bi = pend_order[k];
//         if (bi >= b.size()) continue;

//         unsigned int val = b[bi];
//         unsigned int pair_first = pairs[bi].first;

//         // Safe way to find insertion limit (limit_idx)
//         size_t limit_idx = 0;
//         for (; limit_idx < main_chain.size(); ++limit_idx) {
//             if (main_chain[limit_idx] == pair_first)
//                 break;
//         }

//         // Insertion within [0..limit_idx]
//         std::deque<unsigned int>::iterator insert_pos =
//             std::lower_bound(main_chain.begin(),
//                              main_chain.begin() + std::min(limit_idx + 1, main_chain.size()),
//                              val);

//         main_chain.insert(insert_pos, val);
//     }

//     return main_chain;
// }
