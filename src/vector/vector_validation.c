/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:29:40 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:29:54 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_valid_vector_string(const char *str)
{
	size_t	length;
	size_t	i;

	i = 0;
	if (!str || ft_count_char(str, '.') > 3 || ft_count_char(str, ',') != 2)
		return (false);
	length = ft_strlen(str);
	if (ft_isdigit(str[0]) || str[0] == '-' || str[0] == '+')
		i++;
	else
		return (false);
	if (!ft_isdigit(str[length - 1]))
		return (false);
	while (i < length - 1)
	{
		if (ft_strchr(".,", str[i]) && (str[i + 1] == '-' || str[i + 1] == '+'))
			i++;
		else if (ft_strchr(".,", str[i]) && !ft_isdigit(str[i + 1]))
			return (false);
		else
			i++;
	}
	return (true);
}

bool	vector_compare(t_vector *a, t_vector *b)
{
	if (a->x == b->x && a->y == b->y && a->z == b->z)
		return (true);
	return (false);
}
