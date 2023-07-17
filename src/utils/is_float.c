/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:48:18 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:48:18 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_float(const char *str)
{
	bool	digits_found;

	if (*str == '+' || *str == '-')
		str++;
	digits_found = false;
	while (ft_isdigit(*str))
	{
		digits_found = true;
		str++;
	}
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*(str - 1) == '.')
		return (false);
	return (digits_found && !(*str));
}
