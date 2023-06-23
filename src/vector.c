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

#include "../includes/minirt.h"

t_vector    *new_vector(float x, float y, float z)
{
    t_vector    *vector;

    vector = (t_vector *) malloc(sizeof(t_vector));
    if (!vector)
        handle_error(MEMORY_ERROR);
    vector->x = x;
    vector->y = y;
    vector->z = z;
    return (vector);
}

t_vector    *vec_substract(t_vector *a, t_vector *b)
{
    t_vector    *result;

    result = new_vector(a->x - b->x, a->y - b->y, a->z - b->z);
    return (result);
}

float   vec_length(t_vector *v)
{
    float   result;

    result = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
    return (result);
}

void    vec_normalize(t_vector *v)
{
    float   length;

    length = vec_length(v);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

float   vec_product(t_vector *a, t_vector *b)
{
    float   result;

    result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
    return (result);
}