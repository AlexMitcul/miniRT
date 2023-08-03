/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:20:57 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/02 01:45:46 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_intersection	*intersection_init(void)
{
	t_intersection	*intersection;

	intersection = ft_calloc(1, sizeof(t_intersection));
	// intersection->t = MAX_T;
	intersection->t = INFINITY;
	return (intersection);
}

t_ray	*new_ray(t_vector *point, t_vector *direction)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->o = vec_dup(point);
	// vec_normalize(direction);
	ray->d = vec_dup(direction);
	ray->intersection = intersection_init();
	return (ray);
}

t_ray	*scene_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;
	t_vector	*direction;

	// direction = vec_substract(point, origin);
	direction = vec_substract(origin, point);
	ray = new_ray(origin, direction);
	free(direction);
	return (ray);
}

/* t_ray	*light_ray(t_vector *origin, t_vector *point)
{
	t_ray		*ray;
	t_vector	*direction;

	// ray = ft_calloc(1, sizeof(t_ray));
	// ray->o = new_vector(origin->x, origin->y, origin->z); // free needed
	// ray->d = vec_substract(origin, point);
	// vec_normalize(ray->d);
	direction = vec_substract(point, origin);
	ray = new_ray(origin, direction);
	free(direction);
	// ray->d = vec_substract(point, origin); // free needed
	return (ray);
} */

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

	// ray = ft_calloc(1, sizeof(t_ray));
	// ray->o = vec_dup(camera->origin);
	// right = vec_multiply(point->x, camera->u);
	right = vec_multiply(point->x, camera->u);
	up = vec_multiply(point->y, camera->v);
	tmp = vec_add(camera->f, up);
	// ray->d = vec_add(tmp, right);
	direction = vec_add(tmp, right);
	free(tmp);
	// direction = matmul3x1(camera->matrix, point);
	// vec_normalize(direction);
	// vec_normalize(ray->d);
	// tmp = vec_substract(direction, camera->origin);
	ray = new_ray(camera->origin, direction);
	// ray = new_ray(camera->origin, tmp);
	// free(tmp);
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
