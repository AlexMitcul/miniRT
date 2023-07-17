/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:48:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/17 11:48:07 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_color_string(const char *line)
{
	char	**splitted;
	size_t	count;

	splitted = ft_split(line, ',');
	if (!splitted || !(*splitted))
		return (ft_free_strings(splitted), false);
	count = 0;
	while (splitted[count] && ft_isdecimal(splitted[count]))
		count++;
	ft_free_strings(splitted);
	if (count != 3)
		return (false);
	return (true);
}
