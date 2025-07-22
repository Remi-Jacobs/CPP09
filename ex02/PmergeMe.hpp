/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:10:37 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/22 20:20:18 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <climits>
#include <algorithm>
#include <utility>
#include <deque>
#include<ctime>
class PmergeMe
{
private:
	std::vector<unsigned int> Vec;
	std::deque<unsigned int> Deq;
	bool odd;
public:
	PmergeMe();
	~PmergeMe();

	void CheckAndPrintArgs(int ac, const char **argv);
	std::vector<unsigned int> fordJohnson(std::vector<unsigned int> &Arg);
	std::deque<unsigned int> fordJohnsonDeque(std::deque<unsigned int> &Arg);
	std::vector<unsigned int> &getVec();
	std::deque<unsigned int> &getDeq();
};

#endif