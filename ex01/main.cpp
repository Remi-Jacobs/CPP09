/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:16:06 by ojacobs           #+#    #+#             */
/*   Updated: 2025/07/09 19:48:00 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char** av)
{
	if (ac != 2)
	{
        std::cerr << "Invalid Parameters" << std::endl;
        return 1;
    }
	RPN rpn;
    try
	{
        std::string paras = av[1]; 
        std::cout << "Result: " << rpn.do_RPN(paras) << std::endl; 
	} 
	catch (const std::exception &e)
	{
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

// int main()
// {
//     RPN rpn;
//     try {
//         int result = rpn.load_stacks("3 4 + 2 *");
//         std::cout << "Result: " << result << std::endl;  // Output: 14
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << std::endl;
//     }
// }