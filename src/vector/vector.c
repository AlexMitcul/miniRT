/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:35:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/08/06 19:16:38 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	*new_vector(float x, float y, float z)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		handle_error(MEMORY_ERROR, NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*new_vector_from_strings(const char *str)
{
	char	**splitted;
	float	x;
	float	y;
	float	z;

	if (is_valid_vector_string(str) == false)
		return (NULL);
	splitted = ft_split(str, ',');
	if (!splitted)
		return (NULL);
	x = ft_atof(splitted[0]);
	y = ft_atof(splitted[1]);
	z = ft_atof(splitted[2]);
	ft_free_strings(splitted);
	return (new_vector(x, y, z));
}

bool	is_vector(const char *str, t_vector_type type)
{
	t_vector	*vector;

	vector = new_vector_from_strings(str);
	if (!vector)
		return (false);
	if (type == NORMALIZED)
	{
		if (vector->x > 1 || vector->y > 1 || vector->z > 1)
			return (free_vector(vector), false);
		if (vector->x < -1 || vector->y < -1 || vector->z < -1)
			return (free_vector(vector), false);
	}
	free_vector(vector);
	return (true);
}

void	free_vector(t_vector *vector)
{
	if (vector)
		free(vector);
}
