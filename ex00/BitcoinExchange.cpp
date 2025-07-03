/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:29:14 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/03 20:23:30 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Trim leading and trailing whitespace because input is string and might not be controlled.

std::string Trim(const std::string& str)
{
    std::string::size_type start = 0;
    while( start < str.size() && std::isspace(static_cast<unsigned char> (str[start])))
        ++start;
    std::string::size_type end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char> (str[end -1])))
        --end;
    return str.substr(start, end - start);
}

// Validate date in format YYYY-MM-DD
bool isValidDate(const std::string& date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int y, m, d;
    char dash1, dash2;
    std::istringstream ss(date);
    if (!(ss >> y >> dash1 >> m >> dash2 >> d))
        return false;
    if (dash1 != '-' || dash2 != '-')
        return false;
    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    static const int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2)
    {
        bool leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if (d > (leap ? 29 : 28))
            return false;
    }
    else
    {
        if (d > daysInMonth[m - 1])
            return false;
    }

    return true;
}

// Parse and validate float/integer value from string
bool parseValue(const std::string& s, double& out)
{
    std::istringstream ss(s);
    ss >> out;
    if (ss.fail() || !ss.eof())
    {
        std::cout << "Error: not a valid number." << std::endl;
        return false;
    }
    if (out < 0.0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (out > 1000.0)
    {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

// Load data.csv exchange rates into map

void BitcoinExchange::set_btc_Data(const std::string& filename)
{
    // std::map<std::string, double> btc_Data;
    std::ifstream file(filename.c_str());
    std::string line;

    std::getline(file, line);
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date;
        std::string rate;
        if(std::getline(ss, date, ',') && std::getline(ss, rate))
        {
            std::stringstream conv(rate);
            double conv_rate;
            conv >> conv_rate;
            if (!conv.fail())
                btc_Data[Trim(date)] = conv_rate;
        }
    }
}
// std::map<std::string, double> loadExchangeRates(const std::string& filename)
// {
//     std::map<std::string, double> rates;
//     std::ifstream file(filename.c_str());
//     std::string line;

//     std::getline(file, line); // Skip header

//     while (std::getline(file, line)) {
//         std::stringstream ss(line);
//         std::string date, rateStr;
//         if (std::getline(ss, date, ',') && std::getline(ss, rateStr))
//         {
//             std::stringstream conv(rateStr);
//             double rate;
//             conv >> rate;
//             if (!conv.fail())
//                 rates[Trim(date)] = rate;
//         }
//     }
//     return rates;
// }

void BitcoinExchange::set_input_Data(const std::string& filename, std::ifstream &input)
{
    std::string line;
    std::getline(input, line); // Skip header line
    
      while (std::getline(input, line))
      {
        size_t pipe = line.find('|');
        if (pipe == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = Trim(line.substr(0, pipe));
        std::string valueStr = Trim(line.substr(pipe + 1));
        double value;

        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!parseValue(valueStr, value))
            continue;

        std::map<std::string, double>::iterator it = exchangeRates.upper_bound(date);
        if (it != exchangeRates.begin()) {
            --it;
            double rate = it->second;
            std::cout << date << " => " << value << " = "
                      << std::fixed << std::setprecision(2)
                      << (value * rate) << std::endl;
        } else {
            std::cout << "Error: no exchange rate available for " << date << std::endl;
        }
    }
    
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::map<std::string, double> exchangeRates = loadExchangeRates("data.csv");

    std::string line;
    std::getline(input, line); // Skip header line

    while (std::getline(input, line)) {
        size_t pipe = line.find('|');
        if (pipe == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pipe));
        std::string valueStr = trim(line.substr(pipe + 1));
        double value;

        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!parseValue(valueStr, value))
            continue;

        std::map<std::string, double>::iterator it = exchangeRates.upper_bound(date);
        if (it != exchangeRates.begin()) {
            --it;
            double rate = it->second;
            std::cout << date << " => " << value << " = "
                      << std::fixed << std::setprecision(2)
                      << (value * rate) << std::endl;
        } else {
            std::cout << "Error: no exchange rate available for " << date << std::endl;
        }
    }

    return 0;
}
