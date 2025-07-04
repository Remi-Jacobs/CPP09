/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:29:19 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/04 19:16:16 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <iomanip>


class BitcoinExchange
{
private:
	std::map<std::string, double> btc_Data;
	std::map<std::string, double> input_Data;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange& operator =(const BitcoinExchange &src);
	~BitcoinExchange();
	void set_btc_Data(const std::string& filename);
	void set_input_Data(std::ifstream &input);
};