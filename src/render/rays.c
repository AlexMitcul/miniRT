/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:07:56 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/07 20:12:07 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_intersection	*intersection_init(void)
{
	t_intersection	*intersection;

	intersection = malloc(sizeof(t_intersection));
	ft_memset(intersection, 0, sizeof(t_intersection));
	intersection->t0 = INFINITY;
	return (intersection);
}

static t_ray	*new_ray(t_vector *point, t_vector *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->o = vec_dup(point);
	ray->d = vec_dup(direction);
	ray->intersection = intersection_init();
	return (ray);
}

t_ray	*camera_ray(t_camera *camera, t_vector *point)
{
	t_ray		*ray;
	t_vector	*up;
	t_vector	*right;
	t_vector	*tmp;
	t_vector	*direction;

	right = vec_multiply(point->x, camera->u);
	up = vec_multiply(point->y, camera->v);
	tmp = vec_add(camera->f, up);
	direction = vec_add(tmp, right);
	free(tmp);
	vec_normalize(direction);
	ray = new_ray(camera->origin, direction);
	ray->t_min = DISTANCE_TO_VIEWPORT;
	ray->t_max = INFINITY;
	free(up);
	free(right);
	free(direction);
	return (ray);
}

t_ray	*scene_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;
	t_vector	*direction;

	direction = vec_substract(point, origin);
	ray = new_ray(origin, direction);
	ray->t_min = 0.0f;
	ray->t_max = 1.0f;
	free(direction);
	return (ray);
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
