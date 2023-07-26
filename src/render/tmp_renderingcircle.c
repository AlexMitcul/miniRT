/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_renderingcircle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:31:07 by amenses-          #+#    #+#             */
/*   Updated: 2023/07/26 13:30:07 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	rgb2int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

void	pixel_put(t_window_data *img, int x, int y, t_color color)
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
	v->x = x * (scene->camera->viewport_width / CANVAS_WIDTH) - scene->camera->viewport_width / 2;
	v->y = y * (scene->camera->viewport_height / CANVAS_HEIGHT) - scene->camera->viewport_height / 2;
	v->z = DISTANCE_TO_VIEWPORT;
	return (v);
}

void	intersect_ray_sphere(t_scene *scene, float *t1, float *t2, t_vector direction)
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_vector	*co;

	*t1 = 0;
	*t2 = 0;
	co = vec_substract(scene->camera->origin, scene->spheres->center);
	a = vec_product(&direction, &direction);
	b = 2 * vec_product(co, &direction);
	c = vec_product(co, co) - scene->spheres->radius * scene->spheres->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	*t1 = (-b + (float)sqrt(discr)) / (2 * a);
	*t2 = (-b - (float)sqrt(discr)) / (2 * a);
}

t_color	ray_tracer(t_scene *scene, t_vector *direction)
{
	float	t[2];
	t_color	color;

	intersect_ray_sphere(scene, &t[0], &t[1], *direction);
	if (t[0] > DISTANCE_TO_VIEWPORT && t[0] < 10000000)
		color = *scene->spheres->color;
	else if (t[1] > DISTANCE_TO_VIEWPORT && t[1] < 10000000 && t[1] < t[0])
	{
		color.r = 0;
		color.g = 255;
		color.b = 0;
	}
	else
	{
		color.r = 0;
		color.g = 0;
		color.b = 0;
	}
	return (color);
}


void	render_sphere(t_scene *scene)
{
	int x;
	int y;
	t_color color;
	t_vector	*direction;
	float	fov;

	fov = scene->camera->fov * PI / 180;
	y = -1;
	scene->camera->aspect_ratio = (float)CANVAS_HEIGHT / (float)CANVAS_WIDTH;
	scene->camera->viewport_width = 2 * (float)atan(scene->camera->fov / 2 * DISTANCE_TO_VIEWPORT);
	scene->camera->viewport_height = scene->camera->viewport_width * scene->camera->aspect_ratio;
	while (++y < CANVAS_HEIGHT)
	{
		x = -1;
		while (++x < CANVAS_WIDTH)
		{
			direction = vec_substract(canvas_to_viewport(scene, x, y), scene->camera->origin);
			vec_normalize(direction);
			color = ray_tracer(scene, direction);
			pixel_put(scene->window_data, x, y, color);
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->window_data->img, 0, 0);
}
