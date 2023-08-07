/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interceptor_hit_points.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:59 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/07 19:27:27 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_quadratic		q;
	t_vector		*co;

	co = vec_substract(ray->o, sphere->center);
	q.a = vec_product(ray->d, ray->d);
	q.b = 2.0f * vec_product(co, ray->d);
	q.c = vec_product(co, co) - (float)pow(sphere->radius, 2);
	free(co);
	q.d = (q.b * q.b) - (4.0f * q.a * q.c);
	if (q.d < 0)
		return (1);
	ray->intersection->t[0] = (-q.b + (float)sqrt(q.d)) / (2.0f * q.a);
	ray->intersection->t[1] = (-q.b - (float)sqrt(q.d)) / (2.0f * q.a);
	return (0);
}

int	hit_plane(t_plane *plane, t_ray *ray)
{
	float		po_dot_n;
	t_vector	*po;
	float		d_dot_n;
	int			i;

	i = 0;
	if (plane->is_cylinder_cap)
		i = plane->is_cylinder_cap;
	po = vec_substract(ray->o, plane->origin);
	po_dot_n = vec_product(po, plane->direction);
	free(po);
	d_dot_n = vec_product(ray->d, plane->direction);
	if (f_abs(d_dot_n) > 0.0f && (po_dot_n * d_dot_n < 0.0f))
	{
		ray->intersection->t[i] = -1.0f * po_dot_n / d_dot_n;
		return (0);
	}
	return (1);
}

static int	cap_check(t_cylinder *cy, t_ray *ray, float *t, int cap)
{
	t_vector	*cp[2];
	t_vector	*p;

	p = ray_point(ray, *t);
	cp[0] = vec_substract(p, cy->cap[0]->origin);
	cp[1] = vec_substract(p, cy->cap[1]->origin);
	if (cap >= 0 && vec_product(cp[cap], cp[cap]) > (float)pow(cy->radius, 2))
		*t = 0;
	if (cap == -1 && (vec_product(cp[0], cy->axis) < 0.0f || \
		vec_product(cp[1], cy->axis) > 0.0f))
		*t = 0;
	free(p);
	free(cp[0]);
	free(cp[1]);
	return (!*t);
}

int	hit_cylinder(t_cylinder *cy, t_ray *ray)
{
	t_intersection	*hit;
	t_quadratic		q;
	t_vector		*co;

	hit = ray->intersection;
	co = vec_substract(ray->o, cy->cap[0]->origin);
	q.a = vec_product(ray->d, ray->d) - \
		(float)pow(vec_product(ray->d, cy->axis), 2);
	q.b = 2.0f * vec_product(co, ray->d) - \
		2.0f * vec_product(ray->d, cy->axis) * vec_product(co, cy->axis);
	q.c = vec_product(co, co) - (float)pow(vec_product(co, cy->axis), 2) - \
		(float)pow(cy->radius, 2);
	q.d = (q.b * q.b) - (4.0f * q.a * q.c);
	if (q.d > 0)
	{
		hit->t[0] = (-q.b + (float)sqrt(q.d)) / (2.0f * q.a);
		cap_check(cy, ray, &hit->t[0], -1);
		hit->t[1] = (-q.b - (float)sqrt(q.d)) / (2.0f * q.a);
		cap_check(cy, ray, &hit->t[1], -1);
	}
	hit_plane(cy->cap[0], ray);
	cap_check(cy, ray, &hit->t[2], 0);
	hit_plane(cy->cap[1], ray);
	cap_check(cy, ray, &hit->t[3], 1);
	return (free(co), !hit->t[0] && !hit->t[1] && !hit->t[2] && !hit->t[3]);
}

void	set_cylinder_caps(t_cylinder *cylinders)
{
	t_cylinder	*cy;
	t_vector	*cap_point[2];

	cy = cylinders;
	while (cy)
	{
		if (cy->cap[0])
			free_plane(cy->cap[0]);
		if (cy->cap[1])
			free_plane(cy->cap[1]);
		vec_normalize(cy->axis);
		cap_point[0] = vec_point(cy->center, cy->axis, \
			-1.0f * cy->height / 2.0f);
		cap_point[1] = vec_point(cy->center, cy->axis, cy->height / 2.0f);
		cy->cap[0] = new_plane(cap_point[0], vec_dup(cy->axis), \
			color_dup(cy->color));
		cy->cap[1] = new_plane(cap_point[1], vec_multiply(-1.0f, cy->axis), \
			color_dup(cy->color));
		cy->cap[0]->is_cylinder_cap = 2;
		cy->cap[1]->is_cylinder_cap = 3;
		cy = cy->next;
	}
}
