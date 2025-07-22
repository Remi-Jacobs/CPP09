
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

unsigned int jacobsthal(unsigned int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	unsigned int a = 0, b = 1, j = 0;
	for (unsigned int i = 2; i <= n; ++i) {
		j = b + 2 * a;
		a = b;
		b = j;
	}
	return j;
}

std::vector<size_t> jacobsthal_insertion_order(size_t n) {
	std::vector<size_t> result;
	std::vector<bool> seen(n, false);  // Marks which indices we've already added

	// Generate Jacobsthal sequence
	for (size_t j = 1; ; ++j) {
		size_t idx = jacobsthal(j);
		if (idx >= n)
			break;
		if (!seen[idx]) {
			result.push_back(idx);
			seen[idx] = true;
		}
	}

	// Always include 0 first if not already
	if (!seen[0]) {
		result.insert(result.begin(), 0);
		seen[0] = true;
	}

	// Append missing indices in increasing order
	for (size_t i = 0; i < n; ++i) {
		if (!seen[i]) {
			result.push_back(i);
			seen[i] = true;
		}
	}

	return result;
}

std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> &Arg) {
	// Print input at this recursion level
	std::cout << "Input Arg: ";
	for (size_t i = 0; i < Arg.size(); ++i)
		std::cout << Arg[i] << " ";
	std::cout << "\n";

	if (Arg.size() <= 1)
		return Arg;

	bool has_odd = Arg.size() % 2 != 0;
	unsigned int odd = 0;
	if (has_odd) {
		odd = Arg.back();
		Arg.pop_back();
		std::cout << "Straggler (odd element): " << odd << "\n";
	}

	std::vector<std::pair<unsigned int, unsigned int> > pairs;
	for (size_t i = 0; i + 1 < Arg.size(); i += 2) {
		if (Arg[i] >= Arg[i + 1])
			pairs.push_back(std::make_pair(Arg[i], Arg[i + 1]));
		else
			pairs.push_back(std::make_pair(Arg[i + 1], Arg[i]));
	}

	std::cout << "Pairs (larger, smaller): ";
	for (size_t i = 0; i < pairs.size(); ++i)
		std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
	std::cout << "\n";

	std::vector<unsigned int> a, b;
	for (size_t i = 0; i < pairs.size(); ++i) {
		a.push_back(pairs[i].first);
		b.push_back(pairs[i].second);
	}
	if (has_odd) {
		b.push_back(odd);
		std::cout << "Appended straggler to b: " << odd << "\n";
	}

	std::cout << "Main chain before recursive sort (a): ";
	for (size_t i = 0; i < a.size(); ++i) std::cout << a[i] << " ";
	std::cout << "\nPending insertions (b): ";
	for (size_t i = 0; i < b.size(); ++i) std::cout << b[i] << " ";
	std::cout << "\n";

	std::vector<unsigned int> main_chain = fordJohnson(a);  // Recursive sort on a

	std::cout << "Sorted main chain (after recursion): ";
	for (size_t i = 0; i < main_chain.size(); ++i) std::cout << main_chain[i] << " ";
	std::cout << "\n";

	// Track where each a[i] came from
	std::vector<size_t> a_origin_index;
	for (size_t i = 0; i < main_chain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == main_chain[i]) {
				a_origin_index.push_back(j);
				break;
			}
		}
	}

	std::vector<size_t> pend_order = jacobsthal_insertion_order(b.size());

	std::cout << "Jacobsthal insertion order: ";
	for (size_t i = 0; i < pend_order.size(); ++i)
		std::cout << pend_order[i] << " ";
	std::cout << "\n";

	for (size_t k = 0; k < pend_order.size(); ++k)
	{
		size_t bi = pend_order[k];
		if (bi >= b.size()) continue;

		unsigned int val = b[bi];
		std::cout << "Inserting: " << val << " from b[" << bi << "]\n";

		// Corrected insertion limit logic
		unsigned int pair_first = pairs[bi].first;
		size_t limit_idx = 0;
		for (; limit_idx < main_chain.size(); ++limit_idx) {
			if (main_chain[limit_idx] == pair_first)
				break;
		}

		std::cout << "Insertion limit (up to index): " << limit_idx << "\n";

		std::vector<unsigned int>::iterator insert_pos = 
    	std::lower_bound(main_chain.begin(), main_chain.begin() + std::min(limit_idx + 1, main_chain.size()), val);
		main_chain.insert(insert_pos, val);

		std::cout << "Main chain after inserting " << val << ": ";
		for (size_t i = 0; i < main_chain.size(); ++i)
			std::cout << main_chain[i] << " ";
		std::cout << "\n";
}


	std::cout << "Final main chain at this level: ";
	for (size_t i = 0; i < main_chain.size(); ++i)
		std::cout << main_chain[i] << " ";
	std::cout << "\n\n";

	return main_chain;
}

