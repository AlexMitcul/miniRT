/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_renderingcircle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:31:07 by amenses-          #+#    #+#             */
/*   Updated: 2023/08/01 16:53:45 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_menu(t_scene *scene);
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
	free_menu(scene);
	return (0);
}

int	rgb2int(t_color *color)
{
	return (color->r << 16 | color->g << 8 | color->b);
}

void	pixel_put(t_window_data *img, int x, int y, t_color *color)
{
	char	*pxl;

	// (void)color;
	pxl = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pxl = rgb2int(color);
}

t_vector	*canvas_to_viewport(t_scene *scene, int x, int y)
{
	t_vector	*v;

	v = new_vector(0, 0, 0);
	v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH) \
		- scene->camera->viewport_width / 2;
	v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT) \
		- scene->camera->viewport_height / 2;
	// v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH) - 1;
	// v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT) - 1;
	v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

void	intersect_ray_sphere(t_scene *scene, t_sphere *sp, float *t1, float *t2, t_vector direction)
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_vector	*co;

	*t1 = 0;
	*t2 = 0;
	co = vec_substract(scene->camera->origin, sp->center);
	a = vec_product(&direction, &direction);
	b = 2 * vec_product(co, &direction);
	c = vec_product(co, co) - sp->radius * sp->radius;
	free(co);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
	// printf("t1: %f, t2: %f\n", *t1, *t2);
}

void	set_sp_closest_intersection(t_sphere *sp, t_sphere **closest_sp, \
		float t1, float t2, float *closest_t)
{
	if (t1 > DISTANCE_TO_VIEWPORT && t1 < MAX_T && t1 < *closest_t)
	{
		*closest_t = t1;
		*closest_sp = sp;
	}
	if (t2 > DISTANCE_TO_VIEWPORT && t2 < MAX_T && t2 < *closest_t)
	{
		*closest_t = t2;
		*closest_sp = sp;
	}
}

t_color	*ray_tracer(t_scene *scene, t_vector *direction)
{
	float		t[2];
	t_sphere	*sp;
	float		closest_t;
	t_sphere	*closest_sp;

	sp = scene->spheres;
	closest_t = MAX_T;
	closest_sp = NULL;
	while (sp)
	{
		intersect_ray_sphere(scene, sp, &t[0], &t[1], *direction);
		set_sp_closest_intersection(sp, &closest_sp, t[0], t[1], &closest_t);
		sp = sp->next;
	}
	free(direction); // free direction vector
	if (!closest_sp)
		return (scene->background_color);
	return (closest_sp->color);
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
	t_vector	*direction;
	t_vector	*viewport_point;

	y = -1;
	while (++y < CANVAS_HEIGHT)
	{
		x = -1;
		while (++x < CANVAS_WIDTH)
		{
			viewport_point = canvas_to_viewport(scene, x, y);
			direction = vec_substract(viewport_point, scene->camera->origin);
			free(viewport_point);
			vec_normalize(direction);
			pixel_put(scene->window_data, x, y, ray_tracer(scene, direction));
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, 0, 0);
}
