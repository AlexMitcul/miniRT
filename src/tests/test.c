/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:08:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/26 11:02:31 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void validate(bool status, size_t test_index)
{
    if (status == true)
        printf("\033[32m Test %zu - OK \n\033[0m", test_index);
    else
        printf("\033[31m Test %zu - KO \n\033[0m", test_index);
}

void	test(void)
{
	test_color();
	test_parser();
}

