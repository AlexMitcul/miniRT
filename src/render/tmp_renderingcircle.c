/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_renderingcircle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:31:07 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/05 03:46:18 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* t_vector	*rodrigues_rotation(t_vector *v, t_vector *k, float theta)
{
	t_vector	*result;
	t_vector	*cross;
	float		cos_theta;
	float		sin_theta;

	result = vec_dup(v);
	cross = vec_cross_product(k, v);
	cos_theta = cos(theta);
	sin_theta = sin(theta);
	result->x = v->x * cos_theta + cross->x * sin_theta + k->x * \
		vec_product(k, v) * (1 - cos_theta);
	result->y = v->y * cos_theta + cross->y * sin_theta + k->y * \
		vec_product(k, v) * (1 - cos_theta);
	result->z = v->z * cos_theta + cross->z * sin_theta + k->z * \
		vec_product(k, v) * (1 - cos_theta);
	free(cross);
	return (result);
} */

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

	// x += CANVAS_WIDTH / 2;
	// y += CANVAS_HEIGHT / 2;
	// (void)color;
	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

// t_vector	*canvas_to_viewport(t_scene *scene, int x, int y)
t_vector	*canvas_to_viewport(t_scene *scene, t_vector *canvas_point)
{
	t_vector	*v;

	v = new_vector(0, 0, 0);
	/* v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH) \
		- scene->camera->viewport_width / 2;
	v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT) \
		- scene->camera->viewport_height / 2; */
	v->x = canvas_point->x * scene->camera->viewport_width;
	v->y = canvas_point->y * scene->camera->viewport_height;
	// v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH);
	// v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT);
	v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

void	intersect_sphere(t_sphere *sphere, t_ray *ray, float *t1, float *t2)
{
	t_vector		*co;
	float			a;
	float			b;
	float			c;
	float			discr;
	// t_ray			*tmp;

	// printf("intersect sphere\n");
	// printf("ray->d: %f %f %f\n", ray->d->x, ray->d->y, ray->d->z);
	// ray->o = new_vector(0, 0, 0);
	// printf("ray->o: %f %f %f\n", ray->o->x, ray->o->y, ray->o->z);
	// tmp = new_ray(ray->o, ray->d);

	co = vec_substract(ray->o, sphere->center);
	// vec_normalize(ray->d);
	// co = vec_dup(ray->o);
	// printf("co: %f %f %f\n", co->x, co->y, co->z);
	
	a = vec_product(ray->d, ray->d);
	b = 2 * vec_product(co, ray->d);
	c = vec_product(co, co) - (float)pow(sphere->radius, 2);
	free(co);
	discr = (b * b) - (4 * a * c);
	if (discr < 0)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
}

void	intersect_plane(t_plane *plane, t_ray *ray, float *t1, float *t2)
{
	float		op_dot_n;
	t_vector	*op;
	float		d_dot_n;
	// op = vec_substract(plane->origin, ray->o);
	op = vec_substract(plane->origin, ray->o);
	op_dot_n = vec_product(op, plane->direction);
	// free(op);
	d_dot_n = vec_product(ray->d, plane->direction);
	if (d_dot_n > EPSYLON)
		*t1 = op_dot_n / d_dot_n;
	(void)t2;
	/* t_vector	*minus_n;
	minus_n = vec_multiply(-1.0f, plane->direction);
	op_dot_n = vec_product(op, minus_n);
	d_dot_n = vec_product(ray->d, minus_n);
	if (d_dot_n > EPSYLON)
		*t2 = op_dot_n / d_dot_n;
	free(minus_n); */
	free(op);
}

void	cyl_cap(t_cylinder *cyl, t_ray *ray, float *t, int cap)
{
	t_vector	*cp[2];
	t_vector	*p;
	t_vector	*c[2];
	
	c[0] = vec_point(cyl->center, cyl->axis, -1.0 * cyl->height / 2);
	c[1] = vec_point(cyl->center, cyl->axis, cyl->height / 2);
	p = ray_point(ray, *t);
	cp[0] = vec_substract(p, c[0]);
	cp[1] = vec_substract(p, c[1]);
	// *t *= (vec_product(cp, cyl->axis) == 0);
	if (cap >= 0 && vec_product(cp[cap], cp[cap]) > (float)pow(cyl->radius, 2))
		*t = 0;
	if (cap < 0 && (vec_product(cp[0], cyl->axis) < 0 || \
		vec_product(cp[1], cyl->axis) > 0))
		*t = 0;
	free(c[0]);
	free(c[1]);
	free(p);
	free(cp[0]);
	free(cp[1]);
}

void	vec_swap(t_vector **a, t_vector **b)
{
	t_vector	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	intersect_cylinder(t_cylinder *cyl, t_ray *ray, float *t1, float *t2, \
	float *t3, float *t4, float *t5, float *t6) // t3?
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_plane		*plane;
	// t_vector	*n[2];
	t_vector	*c1;
	t_vector	*c1o;
	// t_vector	*center_line;
	t_vector	*tmp[3];

	// n[0] = vec_dup(cyl->axis);
	// n[1] = vec_multiply(-1.0f, cyl->axis);
	// center_line = vec_substract(cyl->c[1], cyl->c[0]);
	// if (vec_product(center_line, cyl->axis) < 0)
	// 	vec_swap(&n[0], &n[1]);
	plane = new_plane(vec_point(cyl->center, cyl->axis, cyl->height / 2), \
		vec_dup(cyl->axis), color_dup(cyl->color));
	plane->next = new_plane(vec_point(cyl->center, cyl->axis, -cyl->height / 2), \
		vec_dup(cyl->axis), color_dup(cyl->color)); // inverting vector? does it resolve the double intersection for plane?
	
	// printf("n[0]:`%f %f %f\n", n[0]->x, n[0]->y, n[0]->z);
	// printf("n[1]:`%f %f %f\n", n[1]->x, n[1]->y, n[1]->z);

	/* a = vec_product(ray->d, ray->d) - (float)pow(vec_product(ray->d, cyl->axis), 2);
	b = 2 * vec_product(ray->o, ray->d) - 2 * vec_product(ray->d, cyl->axis) * \
		vec_product(ray->o, cyl->axis);
	c = vec_product(ray->o, ray->o) - (float)pow(vec_product(ray->o, cyl->axis), 2) - \
		(float)pow(cyl->radius, 2); */
	c1 = vec_point(cyl->center, cyl->axis, -1.0 * cyl->height / 2);
	c1o = vec_substract(ray->o, c1);
	tmp[0] = vec_multiply(vec_product(ray->d, cyl->axis), cyl->axis);
	tmp[1] = vec_substract(ray->d, tmp[0]);
	free(tmp[0]);
	tmp[0] = vec_multiply(vec_product(c1o, cyl->axis), cyl->axis);
	tmp[2] = vec_substract(c1o, tmp[0]);
	a = vec_product(tmp[1], tmp[1]);
	b = 2 * vec_product(tmp[1], tmp[2]);
	c = vec_product(tmp[2], tmp[2]) - (float)pow(cyl->radius, 2);
	discr = (b * b) - (4 * a * c);
	if (discr > 0)
	{
		*t1 = (-b + (float)sqrt(discr)) / (2 * a);
		cyl_cap(cyl, ray, t1, -1);
		*t2 = (-b - (float)sqrt(discr)) / (2 * a);
		cyl_cap(cyl, ray, t2, -1);
	}
	intersect_plane(plane, ray, t3, t4);
	cyl_cap(cyl, ray, t3, 1);
	cyl_cap(cyl, ray, t4, 1);
	intersect_plane(plane->next, ray, t5, t6);
	cyl_cap(cyl, ray, t5, 0);
	cyl_cap(cyl, ray, t6, 0);
	free_plane_list(plane);
	// free_vector(n);
	// free(center_line);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
}

void	sp_closest_intersection(t_sphere *sphere, t_ray *ray, float t[2], \
				float t_min, float t_max)
{
	if (t[0] > t_min && t[0] < t_max && t[0] < ray->intersection->t)
	{
		ray->intersection->t = t[0];
		ray->intersection->sp = sphere;
		ray->intersection->type = SPHERE;
		ray->intersection->color = sphere->color;
		if (ray->intersection->p)
			free(ray->intersection->p);
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		if (ray->intersection->n)
			free(ray->intersection->n);
		ray->intersection->n = vec_substract(ray->intersection->p, \
		ray->intersection->sp->center);
		vec_normalize(ray->intersection->n);
	}
	if (t[1] > t_min && t[1] < t_max && t[1] < ray->intersection->t)
	{
		ray->intersection->t = t[1];
		ray->intersection->sp = sphere;
		ray->intersection->type = SPHERE;
		ray->intersection->color = sphere->color;
		if (ray->intersection->p)
			free(ray->intersection->p);
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		if (ray->intersection->n)
			free(ray->intersection->n);
		ray->intersection->n = vec_substract(ray->intersection->p, \
		ray->intersection->sp->center);
		vec_normalize(ray->intersection->n);
	}
}

void	pl_closest_intersection(t_plane *pl, t_ray *ray, float *t, \
				float t_min, float t_max)
{
	// printf("t: %f\n", t);
	if (t[0] > t_min && t[0] < t_max && t[0] < ray->intersection->t)
	{
		ray->intersection->t = t[0];
		ray->intersection->pl = pl;
		ray->intersection->type = PLANE;
		ray->intersection->color = pl->color;
		if (ray->intersection->p)
			free(ray->intersection->p);
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		if (ray->intersection->n)
			free(ray->intersection->n);
		ray->intersection->n = vec_dup(pl->direction);
		vec_normalize(ray->intersection->n);
	}
	if (t[1] > t_min && t[1] < t_max && t[1] < ray->intersection->t)
	{
		ray->intersection->t = t[1];
		ray->intersection->pl = pl;
		ray->intersection->type = PLANE;
		ray->intersection->color = pl->color;
		if (ray->intersection->p)
			free(ray->intersection->p);
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		if (ray->intersection->n)
			free(ray->intersection->n);
		ray->intersection->n = vec_dup(pl->direction);
		vec_normalize(ray->intersection->n);
	}
}

void	cyl_closest_intersection(t_cylinder *cyl, t_ray *ray, float *t, float t_min, float t_max)
{
	int			i;
	t_vector	*c1p;
	t_vector	*tmp;

	i = -1;
	while (i++ < 5)
	{
		if (t[i] > t_min && t[i] < t_max && t[i] < ray->intersection->t)
		{
			ray->intersection->t = t[i];
			ray->intersection->cyl = cyl;
			ray->intersection->type = CYLINDER;
			ray->intersection->color = cyl->color;
			if (ray->intersection->p)
				free(ray->intersection->p);
			ray->intersection->p = ray_point(ray, ray->intersection->t);
			if (ray->intersection->n)
				free(ray->intersection->n);
			if (i < 2)
			{
				c1p = vec_substract(ray->intersection->p, cyl->center);
				tmp = vec_point(cyl->c[0], cyl->axis, vec_product(cyl->axis, c1p));
				ray->intersection->n = vec_substract(ray->intersection->p, tmp);
				vec_normalize(ray->intersection->n);
				free(c1p);
			}
			else
				// ray->intersection->n = vec_multiply(-1.0f, cyl->axis);
				ray->intersection->n = vec_dup(cyl->axis); // consider front/face thing?
		}
	}
	/* if (t[0] > t_min && t[0] < t_max && t[0] < ray->intersection->t)
	{
		ray->intersection->t = t[0];
		ray->intersection->cyl = cyl;
		ray->intersection->type = CYLINDER;
		ray->intersection->color = cyl->color;
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		ray->intersection->n = vec_substract(ray->intersection->p, cyl->center);
		vec_normalize(ray->intersection->n);
	}
	if (t[1] > t_min && t[1] < t_max && t[1] < ray->intersection->t)
	{
		ray->intersection->t = t[1];
		ray->intersection->cyl = cyl;
		ray->intersection->type = CYLINDER;
		ray->intersection->color = cyl->color;
		ray->intersection->p = ray_point(ray, ray->intersection->t);
		ray->intersection->n = vec_substract(ray->intersection->p, cyl->center);
		vec_normalize(ray->intersection->n);
	} */
}

int	shadow(t_scene *scene, t_intersection *inter)
{
	t_ray		*shadow_ray;
	t_vector	*direction;
	float		t[6];
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	int			r;
	
	r = 0;
	direction = vec_substract(scene->light->origin, inter->p);
	shadow_ray = new_ray(inter->p, direction); // do not normalize
	free(direction);
	ft_bzero(t, sizeof(float) * 6);
	sp = scene->spheres;
	/* int i = (inter->sp != NULL) + (inter->pl != NULL) + (inter->cyl != NULL);
	if (i > 1)
	{
		printf("ERROR: more than one non NULL\n");
		printf("inter->sp: %p\n", inter->sp);
		printf("inter->pl: %p\n", inter->pl);
		printf("inter->cyl: %p\n", inter->cyl);
		printf("inter->t: %f\n", inter->t);
		printf("inter->type: %d\n", inter->type);
	} */
	while (sp)
	{
		if (!(sp == inter->sp && inter->type == SPHERE))
		{
			intersect_sphere(sp, shadow_ray, &t[0], &t[1]);
			sp_closest_intersection(sp, shadow_ray, t, EPSYLON, 1.0f);
		}
		sp = sp->next;
	}
	pl = scene->planes;
	while (pl)
	{
		if (!(pl == inter->pl && inter->type == PLANE))
		{
			intersect_plane(pl, shadow_ray, &t[0], &t[1]);
			pl_closest_intersection(pl, shadow_ray, t, EPSYLON, 1.0f);
		}
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		if (!(cy == inter->cyl && inter->type == CYLINDER))
		{
			intersect_cylinder(cy, shadow_ray, &t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
			cyl_closest_intersection(cy, shadow_ray, t, EPSYLON, 1.0f);
		}
		cy = cy->next;
	}
	r = shadow_ray->intersection->t != INFINITY;
	free_ray(shadow_ray);
	return (r);
}

float	diffuse_lighting(t_scene *scene, t_ray *ray)
{
	float		intensity;
	t_ray		*light_ray;
	float		n_dot_light;

	intensity = scene->ambient_light->lighting;
	light_ray = scene_ray(scene->light->origin, ray->intersection->p);
	vec_normalize(light_ray->d);
	if (shadow(scene, ray->intersection))
	{
		free_ray(light_ray);
		// printf("in the shadow\n");
		return (intensity / 2);
	}
	printf("intersection->n: %f, %f, %f\n", ray->intersection->n->x, ray->intersection->n->y, ray->intersection->n->z);
	printf("light_ray->d: %f, %f, %f\n", light_ray->d->x, light_ray->d->y, light_ray->d->z);
	n_dot_light = vec_product(ray->intersection->n, light_ray->d);
	if (n_dot_light > 0) // && !shadow(scene, ray->intersection->p))
	{
		printf("n_dot_light: %f\n", n_dot_light); // LIGHT RAY NOT GOING IN THE RIGHT DIRECTION?
		intensity += scene->light->brightness * n_dot_light / \
		(vec_length(ray->intersection->n) * vec_length(light_ray->d));
	}
	free_ray(light_ray);
	return (intensity / 2);
}


t_color	*ray_tracer(t_scene* scene, t_ray *ray)
{
	float		t[6];
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cyl;
	float		lighting;

	sp = scene->spheres;
	ft_bzero(t, sizeof(float) * 6);
	while (sp)
	{
		intersect_sphere(sp, ray, &t[0], &t[1]);
		sp_closest_intersection(sp, ray, t, DISTANCE_TO_VIEWPORT, INFINITY);
		sp = sp->next;
	}
	pl = scene->planes;
	// ft_bzero(t, sizeof(float) * 2);
	while (pl)
	{
		intersect_plane(pl, ray, &t[0], &t[1]);
		pl_closest_intersection(pl, ray, t, DISTANCE_TO_VIEWPORT, INFINITY);
		pl = pl->next;
	}
	cyl = scene->cylinders;
	while (cyl)
	{
		vec_normalize(cyl->axis);
		cyl->c[0] = vec_point(cyl->center, cyl->axis, -cyl->height / 2);
		cyl->c[1] = vec_point(cyl->center, cyl->axis, cyl->height / 2);
		intersect_cylinder(cyl, ray, &t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
		cyl_closest_intersection(cyl, ray, t, DISTANCE_TO_VIEWPORT, INFINITY);
		cyl = cyl->next;
	}
	if (ray->intersection->t == INFINITY)
		return (color_dup(scene->background_color));
	// printf("t = %f\n", ray->intersection->t);
	// printf("type = %d\n", ray->intersection->type);
	// return (new_color(255, 255, 255));
	/* ray->intersection->p = ray_point(ray, ray->intersection->t);
	ray->intersection->n = vec_substract(ray->intersection->p, \
		ray->intersection->sp->center);
	vec_normalize(ray->intersection->n); */
	lighting = diffuse_lighting(scene, ray);
	return (color_multiply(lighting, ray->intersection->color));
}

// cyllinder
// plane
// diffuse light
// ambient light
// hard shadows
// antialising for smoother edges? mean filter

t_vector	*get_canvas_point(int x, int y)
{
	float	cx;
	float	cy;
	// float	e[2];

	// ft_bzero(e, sizeof(float) * 2);
	// e[0] = (float) !(CANVAS_WIDTH % 2) * 0.5;
	// e[1] = (float) !(CANVAS_HEIGHT % 2) * 0.5;
	cx = 2.0f * ((float)x) / (float)CANVAS_WIDTH - 1.0f;
	cy = 2.0f * ((float)y) / (float)CANVAS_HEIGHT - 1.0f;
	// cx = 2.0f * ((float)x + e[0]) / (float)CANVAS_WIDTH - 1.0f;
	// cy = 2.0f * ((float)y + e[1]) / (float)CANVAS_HEIGHT - 1.0f;
	// cx *= -1;
	cy *= -1;
	return (new_vector(cx, cy, 0.0f));
}

/* void	adjust_vectors(t_scene *scene) //  not that simple
{
	t_plane		*pl;
	t_cylinder	*cy;
	
	pl = scene->planes;
	while (pl)
	{
		if (vec_product(pl->direction, scene->camera->direction) < 0)
		{
			free(pl->direction);
			pl->direction = vec_multiply(-1, pl->direction);
		}
		vec_normalize(pl->direction);
		pl = pl->next;
	}
	cy = scene->cylinders;
	while (cy)
	{
		vec_normalize(cy->axis);
		cy = cy->next;
	}
} */

void	render_sphere(t_scene *scene)
{
	int 		x;
	int 		y;
	// t_vector	*direction;
	t_vector	*viewport_point;
	t_vector	*canvas_point;
	t_color		*color;
	t_ray		*ray;

	printf("camera origin: %f %f %f\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
	
	// y = -CANVAS_HEIGHT / 2 - 1;
	y = -1;
	// while (++y < CANVAS_HEIGHT / 2)
	while (++y < CANVAS_HEIGHT)
	{
		
		// x = -CANVAS_WIDTH / 2 - 1;
		x = -1;
		// while (++x < CANVAS_WIDTH / 2)
		while (++x < CANVAS_WIDTH)
		{
			canvas_point = get_canvas_point(x, y);
			viewport_point = canvas_to_viewport(scene, canvas_point);
			// printf("x: %d y: %d\n", x, y);
			// printf("canvas_point: %f %f %f\n", canvas_point->x, canvas_point->y, canvas_point->z);
			// printf("viewport_point: %f %f %f\n", viewport_point->x, viewport_point->y, viewport_point->z);
			// printf("x: %d y: %d\n", x, y);
			ray = camera_ray(scene->camera, viewport_point);
			vec_normalize(ray->d);
			// ray = new_ray(scene->camera->origin, viewport_point, scene->camera);
			// printf("ray: %f %f %f\n", ray->o->x, ray->o->y, ray->o->z);
			// printf("ray: %f %f %f\n", ray->d->x, ray->d->y, ray->d->z);
			// viewport_point = canvas_to_viewport(scene, x, y);
			// direction = vec_substract(viewport_point, scene->camera->origin);
			// free(viewport_point);
			// vec_normalize(direction);
			color = ray_tracer(scene, ray);
			// color = ray_tracer(scene, direction);
			
			// printf("direction: %f %f %f\n", direction->x, direction->y, direction->z);
			pixel_put(scene->window_data, x, y, color);
			free_ray(ray);
			// free(direction); // free direction vector
			free(canvas_point);
			free(viewport_point);
			free(color);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, 0, 0);
}
