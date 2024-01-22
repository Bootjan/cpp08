/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:06:39 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/19 22:22:51 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <vector>
# include <list>

template <typename T>
void	easyfind(T& cont, int needle)
{
	if (std::find(cont.begin(), cont.end(), needle) == cont.end())
		std::cout << "Not found" << std::endl;
	else
		std::cout << "Found" << std::endl;
}

#endif