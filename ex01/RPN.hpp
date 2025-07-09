/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:49:38 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/09 19:45:13 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>
#include <iostream>

class RPN
{
private:
    std::stack<int> para;     // operand stack
    std::stack<char> ops;     // operator stack

    int perform_operation(int a, int b);
    void quick_maths();

public:
    RPN();
    RPN(const RPN& src);
    RPN& operator=(const RPN& src);
    ~RPN();

    int do_RPN(const std::string& target);
};

#endif