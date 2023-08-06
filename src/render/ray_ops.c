/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:20:57 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 00:16:52 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_intersection	*intersection_init(void)
{
	t_intersection	*intersection;

	intersection = ft_calloc(1, sizeof(t_intersection));
	intersection->t0 = INFINITY;
	return (intersection);
}

t_ray	*new_ray(t_vector *point, t_vector *direction)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = vec_dup(point);
	ray->d = vec_dup(direction);
	ray->intersection = intersection_init();
	return (ray);
}

t_ray	*scene_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;
	t_vector	*direction;

	direction = vec_substract(point, origin); // m
	ray = new_ray(origin, direction);
	free(direction);
	return (ray);
}

t_vector	*matmul3x1(float m[3][3], t_vector *p)
{
	t_vector	*r;

	r = ft_calloc(1, sizeof(t_vector));
	r->x = p->x * m[0][0] + p->y * m[1][0] + p->z * m[2][0];
	r->y = p->x * m[0][1] + p->y * m[1][1] + p->z * m[2][1];
	r->z = p->x * m[0][2] + p->y * m[1][2] + p->z * m[2][2];
	return (r);
}

void	cam_matrix(t_camera *camera)
{
	camera->matrix[0][0] = camera->u->x;
	camera->matrix[0][1] = camera->u->y;
	camera->matrix[0][2] = camera->u->z;
	camera->matrix[1][0] = camera->v->x;
	camera->matrix[1][1] = camera->v->y;
	camera->matrix[1][2] = camera->v->z;
	camera->matrix[2][0] = camera->f->x;
	camera->matrix[2][1] = camera->f->y;
	camera->matrix[2][2] = camera->f->z;
}


t_ray	*camera_ray(t_camera *camera, t_vector *point)
{
	t_ray		*ray;
	t_vector	*up;
	t_vector	*right;
	t_vector 	*tmp;
	t_vector	*direction;

	right = vec_multiply(point->x, camera->u);
	up = vec_multiply(point->y, camera->v);
	tmp = vec_add(camera->f, up);
	direction = vec_add(tmp, right);
	free(tmp);
	vec_normalize(direction); // n
	if (camera->direction->z < 0)
		printf("cam_direction: %f %f %f\n", direction->x, direction->y, direction->z);
	ray = new_ray(camera->origin, direction);
	free(up);
	free(right);
	free(direction);
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

t_vector	*vec_point(t_vector *origin, t_vector *directions, float t)
{
	t_vector	*point;

	point = new_vector(0, 0, 0);
	point->x = origin->x + t * directions->x;
	point->y = origin->y + t * directions->y;
	point->z = origin->z + t * directions->z;
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
