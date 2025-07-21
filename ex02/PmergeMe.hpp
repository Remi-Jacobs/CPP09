/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:10:37 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/21 15:11:50 by ojacobs          ###   ########.fr       */
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
class PmergeMe
{
private:
	std::vector<unsigned int> Vec;
	bool odd;
public:
	PmergeMe();
	~PmergeMe();

	void CheckAndPrintArgs(int ac, const char **argv);
	std::vector<unsigned int> fordJohnson(std::vector<unsigned int> &Arg);
	std::vector<unsigned int> &getVec();
};

#endif