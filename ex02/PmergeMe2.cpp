
#include "PmergeMe.hpp"

unsigned int jacobsthal(unsigned int n) {
    // J(0) = 0, J(1) = 1, J(n) = J(n-1) + 2*J(n-2)
    if (n == 0) return 0;
    if (n == 1) return 1;
    unsigned int a = 0, b = 1, j = 0;
    for (unsigned int i = 2; i <= n; ++i) {
        j = b + 2*a;
        a = b;
        b = j;
    }
    return j;
}

std::vector<size_t> jacobsthal_insertion_order(size_t pend_size) {
    // Compute indices for Jacobsthal optimal pend insertion order for length N:
    std::vector<size_t> order;
    size_t prev = 1;
    size_t idx = 2;
    while (true) {
        size_t curr = jacobsthal(idx);
        size_t count = curr - prev;
        if (order.size() + count > pend_size)
            break;
        // Insert indices in reverse order for this block
        for (size_t i = 0; i < count; ++i)
            order.push_back(curr - i - 1);
        prev = curr;
        ++idx;
    }
    // Insert any remaining elements in reverse order
    for (size_t i = pend_size; i > order.size(); --i)
        order.push_back(i - 1);
    return order;
}

// Main sort function
std::vector<unsigned int> PmergeMe::fordJohnson(std::vector<unsigned int> Arg)
{
    if (Arg.size() <= 1)
        return Arg;

    // 1. Deal with odd element (straggler)
    bool has_odd = Arg.size() % 2 != 0;
    unsigned int odd = 0;
    if (has_odd) {
        odd = Arg.back();
        Arg.pop_back();
    }

    // 2. Form pairs, always larger first
    std::vector<std::pair<unsigned int, unsigned int> > pairs;
    for (size_t i = 0; i + 1 < Arg.size(); i += 2) {
        if (Arg[i] >= Arg[i+1])
            pairs.push_back(std::make_pair(Arg[i], Arg[i+1]));
        else
            pairs.push_back(std::make_pair(Arg[i+1], Arg[i]));
    }

    // 3. Split into main (a) and pend (b)
    std::vector<unsigned int> a, b;
    for (size_t i = 0; i < pairs.size(); ++i) {
        a.push_back(pairs[i].first);
        b.push_back(pairs[i].second);
    }
    if (has_odd)
        b.push_back(odd);

    // 4. Recursively sort `a` to build main chain
    std::vector<unsigned int> main_chain = fordJohnson(a);

    // --- INSERTION PHASE: Pend elements in Jacobsthal order ---
    // For full optimality, search boundaries should be up to their respective `a` in main_chain,
    // but here we do standard binary insertion for clarity.

    std::vector<size_t> pend_order = jacobsthal_insertion_order(b.size());

    for (size_t k = 0; k < pend_order.size(); ++k) {
        size_t bi = pend_order[k];
        // For full optimality, use correct search boundary: up to corresponding pair element in main_chain
        // For simplicity, use lower_bound across whole main_chain (fits project's requirements)
        std::vector<unsigned int>::iterator pos =
            std::lower_bound(main_chain.begin(), main_chain.end(), b[bi]);
        main_chain.insert(pos, b[bi]);
    }
    return main_chain;
}