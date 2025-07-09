/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:21:37 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/09 19:45:27 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &src)
{
	this->para = src.para;
    this->ops = src.ops;
}

RPN& RPN::operator=(const RPN &src)
{
	if (this != &src)
	{
		this->para = src.para;
		this->ops = src.ops;
	}
	return *this;
}

RPN::~RPN()
{}

int RPN::perform_operation(int a, int b)
{
	char sign = ops.top();
	ops.pop();
	if(sign == '+') return a + b;
	if(sign == '-') return a - b;
	if(sign == '*') return a * b;
	if(sign == '/')
	{
		if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
	}
	
	throw std::runtime_error("Unknown operator");
}

void RPN::quick_maths()
{
	if(para.size() < 2 || ops.empty())
		throw std::runtime_error("Error, Invalid expression");
	if(para.size() >= 2)
	{
		int b = para.top();
		para.pop();
		int a = para.top();
		para.pop();
		para.push(perform_operation(a,b));
	}
}

int RPN::do_RPN(const std::string& target)
{
    for (std::string::size_type i = 0; i < target.size(); ++i)
    {
        char c = target[i];

        if (std::isspace(static_cast<unsigned char>(c)))
            continue;

        if (std::isdigit(c))
        {
            para.push(c - '0'); // convert char to int
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            ops.push(c);
            quick_maths();
        }
        else
        {
            throw std::runtime_error("Error, invalid character in expression");
        }
    }

    if (para.size() != 1)
        throw std::runtime_error("Error, malformed expression");

    return para.top();
}
