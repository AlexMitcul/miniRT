/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:45:24 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/08 18:12:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * Tested
 */
bool	is_valid_color_string(const char *str)
{
	size_t	i;
	size_t	commas;

	if (!str || *str == '\0' || ft_strlen(str) > 11)
		return (false);
	i = 0;
	commas = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
			;
		else if (str[i] == ',' && ft_isdigit(str[i - 1]))
			commas++;
		else
			return (false);
	}
	if (commas != 2 || str[i - 1] == ',')
		return (false);
	return (true);
}

/*
 * @ Description:
 * Transform string from format `255,255,255` to struct t_color
 * @ Input:
 * char * in format `255.255.255`, NULL-ended
 * @ Return value:
 * if string isn't in right format returns NULL
 * otherwise return (t_color *);
 */
t_color	*new_color_from_string(const char *data)
{
	char	**splitted;
	t_color	*color;

	if (is_valid_color_string(data) == false)
		return (NULL);
	splitted = ft_split(data, ',');
	if (!splitted)
		return (NULL);
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		return (ft_free_strings(splitted), NULL);
	if (is_unsigned_char_datatype(splitted) == false)
		return (ft_free_strings(splitted), free_color(color), NULL);
	color->r = ft_atoi(splitted[0]);
	color->g = ft_atoi(splitted[1]);
	color->b = ft_atoi(splitted[2]);
	ft_free_strings(splitted);
	return (color);
}

/* @ Description:
 * Allocate t_color struct using
 * @ Input:
 * int r, int g, int b => red, green, blue colors value in range [0, 255]
 * @ Return value:
 * if one of param isn't in range [0, 255] return NULL
 * otherwise return (t_color *);
 */
t_color	*new_color(const int r, const int g, const int b)
{
	t_color	*color;

	if (r > 255 || g > 255 || b > 255)
		return (NULL);
	if (r < 0 || g < 0 || b < 0)
		return (NULL);
	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

void	free_color(t_color *color)
{
	if (!color)
		return ;
	free(color);
}

bool	color_compare(t_color *a, t_color *b)
{
	if (a->r == b->r && a->g == b->g && a->b == b->b)
		return (true);
	return (false);
}
