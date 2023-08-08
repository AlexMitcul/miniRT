/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interceptor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:40:00 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 20:51:52 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	closest_sp(t_sphere *sphere, t_ray *ray)
{
	int				i;
	t_intersection	*hit;

	hit = ray->intersection;
	i = -1;
	while (++i < 2)
	{
		if (hit->t[i] > ray->t_min && hit->t[i] < ray->t_max \
			&& hit->t[i] < hit->t0)
		{
			hit->t0 = hit->t[i];
			hit->sp = sphere;
			hit->type = SPHERE;
			hit->color = sphere->color;
			if (hit->p)
				free(hit->p);
			hit->p = ray_point(ray, hit->t0);
			if (hit->n)
				free(hit->n);
			hit->n = vec_substract(hit->p, hit->sp->center);
			vec_normalize(hit->n);
		}
	}
	return (hit->type != SPHERE);
}

static int	closest_pl(t_plane *pl, t_ray *ray)
{
	t_intersection	*hit;

	hit = ray->intersection;
	if (hit->t[0] > ray->t_min && hit->t[0] < ray->t_max \
		&& hit->t[0] < hit->t0)
	{
		hit->t0 = hit->t[0];
		hit->pl = pl;
		hit->type = PLANE;
		hit->color = pl->color;
		if (hit->p)
			free(hit->p);
		hit->p = ray_point(ray, hit->t0);
		if (hit->n)
			free(hit->n);
		if (vec_product(ray->d, pl->direction) > 0)
			hit->n = vec_multiply(-1.0f, pl->direction);
		else
			hit->n = vec_dup(pl->direction);
		vec_normalize(hit->n);
	}
	return (hit->type != PLANE);
}

static void	set_cy_normal(t_cylinder *cy, t_intersection *hit, int i)
{
	t_vector		*cp;
	t_vector		*tmp;

	if (hit->n)
		free(hit->n);
	cp = vec_substract(hit->p, cy->center);
	if (i < 2)
	{
		tmp = vec_point(cy->center, cy->axis, vec_product(cy->axis, cp));
		hit->n = vec_substract(hit->p, tmp);
		vec_normalize(hit->n);
		free(tmp);
	}
	else if (i == 2)
		hit->n = vec_multiply(-1.0f, cy->axis);
	else
		hit->n = vec_dup(cy->axis);
	free(cp);
}

static int	closest_cy(t_cylinder *cy, t_ray *ray)
{
	int				i;
	t_intersection	*hit;

	hit = ray->intersection;
	i = -1;
	while (++i < 4)
	{
		if (hit->t[i] > ray->t_min && hit->t[i] < ray->t_max \
			&& hit->t[i] < hit->t0)
		{
			hit->t0 = hit->t[i];
			hit->cy = cy;
			hit->type = CYLINDER;
			hit->color = cy->color;
			if (hit->p)
				free(hit->p);
			hit->p = ray_point(ray, hit->t0);
			set_cy_normal(cy, hit, i);
		}
	}
	return (hit->type != CYLINDER);
}

int	intersect_object(void *object, t_ray *ray, int type)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = NULL;
	pl = NULL;
	cy = NULL;
	if (type == SPHERE)
	{
		sp = (t_sphere *)object;
		return (hit_sphere(sp, ray) || closest_sp(sp, ray));
	}
	else if (type == PLANE)
	{
		pl = (t_plane *)object;
		return (hit_plane(pl, ray) || closest_pl(pl, ray));
	}
	else if (type == CYLINDER)
	{
		cy = (t_cylinder *)object;
		return (hit_cylinder(cy, ray) || closest_cy(cy, ray));
	}
	return (1);
}
