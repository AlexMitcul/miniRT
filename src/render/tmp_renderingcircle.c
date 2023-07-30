/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_renderingcircle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:31:07 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/29 01:06:01 by amenses-         ###   ########.fr       */
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

	// x += CANVAS_WIDTH / 2;
	// y += CANVAS_HEIGHT / 2;
	// (void)color;
	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

t_vector	*canvas_to_viewport(t_scene *scene, int x, int y)
{
	t_vector	*v;

	v = new_vector(0, 0, 0);
	// x = 2 * x / CANVAS_WIDTH - 1;
	// y = 2 * y / CANVAS_HEIGHT - 1;
	v->x = (float)x * (scene->camera->viewport_width / (float)CANVAS_WIDTH) \
		- scene->camera->viewport_width / 2;
	v->y = (float)y * (scene->camera->viewport_height / (float)CANVAS_HEIGHT) \
		- scene->camera->viewport_height / 2;
	// v->y *= -1.0;
	// v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH) - 1;
	// v->x *= scene->camera->aspect_ratio;
	// v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT) - 1;
	// v->y *= scene->camera->aspect_ratio;
	v->z = scene->focal_length;
	// v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

void	intersect_sphere(t_sphere *sphere, t_ray *ray, float *t1, float *t2)
{
	t_vector		*co;
	float			a;
	float			b;
	float			c;
	float			discr;

	// printf("intersect sphere\n");
	// printf("ray->d: %f %f %f\n", ray->d->x, ray->d->y, ray->d->z);
	// ray->o = new_vector(0, 0, 0);
	// printf("ray->o: %f %f %f\n", ray->o->x, ray->o->y, ray->o->z);
	co = vec_substract(ray->o, sphere->center);
	// printf("co: %f %f %f\n", co->x, co->y, co->z);
	a = vec_product(ray->d, ray->d);
	b = 2 * vec_product(co, ray->d);
	c = vec_product(co, co) - sphere->radius * sphere->radius;
	free(co);
	discr = b * b - 4 * a * c;
	if (discr < 0 || a < 0.000000001)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
}

/* void	intersect_ray_sphere(t_scene *scene, t_sphere *sp, float *t1, float *t2, t_vector direction)
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_vector	*oc;

	*t1 = 0;
	*t2 = 0;
	oc = vec_substract(scene->camera->origin, sp->center);
	// printf("oc: %f %f %f\n", oc->x, oc->y, oc->z);
	a = vec_product(&direction, &direction);
	b = 2 * vec_product(oc, &direction);
	c = vec_product(oc, oc) - sp->radius * sp->radius;
	free(oc);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
	// printf("t1: %f, t2: %f\n", *t1, *t2);
} */

// void	set_sp_closest_intersection(t_sphere *sp, t_sphere **closest_sp, float t1, float t2, float *closest_t)
void	closest_intersection(t_sphere *sphere, t_ray *ray, float t[2], \
				float t_min, float t_max)
{
	// printf("closest_intersection\n");
	// printf("sphere->center: %f %f %f\n", sphere->center->x, sphere->center->y, sphere->center->z);
	if (t[0] > t_min && t[0] < t_max && t[0] < ray->intersection->t)
	{
		ray->intersection->t = t[0];
		ray->intersection->sp = sphere;
		// *closest_t = t1;
		// *closest_sp = sp;
	}
	if (t[1] > t_min && t[1] < t_max && t[1] < ray->intersection->t)
	{
		ray->intersection->t = t[1];
		ray->intersection->sp = sphere;
		// *closest_t = t2;
		// *closest_sp = sp;
	}
	// printf("ray->intersection->t: %f\n", ray->intersection->t);
	// t_sphere *sp = ray->intersection->sp;
	// if (ray->intersection->sp)
	// {
	// 	// printf()
	// 	printf("intersection sp center: %f\n", sp->center->x);
	// }

}

/* void	shadow_intersect_ray_sphere(t_scene *scene, t_sphere *sp, float *t1, float *t2, \
		t_vector *intersection_point, t_vector direction)
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_vector	*oc;

	*t1 = 0;
	*t2 = 0;
	oc = vec_substract(intersection_point, sp->center);
	// printf("oc: %f %f %f\n", oc->x, oc->y, oc->z);
	a = vec_product(&direction, &direction);
	b = 2 * vec_product(oc, &direction);
	c = vec_product(oc, oc) - sp->radius * sp->radius;
	free(oc);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
	// printf("t1: %f, t2: %f\n", *t1, *t2);
} */

/* int	shadow_check(t_scene *scene, t_vector *intersection_point, t_vector *light_direction)
{
	float		t[2];
	t_sphere	*sp;
	float		closest_t;
	t_sphere	*closest_sp;
	// float		lighting;
	// t_vector	*intersection_point;
	// t_vector	*normal;
	// t_vector	*t_dot_direction;

	sp = scene->spheres;
	closest_t = MAX_T;
	closest_sp = NULL;
	while (sp)
	{
		shadow_intersect_ray_sphere(scene, sp, &t[0], &t[1], intersection_point, *light_direction);
		set_sp_closest_intersection(sp, &closest_sp, t[0], t[1], &closest_t);
		sp = sp->next;
	}
	if (!closest_sp)
		return (0);
	return (1);
} */

/* lighting intensity [0,1] */
// float	diffuse_lighting(t_scene *scene, t_vector *intersection_point, t_vector *normal)
float	diffuse_lighting(t_scene *scene, t_ray *ray)
{
	float		intensity;
	// t_vector	*light_direction;
	t_ray		*light_ray;
	float		n_dot_light;

	intensity = scene->ambient_light->lighting;
	light_ray = new_ray(ray->intersection->p, scene->light->origin);
	
	// light_direction = vec_substract(scene->light->origin, intersection_point);
	n_dot_light = vec_product(ray->intersection->n, light_ray->d);
	// normal_dot_light = vec_product(normal, light_direction);
	/* if (shadow_check(scene, intersection_point, light_direction)) //
		return (intensity / 2); // */
	if (n_dot_light > 0)
	{
		intensity += scene->light->brightness * n_dot_light / \
		(vec_length(ray->intersection->n) * vec_length(light_ray->d));
		// printf("intensity: %f\n", intensity);
	}
	free_ray(light_ray);
	// free(light_direction);
	return (intensity / 2);
}

t_intersection	*intersection_init(void)
{
	t_intersection	*intersection;

	intersection = ft_calloc(1, sizeof(t_intersection));
	intersection->t = MAX_T;
	return (intersection);
}

// t_color	*ray_tracer(t_scene *scene, t_vector *direction)
t_color	*ray_tracer(t_scene* scene, t_ray *ray)
{
	float		t[2];
	t_sphere	*sp;
	// float		closest_t;
	// t_sphere	*closest_sp;
	float		lighting;
	// t_vector	*intersection_point;
	// t_vector	*normal;
	// t_vector	*t_dot_direction;

	sp = scene->spheres;
	ft_bzero(t, sizeof(float) * 2);
	// t = ft_calloc(2, sizeof(float));
	// closest_t = MAX_T;
	// closest_sp = NULL;
	ray->intersection = intersection_init();
	while (sp)
	{
		intersect_sphere(sp, ray, &t[0], &t[1]);
		// intersect_ray_sphere(sp, ray);
		// intersect_ray_sphere(scene, sp, &t[0], &t[1], *direction);
		// printf("(BEFORE)\n");
		// printf("sphere->center: %f %f %f\n", sp->center->x, sp->center->y, sp->center->z);
		closest_intersection(sp, ray, t, DISTANCE_TO_VIEWPORT, MAX_T);
		// set_sp_closest_intersection(sp, &closest_sp, t[0], t[1], &closest_t);
		sp = sp->next;
	}
	// if (!closest_sp)
	// free(t);
	if (ray->intersection->t == MAX_T)
		return (color_dup(scene->background_color));
	// ray->o = new_vector(0, 0, 0);
	ray->intersection->p = ray_point(ray, ray->intersection->t);
	ray->intersection->n = vec_substract(ray->intersection->p, \
		ray->intersection->sp->center);
	ray->intersection->color = ray->intersection->sp->color; // really? maybe for multiple objects
	vec_normalize(ray->intersection->n);
	// t_dot_direction = vec_multiply(closest_t, direction);
	// intersection_point = vec_add(scene->camera->origin, t_dot_direction);
	// normal = vec_substract(intersection_point, closest_sp->center);
	// vec_normalize(normal);
	lighting = diffuse_lighting(scene, ray);
	// lighting = diffuse_lighting(scene, intersection_point, normal);
	// free(t_dot_direction);
	// free(intersection_point);
	// free(normal);
	return (color_multiply(lighting, ray->intersection->color));
	// return (color_multiply(lighting, closest_sp->color));
}

// cyllinder
// plane
// diffuse light
// ambient light
// hard shadows



void	render_sphere(t_scene *scene)
{
	int 		x;
	int 		y;
	// t_vector	*direction;
	t_vector	*viewport_point;
	t_color		*color;
	t_ray		*ray;

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
			viewport_point = canvas_to_viewport(scene, x, y);
			// printf("canvas_point: %d %d\n", x, y);
			// printf("viewport_point: %f %f %f\n", viewport_point->x, viewport_point->y, viewport_point->z);
			// printf("x: %d y: %d\n", x, y);
			ray = new_ray(scene->camera->origin, viewport_point);
			// printf("ray: %f %f %f\n", ray->o->x, ray->o->y, ray->o->z);
			// printf("ray: %f %f %f\n", ray->d->x, ray->d->y, ray->d->z);
			// viewport_point = canvas_to_viewport(scene, x, y);
			// direction = vec_substract(viewport_point, scene->camera->origin);
			// free(viewport_point);
			// vec_normalize(direction);
			color = ray_tracer(scene, ray);
			// color = ray_tracer(scene, direction);
			
			// printf("direction: %f %f %f\n", direction->x, direction->y, direction->z);
			pixel_put(scene->window_data, x, CANVAS_HEIGHT - y - 1, color);
			free_ray(ray);
			// free(direction); // free direction vector
			free(viewport_point);
			free(color);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, 0, 0);
}
