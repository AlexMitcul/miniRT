/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:20:57 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/28 19:07:38 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	*vec_dup(t_vector *v)
{
	t_vector	*dup;

	dup = malloc(sizeof(t_vector));
	dup->x = v->x;
	dup->y = v->y;
	dup->z = v->z;
	return (dup);
}

t_ray	*new_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = origin;
	// ray->o = vec_dup(origin); // free needed
	ray->d = vec_substract(point, origin); // free needed
	vec_normalize(ray->d);
	return (ray);
}

t_vector	*ray_point(t_ray *ray, float t)
{
	t_vector	*point;

	point = new_vector(0, 0, 0);
	point->x = ray->o->x + t * ray->d->x;
	point->y = ray->o->y + t * ray->d->y;
	point->z = ray->o->z + t * ray->d->z;
	return (point);
}

void	free_ray(t_ray *ray)
{
	// if (ray->o)
	// 	free(ray->o);
	if (ray->d)
		free(ray->d);
	if (ray->intersection)
	{
		if (ray->intersection->p)
			free(ray->intersection->p);
		if (ray->intersection->n)
			free(ray->intersection->n);
		// if (ray->intersection->color)
		// 	free(ray->intersection->color);
		free(ray->intersection);
	}
	free(ray);
	ray = NULL;
}
