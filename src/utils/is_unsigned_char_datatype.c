/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_unsigned_char_datatype.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:08:20 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:48:27 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include <stdbool.h>

bool	is_unsigned_char_datatype(char **data)
{
	int	x;
	int	y;
	int	z;

	x = ft_atoi(data[0]);
	y = ft_atoi(data[1]);
	z = ft_atoi(data[2]);
	if (x > 255 || y > 255 || z > 255)
		return (false);
	if (x < 0 || y < 0 || z < 0)
		return (false);
	return (true);
}
