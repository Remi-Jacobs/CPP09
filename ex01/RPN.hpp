/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:49:38 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/07 17:20:50 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include <iostream>
#include <string>
#include <sstream>

class RPN
{
	private:
		std::stack <int,int> rpn;
	
	public:
		RPN();
		RPN(const RPN &src);
		RPN& operator=(const RPN &src);
		~RPN();
		int doPolishNotation(const char *str);
};