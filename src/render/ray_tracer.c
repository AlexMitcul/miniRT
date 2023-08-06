/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:45:12 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 20:53:50 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	*ray_point(t_ray *ray, float t)
{
	t_vector	*point;

	point = new_vector(0, 0, 0);
	point->x = ray->o->x + t * ray->d->x;
	point->y = ray->o->y + t * ray->d->y;
	point->z = ray->o->z + t * ray->d->z;
	return (point);
}

static void	cast_shadows(t_scene *scene, t_ray *light_ray, t_intersection *hit)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = scene->spheres;
	while (sp)
	{
		if (!(sp == hit->sp && hit->type == SPHERE))
			intersect_object(sp, light_ray, SPHERE);
		sp = sp->next;
	}
	pl = scene->planes;
	while (pl)
	{
		if (!(pl == hit->pl && hit->type == PLANE))
			intersect_object(pl, light_ray, PLANE);
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		if (!(cy == hit->cy && hit->type == CYLINDER))
			intersect_object(cy, light_ray, CYLINDER);
		cy = cy->next;
	}
}

static float	diffuse_lighting(t_scene *scene, t_ray *ray)
{
	float			intensity;
	t_ray			*light_ray;
	float			n_dot_light;
	t_intersection	*hit;

	hit = ray->intersection;
	intensity = scene->ambient_light->lighting;
	light_ray = scene_ray(hit->p, scene->light->origin);
	cast_shadows(scene, light_ray, hit);
	if (light_ray->intersection->type != TYPE_NONE)
	{
		free_ray(light_ray);
		return (intensity / 2.0f);
	}
	vec_normalize(light_ray->d);
	n_dot_light = vec_product(hit->n, light_ray->d);
	if (n_dot_light > 0.0f)
	{
		intensity += scene->light->brightness * n_dot_light / \
		(vec_length(hit->n) * vec_length(light_ray->d));
	}
	free_ray(light_ray);
	return (intensity / 2.0f);
}

static int	target_hit(t_scene *scene, t_ray *ray)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = scene->spheres;
	while (sp)
	{
		intersect_object(sp, ray, SPHERE);
		sp = sp->next;
	}
	pl = scene->planes;
	while (pl)
	{
		intersect_object(pl, ray, PLANE);
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		intersect_object(cy, ray, CYLINDER);
		cy = cy->next;
	}
	return (ray->intersection->t0 != INFINITY);
}

t_color	*trace_ray(t_scene *scene, t_ray *ray)
{
	float		lighting;

	if (!target_hit(scene, ray))
		return (color_dup(scene->background_color));
	lighting = diffuse_lighting(scene, ray);
	return (color_multiply(lighting, ray->intersection->color));
}
