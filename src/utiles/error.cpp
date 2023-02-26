/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:10:45 by hboumahd          #+#    #+#             */
/*   Updated: 2023/02/26 15:16:36 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.hpp"

void fun_error(std::string errorMsg, int exitStatus)
{
    std::cout << errorMsg << "\n";
    exit(exitStatus);
}