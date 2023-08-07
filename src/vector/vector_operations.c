/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:28:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/07/30 01:02:24 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	*vec_add(t_vector *a, t_vector *b)
{
	t_vector	*result;

	result = new_vector(a->x + b->x, a->y + b->y, a->z + b->z);
	return (result);
}

t_vector	*vec_substract(t_vector *a, t_vector *b)
{
	t_vector	*result;

	result = new_vector(a->x - b->x, a->y - b->y, a->z - b->z);
	return (result);
}

float	vec_length(t_vector *v)
{
	float	result;

	result = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	return (result);
}

void	vec_normalize(t_vector *v)
{
	float	length;

	length = vec_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

float	vec_product(t_vector *a, t_vector *b)
{
	float	result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}
