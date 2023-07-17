/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_decimal_in_range.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:47:32 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:47:40 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"

int	ft_isdecimal(const char *str);

int	ft_is_decimal_in_range(const char *str, int low, int high)
{
	int	value;

	value = ft_isdecimal(str);
	if (value >= low && value <= high)
		return (1);
	return (0);
}
