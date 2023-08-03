/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:01:30 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/02 23:13:31 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	*vec_multiply(float scalar, t_vector *v)
{
	t_vector	*result;

	result = vec_dup(v);
	result->x *= scalar;
	result->y *= scalar;
	result->z *= scalar;
	return (result);
}

t_vector	*vec_cross_product(t_vector *a, t_vector *b)
{
	t_vector	*result;
	
	result = new_vector(0, 0, 0);
	result->x = (a->y * b->z) - (a->z * b->y);
	result->y = (a->z * b->x) - (a->x * b->z);
	result->z = (a->x * b->y) - (a->y * b->x);
	return (result);
}

t_vector *vec_dup(t_vector *v)
{
	t_vector	*result;

	result = new_vector(v->x, v->y, v->z);
	return (result);
}
