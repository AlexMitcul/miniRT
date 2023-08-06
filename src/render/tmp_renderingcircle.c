/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_renderingcircle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:31:07 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/06 02:50:09 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	new_image(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->window_data->img);
	scene->window_data->img = mlx_new_image(scene->mlx, \
	CANVAS_WIDTH, CANVAS_HEIGHT);
	if (!scene->window_data->img)
		return (1);
	scene->window_data->addr = mlx_get_data_addr(scene->window_data->img, \
		&scene->window_data->bits_per_pixel, \
		&scene->window_data->line_length, &scene->window_data->endian);
	return (0);
}

int	rgb2int(t_color *color)
{
	return (color->r << 16 | color->g << 8 | color->b);
}

void	pixel_put(t_window_data *img, int x, int y, t_color *color)
{
	char	*pxl;

	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

t_vector	*canvas_to_viewport(t_scene *scene, t_vector *canvas_point)
{
	t_vector	*v;

	v = new_vector(0.0f, 0.0f, 0.0f);
	v->x = canvas_point->x * scene->camera->viewport_width;
	v->y = canvas_point->y * scene->camera->viewport_height;
	v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

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

float	f_abs(float a)
{
	if (a < 0.0f)
		return (-a);
	return (a);
}

int	hit_plane(t_plane *plane, t_ray *ray, int i)
{
	float		po_dot_n;
	t_vector	*po;
	float		d_dot_n;

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

int	cap_check(t_cylinder *cy, t_ray *ray, float *t, int cap)
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

void	vec_swap(t_vector **a, t_vector **b)
{
	t_vector	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	hit_cylinder(t_cylinder *cy, t_ray *ray)
{
	t_intersection	*hit;
	t_quadratic		q;
	t_vector		*co;

	hit = ray->intersection;
	co = vec_substract(ray->o, cy->cap[0]->origin);
	q.a = vec_product(ray->d, ray->d) - (float)pow(vec_product(ray->d, cy->axis), 2);
	q.b = 2.0f * vec_product(co, ray->d) - 2.0f * vec_product(ray->d, cy->axis) * \
		vec_product(co, cy->axis);
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
	hit_plane(cy->cap[0], ray, 2);
	cap_check(cy, ray, &hit->t[2], 0);
	hit_plane(cy->cap[1], ray, 3);
	cap_check(cy, ray, &hit->t[3], 1);
	free(co);
	return (!hit->t[0] && !hit->t[1] && !hit->t[2] && !hit->t[3]);
}

int	closest_sp(t_sphere *sphere, t_ray *ray, float t_min, float t_max)
{
	int				i;
	t_intersection	*hit;

	hit = ray->intersection;
	i = -1;
	while (++i < 2)
	{
		if (hit->t[i] > t_min && hit->t[i] < t_max && hit->t[i] < hit->t0)
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

int	closest_pl(t_plane *pl, t_ray *ray, float t_min, float t_max)
{
	t_intersection	*hit;

	hit = ray->intersection;
	if (hit->t[0] > t_min && hit->t[0] < t_max && hit->t[0] < hit->t0)
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

void	set_cy_normal(t_cylinder *cy, t_intersection *hit, int i)
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

int	closest_cy(t_cylinder *cy, t_ray *ray, float t_min, float t_max)
{
	int				i;
	t_intersection	*hit;

	hit = ray->intersection;
	i = -1;
	while (i++ < 4)
	{
		if (hit->t[i] > t_min && hit->t[i] < t_max && hit->t[i] < hit->t0)
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

// include limits fot t
int	intersect_object(void *object, t_ray *ray, int id, int pl_i)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = NULL;
	pl = NULL;
	cy = NULL;
	if (id == SPHERE)
	{
		sp = (t_sphere *)object;
		return (hit_sphere(sp, ray) || closest_sp(sp, ray, 0.0f, 1.0f));
	}
	else if (id == PLANE)
	{
		pl = (t_plane *)object;
		return (hit_plane(pl, ray, pl_i) || closest_pl(pl, ray, 0.0f, 1.0f));
	}
	else if (id == CYLINDER)
	{
		cy = (t_cylinder *)object;
		return (hit_cylinder(cy, ray) || closest_cy(cy, ray, 0.0f, 1.0f));
	}
	return (1);
}

void	cast_shadows(t_scene *scene, t_ray *light_ray, t_intersection *hit)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = scene->spheres;
	while (sp)
	{
		if (!(sp == hit->sp && hit->type == SPHERE))
			intersect_object(sp, light_ray, SPHERE, 0);
		sp = sp->next;
	}
	pl = scene->planes;
	while (pl)
	{
		if (!(pl == hit->pl && hit->type == PLANE))
			intersect_object(pl, light_ray, PLANE, 0);
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		if (!(cy == hit->cy && hit->type == CYLINDER))
			intersect_object(cy, light_ray, CYLINDER, 0);
		cy = cy->next;
	}
}

float	diffuse_lighting(t_scene *scene, t_ray *ray)
{
	float		intensity;
	t_ray		*light_ray;
	float		n_dot_light;

	intensity = scene->ambient_light->lighting;
	light_ray = scene_ray(ray->intersection->p, scene->light->origin);
	cast_shadows(scene, light_ray, ray->intersection);
	if (light_ray->intersection->type != TYPE_NONE)
		return (free_ray(light_ray), intensity / 2.0f);
	vec_normalize(light_ray->d);
	n_dot_light = vec_product(ray->intersection->n, light_ray->d);
	if (n_dot_light > 0.0f)
	{
		intensity += scene->light->brightness * n_dot_light / \
		(vec_length(ray->intersection->n) * vec_length(light_ray->d));
	}
	free_ray(light_ray);
	return (intensity / 2.0f);
}

t_color	*ray_tracer(t_scene* scene, t_ray *ray) // shorten
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	float		lighting;

	sp = scene->spheres;
	while (sp)
	{
		hit_sphere(sp, ray);
		closest_sp(sp, ray, DISTANCE_TO_VIEWPORT, INFINITY);
		sp = sp->next;
	}
	pl = scene->planes;
	while (pl)
	{
		hit_plane(pl, ray, 0);
		closest_pl(pl, ray, DISTANCE_TO_VIEWPORT, INFINITY);
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		hit_cylinder(cy, ray);
		closest_cy(cy, ray, DISTANCE_TO_VIEWPORT, INFINITY);
		cy = cy->next;
	}
	if (ray->intersection->t0 == INFINITY)
		return (color_dup(scene->background_color));
	lighting = diffuse_lighting(scene, ray);
	return (color_multiply(lighting, ray->intersection->color));
}

// cyllinder CHECK
// plane CHECK
// diffuse light CHECK.
// ambient light CHECK
// hard shadows CHECK
// antialising for smoother edges? mean filter

t_vector	*get_canvas_point(int x, int y)
{
	float	cx;
	float	cy;

	cx = 2.0f * ((float)x) / (float)CANVAS_WIDTH - 1.0f;
	cy = 2.0f * ((float)y) / (float)CANVAS_HEIGHT - 1.0f;
	cy *= -1.0f;
	return (new_vector(cx, cy, 0.0f));
}

void	set_cylinder_caps(t_cylinder *cylinders)
{
	t_cylinder	*cy;
	t_vector	*cap_point[2];
	
	cy = cylinders;
	while (cy)
	{
		vec_normalize(cy->axis);
		cap_point[0] = vec_point(cy->center, cy->axis, -1.0f * cy->height / 2.0f);
		cap_point[1] = vec_point(cy->center, cy->axis, cy->height / 2.0f);
		cy->cap[0] = new_plane(cap_point[0], vec_dup(cy->axis), \
			color_dup(cy->color));
		cy->cap[1] = new_plane(cap_point[1], vec_multiply(-1.0f, cy->axis), \
			color_dup(cy->color));
		cy = cy->next;
	}
}

t_render	*new_render(t_scene *scene, int x, int y)
{
	t_render	*render;
	
	render = ft_calloc(1, sizeof(t_render));
	render->canvas_point = get_canvas_point(x, y);
	render->viewport_point = canvas_to_viewport(scene, render->canvas_point);
	render->ray = camera_ray(scene->camera, render->viewport_point);
	vec_normalize(render->ray->d);
	return (render);
}

void	free_render(t_render *render)
{
	if (!render)
		return ;
	if (render->canvas_point)
		free_vector(render->canvas_point);
	if (render->viewport_point)
		free_vector(render->viewport_point);
	if (render->ray)
		free_ray(render->ray);
	if (render->color)
		free_color(render->color);
	free(render);
}

void	render_sphere(t_scene *scene)
{
	int 		x;
	int 		y;
	t_render	*render;

	set_cylinder_caps(scene->cylinders);
	y = -1;
	while (++y < CANVAS_HEIGHT)
	{
		x = -1;
		while (++x < CANVAS_WIDTH)
		{
			render = new_render(scene, x, y);
			render->color = ray_tracer(scene, render->ray);
			pixel_put(scene->window_data, x, y, render->color);
			free_render(render);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, 0, 0);
}
