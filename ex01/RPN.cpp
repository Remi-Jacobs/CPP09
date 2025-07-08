/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:21:37 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/08 19:41:00 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"



RPN::RPN()
{
	
}
RPN::RPN(const RPN &src)
{
	
}
RPN& RPN::operator=(const RPN &src)
{
	
}
RPN::~RPN()
{
	
}

int RPN::doPolishNotation(const char *str)
{
	
}

int isooperator(std::string ops)
{
	std::string selection[4] = {"+","-","*","/"};
	for(int i = 0; i < 5; i++)
	{
		if(ops == selection[i] || i == 4)
		switch (i)
		{
			case 0: return 1;
			case 1: return 2;
			case 2: return 3;
			case 3: return 4;
			default: return std::isdigit(static_cast <unsigned char>(ops[i])) ? 5 : 0;
		}
	}
}

//1 2
//*
//2 0
//2 <-
//2 2
//'/'
//1 0
//2 <-
//1 2 
//'*'
//2 0
//2 <-
