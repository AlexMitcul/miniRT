/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:20:57 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/31 01:13:26 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	*new_ray(t_vector *point, t_vector *direction)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = vec_dup(point);
	vec_normalize(direction);
	ray->d = vec_dup(direction);
	return (ray);
}

t_ray	*light_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;
	t_vector	*direction;

	// ray = ft_calloc(1, sizeof(t_ray));
	// ray->o = new_vector(origin->x, origin->y, origin->z); // free needed
	// ray->d = vec_substract(origin, point);
	// vec_normalize(ray->d);
	direction = vec_substract(origin, point);
	ray = new_ray(origin, direction);
	free(direction);
	// ray->d = vec_substract(point, origin); // free needed
	return (ray);
}

t_ray	*camera_ray(t_camera *camera, t_vector *point)
{
	t_ray		*ray;
	t_vector	*up;
	t_vector	*right;
	t_vector 	*tmp;
	t_vector	*direction;

	// ray = ft_calloc(1, sizeof(t_ray));
	// ray->o = vec_dup(camera->origin);
	right = vec_multiply(point->x, camera->u);
	up = vec_multiply(point->y, camera->v);
	tmp = vec_add(camera->f, up);
	// ray->d = vec_add(tmp, right);
	direction = vec_add(tmp, right);
	// vec_normalize(direction);
	// vec_normalize(ray->d);
	ray = new_ray(camera->origin, direction);
	free(tmp);
	free(up);
	free(right);
	free(direction);
	return (ray);
}

/* // t_ray	*new_ray(t_vector *origin, t_vector *point)
t_ray	*new_ray(t_vector *origin, t_vector *point, t_camera *camera)
{
	t_ray		*ray;
	t_vector	*up;
	t_vector	*right;
	t_vector 	*tmp;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = vec_dup(origin);
	right = vec_multiply(point->x, camera->u);
	up = vec_multiply(point->y, camera->v);
	tmp = vec_add(camera->f, up);
	ray->d = vec_add(tmp, right);
	vec_normalize(ray->d);
	free(tmp);
	free(up);
	free(right);
	// ray->d = vec_substract(point, origin); // free needed
	return (ray);
} */

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
	if (ray->o)
		free(ray->o);
	if (ray->d)
		free(ray->d);
	if (ray->intersection)
	{
		if (ray->intersection->p)
			free(ray->intersection->p);
		if (ray->intersection->n)
			free(ray->intersection->n);
		free(ray->intersection);
	}
	free(ray);
}
