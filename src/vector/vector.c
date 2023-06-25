/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:35:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/23 15:35:55 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector    *new_vector(float x, float y, float z)
{
    t_vector    *vector;

    vector = (t_vector *) malloc(sizeof(t_vector));
    if (!vector)
        handle_error(MEMORY_ERROR, NULL);
    vector->x = x;
    vector->y = y;
    vector->z = z;
    return (vector);
}

t_vector *new_vector_from_strings(const char *xs, const char *ys, const char *zs)
{
	float x;
	float y;
	float z;

	x = ft_atof(xs);
	y = ft_atof(ys);
	z = ft_atof(zs);
	return (new_vector(x, y, z));
}

t_vector *parse_vector(const char *str)
{
	char **s;
	size_t	count;

	s = ft_split(str, ',');
	count = 0;
	while (s[count])
		count++;
	if (count != 3)
		return (NULL);
	return (new_vector_from_strings(s[0], s[1], s[2]));
}

