/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:20:57 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/28 03:38:16 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	*new_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = origin;
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
	free(ray->d);
	if (ray->intersection)
	{
		if (ray->intersection->p)
			free(ray->intersection->p);
		if (ray->intersection->n)
			free(ray->intersection->n);
		if (ray->intersection->color)
			free(ray->intersection->color);
		if (ray->intersection->sp)
			free(ray->intersection->sp);
		if (ray->intersection->pl)
			free(ray->intersection->pl);
		if (ray->intersection->cyl)
			free(ray->intersection->cyl);
		free(ray->intersection);
	}
	free(ray);
}
